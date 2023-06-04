#include "Component.h"

Component::Component() {
}

void Component::SetCompName(const string& value) {
    CompName = value;
}

const string& Component::GetCompName() const {
    return CompName;
}

void Component::SetModelName(const string& value) {
    ModelName = value;
}

const string& Component::GetModelName() const {
    return ModelName;
}

void Component::SetSource(const string& value) {
    Source = value;
}

const string& Component::GetSource() const {
    return Source;
}

void Component::SetPlacement(const string& type, const Point& pt, const string& orient) {
    Placement.Type = type;
    Placement.Pt = pt;
    Placement.Orient = orient;
}

const PlaceParams& Component::GetPlacement() const {
    return Placement;
}
