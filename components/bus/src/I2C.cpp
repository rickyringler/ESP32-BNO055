#include "../include/I2C.h"

I2C::I2C()
{
    InitializeI2C();
};

esp_err_t I2C::InitializeI2C() noexcept
{
    Config =  BuildI2CConfig();
    i2c_param_config(I2C_PORT, Config);
    i2c_driver_install(I2C_PORT, Config->mode, 0, 0, 0);

    return ESP_OK;
}

i2c_config_t* I2C::BuildI2CConfig() noexcept
{
    i2c_config_t* Config = new i2c_config_t;
    Config->mode = I2C_MODE_MASTER;
    Config->sda_io_num = SDA_IO;
    Config->scl_io_num = SCL_IO;
    Config->sda_pullup_en = GPIO_PULLUP_ENABLE;
    Config->scl_pullup_en = GPIO_PULLUP_ENABLE;
    return Config;
}

[[nodiscard]] esp_err_t I2C::SwitchBank(uint8_t Bank) const noexcept
{
    uint8_t Data[2] = {0,0};
    Data[0] = 0x00;
    Data[1] = Bank;

    return i2c_master_write_to_device(I2C_PORT, I2C_HIGH, Data, sizeof(Bank), this->TransactionDelay);
}

[[nodiscard]] esp_err_t I2C::ReadBytes(uint8_t Address, uint8_t Register, uint8_t* Data, size_t Length, TickType_t Timeout) const noexcept
{
    return i2c_master_write_read_device(I2C_PORT, Address, &Register, 1, Data, Length, Timeout);
}

[[nodiscard]] esp_err_t I2C::WriteBytes(uint8_t Address, const uint8_t* Data, size_t Length, TickType_t Timeout) const noexcept
{
    return i2c_master_write_to_device(I2C_PORT, Address, Data, Length, Timeout);
}