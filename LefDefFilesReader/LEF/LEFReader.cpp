#include "LEFReader.h"
#include "../lib/containers/types.h"
#include <cassert>
#include <iostream>
#include <fstream>
#include <unordered_map>

LEF LEFReader::readLEF(std::string fileName)
{
	static const int
		VERSION = 1,
		BUSBITCHARS = 2,
		DIVIDERCHAR = 3,
		UNITS = 4,
		MANUFACTURINGGRID = 5,
		USEMINSPACING = 6,
		PROPERTYDEFINITIONS = 7,
		SITE = 8,
		LAYER = 9,
		VIA = 10,
		VIARULE = 11,
		MACRO = 12,
		END = 13;

	static const std::unordered_map <std::string, int> KEY_WORDS{
		{"#", -1},
		{"###", -1},
		{ ";", 0},
		{ "VERSION", 1 },
		{ "BUSBITCHARS", 2 },
		{ "DIVIDERCHAR", 3 },
		{ "UNITS", 4 },
		{ "MANUFACTURINGGRID", 5 },
		{ "USEMINSPACING", 6 },
		{ "PROPERTYDEFINITIONS", 7 },
		{ "SITE", 8 },
		{ "LAYER", 9 },
		{ "VIA", 10 },
		{ "VIARULE", 11 },
		{ "MACRO", 12 },
		{ "END", 13 }
	};

    std::ifstream fis(fileName);
	if (!fis.is_open()) {
        std::cout << "Can't open " << fileName << ". File not found.\n";
		assert(0);
	}
    std::string word;
	LEF lef;
	fis >> word;
	while (!fis.eof()) {
		auto it = KEY_WORDS.find(word);
		if (it == KEY_WORDS.end()) {
            std::cout << "Cant find word: " << word << "\n";
			assert(0);
		}
		switch (it->second) {
		case -1:
			std::getline(fis, word);
			break;
		case 0:
			break;
		case VERSION:
		{
			Param param;
			param.type = word;
			fis >> word;
			param.num = word;
			lef.params.push_back(param);
			break;
		}
		case BUSBITCHARS:
		{
			//TODO fix to normal string
			Param param;
			param.type = word;
			std::getline(fis, word);
			param.num = word;
			lef.params.push_back(param);
			break;
		}
		case DIVIDERCHAR:
		{
			//TODO fix to normal string
			Param param;
			param.type = word;
			std::getline(fis, word);
			param.num = word;
			lef.params.push_back(param);
			break;
		}
		case UNITS: 
		{
			lef.units = readUnits(fis,word);
			break;
		}
		case MANUFACTURINGGRID:
		{
			Param param;
			param.type = word;
			fis>>word;
			param.num = word;
			lef.params.push_back(param);
			break;
		}
		case USEMINSPACING:
		{
			//
			// USEMINSPACING OBS OFF ;
			// 
			//TODO fix to normal struct
			Param param;
			param.type = word;
			std::getline(fis, word);
			param.num = word;
			lef.params.push_back(param);
			break;
		}
		case PROPERTYDEFINITIONS:
		{
			lef.propertyDefinitions = readPropertyDefinitions(fis, word);
			break;
		}
		case SITE:
		{
			lef.siteProperties.push_back(readSiteProperties(fis, word));
			break;
		}
		case LAYER:
		{
			lef.layerProperties.push_back(readLayerProperties(fis, word));
			break;
		}
		case VIA:
		{
			lef.vias.push_back(readVia(fis, word));
			break;
		}
		case VIARULE:
		{
			lef.viaRules.push_back(readViaRule(fis, word));
			break;
		}
		case MACRO:
		{
			lef.macros.push_back(readMacro(fis, word));
			break;
		}
		case END:
			return lef;
		}
		fis >> word;
	}
}

