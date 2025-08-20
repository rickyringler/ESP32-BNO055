#ifndef I2C_H
#define I2C_H

#include "driver/i2c.h"

#define I2C_PORT        I2C_NUM_0
#define SDA_IO          23
#define SCL_IO          22
#define I2C_FREQ        100000
#define I2C_HIGH        0x28
#define I2C_LOW         0x29

class I2C final
{
    public:

    I2C();

    [[nodiscard]] esp_err_t SwitchBank(uint8_t Bank) const noexcept;
    [[nodiscard]] esp_err_t ReadBytes(uint8_t Address, uint8_t Register, uint8_t* Data, size_t Length, TickType_t Timeout) const noexcept;
    [[nodiscard]] esp_err_t WriteBytes(uint8_t Address, const uint8_t* Data, size_t Length, TickType_t Timeout) const noexcept;
    esp_err_t InitializeI2C() noexcept;

    private:

    const uint16_t TransactionDelay = 150 / portTICK_PERIOD_MS;

    i2c_config_t* Config = nullptr;
    i2c_config_t* BuildI2CConfig() noexcept;
    bool Scan() const;


};

#endif