#pragma once

#include "cell_grid/CellGrid.h"
#include "row/Row.h"
#include "track/Track.h"
#include "../../lib/containers/rect/Rect.h"

#include <string>
#include <vector>

using namespace std;

class Design {

	int Units;
	vector <Rect> DieArea;
	vector <Row> Rows;
	vector <Track> Tracks;
	CellGrid GCellGrid;

public:
	Design(const int units = 0);

	void SetUnits(const int value);
	int GetUnits() const;

	void AddDieArea(const Rect& value);
	const vector<Rect>& GetDieArea() const;
	void ClearDieArea();

	void AddRow(const Row& value);
	const vector <Row>& GetRows() const;
	void ClearRows();

	void AddTrack(const Track& value);
	const vector <Track>& GetTrack() const;
	void ClearTrack();

	void SetGCellGrid(const CellGrid& gCellGrid);
	const CellGrid& GetGCellGrid() const;
};

