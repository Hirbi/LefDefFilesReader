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

void Pin::setSpecial(bool isIt) {
    special = isIt;
}

void Pin::setName(const std::string& name) {
    this->name = name;
}

std::string Pin::getName()
{
    return this->name;
}

void Pin::setNet(const std::string& value) {
    this->net = value;
}

