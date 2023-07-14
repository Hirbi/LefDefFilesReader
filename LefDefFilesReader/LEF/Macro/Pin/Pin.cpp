#include "Pin.h"

void Pin::addPort(Port port)
{
    this->ports.push_back(port);
}

void Pin::setDirection(std::string direction)
{
    this->direction = direction;
}

void Pin::setUse(std::string use)
{
    this->use = use;
}

void Pin::setShape(std::string shape)
{
    this->shape = shape;
}

std::string Pin::getName()
{
    return this->name;
}