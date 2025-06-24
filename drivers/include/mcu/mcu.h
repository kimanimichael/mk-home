#ifndef DEVICE_ID_H
#define DEVICE_ID_H

class MCU {
public:
    virtual ~MCU() = default;

    virtual const char* get_mcu_id() = 0;

    char _device_id[14];
};

#endif
