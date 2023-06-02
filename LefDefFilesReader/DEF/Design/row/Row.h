#pragma once

#include <string>

using namespace std;

using Pair = pair<int, int>;

class Row {
	// main options
	string Name;
	string SiteName;
	Pair Orig;
	string SiteOrient;
	// optional
	Pair Num;
	Pair Step;
public:
	Row();

	void SetName(string& value);
	const string& GetName() const;

	void SetSiteName(const string& value);
	const string& GetSiteName() const;

	void SetOrig(int first, int second);
	const Pair& GetOrig() const;

	void SetSiteOrient(const string& value);
	const string& GetSiteOrient() const;

	void SetNum(int first, int second);
	const Pair& GetNum() const;

	void SetStep(int first, int second);
	const Pair& GetStep() const;
};

