#include "../include/I2C.h"

#include <esp_log.h>

I2C::I2C()
{
    InitializeI2C();
};

static esp_err_t read_chip_id(uint8_t addr) {
    const uint8_t reg = 0x00;
    uint8_t id = 0;
    i2c_cmd_handle_t cmd = i2c_cmd_link_create();
    i2c_master_start(cmd);
    i2c_master_write_byte(cmd, (addr << 1) | I2C_MASTER_WRITE, true);
    i2c_master_write_byte(cmd, reg, true);
    i2c_master_start(cmd);
    i2c_master_write_byte(cmd, (addr << 1) | I2C_MASTER_READ, true);
    i2c_master_read_byte(cmd, &id, I2C_MASTER_NACK);
    i2c_master_stop(cmd);
    esp_err_t err = i2c_master_cmd_begin(I2C_PORT, cmd, pdMS_TO_TICKS(250));
    i2c_cmd_link_delete(cmd);

    if (err == ESP_OK) ESP_LOGI("BNO055", "CHIP_ID at 0x%02X = 0x%02X", addr, id);
    else ESP_LOGW("BNO055", "CHIP_ID read failed at 0x%02X, err=%d", addr, (int)err);
    return err;
}

void probe_bno055() {
    read_chip_id(0x28);
    read_chip_id(0x29);
}


esp_err_t I2C::InitializeI2C() noexcept
{
    Config = BuildI2CConfig();

    esp_err_t err = i2c_param_config(I2C_PORT, Config);
    if (err != ESP_OK)
    {
        ESP_LOGE("I2C", "i2c_param_config failed: %s", esp_err_to_name(err));
        return err;
    }

    err = i2c_driver_install(I2C_PORT, Config->mode, 0, 0, 0);
    if (err != ESP_OK)
    {
        ESP_LOGE("I2C", "i2c_driver_install failed: %s", esp_err_to_name(err));
        return err;
    }

    Scan();
    probe_bno055();
    return ESP_OK;
}

i2c_config_t* I2C::BuildI2CConfig() noexcept
{
    this->Config = new i2c_config_t;
    *Config = {};
    Config->mode = I2C_MODE_MASTER;
    Config->sda_io_num = SDA_IO;
    Config->scl_io_num = SCL_IO;
    Config->sda_pullup_en = GPIO_PULLUP_ENABLE;
    Config->scl_pullup_en = GPIO_PULLUP_ENABLE;
    Config->master.clk_speed = 50000;
    return Config;
}

[[nodiscard]] esp_err_t I2C::SwitchBank(uint8_t Bank) const noexcept
{
    uint8_t Data[2] = {0,0};
    Data[0] = 0x07;
    Data[1] = Bank;

    return i2c_master_write_to_device(I2C_PORT, I2C_HIGH, Data, sizeof(Data), pdMS_TO_TICKS(15));
}

[[nodiscard]] esp_err_t I2C::ReadBytes(uint8_t Address, uint8_t Register, uint8_t* Data, size_t Length, TickType_t Timeout) const noexcept
{
    return i2c_master_write_read_device(I2C_PORT, Address, &Register, 1, Data, Length, Timeout);
}

[[nodiscard]] esp_err_t I2C::WriteBytes(uint8_t Address, const uint8_t* Data, size_t Length, TickType_t Timeout) const noexcept
{
    return i2c_master_write_to_device(I2C_PORT, Address, Data, Length, Timeout);
}

bool I2C::Scan() const {
    ESP_LOGI("SCAN", "Starting I2C scan...");
    bool any = false;

    for (uint8_t addr = 0x03; addr < 0x78; ++addr) {
        i2c_cmd_handle_t cmd = i2c_cmd_link_create();
        i2c_master_start(cmd);
        i2c_master_write_byte(cmd, (addr << 1) | I2C_MASTER_WRITE, true);
        i2c_master_stop(cmd);
        esp_err_t err = i2c_master_cmd_begin(I2C_PORT, cmd, pdMS_TO_TICKS(50));
        i2c_cmd_link_delete(cmd);

        if (err == ESP_OK) {
            ESP_LOGI("SCAN", "I2C device found at 0x%02X", addr);
            any = true;
        }
    }

    if (!any) ESP_LOGW("SCAN", "No I2C devices found.");
    return any;
}