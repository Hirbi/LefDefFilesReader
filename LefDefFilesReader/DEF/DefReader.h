#pragma once

#include "Design/Design.h"
#include "../objects/Objects.h"

#include <string>
#include <fstream>

using namespace std;

class DefReader {
	double Version;
	char DividerChar;
	string BusbitChars;
public:
	void ReadData(const string& filename, Objects& objs);

private:
	Design ReadDesign(ifstream& is);
};