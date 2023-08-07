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
<<<<<<< .merge_file_BAnFkW
		Rect(int v1 = 0, int v2 = 0, int v3 = 0, int v4 = 0) : First(v1, v2), Second(v3, v4) 
=======
		Rect(int v1 = 0, int v2 = 0, int v3 = 0, int v4 = 0) : First(v1, v2), Second(v3, v4)
>>>>>>> .merge_file_1GxjgD
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
<<<<<<< .merge_file_BAnFkW
=======

namespace LefPrimitiveTypes {

	struct Resistance {
	public:
		std::string type;
		double value;

	};
	struct Capacitance {
	public:
		std::string type;
		double value;
	};
	struct SpacingTable {
		int parallelRunLength;
		std::vector<Point> widths;
	};
	struct Enclosure {
		std::string type;
		Point point;
	};
	struct DCCurrentDensity {
		std::string type;
		double value;
	};
	struct ACCurrentDensity {
		std::string type;
		double value;
	};

	//LEFParams structs
	struct Units {
	public:
		int timeValue;
		int resistanceValue;
		int capacitanceValue;
		int dataBaseValue;
		std::string timeUnit;
		std::string resistanceUnit;
		std::string capacitanceUnit;
		std::string dataBaseUnit;
	};
	struct PropertyDefinition {
		std::string layer;
		std::string type;
	};
}
>>>>>>> .merge_file_1GxjgD
