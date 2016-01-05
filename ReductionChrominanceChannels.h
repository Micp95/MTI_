#ifndef REDUCTIONCHROMINANCECHANNELS_H
#define REDUCTIONCHROMINANCECHANNELS_H

#include<string>
#include"PPMFile.h"

using namespace std;


class ReductionChrominanceChannels {

public:
	ReductionChrominanceChannels(string input, string output);
	~ReductionChrominanceChannels() {};

private:
	string nameOfFile, nameToSave;
	PPMFile ppmToRead;
	PixelOnFloats** outputBitmap;
	PixelOnFloats ConvertRGBtoYUV(Pixel & pix);
	Pixel ConvertYUVtoRGB(PixelOnFloats & pix);

public:
	void ReduceChrominance(string method);
	void Save();
	void ConvertAllToRGB();

};


#endif
