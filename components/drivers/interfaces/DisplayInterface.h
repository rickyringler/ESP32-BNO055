#ifndef DISPLAYINTERFACE_H
#define DISPLAYINTERFACE_H

#include <cstdint>

class DisplayInterface
{
    public:

    virtual ~DisplayInterface()=default;

    [[gnu::hot]] virtual bool Draw(const uint16_t* Data, uint16_t Width, uint16_t Height) noexcept=0;
    virtual bool Clear() noexcept=0;

    private:

    virtual bool Flush() noexcept=0;

};

#endif