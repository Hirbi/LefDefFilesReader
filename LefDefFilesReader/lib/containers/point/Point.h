#pragma once

class Point {
public:
	double First;
	double Second;

	Point(const double first = 0.0, const double second = 0.0);
	Point(const Point& value);

	void SetFirst(const double value);
	void SetSecond(const double value);

	double GetFirst(const double value) const;
	double GetSecond(const double value) const;

};

