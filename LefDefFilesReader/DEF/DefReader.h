#pragma once

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

	const Row ReadRow(ifstream& is);

	const Track ReadTracks(ifstream& is);

	void ReadGCellGrid(ifstream& is, CellGrid& gCellGrid);

	void ReadVias(ifstream& is, vector <Via>& vias);

	void ReadComponents(ifstream& is, vector<Component>& components);

	void ReadPins(ifstream& is, vector <Pin>& pins);

	void ReadSpecialnets(ifstream& is, vector <Specialnet>& specialnets);

	void ReadNets(ifstream& is, vector<Net>& nets);
};