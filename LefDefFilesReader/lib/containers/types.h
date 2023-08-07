#pragma once

#include <string>
#include <vector>

using namespace std;

namespace PrimitiveTypes {
	struct IntPair {
		int First;
		int Second;
	};

	struct DoublePair {
		double First;
		double Second;
	};

	struct StringPair {
		string First;
		string Second;
	};

	struct Point {
		int First;
		int Second;

		Point(int v1 = 0, int v2 = 0) : First(v1), Second(v2)
		{}
	};

	struct Rect {
		Point First;
		Point Second;

		Rect(Point first, Point second) : First(first), Second(second)
		{}
		Rect(int v1 = 0, int v2 = 0, int v3 = 0, int v4 = 0) : First(v1, v2), Second(v3, v4) 
		{}
	};
}

using namespace PrimitiveTypes;

namespace DefPrimitiveTypes {
	struct Parameters {
		int Start;
		int NumColumnsRows;
		int Space;
	};

	struct PlaceParams {
		string Type;
		Point Pt;
		string Orient;
	};

	struct VLayers {
		string BotMetalLayer;
		string CutLayer;
		string TopMetalLayer;
	};
}
