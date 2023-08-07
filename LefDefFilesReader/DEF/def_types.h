#pragma once

#include "../lib/containers/types.h"
#include "../LEF/LEF.h"

#include <string>
#include <vector>

using namespace std;
using namespace PrimitiveTypes;

namespace DefTypes {

	struct CellGrid {
		DefPrimitiveTypes::Parameters X;
		DefPrimitiveTypes::Parameters Y;
	};

	struct Component {
		string CompName;
		string ModelName;
		DefPrimitiveTypes::PlaceParams Placement;
		// optional 
		string Source;
	};

	struct Net {
		string Name;
		vector<StringPair> CompPinNames;
		string Use;
	};

	struct Row {
		// main options
		string Name;
		string SiteName;
		IntPair Orig;
		string SiteOrient;
		// optional
		IntPair Num;
		IntPair Step;
	};

	struct Specialnet : public Net {
		string WiringType;
		string RouteLayerName;
		int RouteWidth;
		string Shape;
		vector <Point> RoutingPoints;
		vector <RoutingLayer> RoutingLayers;
	};

	struct Track {
		char Direction; // x or y -> can use bool
		int Start;
		int NumTracks;
		int Space;
		vector <string> Layers;
	};
}

using namespace DefTypes;


struct Design {
	int Units;
	vector <Rect> DieArea;
	vector <Row> Rows;
	vector <Track> Tracks;
	CellGrid GCellGrid;
	vector <Via> Vias;
	vector <Component> Components;
	vector <Pin> Pins;
	vector <Specialnet> Specialnets;
	vector <Net> Nets;
};