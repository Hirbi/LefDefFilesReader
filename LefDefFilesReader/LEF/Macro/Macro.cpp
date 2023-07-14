#include "Macro.h"

void Macro::addMacroParam(MacroParam macroParam)
{
    //this->macroParams.insert({ macroParam.getType(), macroParam });
    //this->macroParams.push_back(macroParam);
    //this->macroParam = macroParam;
    //TODO Как тебя ебать, как тебя ебать

void Macro::addPin(Pin pin)
{
    this->pins.insert({ pin.getName(), pin });
}

void Macro::setOBS(OBS obs)
{
    this->obs = obs;
}

void Macro::setName(std::string name)
{
    this->name = name;
}