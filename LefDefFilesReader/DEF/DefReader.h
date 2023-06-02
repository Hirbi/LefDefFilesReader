#pragma once

#include "Design/Design.h"
#include "Design/row/Row.h"
#include "../objects/Objects.h"

#include <fstream>
#include <string>

using namespace std;

class DefReader {
	double Version;
	char DividerChar;
	string BusbitChars;
public:
	void ReadData(const string& filename, Objects& objs);

private:
	Design ReadDesign(ifstream& is);

	const Row ReadRow(ifstream& is);
};