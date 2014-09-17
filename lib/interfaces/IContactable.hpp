#ifndef ICONTACTABLE_HPP
#define ICONTACTABLE_hpp

#include "lib/Data.hpp"

class IContactable
{
public:
    virtual void onContact( Contact contact ) = 0;
};

#endif