Via LEFReader::readVia(std::ifstream& fis, std::string& word) {
	static const int
		VIA = 1,
		LAYER = 2,
		ENCLOSURE = 3,
		RECT = 4,
		SPACING = 5,
		END = 6;


	static const std::unordered_map <std::string, int> KEY_WORDS{
		{"#", -1},
		{"###", -1},
		{ ";", 0},
		{ "VIA", 1 },
		{ "LAYER", 2 },
		{ "ENCLOSURE", 3 },
		{ "RECT", 4 },
		{ "SPACING", 5 },
		{ "END", 6 }
	};

	Via via;
	while (!fis.eof()) {
		auto it = KEY_WORDS.find(word);
		if (it == KEY_WORDS.end()) {
			std::cout << "Cant find word: " << word << "\n";
			assert(0);
		}
		switch (it->second) {
		case -1:
			std::getline(fis, word);
			break;
		case 0:
			break;
		case VIA:
		{
			fis >> word;
			via.name = word;
			fis >> word;
			via.type = word;
			break;
		}
		case LAYER:
		{
			fis >> word;
			via.layers.push_back(word);
			break;
		}
		case ENCLOSURE:
		{
			Param param;
			double a1, a2;
			param.type = word;
			fis >> a1 >> a2;
			param.num = Point(a1, a2);
			via.params.push_back(param);
			break;
		}
		case RECT:
		{
			Param param;
			double a1, a2, b1, b2;
			param.type = word;
			fis >> a1 >> a2 >> b1 >> b2;
			param.num = Rect(a1, a2, b1, b2);
			via.params.push_back(param);
			break;
		}
		case SPACING:
		{
			Param param;
			double a1, a2;
			param.type = word;
			fis >> a1 >> word >> a2;
			param.num = Point(a1, a2);
			via.params.push_back(param);
			break;
		}
		case END:
		{
			fis >> word;
			return via;
			break;
		}
		}
		fis >> word;
	}
}

ViaRule LEFReader::readViaRule(std::ifstream& fis, std::string& word) {
	static const int
		VIARULE = 1,
		LAYER = 2,
		ENCLOSURE = 3,
		RECT = 4,
		SPACING = 5,
		END = 6;


	static const std::unordered_map <std::string, int> KEY_WORDS{
		{"#", -1},
		{"###", -1},
		{ ";", 0},
		{ "VIARULE", 1 },
		{ "LAYER", 2 },
		{ "ENCLOSURE", 3 },
		{ "RECT", 4 },
		{ "SPACING", 5 },
		{ "END", 6 }
	};

	ViaRule viaRule;
	while (!fis.eof()) {
		auto it = KEY_WORDS.find(word);
		if (it == KEY_WORDS.end()) {
			std::cout << "Cant find word: " << word << "\n";
			assert(0);
		}
		switch (it->second) {
		case -1:
			std::getline(fis, word);
			break;
		case 0:
			break;
		case VIARULE:
		{
			fis >> word;
			viaRule.name = word;
			fis >> word;
			viaRule.type = word;
			break;
		}
		case LAYER:
		{
			fis >> word;
			viaRule.layers.push_back(word);
			break;
		}
		case ENCLOSURE:
		{
			Param param;
			double a1, a2;
			param.type = word;
			fis >> a1 >> a2;
			param.num = Point(a1, a2);
			viaRule.params.push_back(param);
			break;
		}
		case RECT:
		{
			Param param;
			double a1, a2, b1, b2;
			param.type = word;
			fis >> a1 >> a2 >> b1 >> b2;
			param.num = Rect(a1, a2, b1, b2);
			viaRule.params.push_back(param);
			break;
		}
		case SPACING:
		{
			Param param;
			double a1, a2;
			param.type = word;
			fis >> a1 >> word >> a2;
			param.num = Point(a1, a2);
			viaRule.params.push_back(param);
			break;
		}
		case END:
		{
			fis >> word;
			return viaRule;
			break;
		}
		}
		fis >> word;
	}
}

