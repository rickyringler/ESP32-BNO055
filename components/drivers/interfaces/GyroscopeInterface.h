#ifndef GYROSCOPEINTERFACE_H
#define GYROSCOPEINTERFACE_H

#include "driver/i2c.h"

class GyroscopeInterface
{
    public:

    virtual ~GyroscopeInterface()=default;

    [[gnu::hot]] virtual bool Draw(const uint16_t* Data, uint16_t Width, uint16_t Height) noexcept=0;
    virtual bool Clear() noexcept=0;

    private:

    virtual bool Flush() noexcept=0;
    virtual esp_err_t ReadRegister(uint8_t Register, uint8_t* Buffer, size_t BufferSize)=0;
    virtual esp_err_t WriteRegister(uint8_t Register, uint8_t Value)=0;
    virtual esp_err_t SwitchBank(uint8_t Bank)=0;
};

#endif