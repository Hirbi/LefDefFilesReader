#pragma once
#include <string>
#include <vector>
#include "../rect/Rect.h"

class Layer
{
private:
    std::string name;
    std::vector<Rect> rects;
public:

    void addRect(Rect& rect);
    void setName(std::string name);

    std::string getName();
};

