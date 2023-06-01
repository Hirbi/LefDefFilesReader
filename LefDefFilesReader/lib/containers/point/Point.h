#pragma once

class Point {
public:
	double First;
	double Second;

	Point(double First = 0.0, double Second = 0.0);

	void SetFirst(double value);
	void SetSecond(double value);

	double GetFirst(double value);
	double GetSecond(double value);

};

