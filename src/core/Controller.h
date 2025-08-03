#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "../utilities/PCH.h"

class Controller
{
public:

    Controller();
    ~Controller();

private:

    void* IMU = nullptr;
    void* LCD = nullptr;

};

#endif