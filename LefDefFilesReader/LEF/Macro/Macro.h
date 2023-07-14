#pragma once
#include <unordered_map>
#include <vector>

#include "OBS/OBS.h"
#include "Param/MacroParam.h"
#include "Pin/Pin.h"

class Macro
{
private:
    std::string name;
    //std::unordered_map<std::string, MacroParam> macroParams;
    //std::vector<MacroParam> macroParams;
    //MacroParam macroParam;
    std::unordered_map<std::string, Pin> pins;
    OBS obs;

public:

    void addMacroParam(MacroParam macroParam);
    void addPin(Pin pin);
    void setOBS(OBS obs);
    void setName(std::string name);

};

