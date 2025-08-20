#include "Controller.h"

Controller::Controller()
{
    this->IMU = new BNO055(I2C_LOW, pdMS_TO_TICKS(150), 16.0f);
    this->Buffer = new CircularBuffer<float, 10>(sizeof(float), 10);
}

void Controller::PrintRoll()
{
    const float RollValue = IMU->GetRoll();
    Buffer->Push(RollValue);
    ESP_LOGI("ROLL", "Roll = %.2f", RollValue);
}

Controller::~Controller()
{
    delete IMU;
}