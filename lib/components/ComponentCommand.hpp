#ifndef COMPONENT_COMMAND_HPP
#define COMPONENT_COMMAND_HPP

#include <functional>
#include <string>

template<typename T>
class ComponentCommand
{
    public:
        std::function<void(T&)> execute;
        std::string targetType;
};

#endif
