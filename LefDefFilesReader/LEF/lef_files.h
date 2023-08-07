#pragma once

#include <string>
#include <vector>

#include "../lib/containers/types.h"

using namespace std;

struct Layer {
	string Name;
	vector<Rect> Rects;
};

struct RoutingLayer : public Layer {
	int RouteWidth;
	string Shape;
	vector <Point> RoutingPoints;
	string ViaLayer;
};

struct Port {
	vector <Layer> Layers;
	DefPrimitiveTypes::PlaceParams Placement;
};

struct Pin {
	string Name;
	string Direction;
	string Use;
	string Shape;
	vector<Port> Ports;
	string Net;
	bool Special;
};