#pragma once

#include "../../../lib/containers/point/Point.h"
#include "../../objects/place_params/PlaceParams.h"

#include <string>

using namespace std;

class Component {
	string CompName; 
	string ModelName;
	PlaceParams Placement;
	// optional 
	string Source;

public:
	Component();

	void SetCompName(const string& value);
	const string& GetCompName() const;

	void SetModelName(const string& value);
	const string& GetModelName() const;

	void SetSource(const string& value);
	const string& GetSource() const;

	void SetPlacement(const string& type, const Point& pt, const string& orient);
	const PlaceParams& GetPlacement() const;
};

