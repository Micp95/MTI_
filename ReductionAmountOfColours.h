#ifndef REDUCTIONAMOUNTOFCOLOURS_H
#define REDUCTIONAMOUNTOFCOLOURS_H

#include<string>
#include"PPMFile.h"

using namespace std;

class ReductionAmountOfColours {
public:
	ReductionAmountOfColours(string input, string output) : nameOfFile(input), nameToSave(output), ppmToRead(input) {
		ppmToRead.LoadFile();
	}
	void ReduceColours();
	void Save();

private:
	string nameOfFile, nameToSave;
	PPMFile ppmToRead;
	
};


#endif
