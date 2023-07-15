#pragma once

#include "../../../lib/containers/Layer/Layer.h"
#include "../../../objects/routing_layer/RoutingLayer.h"
#include "../../../lib/containers/point/Point.h"

#include <string>
#include <vector>
using namespace std;


class SpecialWiring {
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


class Specialnet {
	string Name;
	vector <string> PinsNames;
	vector <pair<string, string> > CompPatternsPinsNames;
	string Use;
	SpecialWiring SpecWiring;

public:
	void SetName(const string& value);
	const string& GetName() const;

	void AddPinName(const string& value);
	const vector<string>& GetPinNames() const;

	void SetUse(const string& value);
	const string& GetUse() const;

	void AddCompPatternPinName(const pair<string, string>& value);
	void AddCompPatternPinName(const string& componentPattern, const string& pinName);
	const vector <pair<string, string> >& GetCompPatternPinNames() const;
	
	void SetSpecialWiring(const SpecialWiring& value);
	const SpecialWiring& GetSpecialWiring() const;
	SpecialWiring* MutableSpecialWiring();
};
