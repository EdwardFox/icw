#ifndef ISPAWNER_COMPONENT_HPP
#define ISPAWNER_COMPONENT_HPP

#include <string>

class ISpawnerComponent
{
public:

    virtual ~ISpawnerComponent() {};

    virtual void spawn() = 0;

    unsigned int getAmountMax() const
    {
        return mAmountMax;
    }

    void setAmountMax( unsigned int amountMax )
    {
        mAmountMax = amountMax;
    }

    unsigned getIntervalMin() const
    {
        return mIntervalMin;
    }

    void setIntervalMin( unsigned intervalMin )
    {
        mIntervalMin = intervalMin;
    }

    unsigned getIntervalMax() const
    {
        return mIntervalMax;
    }

    void setIntervalMax( unsigned intervalMax )
    {
        mIntervalMax = intervalMax;
    }

    std::string getGameObjectType() const
    {
        return mGameObjectType;
    }

    void setGameObjectType( std::string type )
    {
        mGameObjectType = type;
    }

    void setProperties( std::vector<std::tuple<std::string, std::string>> properties )
    {
        mProperties = properties;
    }

    const std::vector<std::tuple<std::string, std::string>>* getProperties() const
    {
        return &mProperties;
    }

private:
    unsigned mAmountMax;
    unsigned mIntervalMin;
    unsigned mIntervalMax;
    std::string mGameObjectType;
    std::vector<std::tuple<std::string, std::string>> mProperties;
};

#endif