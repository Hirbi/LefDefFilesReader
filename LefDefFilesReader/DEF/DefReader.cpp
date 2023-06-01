#pragma once
#include "DefReader.h"
#include "../lib/functions/functions.h"

#include <assert.h>
#include <iostream>
#include <string>
#include <unordered_map>
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
			design.Units = stoi(word);
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
				design.DieArea.push_back(Rect(First, Second));
			}
			cout << "hehe";
			break;
		case ROW:
			break;
		case TRACKS:
			break;
		case GCELLGRID:
			break;
		case VIAS:
			break;
		case COMPONENTS:
			break;
		case PINS:
			break;
		case SPECIALNETS:
			break;
		case NETS:
			break;
		case END:
			break;
		}
	}
	return design;
}
