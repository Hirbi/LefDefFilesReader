#pragma once
#include "../point/Point.h"

class Rect {
public:
	Point First;
	Point Second;

	Rect(int firstX = 0.0, int firstY = 0.0, int secondX = 0.0, int secondY = 0.0);
	Rect(Point& first, Point& second);
	Rect(const Rect& value);

	void SetFirst(const Point& value);
	void SetFirst(const int first, const int second);

	void SetSecond(const Point& value);
	void SetSecond(const int first, const int second);

	Point GetFirst() const;
	Point GetSecond() const;

};