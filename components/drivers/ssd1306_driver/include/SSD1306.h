#ifndef SSD1306_H
#define SSD1306_H

#include "../../interfaces/GyroscopeInterface.h"

class SSD1306 final : public GyroscopeInterface
{
public:
    
    [[gnu::hot]] bool Draw(const uint16_t* Data, uint16_t Width, uint16_t Height) noexcept override;
    bool Clear() noexcept override;

private:

    bool Flush() noexcept override;
    esp_err_t ReadRegister(uint8_t Register, uint8_t* Buffer, size_t BufferSize) override;
    esp_err_t WriteRegister(uint8_t Register, uint8_t Value) override;
    esp_err_t SwitchBank(uint8_t Bank) override;
};

#endif