#pragma once
#include <string>
#include "../../lib/containers/point/Point.h"

namespace {
	struct PlaceParams {
		std::string Type;
		Point Pt;
		std::string Orient;
	};
}