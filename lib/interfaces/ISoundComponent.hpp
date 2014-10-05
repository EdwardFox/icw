#ifndef ISOUND_COMPONENT_HPP
#define ISOUND_COMPONENT_HPP

#include <string>
#include <SFML/Audio/Sound.hpp>

class GameObject;

class ISoundComponent
{
public:

    virtual ~ISoundComponent() {};

    virtual void addSound( std::string name, sf::Sound sound ) = 0;

    virtual sf::Sound* getSound( std::string name ) = 0;
};

#endif