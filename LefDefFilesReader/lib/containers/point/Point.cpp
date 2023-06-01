#include "Point.h"

Point::Point(const double first, const double second) :
	First(first), Second(second) {
}

Point::Point(const Point& value) {
	First = value.First;
	Second = value.Second;
}

void Point::SetFirst(const double value) {
	First = value;
}

void Point::SetSecond(const double value) {
	Second = value;
}

double Point::GetFirst(const double value) const {
	return First;
} 

double Point::GetSecond(const double value) const {
	return Second;
}
