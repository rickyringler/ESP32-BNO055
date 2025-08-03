#ifndef BUFFERSTATE_H
#define BUFFERSTATE_H

struct BufferState
{
    size_t* ElementSize;
    size_t* MaximumElements;
    [[nodiscard]] inline const size_t* GetElementSize()     const {return this->ElementSize;};
    [[nodiscard]] inline const size_t* GetMaximumElements() const {return this->MaximumElements;};
};

#endif