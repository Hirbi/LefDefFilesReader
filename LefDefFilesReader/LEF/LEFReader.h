#pragma once
#include <string>
#include "LEF.h"

class LEFReader
{
private:

    Macro readMacro(std::ifstream& fis, std::string& word);
    Pin readPin(std::ifstream& fis, std::string& word);
    Obs readObs(std::ifstream& fis, std::string& word);
    Port readPort(std::ifstream& fis, std::string& word);
    Layer readLayer(std::ifstream& fis, std::string& word);
    Units readUnits(std::ifstream& fis, std::string& word);
    std::vector<PropertyDefinition> readPropertyDefinitions(std::ifstream& fis, std::string& word);
    SiteProperty readSiteProperties(std::ifstream& fis, std::string& word);
    LayerProperty readLayerProperties(std::ifstream& fis, std::string& word);
    SpacingTable readSpacingTable(std::ifstream& fis, std::string& word);
    Via readVia(std::ifstream& fis, std::string& word);
    ViaRule readViaRule(std::ifstream& fis, std::string& word);


public:

    LEF readLEF(std::string fileName);
};

