#ifndef BNO055_DEVICE_DRIVER_H
#define BNO055_DEVICE_DRIVER_H

#include <cstdint>
#include "driver/i2c.h"
#include "../../interfaces/GyroscopeInterface.h"
#include "../../../bus/include/I2C.h"
#include "../../common/states/DeviceState.h"
#include "../src/Banks.h"
#include "../src/Registers.h"

class BNO055 final : public GyroscopeInterface
{
    public:

    explicit BNO055(const uint8_t Address, const uint16_t Delay, const float ScalingFactor) noexcept;
    ~BNO055() override;

    float GetRoll() noexcept;

    static constexpr uint8_t ToU8(Banks Bank);
    static constexpr uint8_t ToU8(Registers Register);

    private:

    I2C* I2CBus;
    DeviceState* State;
    const uint8_t Address;
    const uint16_t TransactionDelay;
    const float ScalingFactor;

    bool Initialize() noexcept;
    esp_err_t ReadRegister(Registers Register, uint8_t* Buffer, size_t BufferSize);
    esp_err_t WriteRegister(Registers Register, uint8_t Value) const;
    esp_err_t SwitchBank(Banks Bank) const;
};

#endif