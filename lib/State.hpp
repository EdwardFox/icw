#ifndef STATE_HPP
#define STATE_HPP

#include <functional>
#include <unordered_map>
#include <string>

class GameObject;

class State
{
public:
    State( std::string state );

    std::string onAction( std::string action, GameObject& object );

    void addAction( std::string key, std::function<std::string( GameObject& object )> action );

    std::string getStateName() const
    {
        return mStateName;
    }

private:
    std::unordered_map<std::string, std::function<std::string( GameObject& object )>> mActions;
    std::string mStateName;

};

#endif