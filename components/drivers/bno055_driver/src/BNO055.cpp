#include "../include/BNO055.h"

BNO055::BNO055(const uint8_t Address, const uint16_t Delay, const float ScalingFactor) noexcept
{
    Initialize(Address, Delay, ScalingFactor);
}

BNO055::~BNO055()
{
    delete I2CBus;
    delete State;
}

bool BNO055::Initialize(const uint8_t& Address, const uint16_t& Delay, const float& ScalingFactor) noexcept
{
    this->I2CBus = new I2C;
    this->State = new DeviceState;
    this->Address = Address;
    this->TransactionDelay = Delay;
    this->ScalingFactor = ScalingFactor;
    return true;
}

float BNO055::GetRoll() noexcept
{
    uint8_t RawData[2];
    if (ReadRegister(0x08, RawData, 2) != ESP_OK) return 0.0f;

    int16_t Value = (int16_t)(RawData[1]<<8 | RawData[0]);
    return Value / this->ScalingFactor;
}

esp_err_t BNO055::ReadRegister(uint8_t Register, uint8_t* Buffer, size_t BufferSize)
{
    State->UpdateRegister(Register);
    return I2CBus->ReadBytes(Address, Register, Buffer, BufferSize, TransactionDelay);
}

esp_err_t BNO055::WriteRegister(uint8_t Register, uint8_t Data)
{
    uint8_t Packet[2] = {Register, Data};
    State->UpdateRegister(Register);
    return I2CBus->WriteBytes(this->Address, Packet, 2, TransactionDelay);
}

esp_err_t BNO055::SwitchBank(uint8_t Bank)
{
    if (this->State->GetBank() == Bank) return ESP_OK;
    uint8_t Packet[2] = {REG_BANK_SEL, Bank};
    esp_err_t Error = I2CBus->WriteBytes(Address, Packet, sizeof(Packet), TransactionDelay);
    if (Error == ESP_OK) State->UpdateBank(Bank);
    return ESP_OK;
}