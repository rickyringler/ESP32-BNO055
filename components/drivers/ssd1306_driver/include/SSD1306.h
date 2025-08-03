#ifndef SSD1306_H
#define SSD1306_H

#include <stdint.h>
#include "driver/i2c.h"
#include "../../interfaces/DisplayInterface.h"
#include "../../../bus/include/I2C.h"
#include "../../common/DeviceState.h"
#include "../../common/FrameBuffer.h"
#include "../src/Banks.h"
#include "../src/Registers.h"

class SSD1306 final : public DisplayInterface
{
public:

    explicit SSD1306(const uint8_t Address, const uint16_t Delay) noexcept;
    ~SSD1306() override;

    static constexpr uint8_t Height = 128;
    static constexpr uint8_t Width  = 64;

    [[gnu::hot]] bool Draw(const uint16_t* Data, uint16_t Width, uint16_t Height) noexcept override;
    bool Clear() noexcept override;

private:

    I2C* I2CBus;
    DeviceState* State;
    const uint8_t Address;
    const uint16_t TransactionDelay;

    bool Flush() noexcept override;
    esp_err_t ReadRegister(uint8_t Register, uint8_t* Buffer, size_t BufferSize);
    esp_err_t WriteRegister(uint8_t Register, uint8_t Value);
    esp_err_t SwitchBank(uint8_t Bank);
};

#endif