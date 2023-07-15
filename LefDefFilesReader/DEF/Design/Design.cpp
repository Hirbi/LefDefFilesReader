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

const vector<Row>& Design::GetRows() const {
	return Rows;
}

void Design::ClearRows() {
	Rows.clear();
}

void Design::AddTrack(const Track& value) {
	Tracks.push_back(value);
}

const vector<Track>& Design::GetTrack() const {
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

void Design::AddVia(const Via& value) {
	Vias.push_back(value);
}

const vector<Via>& Design::GetVia() const {
	return Vias;
}

void Design::ClearVia() {
	Vias.clear();
}

void Design::SetComponents(const vector<Component>& value) {
	Components = value;
}

void Design::AddComponent(const Component& value) {
	Components.push_back(value);
}

const vector<Component>& Design::GetComponents() const {
	return Components;
}

void Design::ClearComponents() {
	Components.clear();
}

void Design::SetPins(const vector<Pin>& value) {
	Pins = value;
}

void Design::AddPin(const Pin& value) {
	Pins.push_back(value);
}

const vector<Pin>& Design::GetPins() const {
	return Pins;
}

void Design::ClearPins() {
	Pins.clear();
}

void Design::SetSpecialnets(const vector<Specialnet>& value) {
	Specialnets = value;
}

void Design::AddSpecialnet(const Specialnet& value) {
	Specialnets.push_back(value);
}

const vector<Specialnet>& Design::GetSpecialnets() const {
	return Specialnets;
}

void Design::ClearSpecialnets() {
	Specialnets.clear();
}
