//
// Created by novek on 6/25/25.
//

#ifndef NTC_H
#define NTC_H

class NTC {
public:
    virtual ~NTC() = default;

    virtual void _init() = 0;

    virtual float _read() = 0;

    float _temperature = {};
};

#endif //NTC_H
