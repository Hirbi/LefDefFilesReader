#include "CellGrid.h"

void CellGrid::setXParameters(int start, int numColumns, int space) {
	X.Start = start;
	X.NumColumnsRows = numColumns;
	X.Space = space;
}

void CellGrid::setYParameters(int start, int numRows, int space) {
	Y.Start = start;
	Y.NumColumnsRows = numRows;
	Y.Space = space;
}
