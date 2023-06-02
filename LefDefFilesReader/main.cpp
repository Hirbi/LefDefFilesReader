#include "DEF/DefReader.h"
#include "lib/functions/functions.h"
#include "objects/Objects.h"

#include <ctime>
#include <iostream>
#include <string>

using namespace std;


int main() {
	Objects objs;
	const string defFile = "data/lut_s44.def";
	DefReader defReader;
	
	unsigned int start_time = clock();
	defReader.ReadData(defFile, objs);
	unsigned int end_time = clock();
	unsigned int search_time = end_time - start_time;
	std::cout << "Read time: " << search_time << "\n\n";
}