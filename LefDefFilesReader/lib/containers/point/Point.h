#pragma once

class Point {
public:
	int First;
	int Second;

	Point(const int first = 0.0, const int second = 0.0);
	Point(const Point& value);

	void SetFirst(const int value);
	void SetSecond(const int value);

	int GetFirst(const int value) const;
	int GetSecond(const int value) const;

};
