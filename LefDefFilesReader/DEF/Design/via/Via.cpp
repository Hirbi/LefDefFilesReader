#include "Via.h"

Via::Via()
{
}

void Via::SetViaName(const string& value) {
	ViaName = value;
}

const string& Via::SetViaName() const {
	return ViaName;
}

void Via::SetViaRule(const string& value) {
	ViaRule = value;
}

const string& Via::SetViaRule() const {
	return ViaRule;
}

void Via::SetCutSize(const int first, const int second) {
	CutSize.First = first;
	CutSize.Second = second;
}

const Point& Via::GetCutSize() const {
	return CutSize;
}

void Via::SetViaLayers(const string& botMetalLayer, const string& cutLayer, const string& topMetalLayer) {
	ViaLayers.BotMetalLayer = botMetalLayer;
	ViaLayers.CutLayer = cutLayer;
	ViaLayers.TopMetalLayer = topMetalLayer;
}

const VLayers& Via::GetViaLayers() const {
	return ViaLayers;
}

void Via::SetCutSpacing(const int first, const int second) {
	CutSpacing.First = first;
	CutSpacing.Second = second;
}

const Point& Via::GetCutSpacing() const {
	return CutSpacing;
}

void Via::SetEnclosure(const int xFirst, const int xSecond, const int yFirst, const int ySecond) {
	Enclosure.First.First = xFirst;
	Enclosure.First.Second = xSecond;
	Enclosure.Second.First = yFirst;
	Enclosure.Second.Second = ySecond;
}

const Rect& Via::GetEnclosure() const {
	return Enclosure;
}

void Via::SetRowCol(const int first, const int second) {
	RowCol.First = first;
	RowCol.Second = second;
}

const Point& Via::GetRowCol() const {
	return RowCol;
}
