#pragma once
#include "DefReader.h"
#include "def_types.h"
#include "../lib/functions/functions.h"
#include "../LEF/lef_files.h"

#include <assert.h>
#include <iostream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;


void DefReader::ReadData(const string& filename, Objects& objs) {
	static const int
		VERSION = 1,
		DIVIDERCHAR = 2,
		BUSBITCHARS = 3,
		DESIGN = 4;

	static const unordered_map <string, int> KEY_WORDS {
		{ ";", 0},
		{ "VERSION", 1 },
		{ "DIVIDERCHAR", 2 },
		{ "BUSBITCHARS", 3},
		{ "DESIGN", 4},
	};

	ifstream is(filename);
	if (!is.is_open()) {
		cout << "Can't open " << filename << ". File not found.\n";
		return;
	}
	string word;
	while (!is.eof()) {
		is >> word;
		auto it = KEY_WORDS.find(word);
		if (it == KEY_WORDS.end()) {
			return;
			cout << "Cant find word: " << word << "\n";
			assert(0);
		}
		switch (it->second) {
		case 0: // ";"
			continue;
			break;
		case VERSION:
			is >> this->Version;
			break;
		case DIVIDERCHAR:
			is >> word;
			this->DividerChar = word[1];
			break;
		case BUSBITCHARS:
			is >> word;
			this->BusbitChars = strip(word, "\"");
			break;
		case DESIGN: 
			is >> word;
			objs.AddDesign(word, ReadDesign(is));
			break;
		}
	}


}

Design DefReader::ReadDesign(ifstream& is) {
	static const int
		UNITS = 1,
		DIEAREA = 2,
		ROW = 3,
		TRACKS = 4,
		GCELLGRID = 5,
		VIAS = 6,
		COMPONENTS = 7,
		PINS = 8,
		SPECIALNETS = 9,
		NETS = 10,
		END = -1;

	static const unordered_map <string, int> KEY_WORDS{
		{ ";", 0},
		{ "UNITS", 1 },
		{ "DIEAREA", 2 },
		{ "ROW", 3},
		{ "TRACKS", 4},
		{ "GCELLGRID", 5},
		{ "VIAS", 6},
		{ "COMPONENTS", 7},
		{ "PINS", 8},
		{ "SPECIALNETS", 9},
		{ "NETS", 10},
		{ "END", -1}
	};

	Design design;
	string word;
	while (!is.eof()) {
		is >> word;
		auto it = KEY_WORDS.find(word);
		if (it == KEY_WORDS.end()) {
			cout << "Cant find word: " << word << "\n";
			assert(0);
		}
		switch (it->second) {
		case 0: // ";"
			continue;
			break;
		case UNITS:
			is >> word; is >> word; // <DISTANCE MICRONS>
			is >> word;
			design.Units = stoi(word);
			break;
		case DIEAREA:
			while (1) {
				is >> word;
				if (word == ";") { break; }
				Point First, Second;
				is >> First.First >> First.Second
					>> word >> word // here <) (>
				    >> Second.First >> Second.Second
					>> word; // <)>
				design.DieArea.push_back(Rect(First, Second));
			}
			break;
		case ROW:
			design.Rows.push_back(ReadRow(is));
			break;
		case TRACKS:
			design.Tracks.push_back(ReadTracks(is));
			break;
		case GCELLGRID:
			ReadGCellGrid(is, design.GCellGrid);
			break;
		case VIAS:
			ReadVias(is, design.Vias);
			break;
		case COMPONENTS:
			ReadComponents(is, design.Components);
			break;
		case PINS:
			ReadPins(is, design.Pins);
			break;
		case SPECIALNETS:
			ReadSpecialnets(is, design.Specialnets);
			break;
		case NETS:
			ReadNets(is, design.Nets);
			break;
		case END:
			is >> word;
			if (word != "DESIGN") {
				assert(0);
			}
			return design;
			break;
		}
	}
	return design;
}

const Row DefReader::ReadRow(ifstream& is) {
	Row row;
	string word;
	is >> row.Name; // rowName
	is >> row.SiteName; // siteName
	is >> row.Orig.First >> row.Orig.Second; // origX origY
	is >> row.SiteOrient; // siteOrient
	is >> word; // DO or ";"
	if (word == ";") { return row; }
	is >> row.Num.First >> word >> row.Num.Second; // numX BY numY
	is >> word; // STEP or ";"
	if (word == ";") { return row; }
	is >> row.Step.First >> row.Step.Second; //  stepX stepY
	return row;
}

const Track DefReader::ReadTracks(ifstream& is) { 
	Track track;
	string word;
	is >> track.Direction;
	is >> track.Start;
	is >> word; // DO
	is >> track.NumTracks;
	is >> word; // STEP
	is >> track.Space;
	is >> word; // LAYER
	do {
		is >> word;
		track.Layers.push_back(word);
		is >> word;
	} while (word != ";");
	return track;
}

