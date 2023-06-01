#include "Rect.h"

Rect::Rect(double firstX, double firstY, double secondX, double secondY) :
	First(firstX, firstY), Second(secondX, secondY) 
{}

Rect::Rect(Point& first, Point& second) :
	First(first), Second(second)
{}

Rect::Rect(const Rect& value) :
	First(value.First), Second(value.Second)
{}

void Rect::SetFirst(const Point & value) {
	First = value;
}

void Rect::SetFirst(const double first, const double second) {
	First.First = first;
	First.Second = second;
}

void Rect::SetSecond(const Point& value) {
	Second = value;
}

void Rect::SetSecond(const double first, const double second) {
	Second.First = first;
	Second.Second = second;
}

Point Rect::GetFirst() const {
	return First;
}

Point Rect::GetSecond() const {
	return Second;
}

