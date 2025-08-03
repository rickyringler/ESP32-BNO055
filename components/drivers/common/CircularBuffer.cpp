#include "CircularBuffer.h"

template<typename T, size_t Size>
CircularBuffer<T, Size>::CircularBuffer(size_t ElementSize, size_t MaximumElements)
{
    InitializeElementMetaData(ElementSize, MaximumElements);
}

template<typename T, size_t Size>
CircularBuffer<T, Size>::~CircularBuffer()
{
    delete this->State;
}

template<typename T, size_t Size>
bool CircularBuffer<T, Size>::InitializeElementMetaData(size_t ElementSize, size_t MaximumElements) noexcept
{
    this->State = new BufferState;
    this->State->ElementSize = &ElementSize;
    this->State->MaximumElements = &MaximumElements;
    return true;
}

template<typename T, size_t Size>
inline const size_t* CircularBuffer<T, Size>::GetElementSize() const noexcept
{
    return this->State->GetElementSize();
}

template<typename T, size_t Size>
inline const size_t* CircularBuffer<T, Size>::GetMaximumElements() const noexcept
{
    return this->State->GetMaximumElements();
}

template<typename T, size_t Size>
bool CircularBuffer<T, Size>::Push(const T* Data) noexcept
{
    [[UNLIKELY]]if (BufferFull()) return false;

    Buffer[Head & Mask] = Data;
    Head++;

    return true;
}

template<typename T, size_t Size>
bool CircularBuffer<T, Size>::Pop() noexcept
{
    [[UNLIKELY]]if (BufferEmpty()) return false;

    T Value =  Buffer[Tail & Mask];
    Tail++;

    return true;
}