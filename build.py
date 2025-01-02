import click
import colorama
import subprocess
import os

ESP_IDF_DIR = '''$HOME/esp/'''

CMAKE_GEN_CMD = '''cmake -S .  -B cmake-build/{PORT} -G Ninja -DPORT={PORT} -DPLATFORM={PLATFORM}'''
CMAKE_BUILD_CMD = '''cmake --build cmake-build/{PORT}'''

IMAGE_DIR = '''cmake-build/{PORT}/mk-home.bin'''

ESP_FLASH_APPLICATION_CMD = '''ESPBAUD=921600 ninja -C cmake-build/{PORT}/ flash'''

ST_FLASH_CMD = '''st-flash write cmake-build/{PORT}/mk-home.bin 0x8000000'''

def set_up_idf_env(esp_idf_dir):
    export_cmd = f"source {esp_idf_dir}/esp-idf/export.sh && env"
    try:
        output = subprocess.check_output(export_cmd, shell=True, executable='/bin/bash', text=True)
        for line in output.splitlines():
            if '=' in line:
                key, value = line.split('=', 1)
                os.environ[key] = value
    except subprocess.CalledProcessError as e:
        raise Exception(f"Could not set up ESP-IDF environment: {e}")

def build_image(port, platform):
    print(colorama.Fore.MAGENTA + "Compiling firmware" + colorama.Style.RESET_ALL)
    print(port)
    if platform == "ESP_IDF":
        print("ESP-IDF PLATFORM")
        print(colorama.Fore.CYAN, "Sourcing ESP-IDF environment" + colorama.Style.RESET_ALL)
        set_up_idf_env(ESP_IDF_DIR)

    cmake_gen_command = CMAKE_GEN_CMD.format(PORT=port, PLATFORM=platform)
    cmake_build_command = CMAKE_BUILD_CMD.format(PORT=port, PLATFORM=platform)
    print(cmake_gen_command)
    ret = os.system(" ".join(cmake_gen_command.split("\n")))
    if ret != 0:
        raise Exception("CMake generation failed!")
    print(cmake_build_command)
    ret = os.system(" ".join(cmake_build_command.split("\n")))
    if ret != 0:
        raise Exception("CMake build failed")

    print(colorama.Fore.GREEN + "Compiled firmware successfully" + colorama.Style.RESET_ALL)
def _flash_application(port, image):
    print(colorama.Fore.MAGENTA, "Flashing Image" + colorama.Style.RESET_ALL)
    global flash_cmd, baud_cmd

    if port == "ESP32":
        flash_cmd = ESP_FLASH_APPLICATION_CMD.format(PORT = port)
    if port == "STM32F429ZI":
        flash_cmd = ST_FLASH_CMD.format(PORT = port)
    print(flash_cmd)
    ret = os.system(" ".join(flash_cmd.split("\n")))
    if ret != 0:
        raise Exception("Flashing failed")
    else:
        print(colorama.Fore.GREEN, "Flashing Success" + colorama.Style.RESET_ALL)

@click.group()
def cli():
    """
    firmware build tool
    :return:
    """
    print(colorama.Fore.LIGHTGREEN_EX, "[CLI]\n" + colorama.Style.RESET_ALL)

@cli.command()
@click.option("-p", "-port", "port", required=True, type=click.STRING, help="mandatory port")
@click.option("-pl", "-platform", "platform", required=True, type=click.STRING, help="mandatory platform")
@click.option("--compile", is_flag=True, help="Build image")
@click.option("--flash", is_flag=True, help="Flash application")
def build_application(port, platform, compile, flash):
    if compile:
        build_image(port, platform)
    if flash:
        _flash_application(port, platform)

if __name__ == "__main__":
    cli()