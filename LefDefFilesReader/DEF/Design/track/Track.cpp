#include "Track.h"

Track::Track() {
}

void Track::SetDirection(const char value) {
	Direction = value;
}

const char Track::GetDirection() const
{
	return Direction;
}

void Track::SetStart(const int value) {
	Start = value;
}

const int Track::GetStart() const {
	return Start;
}

void Track::SetNumTracks(const int value) {
	NumTracks = value;
}

const int Track::GetNumTracks() const
{
	return NumTracks;
}

void Track::SetSpace(const int value) {
	Space = value;
}

const int Track::GetSpace() const
{
	return Space;
}

void Track::AddLayer(const string& value) {
	Layers.push_back(value);
}

const vector<string>& Track::GetLayers() const
{
	return Layers;
}
