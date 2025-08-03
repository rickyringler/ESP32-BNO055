#include "../include/BNO055.h"
#include "esp_log.h"

BNO055::BNO055(const uint8_t Address, const uint16_t Delay, const float ScalingFactor) noexcept:
    Address(Address),
    TransactionDelay(Delay),
    ScalingFactor(ScalingFactor)
{
    Initialize();
}

BNO055::~BNO055()
{
    delete I2CBus;
    delete State;
}

bool BNO055::Initialize() noexcept
{
    this->I2CBus = new I2C;
    this->State = new DeviceState;
    return true;
}

float BNO055::GetRoll() noexcept
{
    uint8_t* RawData = 0;
    if (ReadRegister(Registers::GYR_DATA_X_MSB, RawData, 2) != ESP_OK) return 0.0f;

    int16_t Value = (int16_t)(RawData[1]<<8 | RawData[0]);
    return Value / this->ScalingFactor;
}

constexpr uint8_t BNO055::ToU8(Banks Bank)
{
    return static_cast<uint8_t>(Bank);
}

constexpr uint8_t BNO055::ToU8(Registers Register)
{
    return static_cast<uint8_t>(Register);
}

esp_err_t BNO055::ReadRegister(Registers Register, uint8_t* Buffer, size_t BufferSize)
{
    uint8_t MyRegister = ToU8(Register);

    State->UpdateRegister(MyRegister);
    return I2CBus->ReadBytes(Address, MyRegister, Buffer, BufferSize, TransactionDelay);
}

esp_err_t BNO055::WriteRegister(Registers Register, uint8_t Data)
{
    uint8_t MyRegister = ToU8(Register);

    uint8_t Packet[2] = {MyRegister, Data};
    State->UpdateRegister(MyRegister);
    return I2CBus->WriteBytes(this->Address, Packet, 2, TransactionDelay);
}

esp_err_t BNO055::SwitchBank(Banks Bank)
{
    uint8_t MyBank = ToU8(Bank);
    uint8_t MyRegister = ToU8(Registers::REG_BANK_SEL);

    if (this->State->GetBank() == MyBank) return ESP_OK;

    uint8_t Packet[2] = {MyRegister, MyBank};
    esp_err_t Error = I2CBus->WriteBytes(Address, Packet, sizeof(Packet), TransactionDelay);
    if (Error == ESP_OK) State->UpdateBank(MyBank);
    return Error;
}
