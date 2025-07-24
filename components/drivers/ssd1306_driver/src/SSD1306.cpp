#include "../include/SSD1306.h"

esp_err_t SSD1306::ReadRegister(uint8_t Register, uint8_t* Buffer, size_t BufferSize) override
{
    return ESP_OK;
}
esp_err_t SSD1306::WriteRegister(uint8_t Register, uint8_t Value) override
{
    return ESP_OK;
}
esp_err_t SSD1306::SwitchBank(uint8_t Bank) override
{
    return ESP_OK;
}