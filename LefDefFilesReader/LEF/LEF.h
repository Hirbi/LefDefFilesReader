#pragma once

#include "../lib/containers/types.h"

#include <vector>
#include <string>
#include <variant>

using namespace LefPrimitiveTypes;



struct Param {
    std::variant<double, std::string, Point, Resistance, Capacitance,
        SpacingTable, Enclosure, Rect, DCCurrentDensity, ACCurrentDensity> num;
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