Units LEFReader::readUnits(std::ifstream & fis, std::string & word) {
	static const int
		UNITS = 1,
		TIME = 2,
		CAPACITANCE = 3,
		RESISTANCE = 4,
		DATABASE = 5,
		END = 6;

	static const std::unordered_map <std::string, int> KEY_WORDS{
		{"#", -1},
		{"###", -1},
		{ ";", 0},
		{ "UNITS", 1},
		{ "TIME", 2 },
		{ "CAPACITANCE", 3 },
		{ "RESISTANCE", 4 },
		{ "DATABASE", 5 },
		{ "END", 6 }
	};
	
	Units units;
	while (!fis.eof()) {
		auto it = KEY_WORDS.find(word);
		if (it == KEY_WORDS.end()) {
			std::cout << "Cant find word: " << word << "\n";
			assert(0);
		}
		switch (it->second) {
		case -1:
			std::getline(fis, word);
			break;
		case 0:
			break;
		case UNITS:
			break;
		case TIME:
		{
			fis >> word;
			units.timeUnit = word;
			fis >> word;
			units.timeValue = stoi(word);
			break;
		}
		case CAPACITANCE:
		{
			fis >> word;
			units.capacitanceUnit = word;
			fis >> word;
			units.capacitanceValue = stoi(word);
			break;
		}
		case RESISTANCE:
		{
			fis >> word;
			units.resistanceUnit = word;
			fis >> word;
			units.resistanceValue = stoi(word);
			break;
		}
		case DATABASE:
		{
			fis >> word;
			units.dataBaseUnit = word;
			fis >> word;
			units.dataBaseValue = stoi(word);
			break;
		}
		case END:
		{
			fis >> word;
			return units;
			break;
		}
		}
		fis >> word;
	}
	return units;
}

std::vector<PropertyDefinition> LEFReader::readPropertyDefinitions(std::ifstream& fis, std::string& word) {
	static const int
		PROPERTYDEFINITIONS = 1,
		LAYER = 2,
		END = 3;

	static const std::unordered_map <std::string, int> KEY_WORDS{
		{"#", -1},
		{"###", -1},
		{ ";", 0},
		{ "PROPERTYDEFINITIONS", 1 },
		{ "LAYER", 2 },
		{ "END", 3 }
	};

	std::vector<PropertyDefinition> propertyDefinitions;
	while (!fis.eof()) {
		auto it = KEY_WORDS.find(word);
		if (it == KEY_WORDS.end()) {
			std::cout << "Cant find word: " << word << "\n";
			assert(0);
		}
		switch (it->second) {
		case -1:
			std::getline(fis, word);
			break;
		case 0:
			break;
		case PROPERTYDEFINITIONS:
		{
			break;
		}
		case LAYER:
		{
			PropertyDefinition propertyDefinition;
			fis >> word;
			propertyDefinition.layer = word;
			fis >> word;
			propertyDefinition.type = word;
			propertyDefinitions.push_back(propertyDefinition);
			break;
		}
		case END:
		{
			fis >> word;
			return propertyDefinitions;
		}
		}
		fis >> word;
	}
}

SiteProperty LEFReader::readSiteProperties(std::ifstream& fis, std::string& word) {
	static const int
		SITE = 1,
		SYMMETRY = 2,
		CLASS = 3,
		SIZE = 4,
		END = 5;

	static const std::unordered_map <std::string, int> KEY_WORDS{
		{"#", -1},
		{"###", -1},
		{ ";", 0},
		{ "SITE", 1},
		{ "SYMMETRY", 2 },
		{ "CLASS", 3 },
		{ "SIZE", 4 },
		{ "END", 5 }
	};

	SiteProperty siteProperty;
	while (!fis.eof()) {
		auto it = KEY_WORDS.find(word);
		if (it == KEY_WORDS.end()) {
			std::cout << "Cant find word: " << word << "\n";
			assert(0);
		}
		switch (it->second) {
		case -1:
			std::getline(fis, word);
			break;
		case 0:
			break;
		case SITE:
			fis >> word;
			siteProperty.name = word;
			break;
		case SYMMETRY:
		{
			Param param;
			param.type = word;
			std::getline(fis, word);
			param.num = word;
			siteProperty.params.push_back(param);
			break;
		}
		case CLASS:
		{
			//TODO delete ";"
			Param param;
			param.type = word;
			std::getline(fis, word);
			param.num = word;
			siteProperty.params.push_back(param);
			break;
		}
		case SIZE:
		{
			Param param;
			double first, second;
			param.type = word;
			fis >> first >> word >> second;
			Point origin(first, second);
			param.num = origin;
			siteProperty.params.push_back(param);
			break;
		}
		case END:
		{
			fis >> word;
			return siteProperty;
			break;
		}
		}
		fis >> word;
	}
}

