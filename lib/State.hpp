#ifndef STATE_HPP
#define STATE_HPP

#include <string>
#include <unordered_map>

class State
{
public:
    State();

    std::string getName() const;

    void setName( std::string name );

    std::string getAnimation() const;

    void setAnimation( std::string anim );

    std::string getFollowUpState() const;

    void setFollowUpState( std::string follow );

    bool hasState( std::string state ) const;

    void addState( std::string state );

    bool returnToPreviousState() const;

    void setReturnToPreviousState( bool ret );

private:
    std::string mName;
    std::string mAnimation;
    std::string mFollowUpState;
    std::unordered_map<std::string, std::string> mFollowStates;
    bool mReturnToPreviousState;

};

#endif