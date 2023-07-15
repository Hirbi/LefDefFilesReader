#pragma once

#include "Design/Design.h"
#include "Design/cell_grid/CellGrid.h"
#include "Design/net/Net.h"
#include "Design/row/Row.h"
#include "Design/specialnet/Specialnet.h"
#include "Design/track/Track.h"
#include "Design/via/Via.h"
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

	const Track ReadTracks(ifstream& is);

	const CellGrid ReadGCellGrid(ifstream& is);

	const vector<Via> ReadVias(ifstream& is);

	const vector<Component> ReadComponents(ifstream& is);

	const vector<Pin> ReadPins(ifstream& is);

	const vector<Specialnet> ReadSpecialnets(ifstream& is);

	const vector<Net> ReadNets(ifstream& is);

};