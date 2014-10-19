#ifndef ICONTACTABLE_HPP
#define ICONTACTABLE_hpp

#include <Box2D/Box2D.h>
#include "lib/Data.hpp"

class IContactable
{
public:

    virtual ~IContactable() {};

    virtual void onContact( Contact contact, IContactable* other, b2BodyType type ) = 0;
};

#endif