#pragma once

#include "../../../lib/containers/point/Point.h"
#include "../../../lib/containers/rect/Rect.h"

#include <string>

using namespace std;

namespace {
	struct VLayers {
		string BotMetalLayer;
		string CutLayer;
		string TopMetalLayer;
	};
}

class Via {
	string ViaName;
	string ViaRule;
	Point CutSize;
	VLayers ViaLayers;
	Point CutSpacing;
	Rect Enclosure; //  xBotEnc yBotEnc xTopEnc yTopEnc
	// optional
	Point RowCol;

public:
	Via();

	void SetViaName(const string& value);
	const string& SetViaName() const;

	void SetViaRule(const string& value);
	const string& SetViaRule() const;

	void SetCutSize(const int first, const int second);
	const Point& GetCutSize() const;

	void SetViaLayers(const string& botMetalLayer, const string& cutLayer, const string& topMetalLayer);
	const VLayers& GetViaLayers() const;

	void SetCutSpacing(const int first, const int second);
	const Point& GetCutSpacing() const;

	void SetEnclosure(const int xFirst, const int xSecond, const int yFirst, const int ySecond);
	const Rect& GetEnclosure() const;

	void SetRowCol(const int first, const int second);
	const Point& GetRowCol() const;
};

