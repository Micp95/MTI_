#include"ReductionAmountOfColours.h"
#include<string>
#include"PPMFile.h"
#include<iostream>

using namespace std;

void ReductionAmountOfColours::ReduceColours() {
	int tmp1 = 0, tmp2 = 0, tmp3 = 0;

	for (int x = 0; x < ppmToRead.width; x++) {
		for (int y = 0; y < ppmToRead.high; y++) {
			tmp1 = *ppmToRead.GetPixel(x, y).R / 32;
			tmp2 = *ppmToRead.GetPixel(x, y).G / 32;
			tmp3 = *ppmToRead.GetPixel(x, y).B / 32;

			ppmToRead.GetPixel(x, y).Set(tmp1, tmp2, tmp3);
		}
	}
}

void ReductionAmountOfColours::Save() {
	ppmToRead.max = 8;
	ppmToRead.SaveFile(nameToSave);
}