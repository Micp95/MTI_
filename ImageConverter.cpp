#include "ImageConverter.h"

#include <iostream>
#include <string>

#include <windows.h>
#include <gdiplus.h>
#include <stdio.h>

#pragma warning(disable:4996)
#pragma comment(lib, "gdiplus.lib")

using namespace Gdiplus;
using namespace std;

ImageConverter::ImageConverter(){

}

ImageConverter::~ImageConverter(){

}


//Funkcja pomocnicza do konwersji ppm do bitmapy
 HBITMAP ImageConverter::Create8bppBitmap(HDC hdc, int width, int height, LPVOID pBits )
{
	BITMAPINFO *bmi = (BITMAPINFO *)malloc(sizeof(BITMAPINFOHEADER) + sizeof(RGBQUAD) * 256);
	BITMAPINFOHEADER &bih(bmi->bmiHeader);
	bih.biSize = sizeof(BITMAPINFOHEADER);
	bih.biWidth = width;
	bih.biHeight = -height;
	bih.biPlanes = 1;
	bih.biBitCount = 8;
	bih.biCompression = BI_RGB;
	bih.biSizeImage = 0;
	bih.biXPelsPerMeter = 14173;
	bih.biYPelsPerMeter = 14173;
	bih.biClrUsed = 0;
	bih.biClrImportant = 0;
	for (int I = 0; I <= 255; I++)
	{
		bmi->bmiColors[I].rgbBlue = bmi->bmiColors[I].rgbGreen = bmi->bmiColors[I].rgbRed = (BYTE)I;
		bmi->bmiColors[I].rgbReserved = 0;
	}

	void *Pixels = NULL;
	HBITMAP hbmp = CreateDIBSection(hdc, bmi, DIB_RGB_COLORS, &Pixels, NULL, 0);

	if (pBits != NULL)
	{
		//fill the bitmap
		BYTE* pbBits = (BYTE*)pBits;
		BYTE *Pix = (BYTE *)Pixels;
		memcpy(Pix, pbBits, width * height);
	}

	free(bmi);

	return hbmp;
}

//Konwersja danych ppm do bitmapy
 HBITMAP ImageConverter::CreateBitmapFromPixels(HDC hDC, UINT uWidth, UINT uHeight, UINT uBitsPerPixel, LPVOID pBits)
{
	if (uBitsPerPixel < 8)
		return NULL;

	if (uBitsPerPixel == 8)
		return Create8bppBitmap(hDC, uWidth, uHeight, pBits);

	HBITMAP hBitmap = 0;
	if (!uWidth || !uHeight || !uBitsPerPixel)
		return hBitmap;
	LONG lBmpSize = uWidth * uHeight * (uBitsPerPixel / 8);
	BITMAPINFO bmpInfo = { 0 };
	bmpInfo.bmiHeader.biBitCount = uBitsPerPixel;
	bmpInfo.bmiHeader.biHeight = uHeight;
	bmpInfo.bmiHeader.biWidth = uWidth;
	bmpInfo.bmiHeader.biPlanes = 1;
	bmpInfo.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	// Pointer to access the pixels of bitmap
	UINT * pPixels = 0;
	hBitmap = CreateDIBSection(hDC, (BITMAPINFO *)&
		bmpInfo, DIB_RGB_COLORS, (void **)&
		pPixels, NULL, 0);

	if (!hBitmap)
		return hBitmap; 

	memcpy(pPixels, pBits, lBmpSize);

	return hBitmap;
}


int ImageConverter::Convert(string input, string output, int pam) {
	//sprawdzenie formatow
	int kropka = input.find_last_of('.');
	string forminp = input.substr(kropka+1);
	kropka = output.find_last_of('.');
	string formout = output.substr(kropka+1);

	if (forminp == "ppm" && formout == "bmp" ){		//jesli ppm to specjalna funkcja
		PPMFile plik(input);
		plik.LoadFile();
		PPMtoBMP(plik,output);
	}		
	else 
		Conversion(input, output, "image/" + formout, pam);
	
	return 0;
}


