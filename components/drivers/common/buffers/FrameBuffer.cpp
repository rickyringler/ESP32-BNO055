#include "FrameBuffer.h"

template <typename T, std::size_t Size>
FrameBuffer<T, Size>::FrameBuffer(uint8_t Width, uint8_t Height)
{
    Initialize(Width, Height);
}

template <typename T, std::size_t Size>
bool FrameBuffer<T, Size>::Initialize(uint8_t Width, uint8_t Height) noexcept
{
    this->Width = Width;
    this->Height = Height;
    return true;
}