LayerProperty LEFReader::readLayerProperties(std::ifstream& fis, std::string& word) {
	static const int
		LAYER = 1,
		TYPE = 2,
		PROPERTY = 3,
		PITCH = 4,
		OFFSET = 5,
		WIDTH = 6,
		SPACINGTABLE = 7,
		THICKNESS = 8,
		EDGECAPACITANCE = 9,
		CAPACITANCE = 10,
		RESISTANCE = 11,
		ANTENNAMODEL = 12,
		ANTENNADIFFSIDEAREARATIO = 13,
		DIRECTION = 14,
		AREA = 15,
		SPACING = 16,
		ENCLOSURE = 17,
		ANTENNADIFFAREARATIO = 18,
		DCCURRENTDENSITY = 19,
		MINENCLOSEDAREA = 20,
		ACCURRENTDENSITY = 21,
		MAXIMUMDENSITY = 22,
		DENSITYCHECKWINDOW = 23,
		DENSITYCHECKSTEP = 24,
		END = 25;

	static const std::unordered_map <std::string, int> KEY_WORDS{
		{"#", -1},
		{"###", -1},
		{ ";", 0},
		{ "LAYER", 1},
		{ "TYPE", 2 },
		{ "PROPERTY", 3 },
		{ "PITCH", 4 },
		{ "OFFSET", 5 },
		{ "WIDTH", 6 },
		{ "SPACINGTABLE", 7 },
		{ "THICKNESS", 8 },
		{ "EDGECAPACITANCE", 9 },
		{ "CAPACITANCE", 10 },
		{ "RESISTANCE", 11 },
		{ "ANTENNAMODEL", 12 },
		{ "ANTENNADIFFSIDEAREARATIO", 13 },
		{ "DIRECTION", 14 },
		{ "AREA", 15},
		{ "SPACING", 16},
		{ "ENCLOSURE", 17},
		{ "ANTENNADIFFAREARATIO", 18},
		{ "DCCURRENTDENSITY", 19},
		{ "MINENCLOSEDAREA", 20},
		{ "ACCURRENTDENSITY", 21},
		{ "MAXIMUMDENSITY", 22 },
		{ "DENSITYCHECKWINDOW", 23 },
		{ "DENSITYCHECKSTEP", 24 },
		{ "END", 25}
	};

	LayerProperty layerProperty;
	while (!fis.eof()) {
		auto it = KEY_WORDS.find(word);
		if (it == KEY_WORDS.end()) {
			std::cout << "Cant find word: " << word << "\n";
			assert(0);
		}
		switch (it->second) {
		case -1:
			std::getline(fis, word);
			fis >> word;
			break;
		case 0:
			fis >> word;
			break;
		case LAYER:
			fis >> word;
			layerProperty.name = word;
			fis >> word;
			break;
		case TYPE:
		{
			Param param;
			param.type = word;
			fis >> word;
			param.num = word;
			layerProperty.params.push_back(param);
			fis >> word;
			break;
		}
		case DIRECTION:
		{
			Param param;
			param.type = word;
			fis >> word;
			param.num = word;
			layerProperty.params.push_back(param);
			fis >> word;
			break;
		}
		case RESISTANCE:
		{
			//TODO fix to normal struct
			// 
			// 2 type:
			// 1. number
			// 2. word + number
			// 
			// 
			//double value;
			//Param param;
			//param.type = word;
			//fis >> word >> value;
			//Resistance resistance;
			//resistance.type = word;
			//resistance.value = value;
			//param.num = resistance;
			//layerProperty.params.push_back(param);
			Param param;
			param.type = word;
			std::getline(fis, word);
			param.num = word;
			layerProperty.params.push_back(param);
			fis >> word;
			break;
		}
		case CAPACITANCE:
		{
			double value;
			Param param;
			param.type = word;
			fis >> word >> value;
			Capacitance capacitance;
			capacitance.type = word;
			capacitance.value = value;
			param.num = capacitance;
			layerProperty.params.push_back(param);
			fis >> word;
			break;
		}
		case PROPERTY:
		{
			Param param;
			param.type = word;
			std::getline(fis, word);
			param.num = word;
			layerProperty.params.push_back(param);
			fis >> word;
			break;
		}
		case PITCH:
		{
			//TODO fix to normall struct
			//
			// 2 type:
			// 1. number
			// 2. number + number (Point) 
			// 
			// 
			//Param param;
			//double first, second;
			//param.type = word;
			//fis >> word;
			//first = stoi(word);
			//fis >> word;
			//second = stoi(word);
			//Point origin(first, second);
			//param.num = origin;
			//layerProperty.params.push_back(param);
			Param param;
			param.type = word;
			std::getline(fis, word);
			param.num = word;
			layerProperty.params.push_back(param);
			fis >> word;
			break;
		}
		case OFFSET:
		{
			//TODO fix to normall struct
			//
			// 2 type:
			// 1. number
			// 2. number + number (Point) 
			// 
			//Param param;
			//double first, second;
			//param.type = word;
			//fis >> first >> second;
			//Point offset(first, second);
			//param.num = offset;
			//layerProperty.params.push_back(param);
			Param param;
			param.type = word;
			std::getline(fis, word);
			param.num = word;
			layerProperty.params.push_back(param);
			fis >> word;
			break;
		}
		case WIDTH:
		{
			Param param;
			param.type = word;
			fis >> word;
			param.num = word;
			layerProperty.params.push_back(param);
			fis >> word;
			break;
		}
		case SPACINGTABLE:
		{
			Param param;
			param.type = word;
			param.num = readSpacingTable(fis, word);
			layerProperty.params.push_back(param);
			break;
		}
		case AREA:
		{
			Param param;
			param.type = word;
			fis >> word;
			param.num = word;
			layerProperty.params.push_back(param);
			fis >> word;
			break;
		}
		case SPACING:
		{
			Param param;
			param.type = word;
			fis >> word;
			param.num = word;
			layerProperty.params.push_back(param);
			fis >> word;
			break;
		}
		case ENCLOSURE:
		{
			Param param;
			double first, second;
			Enclosure enclosure;
			param.type = word;
			fis >> word;
			enclosure.type = word;
			fis >> first >> second;
			Point point(first, second);
			enclosure.point = point;
			param.num = enclosure;
			layerProperty.params.push_back(param);
			fis >> word;
			break;
		}
		case MINENCLOSEDAREA:
		{
			Param param;
			param.type = word;
			fis >> word;
			param.num = word;
			layerProperty.params.push_back(param);
			fis >> word;
			break;
		}
		case THICKNESS:
		{
			Param param;
			param.type = word;
			fis >> word;
			param.num = word;
			layerProperty.params.push_back(param);
			fis >> word;
			break;
		}
		case EDGECAPACITANCE:
		{
			Param param;
			param.type = word;
			fis >> word;
			param.num = word;
			layerProperty.params.push_back(param);
			fis >> word;
			break;
		}
		case ANTENNAMODEL:
		{
			Param param;
			param.type = word;
			fis >> word;
			param.num = word;
			layerProperty.params.push_back(param);
			fis >> word;
			break;
		}
		case ANTENNADIFFSIDEAREARATIO:
		{
			//TODO fix to normal struct
			//
			//  ANTENNADIFFSIDEAREARATIO PWL ( ( 0 400 ) ( 0.0125 400 ) ( 0.0225 2609 ) ( 22.5 11600 ) ) ;
			// type;
			// vector<point> points;
			//
			//
			//
			Param param;
			param.type = word;
			std::getline(fis, word);
			param.num = word;
			layerProperty.params.push_back(param);
			fis >> word;
			break;
		}
		case ANTENNADIFFAREARATIO:
		{
			//TODO fix to normal struct
			//
			// ANTENNADIFFAREARATIO PWL((0 6) (0.0125 6) (0.0225 6.81) (22.5 816));
			// type;
			// vector<point> points;
			//
			Param param;
			param.type = word;
			std::getline(fis, word);
			param.num = word;
			layerProperty.params.push_back(param);
			fis >> word;
			break;
		}
		case DCCURRENTDENSITY:
		{
			Param param;
			param.type = word;
			DCCurrentDensity density;
			fis >> density.type >> density.value;
			param.num = density;
			layerProperty.params.push_back(param);
			fis >> word;
			break;
		}
		case ACCURRENTDENSITY:
		{
			Param param;
			param.type = word;
			ACCurrentDensity density;
			fis >> density.type >> density.value;
			param.num = density;
			layerProperty.params.push_back(param);
			fis >> word;
			break;
		}
		case MAXIMUMDENSITY:
		{
			Param param;
			param.type = word;
			std::getline(fis, word);
			param.num = word;
			layerProperty.params.push_back(param);
			fis >> word;
			break;
		}
		case DENSITYCHECKWINDOW:
		{
			Param param;
			double first, second;
			param.type = word;
			fis >> first >> second;
			Point densityCheckWindow(first, second);
			param.num = densityCheckWindow;
			layerProperty.params.push_back(param);
			fis >> word;
			break;
		}
		case DENSITYCHECKSTEP:
		{
			Param param;
			param.type = word;
			std::getline(fis, word);
			param.num = word;
			layerProperty.params.push_back(param);
			fis >> word;
			break;
		}
		case END:
		{
			fis >> word;
			return layerProperty;
			break;
		}
		}
		
	}
}

