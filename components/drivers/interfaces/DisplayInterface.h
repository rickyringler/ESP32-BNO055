#ifndef DISPLAYINTERFACE_H
#define DISPLAYINTERFACE_H

#include <cstdint>

class DisplayInterface
{
    public:

        virtual ~DisplayInterface()=default;
        virtual void DrawBuffer(const uint16_t* Buffer, uint16_t Width, uint16_t Height)=0;
        virtual void FlushBuffer() noexcept=0;

    private:

};

#endif