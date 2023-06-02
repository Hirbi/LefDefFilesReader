#include "Rect.h"

Rect::Rect(int firstX, int firstY, int secondX, int secondY) :
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

void Rect::SetFirst(const int first, const int second) {
	First.First = first;
	First.Second = second;
}

void Rect::SetSecond(const Point& value) {
	Second = value;
}

void Rect::SetSecond(const int first, const int second) {
	Second.First = first;
	Second.Second = second;
}

Point Rect::GetFirst() const {
	return First;
}

Point Rect::GetSecond() const {
	return Second;
}

