#pragma once
#include <unordered_map>
#include <string>

#include "../../../../objects/place_params/PlaceParams.h"
#include "../../../../lib/containers/Layer/Layer.h"

using namespace std;

class Port
{
private:
    std::vector <Layer> layers;
	PlaceParams Placement;
public:
    void addLayer(Layer layer);

	void SetPlacement(const string& type, const Point& pt, const string& orient);
	PlaceParams GetPlacement() const;
};

