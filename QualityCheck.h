#pragma once

#include <cmath>
#include "PPMFile.h"
#include <string>

using namespace std;

class CheckQuality
{
	int width;
	int high;
public:
	CheckQuality(string,string);
	int LoadHeader(fstream& file);
};