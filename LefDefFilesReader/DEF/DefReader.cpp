#pragma once
#include "DefReader.h"
#include "../lib/containers/rect/Rect.h"
#include "../lib/functions/functions.h"

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
					>> word >> word // <) (>
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
			return design;
			break;
		case SPECIALNETS:
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