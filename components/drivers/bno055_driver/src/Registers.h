#ifndef BNO055_REGISTERS_H
#define BNO055_REGISTERS_H

enum class Registers : uint8_t
{
    REG_BANK_SEL = 0x07,
    GYR_DATA_X_LSB = 0x14,
    GYR_DATA_X_MSB = 0x15
};

#endif