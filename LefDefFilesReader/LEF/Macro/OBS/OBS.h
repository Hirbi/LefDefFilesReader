#pragma once
#include <map>

#include "../../../lib/containers/Layer/Layer.h"
class OBS
{
private:
    std::map<std::string, Layer> layers;
public:
    void addLayer(Layer layer);
};

