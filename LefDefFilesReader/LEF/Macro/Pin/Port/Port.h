#pragma once
#include <unordered_map>
#include <string>
#include "../../../../lib/containers/Layer/Layer.h"


class Port
{
private:
    std::unordered_map<std::string, Layer> layers;
public:
    void addLayer(Layer layer);
};

