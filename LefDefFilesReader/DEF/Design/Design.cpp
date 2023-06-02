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

void Design::AddRow(const Row& row) {
	Rows.push_back(row);
}

const vector<Row>& Design::GetRows() const
{
	return Rows;
}

void Design::ClearRows() {
	Rows.clear();
}
