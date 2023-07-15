#pragma once
#include "DefReader.h"
#include "../lib/containers/rect/Rect.h"
#include "../lib/functions/functions.h"
#include "../LEF/Macro/Pin/Pin.h"
#include "../LEF/Macro/Pin/Port/Port.h"

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
			design.SetUnits(stoi(word));
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
				design.AddDieArea(Rect(First, Second));
			}
			break;
		case ROW:
			design.AddRow(ReadRow(is));
			break;
		case TRACKS:
			design.AddTrack(ReadTracks(is));
			break;
		case GCELLGRID:
			design.SetGCellGrid(ReadGCellGrid(is));
			break;
		case VIAS:
			design.SetVias(ReadVias(is));
			break;
		case COMPONENTS:
			design.SetComponents(ReadComponents(is));
			break;
		case PINS:
			design.SetPins(ReadPins(is));
			break;
		case SPECIALNETS:
			design.SetSpecialnets(ReadSpecialnets(is));
			return design;
			break;
		case NETS:
			return design;
			break;
		case END:
			return design;
			break;
		}
	}
	return design;
}

const Row DefReader::ReadRow(ifstream& is) {
	Row row;
	string word;
	int first, second;
	is >> word; // rowName
	row.SetName(word);
	is >> word; // siteName
	row.SetSiteName(word);
	is >> first >> second; // origX origY
	row.SetOrig(first, second);
	is >> word; // siteOrient
	row.SetSiteOrient(word);
	is >> word; // DO or ";"
	if (word == ";") { return row; }
	is >> first >> word >> second; // numX BY numY
	row.SetNum(first, second);
	is >> word; // STEP or ";"
	if (word == ";") { return row; }
	is >> first >> second; //  stepX stepY
	row.SetStep(first, second);
	return row;
}

const Track DefReader::ReadTracks(ifstream& is) { 
	Track track;
	string word;
	is >> word;
	track.SetDirection(char(word[0]));
	int value;
	is >> value;
	track.SetStart(value);
	is >> word; // DO
	is >> value;
	track.SetNumTracks(value);
	is >> word; // STEP
	is >> value;
	track.SetSpace(value);
	is >> word; // LAYER
	do {
		is >> word;
		track.AddLayer(word);
		is >> word;
	} while (word != ";");
	return track;
}

const CellGrid DefReader::ReadGCellGrid(ifstream& is)
{
	CellGrid gCellGrid;
	int start, NumColumnsRows, space;
	string word;
	is >> word >> start >> word >> NumColumnsRows >> word >> space >> word; // X 0 DO 29 STEP 6900 ;
	gCellGrid.setXParameters(start, NumColumnsRows, space);
	is >> word >> word >> start >> word >> NumColumnsRows >> word >> space >> word; // GCELLGRID Y 0 DO 30 STEP 6900 ;
	gCellGrid.setYParameters(start, NumColumnsRows, space);
	return gCellGrid;
}

const vector<Via> DefReader::ReadVias(ifstream& is) {
	string word, layer1, layer2, layer3;
	int count;
	is >> count >> word; // count ;
	vector <Via> vias(count);
	int value1, value2, value3, value4;
	for (Via& via : vias) {
		is >> word >> word; // - vianame
		via.SetViaName(word);
		is >> word >> word >> word; // + VIARULE viaRuleName
		via.SetViaRule(word);
		is >> word >> word >> value1 >> value2; // + CUTSIZE xSize ySize
		via.SetCutSize(value1, value2);
		is >> word >> word >> layer1 >> layer2 >> layer3; // + LAYERS botmetalLayer cutLayer topMetalLayer
		via.SetViaLayers(layer1, layer2, layer3);
		is >> word >> word >> value1 >> value2; // + CUTSPACING xCutSpacing yCutSpacing
		via.SetCutSpacing(value1, value2);
		is >> word >> word >> value1 >> value2 >> value3 >> value4; // + ENCLOSURE 90 60 100 65
		via.SetEnclosure(value1, value2, value3, value4);
		is >> word; // + or ;
		if (word == ";") { continue; }
		is >> word; // optional params
		if (word == "ROWCOL") {
			is >> value1 >> value2; // ROWCOL 1 4
			via.SetRowCol(value1, value2);
		}
		is >> word;
		if (word == ";") { continue; }
	}
	is >> word; // END
	assert(word == "END");
	is >> word; // VIAS
	return vias;
}