void DefReader::ReadGCellGrid(ifstream& is, CellGrid& gCellGrid) {
	string word;
	is >> word >> gCellGrid.X.Start >> word >> gCellGrid.X.NumColumnsRows >> word >> gCellGrid.X.Space >> word; // X 0 DO 29 STEP 6900 ;
	is >> word >> word >> gCellGrid.Y.Start >> word >> gCellGrid.Y.NumColumnsRows >> word >> gCellGrid.Y.Space >> word; // GCELLGRID Y 0 DO 30 STEP 6900 ;
}

void DefReader::ReadVias(ifstream& is, vector <Via>& vias) {
	string word, layer1, layer2, layer3;
	int count;
	is >> count >> word; // count ;
	vias.resize(count);
	for (Via& via : vias) {
		is >> word >> via.ViaName; // - vianame
		is >> word >> word >> via.ViaRule; // + VIARULE viaRuleName
		is >> word >> word >> via.CutSize.First >> via.CutSize.Second; // + CUTSIZE xSize ySize
		is >> word >> word >> via.ViaLayers.BotMetalLayer >> via.ViaLayers.CutLayer >> via.ViaLayers.TopMetalLayer; // + LAYERS botmetalLayer cutLayer topMetalLayer
		is >> word >> word >> via.CutSpacing.First >> via.CutSpacing.Second; // + CUTSPACING xCutSpacing yCutSpacing
		is >> word >> word >> via.Enclosure.First.First >> via.Enclosure.First.Second >> via.Enclosure.Second.First >> via.Enclosure.Second.Second; // + ENCLOSURE 90 60 100 65
		is >> word; // + or ;
		if (word == ";") { continue; }
		is >> word; // optional params
		if (word == "ROWCOL") {
			is >> via.RowCol.First >> via.RowCol.Second; // ROWCOL 1 4
		}
		is >> word;
		if (word == ";") { continue; }
	}
	is >> word; // END
	assert(word == "END");
	is >> word; // VIAS
}

void DefReader::ReadComponents(ifstream& is, vector<Component>& components) {
	string word, word2, wordSkip;
	int count;
	is >> count >> word; // count ;
	components.resize(count);
	for (Component& component : components) {
		is >> word >> component.CompName; // - compName
		is >> component.ModelName; // modelName
		is >> word >> word; // + SOURCE or TYPE
		if (word == "SOURCE") {
			is >> component.Source; // SOURCE
			is >> word >> component.Placement.Type; // + TYPE
		} // if no -> word = TYPE
		is >> wordSkip >> component.Placement.Pt.First >> component.Placement.Pt.Second >> wordSkip >> component.Placement.Orient; // ( 5520 10880 ) N ;
		is >> word; // ;
	}
	is >> word;
	assert(word == "END");
	is >> word;
}

const Port ReadOnePort(ifstream& is) {
	string word, word2, wordSkip;
	Port port;
	static const int
		LAYER = 1,
		FIXED_PLACED = 2,
		PLUS = -1;
	static const unordered_map <string, int> KEY_PORT {
		{ ";", 0},
		{"LAYER", 1},
		{"FIXED", 2},
		{"PLACED", 2},
		{"+", -1}
	};
	while (is >> word) {
		//is >> word; 
		auto it = KEY_PORT.find(word);
		if (it == KEY_PORT.end()) {
			cout << "Cant read Port in Def\n";
			assert(0);
		}
		switch (it->second)
		{
		case PLUS:
			continue;
		case 0: // ;
			return port;
		case LAYER: {
			Layer layer;
			Rect rect;
			is >> layer.Name;
			is >> word >> rect.First.First >> rect.First.Second >> word;
			is >> word >> rect.Second.First >> rect.Second.Second >> word;
			layer.Rects.push_back(rect);
			port.Layers.push_back(layer);
			break;
		}
		case FIXED_PLACED: {
			port.Placement.Type = word;
			Point pt;
			is >> wordSkip >> port.Placement.Pt.First >> port.Placement.Pt.Second >> wordSkip;
			is >> port.Placement.Orient;
			break;
		}
		default:
			break;
		}
	}
	return port;
}

void DefReader::ReadPins(ifstream& is, vector <Pin>& pins) {
	static const int
		NET = 1,
		SPECIAL = 2,
		DIRECTION = 3,
		USE = 4, 
		PORT = 5,
		PLUS = -1;
	static const unordered_map <string, int> KEY_PIN{
		{ ";", 0},
		{"NET", 1},
		{"SPECIAL", 2},
		{"DIRECTION", 3},
		{"USE", 4},
		{"PORT", 5},
		{"+", -1}
	};
	string word, word2, wordSkip;
	int count;
	is >> count >> word; //  < num ; >
	pins.resize(count);
	for (Pin& pin : pins) {
		bool stop = false;
		is >> word >> pin.Name;
		while (!stop) {
			is >> word;
			auto it = KEY_PIN.find(word);
			if (it == KEY_PIN.end()) {
				cout << "Cant read Pin in Def\n";
				assert(0);
			}
			switch (it->second) {
			case PLUS:
				continue;
				break;
			case NET:
				is >> pin.Net;
				break;
			case DIRECTION:
				is >> pin.Direction;
				break;
			case USE:
				is >> pin.Use;
				break;
			case SPECIAL:
				pin.Special = true;
				break;
			case PORT:
				pin.Ports.push_back(ReadOnePort(is));
				stop = true;
				break;
			}
		}
	}
	is >> word >> word; // END PINS
}

