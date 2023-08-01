#pragma once

#include "../lib/containers/rect/Rect.h"
#include "../lib/containers/point/Point.h"

#include <vector>
#include <string>
#include <variant>

struct Resistance {
public:
    std::string type;
    double value;

};
struct Capacitance {
public:
    std::string type;
    double value;
};
struct SpacingTable {
    int parallelRunLength;
    std::vector<Point> widths;
};
struct Enclosure {
    std::string type;
    Point point;
};


//Variants structs
struct Param {
    std::variant<double, std::string, Point, Resistance, Capacitance, SpacingTable, Enclosure, Rect> num;
    std::string type;
};


//LEFParams structs
struct Units {
public:
    int timeValue;
    int resistanceValue;
    int capacitanceValue;
    int dataBaseValue;
    std::string timeUnit;
    std::string resistanceUnit;
    std::string capacitanceUnit;
    std::string dataBaseUnit;
};
struct PropertyDefinition {
    std::string layer;
    std::string type;
};
struct SiteProperty {
    std::string name;
    std::vector<Param> params;
};
struct LayerProperty {
    std::string name;
    std::vector<Param> params;
};
struct Via {
    std::string name;
    std::string type;
    std::vector<std::string> layers;
    std::vector<Param> params;
};
struct ViaRule {
    std::string name;
    std::string type;
    std::vector<std::string> layers;
    std::vector<Param> params;
};


//LayerProperty params

struct DCCurrentDensity {
    std::string type;
    double value;
};
struct ACCurrentDensity {
    std::string type;
    double value;
};
//struct AntennaDiffRatio{};
//struct AntennaDiffSideAreaRatio{};


//Macro structs
struct Layer {
public:
    std::string name;
    std::vector <Rect> rects;
};
struct Obs {
public:
    std::vector <Layer> layers;
};
struct Port {
public:
    std::vector<Layer> layers;
};
struct Pin {
public:
    std::string name;
    std::vector <Param> params;
    Port port;
};
struct Macro {
public:
    std::string name;
    std::vector<Param> params;
    std::vector<Pin> pins;
    std::vector<Obs> obss;
};



struct LEF {
public:
    Units units;
    std::vector<Param> params;
    std::vector<Via> vias;
    std::vector<ViaRule> viaRules;
    std::vector<SiteProperty> siteProperties;
    std::vector<LayerProperty> layerProperties;
    std::vector<Macro> macros;
    std::vector<PropertyDefinition> propertyDefinitions;
};