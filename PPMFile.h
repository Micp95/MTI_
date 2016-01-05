#pragma once
#ifndef PPMFILE_H
#define PPMFILE_H

#include <iostream>
#include <string>
#include <fstream>


using namespace std;

struct Pixel {
	char* R;
	char* G;
	char* B;
	Pixel():R(0),G(0),B(0){}
	Pixel(char*r,char*g,char*b) :R(r), G(g), B(b) {}
	void Set(char r, char g, char b) {
		if (R == 0)
			return;
		*R = r;
		*G = g;
		*B = b;
	}
	void Sets(char* B_, char* G_, char* R_) {
		B = B_;
		G = G_;
		R = R_;
	}
};

struct PixelOnFloats {
	float* U, *Y, *V;
	
	PixelOnFloats(){
		U = new float;
		Y = new float;
		V = new float;
	}
	PixelOnFloats(float*r, float*g, float*b) :U(r), Y(g), V(b) {}
	void Set(float r, float g, float b) {
		if (U == 0)
			return;
		*U = r;
		*Y = g;
		*V = b;
	}
	void Sets(float* B_, float* G_, float* R_) {
		U = B_;
		Y = G_;
		V = R_;
	}
};

class PPMFile
{
public:
	
	PPMFile(string name);
	~PPMFile();

	void LoadFile();
	void SaveFile(string name);

	Pixel& GetPixel(int x, int y);
	void* GetDate() { return (void*)date; }

	int width;
	int high;
	int max;
	void* Transform();

private:

	Pixel BadPixel;
	string FIleName;
	char* date;
	Pixel** arrs;
	long size;
	
	int LoadHeader(fstream& file);
	int LoadDate(int lhead);
	string CreateHeader();
	void CreateArrs();
	
	int err;
};




#endif