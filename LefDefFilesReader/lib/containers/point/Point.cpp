#include "Point.h"

Point::Point(double First, double Second) :
	First(First), Second(Second) {
}

void Point::SetFirst(double value) {
	First = value;
}

void Point::SetSecond(double value) {
	Second = value;
}

double Point::GetFirst(double value)
{
	return First;
}

double Point::GetSecond(double value)
{
	return Second;
}
