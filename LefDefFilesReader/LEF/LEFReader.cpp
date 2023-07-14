#include "LEFReader.h"

#include <cassert>
#include <iostream>
#include <fstream>
#include <unordered_map>


void LEFReader::readLEF(std::string fileName)
{
	static const int
		VERSION = 1,
		MACRO = 2,
	    END = 3;

	static const std::unordered_map <std::string, int> KEY_WORDS{
		{ ";", 0},
		{ "VERSION", 1 },
		{ "MACRO", 2 },
		{ "END", 3 }
	};

    std::ifstream fis(fileName);
	if (!fis.is_open()) {
        std::cout << "Can't open " << fileName << ". File not found.\n";
		return;
	}
    std::string word;
	while (!fis.eof()) {
		auto it = KEY_WORDS.find(word);
		if (it == KEY_WORDS.end()) {
            std::cout << "Cant find word: " << word << "\n";
			assert(0);
		}
		switch (it->second) {
		case 0:
			break;
		case VERSION:
			break;
		case MACRO:
			break;
		case END:
			break;
		}
		fis >> word;
	}
}

Macro LEFReader::readMacro(std::fstream& fis, std::string& word)
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
		END = 9;

	static const std::unordered_map <std::string, int> KEY_WORDS{
		{ ";", 0},
		{ "MACRO", 1 },
		{ "CLASS", 2 },
		{ "FOREIGN", 3 },
		{ "ORIGIN", 4 },
		{ "SIZE", 5 },
		{ "SYMMETRY", 6 },
		{ "SITE", 7 },
		{ "PIN", 8 },
		{ "END", 9 }
	};

	Macro macro;

	while (!fis.eof()) {
		auto it = KEY_WORDS.find(word);
		if (it == KEY_WORDS.end()) {
			std::cout << "Cant find word: " << word << "\n";
			assert(0);
		}
		switch (it->second) {
		case 0:
			break;
		case MACRO:
		    {
			fis >> word;
			macro.setName(word);
		    break;
		    }
		case CLASS:
		    {
		    break;
		    }
		case FOREIGN:
		    {
		        break;
		    }
		case ORIGIN:
		    {
		        break;
		    }
		case SIZE:
		    {
		        break;
		    }
		case SYMMETRY:
		    {
		        break;
		    }
		case SITE:
		    {
		        break;
		    }
		case PIN:
		    {
		        break;
		    }
		case END:
		    {
		        break;
		    }
		}
		fis >> word;
	}
	return macro;
}
