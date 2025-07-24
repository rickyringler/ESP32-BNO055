#ifndef CIRCULAR_BUFFER_H
#define CIRCULAR_BUFFER_h

#include "../utilities/PCH.h"

struct ElementMetaData
{
    size_t* ElementSize;
    size_t* MaximumElements;
    [[nodiscard]] inline const size_t* GetElementSize()     const {return this->ElementSize;};
    [[nodiscard]] inline const size_t* GetMaximumElements() const {return this->MaximumElements;};
};

template<typename T, size_t Size>
class CircularBuffer final
{
    public:

    static_assert(Size > 0, "Why would you even attempt to allocate a negative quantity of memory?");

    CircularBuffer(size_t ElementSize, size_t MaximumElements);
    ~CircularBuffer();

    bool                  InitializeElementMetaData(size_t ElementSize, size_t MaximumElements) noexcept;
    inline const size_t*  GetSizeElements()    const {return this->Elements;};
    inline const size_t*  GetElementSize()     const noexcept;
    inline const size_t*  GetMaximumElements() const noexcept;
    inline constexpr bool BufferEmpty()        const noexcept{ return Head==Tail;};
    inline constexpr bool BufferFull()         const noexcept{ return Buffer.size() == Size;};
    bool                  Push(const T* Data) noexcept;
    bool                  Pop() noexcept;

    private:

    static constexpr size_t Mask = Size - 1;
    std::array<T, Size> Buffer{};
    void* Head = nullptr;
    void* Tail = nullptr;
    size_t* Elements = nullptr;
    ElementMetaData* MetaElements = nullptr;
};

#endif