const vector<RoutingLayer> ReadRoutingLayers(ifstream& is) {
	vector<RoutingLayer> layers;
	static const int
		BRACKET = 1,
		SHAPE = 2,
		NEW = 3,
		PLUS = -1,
		LAYER_VIA = 4;
	static const unordered_map <string, int> KEY_PIN{
		{ ";", 0},
		{"(", 1},
		{"SHAPE", 2},
		{"NEW", 3},
		{"+", -1}
	};
	string word;
	int num;
	while (is >> word) {
		RoutingLayer rLayer;
		rLayer.Name = word;
		is >> rLayer.RouteWidth;
		bool stop = false;
		while (!stop) {
			is >> word;
			auto it = KEY_PIN.find(word);
			if (it == KEY_PIN.end()) {
				if (word.substr(0, 3) == "via") {
					num = 4;
				} else {
					cout << "Cant read RoutingLayers in Def\n";
					assert(0);
				}	
			} else {
				num = it->second;
			}
			switch (num) {
			case 0: // 0 == ;
				layers.push_back(rLayer);
				return layers;
			case NEW:
				stop = true;
				break;
			case PLUS:
				continue;
				break;
			case SHAPE:
				is >> rLayer.Shape;
				break;
			case BRACKET: {
				Point pt;
				is >> pt.First >> pt.Second >> word;
				rLayer.RoutingPoints.push_back(pt);
				break;
			}
			case LAYER_VIA:
				rLayer.ViaLayer = word;
				break;
			}
		}
		layers.push_back(rLayer);
	}
	return layers;
}

void DefReader::ReadSpecialnets(ifstream& is, vector <Specialnet>& specialnets) {
	static const int
		BRACKET = 1,
		USE = 2,
		ROUTED = 3,
		SHAPE = 4,
		NEW = 5,
		PLUS = -1;
	static const unordered_map <string, int> KEY_SPECIALNET{
		{ ";", 0},
		{"(", 1},
		{"USE", 2},
		{"ROUTED", 3},
		{"SHAPE", 4},
		{"NEW", 5},
		{"+", -1}
	};
	int count;
	string word, word2;
	is >> count >> word;
	specialnets.resize(count);
	// use routed shape
	for (Specialnet& specNet : specialnets) {
		is >> word >> specNet.Name;
		bool stop = false, isRoutePoints = false;
		while (!stop) {
			is >> word;
			auto it = KEY_SPECIALNET.find(word);
			if (it == KEY_SPECIALNET.end()) {
				cout << "Cant read Specialnet in Def\n";
				assert(0);
			}
			switch (it->second) {
			case PLUS:
				continue;
				break;
			case BRACKET:
				if (!isRoutePoints) {
					StringPair strPr;
					is >> strPr.First >> strPr.Second;
					specNet.CompPinNames.push_back(strPr);
					is >> word;
				} else {
					Point pt;
					is >> pt.First >> pt.Second >> word;
					specNet.RoutingPoints.push_back(pt);
				}
				break;
			case USE:
				is >> specNet.Use;
				break;
			case ROUTED:
				specNet.WiringType = word;
				is >> specNet.RouteLayerName;
				is >> specNet.RouteWidth;
				isRoutePoints = true;
				break;
			case SHAPE:
				is >> specNet.Shape;
				isRoutePoints = true;
				break;
			case NEW:
				specNet.RoutingLayers = ReadRoutingLayers(is);
				stop = true;
				break;
			}
		}
	}
	is >> word >> word2;
}

void DefReader::ReadNets(ifstream& is, vector<Net>& nets) {
	static const int
		BRACKET = 1,
		USE = 2,
		PLUS = -1;
	static const unordered_map <string, int> KEY_NET{
		{ ";", 0},
		{"(", 1},
		{"USE", 2},
		{"+", -1}
	};
	int count;
	string word, word2;
	is >> count >> word;
	nets.resize(count);
	for (Net& net : nets) {
		is >> word >> net.Name;
		bool stop = false;
		while (!stop) {
			is >> word;
			auto it = KEY_NET.find(word);
			if (it == KEY_NET.end()) {
				cout << "Cant read Net in Def\n";
				assert(0);
			}
			switch (it->second) {
			case 0: // ;
				stop = true;
				break;
			case PLUS:
				continue;
				break;
			case USE:
				is >> net.Use;
				break;
			case BRACKET: {
				StringPair strPr;
				is >> strPr.First >> strPr.Second;
				net.CompPinNames.push_back(strPr);
				is >> word;
				break;
			}
			}
		}
	}
	is >> word >> word2;
}
