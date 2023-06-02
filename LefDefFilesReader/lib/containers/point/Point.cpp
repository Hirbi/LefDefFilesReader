#include "Point.h"

Point::Point(const int first, const int second) :
	First(first), Second(second) {
}

Point::Point(const Point& value) {
	First = value.First;
	Second = value.Second;
}

void Point::SetFirst(const int value) {
	First = value;
}

void Point::SetSecond(const int value) {
	Second = value;
}

int Point::GetFirst(const int value) const {
	return First;
} 

int Point::GetSecond(const int value) const {
	return Second;
}
