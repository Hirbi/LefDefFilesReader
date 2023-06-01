#pragma once

#include "../DEF/Design/Design.h"

#include <string>
#include <unordered_map>

using namespace std;

class Objects {
	unordered_map <string, Design> Designs;

public:
	Objects();

	void AddDesign(const string& key, const Design& value);
	
	bool IsDesignExists(const string& key) const;

	const Design& GetDesign(const string& key) const;

	const Design& GetOrCreateDesign(const string& key);
};

