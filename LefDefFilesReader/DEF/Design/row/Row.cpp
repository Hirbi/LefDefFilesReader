#include "Row.h"

Row::Row() {
}

void Row::SetName(string& value) {
    Name = value;
}

const string& Row::GetName() const
{
    return Name;
}

void Row::SetSiteName(const string& value) {
    SiteName = value;
}

const string& Row::GetSiteName() const {
    return SiteName;
}

void Row::SetOrig(int first, int second) {
    Orig.first = first;
    Orig.second = second;
}

const Pair& Row::GetOrig() const
{
    return Orig;
}

void Row::SetSiteOrient(const string& value) {
    SiteOrient = value;
}

const string& Row::GetSiteOrient() const {
    return SiteOrient;
}

void Row::SetNum(int first, int second) {
    Num.first = first;
    Num.second = second;
}

const Pair& Row::GetNum() const
{
    return Num;
}

void Row::SetStep(int first, int second) {
    Step.first = first;
    Step.second = second;
}

const Pair& Row::GetStep() const
{
    return Step;
}
