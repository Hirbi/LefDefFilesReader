#pragma once

#include "row/Row.h"
#include "../../lib/containers/rect/Rect.h"

#include <string>
// #include <unordered_map>
#include <vector>

using namespace std;

class Design {

	int Units;
	vector <Rect> DieArea;
	vector <Row> Rows;

public:
	Design(const int units = 0);

	void SetUnits(const int value);
	int GetUnits() const;

	void AddDieArea(const Rect value);
	const vector<Rect>& GetDieArea() const;
	void ClearDieArea();

	void AddRow(const Row& row);
	const vector <Row>& GetRows() const;
	void ClearRows();
};