void ImageConverter::PPMtoBMP(PPMFile& file, string nowy) {
	//Wczytanie parametrow obrazu
	unsigned int cx , cy;
	cx = file.width;
	cy = file.high;

	//Zmienne pomocnicze
	HDC hScreenDC = ::GetDC(NULL);
	HDC hdcNowy = CreateCompatibleDC(hScreenDC);


	//Wczytanie danych do bitmapy
	void* DateFIle = file.Transform();

	HBITMAP hBitmap = CreateBitmapFromPixels(hdcNowy,cx,cy,24, DateFIle);
	HBITMAP hOldBitmap = (HBITMAP)SelectObject(hdcNowy, hBitmap);
	delete[] DateFIle;

	//Ustawienie naglowkow
	size_t headerSize = sizeof(BITMAPINFOHEADER) + 3 * sizeof(RGBQUAD);
	BYTE* pHeader = new BYTE[headerSize];
	LPBITMAPINFO pbmi = (LPBITMAPINFO)pHeader;
	memset(pHeader, 0, headerSize);
	pbmi->bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	pbmi->bmiHeader.biBitCount = 0;
	if (!GetDIBits(hdcNowy, hBitmap, 0, 0, NULL, pbmi, DIB_RGB_COLORS))
		return;

	//Wczytywanie danych + uzupelnianie
	BITMAPFILEHEADER bmf;
	if (pbmi->bmiHeader.biSizeImage <= 0)
		pbmi->bmiHeader.biSizeImage = pbmi->bmiHeader.biWidth*abs(pbmi->bmiHeader.biHeight)*(pbmi->bmiHeader.biBitCount + 7) / 8;
	BYTE* pData = new BYTE[pbmi->bmiHeader.biSizeImage];
	bmf.bfType = 0x4D42; 
	bmf.bfReserved1 = bmf.bfReserved2 = 0;
	bmf.bfSize = sizeof(BITMAPFILEHEADER) + headerSize + pbmi->bmiHeader.biSizeImage;
	bmf.bfOffBits = sizeof(BITMAPFILEHEADER) + headerSize;
	if (!GetDIBits(hdcNowy, hBitmap, 0, abs(pbmi->bmiHeader.biHeight), pData, pbmi, DIB_RGB_COLORS))
	{
		delete pData;
		return;
	}

	//Zapis do pliku
	FILE* hFile = fopen(nowy.c_str(), "wb");
	fwrite(&bmf, sizeof(BITMAPFILEHEADER), 1, hFile);
	fwrite(pbmi, headerSize, 1, hFile);
	fwrite(pData, pbmi->bmiHeader.biSizeImage, 1, hFile);
	fclose(hFile);

	//Czyszczenie
	DeleteObject(hBitmap);
	DeleteDC(hdcNowy);
	delete[] pData;
}


int ImageConverter::Conversion(string input, string output, string format,int parm) {


	//konwersja na potrzebne typy
	wstring widestr = wstring(input.begin(), input.end());
	const wchar_t* name1 = widestr.c_str();

	wstring widestr2 = wstring(output.begin(), output.end());
	const wchar_t* name2 = widestr2.c_str();

	wstring widestr3 = wstring(format.begin(), format.end());
	const wchar_t* typ = widestr3.c_str();


	GdiplusStartupInput gdiplusStartupInput;
	ULONG_PTR gdiplusToken;
	GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);

	CLSID   encoderClsid;
	Status  stat;
	Image*   image = new Image(name1);
	

	//Znalezienie odpowiedniego dekodera
	GetEncoderClsid(typ, &encoderClsid);


	//Dostosowanie parametrow dekodera
	EncoderParameters parametr;
	ULONG quality = parm;


	if (format == "image/tiff") {
		if (parm == 1) {
			quality = EncoderValueCompressionLZW;	//Komprezla LZW
		}
		else
			quality = EncoderValueCompressionNone;	//Brak kompresji
		parametr.Parameter[0].Guid = EncoderCompression;
	}
	else
		parametr.Parameter[0].Guid =EncoderQuality;
	


	//Ustawienie parametrow
	parametr.Count = 1;
	parametr.Parameter[0].Type = EncoderParameterValueTypeLong;
	parametr.Parameter[0].NumberOfValues = 1;
	parametr.Parameter[0].Value = &quality;

	
	EncoderParameters* par = &parametr;

	//Jesli brak parametrow to zeruj
	if (parm == -1)
		par = NULL;

	//Generowanie pliku
	stat = image->Save(name2, &encoderClsid, par);

	//Sprawdzenie statusu bledy
	if (stat != Ok)
		printf("Failure: stat = %d\n", stat);


	//czyszczenie
	delete image;
	GdiplusShutdown(gdiplusToken);


	return 0;
}



int ImageConverter::GetEncoderClsid(const WCHAR* format, CLSID* pClsid)
{
	UINT  num = 0;          // number of image encoders
	UINT  size = 0;         // size of the image encoder array in bytes

	Gdiplus::ImageCodecInfo* pImageCodecInfo = NULL;

	Gdiplus::GetImageEncodersSize(&num, &size);
	if (size == 0)
		return -1;

	pImageCodecInfo = (Gdiplus::ImageCodecInfo*)(malloc(size));
	if (pImageCodecInfo == NULL)
		return -1;

	GetImageEncoders(num, size, pImageCodecInfo);

	for (UINT j = 0; j < num; ++j)
	{
		if (wcscmp(pImageCodecInfo[j].MimeType, format) == 0)
		{
			*pClsid = pImageCodecInfo[j].Clsid;
			free(pImageCodecInfo);
			return j;
		}
	}

	free(pImageCodecInfo);
	return -1;
}

