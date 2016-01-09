#pragma once

#ifndef IMAGECONVERTER_H
#define IMAGECONVERTER_H

#include <iostream>
#include <string>
#include "PPMFile.h"

#include <windows.h>
#include <gdiplus.h>
#include <stdio.h>


using namespace std;


class ImageConverter
{
public:
	ImageConverter();
	~ImageConverter();
	int Convert(string input, string output, int pam = -1);

private:
	void PPMtoBMP(PPMFile& file, string nowy);


	//int GetEncoderClsid(const WCHAR* format, CLSID* pClsid);
	static HBITMAP Create8bppBitmap(HDC hdc, int width, int height, LPVOID pBits = NULL);
	static HBITMAP CreateBitmapFromPixels(HDC hDC, UINT uWidth, UINT uHeight, UINT uBitsPerPixel, LPVOID pBits);
	int GetEncoderClsid(const WCHAR* format, CLSID* pClsid);

	int Conversion(string input, string output,string format, int parm = -1);
};
#endif
