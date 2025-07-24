#ifndef BNO055_DEVICE_DRIVER_H
#define BNO055_DEVICE_DRIVER_H

#include "../../interfaces/GyroscopeInterface.h"
#include "../../../bus/include/I2C.h"
#include "esp_log.h"
#include <stdint.h>
#include "driver/i2c.h"

struct DeviceState
{
    uint8_t Bank = 0;
    uint8_t Register[2] = {0, 0};
    inline void UpdateBank(uint8_t Value) noexcept {Bank = Value;};
    inline void UpdateRegister(uint8_t Value) noexcept {Register[0,1] = Value;};
    [[nodiscard]] inline uint8_t GetBank() const noexcept {return Bank;};
    [[nodiscard]] inline uint8_t GetRegister() const noexcept {return Register[0,1];};
};

class BNO055 final : public GyroscopeInterface
{
    public:

    explicit BNO055(const uint8_t Address, const uint16_t Delay, const float ScalingFactor) noexcept;
    ~BNO055() override;

    float GetRoll() noexcept;

    private:

    I2C* I2CBus;
    DeviceState* State;
    const uint8_t Address = 0x28;
    const uint16_t TransactionDelay = 150 / portTICK_PERIOD_MS;
    const float ScalingFactor = 16.0f;

    bool Initialize(const uint8_t& Address, const uint16_t& Delay, const float& ScalingFactor) noexcept;
    esp_err_t ReadRegister(uint8_t Register, uint8_t* Buffer, size_t BufferSize) override;
    esp_err_t WriteRegister(uint8_t Register, uint8_t Value) override;
    esp_err_t SwitchBank(uint8_t Bank) override;
};

#endif