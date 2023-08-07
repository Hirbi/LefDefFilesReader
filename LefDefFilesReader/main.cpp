#include "DEF/DefReader.h"
#include "LEF/LEFReader.h"
#include "lib/functions/functions.h"
#include "objects/Objects.h"

#include <ctime>
#include <iostream>
#include <string>

using namespace std;


int main() {
	// Def 
	Objects objs;
	const string defFile = "data/lut_s44.def";
	const string defFile2 = "data/test2.def";
	DefReader defReader;

	unsigned int start_time = clock();
	defReader.ReadData(defFile, objs);
	unsigned int end_time = clock();
	unsigned int search_time = end_time - start_time;
	std::cout << search_time << " ";

	// Lef
    LEFReader reader;
    LEF lef;
    start_time = clock();
    lef = reader.readLEF("data/merged_nom.lef");
    end_time = clock();
    search_time = end_time - start_time;
    std::cout << "Read time: " << search_time << "\n\n";
    cout << "suc";
}