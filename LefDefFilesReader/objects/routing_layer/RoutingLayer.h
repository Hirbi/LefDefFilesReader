#pragma once
#include "../../lib/containers/Layer/Layer.h"

#include <string>
#include <vector>

using namespace std;

class RoutingLayer : public Layer {
	int RouteWidth;
	string Shape;
	vector <Point> RoutingPoints;

public:
	void SetRouteWidth(const int value);
	const int GetRouteWidth() const;

	void SetShape(const string& value);
	const string& GetShape() const;

	void AddRoutingPoint(const Point& pt);
	const vector <Point>& GetRoutingPoints() const;
};

