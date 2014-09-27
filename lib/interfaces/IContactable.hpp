#ifndef ICONTACTABLE_HPP
#define ICONTACTABLE_hpp

#include "lib/Data.hpp"

class IContactable
{
public:

    virtual ~IContactable() {};

    virtual void onContact( Contact contact, IContactable* other ) = 0;
};

#endif