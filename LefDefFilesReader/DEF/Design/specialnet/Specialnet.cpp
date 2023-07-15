#include "Specialnet.h"

// start of SpecialWiring

void SpecialWiring::SetWiringType(const string& value) {
	WiringType = value;
}

const string& SpecialWiring::GetWiringType() const {
	return WiringType;
}

void SpecialWiring::SetRouteLayerName(const string& value) {
	RouteLayerName = value;
}

const string& SpecialWiring::GetRouteLayerName() const {
	return RouteLayerName;
}

void SpecialWiring::SetRouteWidth(const int value) {
	RouteWidth = value;
}

const int SpecialWiring::GetRouteWidth() const {
	return RouteWidth;
}

void SpecialWiring::SetShape(const string& value) {
	Shape = value;
}

const string& SpecialWiring::GetShape() const {
	return Shape;
}

void SpecialWiring::AddRoutingPoint(const Point& pt) {
	RoutingPoints.push_back(pt);
}

const vector<Point>& SpecialWiring::GetRoutingPoints() const {
	return RoutingPoints;
}

void SpecialWiring::AddNewLayer(const RoutingLayer& value) {
	RoutingLayers.push_back(value);
}

void SpecialWiring::SetNewLayers(const vector<RoutingLayer>& values) {
	RoutingLayers = values;
}

const vector<RoutingLayer>& SpecialWiring::GetNewLayers() const {
	return RoutingLayers;
}

// end of SpecialWiring

void Specialnet::SetName(const string& value) {
	Name = value;
}

const string& Specialnet::GetName() const {
	return Name;
}

void Specialnet::AddPinName(const string& value) {
	PinsNames.push_back(value);
}

const vector<string>& Specialnet::GetPinNames() const {
	return PinsNames;
}

void Specialnet::SetUse(const string& value) {
	Use = value;
}

const string& Specialnet::GetUse() const {
	return Use;
}

void Specialnet::AddCompPatternPinName(const pair<string, string>& value) {
	CompPatternsPinsNames.push_back(value);
}

void Specialnet::AddCompPatternPinName(const string& componentPattern, const string& pinName) {
	CompPatternsPinsNames.push_back(pair<string, string> {componentPattern, pinName});
}

const vector<pair<string, string>>& Specialnet::GetCompPatternPinNames() const {
	return CompPatternsPinsNames;
}

void Specialnet::SetSpecialWiring(const SpecialWiring& value) {
	SpecWiring = value;
}

const SpecialWiring& Specialnet::GetSpecialWiring() const {
	return SpecWiring;
}

SpecialWiring* Specialnet::MutableSpecialWiring() {
	return &SpecWiring;
}
