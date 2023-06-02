#pragma once

#include <string>
#include <vector>

using namespace std;

class Track {
	char Direction; // x or y -> can use bool
	int Start;
	int NumTracks;
	int Space;
	vector <string> Layers;
public:

	Track();

	void SetDirection(const char value);
	const char GetDirection() const;

	void SetStart(const int value);
	const int GetStart() const;

	void SetNumTracks(const int value);
	const int GetNumTracks() const;

	void SetSpace(const int value);
	const int GetSpace() const;

	void AddLayer(const string& value);
	const vector<string>& GetLayers() const;
};

