#include "Design.h"

Design::Design(const int units) {
}

void Design::SetUnits(const int value) {
	Units = value;
}

int Design::GetUnits() const {
	return Units;
}

void Design::AddDieArea(const Rect& value) {
	DieArea.push_back(value);
}

const vector<Rect>& Design::GetDieArea() const {
	return DieArea;
}

void Design::ClearDieArea() {
	DieArea.clear();
}

void Design::AddRow(const Row& value) {
	Rows.push_back(value);
}

const vector<Row>& Design::GetRows() const
{
	return Rows;
}

void Design::ClearRows() {
	Rows.clear();
}

void Design::AddTrack(const Track& value) {
	Tracks.push_back(value);
}

const vector<Track>& Design::GetTrack() const
{
	return Tracks;
}

void Design::ClearTrack() {
	Tracks.clear();
}

void Design::SetGCellGrid(const CellGrid& gCellGrid) {
	GCellGrid = gCellGrid;
}

const CellGrid& Design::GetGCellGrid() const {
	return GCellGrid;
}

void Design::SetVias(const vector<Via>& value) {
	Vias = value;
}

void Design::AddVia(const Via& via) {
	Vias.push_back(via);
}

const vector<Via>& Design::GetVia() const
{
	return Vias;
}

void Design::ClearVia() {
	Vias.clear();
}