SpacingTable LEFReader::readSpacingTable(std::ifstream& fis, std::string& word) {
	static const int
		SPACINGTABLE = 1,
		PARALLELRUNLENGTH = 2,
		WIDTH = 3;

	static const std::unordered_map <std::string, int> KEY_WORDS{
		{"#", -1},
		{"###", -1},
		{ ";", 0},
		{ "SPACINGTABLE", 1 },
		{ "PARALLELRUNLENGTH", 2 },
		{ "WIDTH", 3 }
	};

	SpacingTable spacingTable;
	while (!fis.eof()) {
		auto it = KEY_WORDS.find(word);
		if (it == KEY_WORDS.end()) {
			return spacingTable;
		}
		switch (it->second) {
		case -1:
			std::getline(fis, word);
			break;
		case 0:
			break;
		case SPACINGTABLE:
		{
			break;
		}
		case PARALLELRUNLENGTH:
		{
			int value;
			fis >> value;
			spacingTable.parallelRunLength = value;
			break;
		}
		case WIDTH:
		{
			double a1, a2;
			fis >> a1 >> a2;
			spacingTable.widths.push_back(Point(a1, a2));
			break;
		}
		}
		fis >> word;
	}
}

Macro LEFReader::readMacro(std::ifstream& fis, std::string& word)
{
	static const int
		MACRO = 1,
		CLASS = 2,
		FOREIGN = 3,
		ORIGIN = 4,
		SIZE = 5,
		SYMMETRY = 6,
		SITE = 7,
		PIN = 8,
		OBS = 9,
		SOURCE = 10,
		END = 11;

	static const std::unordered_map <std::string, int> KEY_WORDS{
		{"#", -1},
		{"###", -1},
		{ ";", 0},
		{ "MACRO", 1 },
		{ "CLASS", 2 },
		{ "FOREIGN", 3 },
		{ "ORIGIN", 4 },
		{ "SIZE", 5 },
		{ "SYMMETRY", 6 },
		{ "SITE", 7 },
		{ "PIN", 8 },
		{ "OBS", 9 },
		{ "SOURCE", 10},
		{ "END", 11 }
	};

	Macro macro;
	
	while (!fis.eof()) {
		auto it = KEY_WORDS.find(word);
		if (it == KEY_WORDS.end()) {
			std::cout << "Cant find word: " << word << "\n";
			assert(0);
		}
		switch (it->second) {
		case -1:
			std::getline(fis, word);
			break;
		case 0:
			break;
		case MACRO:
		    {
			fis >> word;
			macro.name = word;
		    break;
		    }
		case CLASS:
		    {
			//TODO fix to normal string
			//string
			//string + string
			//
			//
			Param param;
			param.type = word;
			std::getline(fis, word);
			//fis >> word;
			param.num = word;
			macro.params.push_back(param);	
			break;
		    }
		case FOREIGN:
		    {
			Param param;
			param.type = word;
			fis >> word;
			param.num = word;
			macro.params.push_back(param);
			break;
		    }
		case SOURCE:
			{
			Param param;
			param.type = word;
			fis >> word;
			param.num = word;
			macro.params.push_back(param);
			break;
		}
		case ORIGIN:
		    {
			Param param;
			double first, second;
			param.type = word;
			fis >> first >> second;
			Point origin(first, second);
			param.num = origin;
			macro.params.push_back(param);
		    break;
		    }
		case SIZE:
		    {
			Param param;
			double first, second;
			param.type = word;
			fis >> first >> word >> second;
			Point origin(first, second);
			param.num = origin;
			macro.params.push_back(param);
		    break;
		    }
		case SYMMETRY:
		    {
			Param param;
			param.type = word;
			std::getline(fis, word);
			param.num = word;
			macro.params.push_back(param);
			break;
		    }
		case SITE:
		    {
			Param param;
			param.type = word;
			fis >> word;
			param.num = word;
			macro.params.push_back(param);
			break;
		    }
		case PIN:
		    {
			macro.pins.push_back(readPin(fis, word));
		    break;
		    }
		case OBS:
			{
			macro.obss.push_back(readObs(fis, word));
			break;
		}
		case END:
		    {
			fis >> word;
			return macro;
		    break;
		    }
		}
		fis >> word;
	}
}

