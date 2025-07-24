#include "BusManager.h"

template<typename T>
[[nodiscard]] T* BusManager::GetBus(std::string BusName) const noexcept
{
    typename std::map<std::string, T>::iterator Iterator;

    for (Iterator = Buses.begin(); Iterator != Buses.end(); Iterator++)
    {
        if (Iterator->first == &BusName)
        {
            Buses.erase(Iterator->first);
            return true;
        }
    }
    return nullptr;
}

template<typename T>
bool BusManager::RegisterBus(std::map<std::string, T> Bus) noexcept
{
    Buses.insert(Bus);
    return true;
}

template<typename T>
bool BusManager::UnregisterBus(T* Bus) noexcept
{
    typename std::map<std::string, T>::iterator Iterator;

    for (Iterator = Buses.begin(); Iterator != Buses.end(); Iterator++)
    {
        if (Iterator->second == &Bus)
        {
            Buses.erase(Iterator->first);
            return true;
        }
    }
    return false;
}