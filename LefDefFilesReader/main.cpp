#include "DEF/DefReader.h"
#include "lib/functions/functions.h"
#include "objects/Objects.h"

#include <iostream>
#include <string>

using namespace std;


int main() {
	Objects objs;
	const string defFile = "data/lut_s44.def";
	DefReader defReader;
	defReader.ReadData(defFile, objs);
}