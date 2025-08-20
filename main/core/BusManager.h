#ifndef BUSMANAGER_H
#define BUSMANAGER_H

#include <string>
#include <map>

class BusManager
{
    public:

    template<typename T>
    [[nodiscard]] T* GetBus(std::string BusName) const noexcept;

    template<typename T>
    bool RegisterBus(std::map<std::string, T> Bus) noexcept;

    private:

    template<typename T>
    std::map<std::string, T> Buses;

    template<typename T>
    bool UnregisterBus(T* Bus) noexcept;
};

#endif