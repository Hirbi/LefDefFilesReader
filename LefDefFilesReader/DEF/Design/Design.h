#pragma once

#include "cell_grid/CellGrid.h"
#include "component/Component.h"
#include "row/Row.h"
#include "track/Track.h"
#include "via/Via.h"
#include "../../lib/containers/rect/Rect.h"
#include "../../LEF/Macro/Pin/Pin.h"

#include <string>
#include <vector>

using namespace std;

class Design {

	int Units;
	vector <Rect> DieArea;
	vector <Row> Rows;
	vector <Track> Tracks;
	CellGrid GCellGrid;
	vector <Via> Vias;
	vector <Component> Components;
	vector <Pin> Pins;

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

	void SetVias(const vector<Via>& value);
	void AddVia(const Via& value);
	const vector <Via>& GetVia() const;
	void ClearVia();

	void SetComponents(const vector<Component>& value);
	void AddComponent(const Component& value);
	const vector <Component>& GetComponents() const;
	void ClearComponents();

	void SetPins(const vector<Pin>& value);
	void AddPin(const Pin& value);
	const vector <Pin>& GetPins() const;
	void ClearPins();
};

