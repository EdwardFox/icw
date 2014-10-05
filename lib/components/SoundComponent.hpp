#ifndef SOUND_COMPONENT_HPP
#define SOUND_COMPONENT_HPP

#include <unordered_map>
#include "lib/interfaces/IComponent.hpp"
#include "lib/interfaces/ISoundComponent.hpp"

class SoundComponent : public IComponent, public ISoundComponent
{
public:
    SoundComponent( GameObject* gameObject );

    virtual ~SoundComponent() {};

    virtual GameObject* getGameObject() const override;

    virtual void update( GameObject* object, sf::Time dt ) override;

    virtual void addSound( std::string name, sf::Sound sound ) override;

    virtual sf::Sound* getSound( std::string name ) override;

private:
    std::unordered_map<std::string, sf::Sound> mSounds;
    GameObject* mGameObject;

};

#endif

