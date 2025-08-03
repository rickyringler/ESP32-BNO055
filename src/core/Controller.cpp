#include "Controller.h"

#include "../components/drivers/bno055_driver/include/BNO055.h"
#include "../components/drivers/ssd1306_driver/include/SSD1306.h"

Controller::Controller()
{
    this->IMU = new BNO055(1,1,1);
    this->LCD = new SSD1306();
}

Controller::~Controller()
{
    delete IMU;
    delete LCD;
}