#include "Port.h"

void Port::addLayer(Layer layer)
{
    this->layers.insert({ layer.getName(), layer });
}