const vector<Component> DefReader::ReadComponents(ifstream& is) {
	string word, word2, wordSkip;
	int count, value1, value2;
	is >> count >> word; // count ;
	vector<Component> components(count);
	for (Component& component : components) {
		is >> word >> word; // - compName
		component.SetCompName(word);
		is >> word; // modelName
		component.SetModelName(word);
		is >> word >> word; // + SOURCE or TYPE
		if (word == "SOURCE") {
			is >> word; // SOURCE
			component.SetSource(word);
			is >> word >> word; // + TYPE
		} // if no -> word = TYPE
		is >> wordSkip >> value1 >> value2 >> wordSkip >> word2; // ( 5520 10880 ) N ;
		component.SetPlacement(word, Point(value1, value2), word2);
		is >> word; // ;
	}
	is >> word;
	assert(word == "END");
	is >> word;
	return components;
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
			is >> word;
			layer.setName(word);
			is >> word >> rect.First.First >> rect.First.Second >> word;
			is >> word >> rect.Second.First >> rect.Second.Second >> word;
			layer.addRect(rect);
			port.addLayer(layer);
			break;
		}
		case FIXED_PLACED: {
			Point pt;
			is >> wordSkip >> pt.First >> pt.Second >> wordSkip;
			is >> word2;
			port.SetPlacement(word, pt, word2);
			break;
		}
		default:
			break;
		}
	}
	return port;
}

const vector<Pin> DefReader::ReadPins(ifstream& is) {
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
	vector <Pin> pins(count);
	for (Pin& pin : pins) {
		bool stop = false;
		is >> word >> word;
		pin.setName(word);
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
				is >> word;
				pin.setNet(word);
				break;
			case DIRECTION:
				is >> word;
				pin.setDirection(word);
				break;
			case USE:
				is >> word;
				pin.setUse(word);
				break;
			case SPECIAL:
				pin.setSpecial(true);
				break;
			case PORT:
				pin.addPort(ReadOnePort(is));
				stop = true;
				break;
			}
		}
	}
	is >> word >> word; // END PINS
	return pins;
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
		rLayer.setName(word);
		is >> num;
		rLayer.SetRouteWidth(num);
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
				is >> word;
				rLayer.SetShape(word);
				break;
			case BRACKET: {
				Point pt;
				is >> pt.First >> pt.Second >> word;
				rLayer.AddRoutingPoint(pt);
				break;
			}
			case LAYER_VIA:
				rLayer.SetViaLayer(word);
				break;
			}
		}
		layers.push_back(rLayer);
	}
	return layers;
}

const vector<Specialnet> DefReader::ReadSpecialnets(ifstream& is) {
	static const int
		BRACKET = 1,
		USE = 2,
		ROUTED = 3,
		SHAPE = 4,
		NEW = 5,
		PLUS = -1;
	static const unordered_map <string, int> KEY_PIN{
		{ ";", 0},
		{"(", 1},
		{"USE", 2},
		{"ROUTED", 3},
		{"SHAPE", 4},
		{"NEW", 5},
		{"+", -1}
	};
	int count, num;
	string word, word2;
	is >> count >> word;
	vector <Specialnet> specialnets(count);
	// use routed shape
	for (Specialnet& specNet : specialnets) {
		is >> word >> word;
		specNet.SetName(word);
		bool stop = false, isRoutePoints = false;
		auto specialWiring = specNet.MutableSpecialWiring();
		while (!stop) {
			is >> word;
			auto it = KEY_PIN.find(word);
			if (it == KEY_PIN.end()) {
				cout << "Cant read Specialnet in Def\n";
				assert(0);
			}
			switch (it->second) {
			case PLUS:
				continue;
				break;
			case BRACKET:
				if (!isRoutePoints) {
					is >> word;
					if (word == "PIN") {
						is >> word;
						specNet.AddPinName(word);
					}
					else {
						is >> word2;
						specNet.AddCompPatternPinName(word, word2);
					}
					is >> word;
				} else {
					Point pt;
					is >> pt.First >> pt.Second >> word;
					specialWiring->AddRoutingPoint(pt);
				}
				break;
			case USE:
				is >> word;
				specNet.SetUse(word);
				break;
			case ROUTED:
				specialWiring->SetWiringType(word);
				is >> word;
				specialWiring->SetRouteLayerName(word);
				is >> num;
				specialWiring->SetRouteWidth(num);
				isRoutePoints = true;
				break;
			case SHAPE:
				is >> word;
				specialWiring->SetShape(word);
				isRoutePoints = true;
				break;
			case NEW:
				specialWiring->SetNewLayers(ReadRoutingLayers(is));
				stop = true;
				break;
			}
		}
	}
	is >> word >> word2;
	return specialnets;
}
