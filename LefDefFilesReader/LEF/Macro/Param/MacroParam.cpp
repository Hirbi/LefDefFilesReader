#include "MacroParam.h"

#include <cassert>
#include <iostream>
#include <unordered_map>

void MacroParam::setType(std::string type)
{
    this->type = type;
}

void MacroParam::setForeign(std::string Foreign)
{
    this->parameter.Foreign = Foreign;
    this->type = "Foreign";
}

void MacroParam::setClass(std::string Class)
{
    this->parameter.Class = Class;
    this->type = "Class";
}

void MacroParam::setSymmetry(std::string Symmetry)
{
    this->parameter.Symmetry = Symmetry;
    this->type = "Symmetry";
}

void MacroParam::setSite(std::string Site)
{
    this->parameter.Site = Site;
    this->type = "Site";
}

void MacroParam::setOrigin(Point Origin)
{
    this->parameter.Origin = Origin;
    this->type = "Origin";
}

void MacroParam::setSize(Point Size)
{
    this->parameter.Size = Size;
    this->type = "Size";
}

std::string MacroParam::getType()
{
    return this->type;
}

MacroParam& MacroParam::operator=(MacroParam& macroParam)
{
    static const int
        CLASS = 2,
        FOREIGN = 3,
        ORIGIN = 4,
        SIZE = 5,
        SYMMETRY = 6,
        SITE = 7,
        PIN = 8,
        END = 9;

    static const std::unordered_map<std::string, int> KEY_WORDS{
        { "CLASS", 2 },
        { "FOREIGN", 3 },
        { "ORIGIN", 4 },
        { "SIZE", 5 },
        { "SYMMETRY", 6 },
        { "SITE", 7 },
    };
    auto it = KEY_WORDS.find(macroParam.type);
    if (it == KEY_WORDS.end()) {
        std::cout << "Cant find word: " << macroParam.type << "\n";
        assert(0);
    }
    switch (it->second)
    {

    case FOREIGN:
        parameter.Foreign = macroParam.parameter.Foreign;
        break;
    case CLASS:
        parameter.Class = macroParam.parameter.Class;
        break;
    case SYMMETRY:
        parameter.Symmetry = macroParam.parameter.Symmetry;
        break;
    case ORIGIN:
        parameter.Origin = macroParam.parameter.Origin;
        break;
    case SIZE:
        parameter.Size = macroParam.parameter.Size;
        break;
    case SITE:
        parameter.Site = macroParam.parameter.Site;
        break;
    }
    type = macroParam.getType();
    return *this;
}