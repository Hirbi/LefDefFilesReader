#pragma once
#include <string>
#include "../../../lib/containers/point/Point.h"

union Param {
    std::string Foreign;
    std::string Class;
    std::string Symmetry;
    std::string Site;
    Point Origin;
    Point Size;


    Param() {}

    ~Param() {}
};

class MacroParam
{
private:

    Param parameter;
    std::string type;

public:

    void setType(std::string Foreign);
    void setForeign(std::string Foreign);
    void setClass(std::string Class);
    void setSymmetry(std::string Symmetry);
    void setSite(std::string Site);
    void setOrigin(Point Origin);
    void setSize(Point Size);

    std::string getType();

    MacroParam& operator=(MacroParam& macroParam);
};

