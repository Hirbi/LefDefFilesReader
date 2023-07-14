#pragma once
#include <vector>

#include "Port/Port.h"


class Pin
{
private:
    std::string name;
    std::string direction;
    std::string use;
    std::string shape;
    std::vector<Port> ports;
    std::string net;
    bool special;
public:
    void addPort(Port port);
    void setDirection(std::string direction);
    void setUse(std::string use);
    void setShape(std::string shape);
    void setSpecial(bool isIt);
    void setName(const std::string& name);
    std::string getName();
    void setNet(const std::string& value);
};

