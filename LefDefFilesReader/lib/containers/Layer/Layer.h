#pragma once
#include <string>
#include <vector>
#include "../rect/Rect.h"

// TODO: Change folder for Layer
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

