#include "Net.h"

void Net::SetName(const string& value) {
    Name = value;
}

const string& Net::GetName() const {
    return Name;
}

void Net::SetUse(const string& value) {
    Use = value;
}

const string& Net::GetUse() const {
    return Use;
}

void Net::AddCompPinName(const pair<string, string>& value) {
    CompPinNames.push_back(value);
}

void Net::AddCompPinName(const string& component, const string& pinName) {
    CompPinNames.push_back(pair<string, string> {component, pinName});
}

const vector<pair<string, string>>& Net::GetCompPatternPinNames() const {
    return CompPinNames;
}
