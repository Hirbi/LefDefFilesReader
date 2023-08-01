#include <iostream>
#include "LEF/LEFReader.h"

using namespace std;


int main() {
    LEFReader reader;
    LEF lef;
    unsigned int start_time = clock();
    lef = reader.readLEF("data/merged_nom.lef");
    unsigned int end_time = clock();
    unsigned int search_time = end_time - start_time;
    std::cout << "Read time: " << search_time << "\n\n";
    cout << "suc";
    
}