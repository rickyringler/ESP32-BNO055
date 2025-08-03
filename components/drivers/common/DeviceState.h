#ifndef DEVICESTATE_h
#define DEVICESTATE_H

struct DeviceState
{
    uint8_t Bank = 0;
    uint8_t Register = 0;
    inline void UpdateBank(uint8_t Value) noexcept {Bank = Value;};
    inline void UpdateRegister(uint8_t Value) noexcept {Register = Value;};
    [[nodiscard]] inline uint8_t GetBank() const noexcept {return Bank;};
    [[nodiscard]] inline uint8_t GetRegister() const noexcept {return Register;};
};

#endif