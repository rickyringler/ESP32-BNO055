#ifndef FRAMEBUFFER_H
#define FRAMEBUFFER_H

#include <cstdint>
#include <array>
#include "../../utilities/PCH.h"
#include "../states/BufferState.h"

template <typename T, std::size_t Size>
class FrameBuffer
{
public:

    static_assert(Size > 0, "Why would you even attempt to allocate a negative quantity of memory?");

    explicit FrameBuffer(uint8_t Width, uint8_t Height);

private:

    static constexpr std::size_t Mask = Size - 1;
    std::array<T, Size> Buffer{};
    uint8_t Width;
    uint8_t Height;
    BufferState* State = nullptr;

    bool Initialize(uint8_t Width, uint8_t Height) noexcept;
};

#endif