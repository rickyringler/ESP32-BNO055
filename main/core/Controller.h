#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "../utilities/PCH.h"
#include "../../components/drivers/bno055_driver/include/BNO055.h"
#include "../../components/drivers/common/buffers/CircularBuffer.h"
#include "../../components/drivers/ssd1306_driver/include/SSD1306.h"
#include "esp_log.h"

class Controller
{
public:

    Controller();
    ~Controller();

    void PrintRoll();

private:

    BNO055* IMU = nullptr;
    CircularBuffer<float, 10> * Buffer = nullptr;
    void* LCD = nullptr;

};

#endif