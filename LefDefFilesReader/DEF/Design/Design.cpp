#include "Design.h"

Design::Design(const int units) :
	Units(units) {
}

void Design::SetUnits(const int value) {
	Units = value;
}

int Design::GetUnits() const {
	return Units;
}

void Design::AddDieArea(const Rect value) {
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