Pin LEFReader::readPin(std::ifstream& fis, std::string& word) {
	static const int
		PIN = 1,
		DIRECTION = 2,
		USE = 3,
		ANTENNAGATEAREA = 4,
		ANTENNADIFFAREA = 5,
		PORT = 6,
		SHAPE = 7,
		END = 8;

	static const std::unordered_map <std::string, int> KEY_WORDS{
		{"#", -1},
		{"###", -1},
		{ ";", 0},
		{ "PIN", 1 },
		{ "DIRECTION", 2 },
		{ "USE", 3 },
		{ "ANTENNAGATEAREA", 4 },
		{ "ANTENNADIFFAREA", 5 },
		{ "PORT", 6 },
		{ "SHAPE", 7 },
		{ "END", 8 }
	};

	Pin pin;

	while (!fis.eof()) {
		auto it = KEY_WORDS.find(word);
		if (it == KEY_WORDS.end()) {
			std::cout << "Cant find word: " << word << "\n";
			assert(0);
		}
		switch (it->second) {
		case -1:
			std::getline(fis, word);
			break;
		case 0:
			break;
		case PIN:
		{
			fis >> word;
			pin.name = word;
			break;
		}
		case DIRECTION:
		{
			Param pinParam;
			pinParam.type = word;
			fis >> word;
			pinParam.num = word;
			pin.params.push_back(pinParam);
			break;
		}
		case USE:
		{
			Param pinParam;
			pinParam.type = word;
			fis >> word;
			pinParam.num = word;
			pin.params.push_back(pinParam);
			break;
		}
		case ANTENNADIFFAREA:
		{
			Param pinParam;
			pinParam.type = word;
			fis >> word;
			pinParam.num = word;
			pin.params.push_back(pinParam);
			break;
		}
		case ANTENNAGATEAREA:
		{
			Param pinParam;
			pinParam.type = word;
			fis >> word;
			pinParam.num = word;
			pin.params.push_back(pinParam);
			break;
		}
		case SHAPE:
		{
			Param pinParam;
			pinParam.type = word;
			fis >> word;
			pinParam.num = word;
			pin.params.push_back(pinParam);
			break;
		}
		case PORT:
		{
			pin.port = readPort(fis, word);
			break;
		}
		case END:
		{
			fis >> word;
			return pin;
		}
		}
		fis >> word;
	}
	
}

