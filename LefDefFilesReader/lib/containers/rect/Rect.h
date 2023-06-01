#include "../point/Point.h"

class Rect {
public:
	Point First;
	Point Second;

	Rect(double firstX = 0.0, double firstY = 0.0, double secondX = 0.0, double secondY = 0.0);
	Rect(Point& first, Point& second);
	Rect(const Rect& value);

	void SetFirst(const Point& value);
	void SetFirst(const double first, const double second);

	void SetSecond(const Point& value);
	void SetSecond(const double first, const double second);

	Point GetFirst() const;
	Point GetSecond() const;

};