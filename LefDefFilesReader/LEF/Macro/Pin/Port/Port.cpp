#include "Port.h"

using namespace std;

void Port::addLayer(Layer layer)
{
    this->layers.push_back(layer);
}

void Port::SetPlacement(const string& type, const Point& pt, const string& orient) {
    Placement.Type = type;
    Placement.Pt = pt;
    Placement.Orient = orient;
}

PlaceParams Port::GetPlacement() const
{
    return PlaceParams();
}
