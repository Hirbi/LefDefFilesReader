#pragma once

namespace {
	struct Parameters {
		int Start;
		int NumColumnsRows;
		int Space;
	};
}

class CellGrid {
	Parameters X;
	Parameters Y;
public:

	void setXParameters(int start, int numColumns, int space);

	void setYParameters(int start, int numRows, int space);
};

