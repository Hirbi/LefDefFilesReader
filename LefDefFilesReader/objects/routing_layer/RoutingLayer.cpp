#include "RoutingLayer.h"

void RoutingLayer::SetRouteWidth(const int value) {
    RouteWidth = value;
}

const int RoutingLayer::GetRouteWidth() const {
    return RouteWidth;
}

void RoutingLayer::SetShape(const string& value) {
    Shape = value;
}

const string& RoutingLayer::GetShape() const {
    return Shape;
}

void RoutingLayer::AddRoutingPoint(const Point& pt) {
    RoutingPoints.push_back(pt);
}

const vector<Point>& RoutingLayer::GetRoutingPoints() const {
    return RoutingPoints;
}
