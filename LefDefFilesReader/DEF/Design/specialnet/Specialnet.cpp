#include "Specialnet.h"

void Specialnet::SetWiringType(const string& value) {
	WiringType = value;
}

const string& Specialnet::GetWiringType() const {
	return WiringType;
}

void Specialnet::SetRouteLayerName(const string& value) {
	RouteLayerName = value;
}

const string& Specialnet::GetRouteLayerName() const {
	return RouteLayerName;
}

void Specialnet::SetRouteWidth(const int value) {
	RouteWidth = value;
}

const int Specialnet::GetRouteWidth() const {
	return RouteWidth;
}

void Specialnet::SetShape(const string& value) {
	Shape = value;
}

const string& Specialnet::GetShape() const {
	return Shape;
}

void Specialnet::AddRoutingPoint(const Point& pt) {
	RoutingPoints.push_back(pt);
}

const vector<Point>& Specialnet::GetRoutingPoints() const {
	return RoutingPoints;
}

void Specialnet::AddNewLayer(const RoutingLayer& value) {
	RoutingLayers.push_back(value);
}

void Specialnet::SetNewLayers(const vector<RoutingLayer>& values) {
	RoutingLayers = values;
}

const vector<RoutingLayer>& Specialnet::GetNewLayers() const {
	return RoutingLayers;
}
