#pragma once
#include <string>

#include "Macro/Macro.h"

class LEFReader
{
private:

    Macro readMacro(std::fstream& fis, std::string& word);
    void readPin(std::fstream& fis, std::string& word);
    void readPort(std::fstream& fis, std::string& word);
    void readLayer(std::fstream& fis, std::string& word);

public:

    void readLEF(std::string fileName);

};

