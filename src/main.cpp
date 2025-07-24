#include "components/drivers/bno055_driver/include/BNO055.h"
#include "utilities/PCH.h"

extern "C" int main(int argc, char** argv)
{
    BNO055 Gyroscope = BNO055();
    return 0;
}