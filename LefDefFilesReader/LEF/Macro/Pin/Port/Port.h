#pragma once
#include <unordered_map>
#include <string>
#include "../../../../lib/containers/Layer/Layer.h"


class Port
{
private:
    std::unordered_map<std::string, Layer> layers;
	PlaceParams Placement;
public:
    void addLayer(Layer layer);

	void SetPlacement(const string& type, const Point& pt, const string& orient);
	PlaceParams GetPlacement() const;
};

