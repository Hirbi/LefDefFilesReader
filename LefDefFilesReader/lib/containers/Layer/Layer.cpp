#include "Layer.h"


void Layer::addRect(Rect &rect)
{
    rects.push_back(rect);
}

void Layer::setName(std::string name)
{
    this->name = name;
}

std::string Layer::getName()
{
    return this->name;
}