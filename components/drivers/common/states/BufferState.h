#ifndef BUFFERSTATE_H
#define BUFFERSTATE_H
#include <cstddef>

struct BufferState
{
    std::size_t* ElementSize;
    std::size_t* MaximumElements;
    [[nodiscard]] inline const std::size_t* GetElementSize()     const {return this->ElementSize;};
    [[nodiscard]] inline const std::size_t* GetMaximumElements() const {return this->MaximumElements;};
};

#endif