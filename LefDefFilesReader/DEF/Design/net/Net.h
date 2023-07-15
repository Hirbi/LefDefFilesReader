#pragma once

#include <string>
#include <vector>

using namespace std;

class Net {
protected:
	string Name;
	vector<pair<string, string> > CompPinNames;
	string Use;
public:

	void SetName(const string& value);
	const string& GetName() const;

	void SetUse(const string& value);
	const string& GetUse() const;

	void AddCompPinName(const pair<string, string>& value);
	void AddCompPinName(const string& componentPattern, const string& pinName);
	const vector <pair<string, string> >& GetCompPatternPinNames() const;
};

