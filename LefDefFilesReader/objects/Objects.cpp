#include "Objects.h"

Objects::Objects() {
}

void Objects::AddDesign(const string& key, const Design& value) {
	Designs.insert(std::pair<string, Design> {key, value});
}

bool Objects::IsDesignExists(const string& key) const {
	return Designs.find(key) != Designs.end();
}

const Design& Objects::GetDesign(const string& key) const {
	auto it = Designs.find(key);
	if (it == Designs.end()) {
		return Design();
	}
	return it->second;
}

const Design& Objects::GetOrCreateDesign(const string& key) {
	auto it = Designs.find(key);
	if (it == Designs.end()) {
		AddDesign(key, Design());
		return Designs.at(key);
	}
	return it->second;
}
