#include "OBS.h"


void OBS::addLayer(Layer layer)
{
    this->layers.insert({ layer.getName(), layer });
}