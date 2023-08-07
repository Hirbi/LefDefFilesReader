#include "DEF/DefReader.h"
#include "lib/functions/functions.h"
#include "objects/Objects.h"

#include <ctime>
#include <iostream>
#include <string>

using namespace std;


int main() {
	unsigned int count = 100;
	unsigned int sum = 0;
	for (unsigned int i = 0; i < count; i++) {
		Objects objs;
		const string defFile = "data/lut_s44.def";
		const string defFile2 = "data/test2.def";
		DefReader defReader;

		unsigned int start_time = clock();
		defReader.ReadData(defFile, objs);
		unsigned int end_time = clock();
		unsigned int search_time = end_time - start_time;
		std::cout << search_time << " ";
		sum += search_time;
	}
	cout << "\nmid= " << sum * 1.0 / count;
}