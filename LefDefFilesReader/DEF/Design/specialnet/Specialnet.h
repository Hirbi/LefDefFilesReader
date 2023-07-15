#pragma once
#include "../net/Net.h"
#include "../../../lib/containers/Layer/Layer.h"
#include "../../../objects/routing_layer/RoutingLayer.h"
#include "../../../lib/containers/point/Point.h"

#include <string>
#include <vector>
using namespace std;


class Specialnet : public Net {
	string WiringType;
	string RouteLayerName;
	int RouteWidth;
	string Shape;
	vector <Point> RoutingPoints;
	vector <RoutingLayer> RoutingLayers;
public:
	void SetWiringType(const string& value);
	const string& GetWiringType() const;

	void SetRouteLayerName(const string& value);
	const string& GetRouteLayerName() const;

	void SetRouteWidth(const int value);
	const int GetRouteWidth() const;

	void SetShape(const string& value);
	const string& GetShape() const;

	void AddRoutingPoint(const Point& pt);
	const vector <Point>& GetRoutingPoints() const;

	void AddNewLayer(const RoutingLayer& value);
	void SetNewLayers(const vector<RoutingLayer>& values);
	const vector<RoutingLayer>& GetNewLayers() const;
};