Obs LEFReader::readObs(std::ifstream& fis, std::string& word) {
	static const int
		OBS = 1,
		LAYER = 2,
		END = 3;

	static const std::unordered_map <std::string, int> KEY_WORDS{
		{"#", -1},
		{"###", -1},
		{ ";", 0},
		{ "OBS", 1 },
		{ "LAYER", 2 },
		{ "END", 3 }
	};

	Obs obs;
	while (!fis.eof()) {
		auto it = KEY_WORDS.find(word);
		if (it == KEY_WORDS.end()) {
			std::cout << "Cant find word: " << word << "\n";
			assert(0);
		}
		switch (it->second) {
		case -1:
			std::getline(fis, word);
			break;
		case 0:
			fis >> word;
			break;
		case OBS:
		{
			fis >> word;
			break;
		}
		case LAYER:
		{
			obs.layers.push_back(readLayer(fis, word));
			break;
		}
		case END:
		{
			return obs;
			break;
		}
		}

	}
}

Port LEFReader::readPort(std::ifstream& fis, std::string& word) {
	static const int
		PORT = 1,
		LAYER = 2,
		END = 3;

	static const std::unordered_map <std::string, int> KEY_WORDS{
		{"#", -1},
		{"###", -1},
		{ ";", 0},
		{ "PORT", 1 },
		{ "LAYER", 2 },
		{ "END", 3 }
	};

	Port port;
	while (!fis.eof()) {
		auto it = KEY_WORDS.find(word);
		if (it == KEY_WORDS.end()) {
			std::cout << "Cant find word: " << word << "\n";
			assert(0);
		}
		switch (it->second) {
		case -1:
			std::getline(fis, word);
			break;
		case 0:
			fis >> word;
			break;
		case PORT:
		{
			fis >> word;
			break;
		}
		case LAYER:
		{
			port.layers.push_back(readLayer(fis, word));
			break;
		}
		case END:
		{
			return port;
			break;
		}
		}
		
	}	
}

Layer LEFReader::readLayer(std::ifstream& fis, std::string& word) {
	static const int
		LAYER = 1,
		RECT = 2,
		END = 3;

	static const std::unordered_map <std::string, int> KEY_WORDS{
		{"#", -1},
		{"###", -1},
		{ ";", 0},
		{ "LAYER", 1 },
		{ "RECT", 2 },
		{ "END", 3 }
	};

	Layer layer;
	fis >> word;
	layer.name = word;
	fis >> word;
	while (!fis.eof()) {
		auto it = KEY_WORDS.find(word);
		if (it == KEY_WORDS.end()) {
			std::cout << "Cant find word: " << word << "\n";
			assert(0);
		}
		switch (it->second) {
		case -1:
			std::getline(fis, word);
			break;
		case 0:
			break;
		case LAYER:
		{
			return layer;
			break;
		}
		case RECT:
		{
			double a1, a2, b1, b2;
			fis >> a1 >> a2 >> b1 >> b2;
			layer.rects.push_back(Rect(a1, a2, b1, b2));
			break;
		}
		case END:
		{
			return layer;
			break;
		}
		}
		fis >> word;
	}
}
