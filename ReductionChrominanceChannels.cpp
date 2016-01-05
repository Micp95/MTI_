#include"ReductionChrominanceChannels.h"
#include"PPMFile.h"
#include"RAWFile.h"
#include<string>
#include<fstream>

using namespace std;

void ReductionChrominanceChannels::Save() {

	RAWFile<float> stream;
	int size = ppmToRead.width * ppmToRead.high * 3;
	float * buffer = new float[size];

	int counter = 0;
	for (int x = 0; x < ppmToRead.width; x++) {
		for (int y = 0; y < ppmToRead.high; y++) {
			buffer[counter++] = *outputBitmap[x][y].Y;
			buffer[counter++] = *outputBitmap[x][y].U;
			buffer[counter++] = *outputBitmap[x][y].V;
		}
	}

	stream.Zapis(nameToSave,buffer,size);

}

void ReductionChrominanceChannels::ReduceChrominance(string method) {
	PixelOnFloats theSame;
	
	if (method == "4:1:1") {	//co czwarta kolumna, co czwarty wiersz

		for (int x = 0; x < ppmToRead.width; x += 4) {	//co czwarta kolumna
			for (int y = 0; y < ppmToRead.high; y++) {

				//wypelniamy pixelem, konwersja dla jednego pixela
				if (y % 4 == 0) {
					theSame = ConvertRGBtoYUV(ppmToRead.GetPixel(x, y));
					outputBitmap[x][y].Set(*theSame.Y, *theSame.U, *theSame.V);
				}
				else
					outputBitmap[x][y].Set(*theSame.Y, *theSame.U, *theSame.V);

				//czy nie wychodzimy za obrazek && uzupelniamy kolejne trzy
				for (int i = x + 1; i < ppmToRead.width && i < x + 4; i++) {
					outputBitmap[i][y].Set(*theSame.Y, *theSame.U, *theSame.V);
				}
			}
		}

	}

	else if(method == "4:2:0"){	//co druga kolumna, co czwarty wiersz

		for (int y = 0; y < ppmToRead.high; y++) {	//co czwraty wiersz
			for (int x = 0; x < ppmToRead.width; x++ ) {	
			
				//wypelniamy pixelem, konwersja dla jednego pixela
				if (x % 2 == 0) {
					theSame = ConvertRGBtoYUV(ppmToRead.GetPixel(x, y));
					outputBitmap[x][y].Set(*theSame.Y, *theSame.U, *theSame.V);
				}
				else
					outputBitmap[x][y].Set(*theSame.Y, *theSame.U, *theSame.V);

				//czy nie wychodzimy za obrazek && uzupelniamy kolejne trzy
				for (int i = x + 1; i < ppmToRead.width && i < x + 4; i++) {
					outputBitmap[i][y].Set(*theSame.Y, *theSame.U, *theSame.V);
				}
			}
		}
	}

	else if(method == "4:2:2") {	//co czwarta kolumna, co drugi wiersz

		for (int x = 0; x < ppmToRead.width; x += 4) {	//co czwarta kolumna
			for (int y = 0; y < ppmToRead.high; y++) {	

				//wypelniamy pixelem, konwersja dla jednego pixela
				if (y % 2 == 0) {
					theSame = ConvertRGBtoYUV(ppmToRead.GetPixel(x, y));
					outputBitmap[x][y].Set(*theSame.Y, *theSame.U, *theSame.V);
				}
				else
					outputBitmap[x][y].Set(*theSame.Y, *theSame.U, *theSame.V);

				//czy nie wychodzimy za obrazek && uzupelniamy kolejne trzy
				for (int i = x+1; i < ppmToRead.width && i < x+4; i++) {
					outputBitmap[i][y].Set(*theSame.Y, *theSame.U, *theSame.V);
				}
			}
		}
	}

	else if(method == "4:4:4") {	//co gruga kolumna, co drugi wiersz

		for (int x = 0; x < ppmToRead.width; x+=2) {	//co druga kolumna
			for (int y = 0; y < ppmToRead.high; y++) {

				//wypelniamy pixelem, konwersja dla jednego pixela
				if (y % 2 == 0) {
					theSame = ConvertRGBtoYUV(ppmToRead.GetPixel(x, y));
					outputBitmap[x][y].Set(*theSame.Y, *theSame.U, *theSame.V);
				}
				else
					outputBitmap[x][y].Set(*theSame.Y, *theSame.U, *theSame.V);

				//czy nie wychodzimy za obrazek
				if(x <= ppmToRead.width)
					outputBitmap[x + 1][y].Set(*theSame.Y, *theSame.U, *theSame.V);

			}
		}
	}

	else if(method == "4:4:0") {	//co jedna kolumna, co dwa wiersze

		for (int x = 0; x < ppmToRead.width; x++) {	//co jedna kolumna
			for (int y = 0; y < ppmToRead.high; y++) {

				//wypelniamy pixelem, konwersja dla jednego pixela
				if (y % 2 == 0) {
					theSame = ConvertRGBtoYUV(ppmToRead.GetPixel(x, y));
					outputBitmap[x][y].Set(*theSame.Y, *theSame.U, *theSame.V);
				}
				else
					outputBitmap[x][y].Set(*theSame.Y, *theSame.U, *theSame.V);
			}
		}
		
	}

	else {
		cout << "\nyou did it wrong!\n";
		return;
	}
	
}

void ReductionChrominanceChannels::ConvertAllToRGB() {

	RAWFile<char> stream;

	int size = ppmToRead.width * ppmToRead.high * 3;
	char * buffer = new char[size];
	Pixel tmp;

	int counter = 0;
	for (int x = 0; x < ppmToRead.width; x++) {
		for (int y = 0; y < ppmToRead.high; y++) {
			tmp = ConvertYUVtoRGB(outputBitmap[x][y]);

			buffer[counter++] = *tmp.R;
			buffer[counter++] = *tmp.G;
			buffer[counter++] = *tmp.B;
		}
	}

	stream.Zapis(nameToSave, buffer, size);

}

PixelOnFloats ReductionChrominanceChannels::ConvertRGBtoYUV(Pixel & pix) {
	PixelOnFloats outPix;

	*outPix.Y = 0.299 * *pix.R + 0.587 * *pix.G + 0.114 * *pix.B;
	*outPix.U = -0.1687 * *pix.R - 0.3313 * *pix.G + 0.5 * *pix.B + 128;
	*outPix.V = 0.5 * *pix.R - 0.4187 * *pix.G - 0.0813 * *pix.B + 128;

	return outPix;
}

Pixel ReductionChrominanceChannels::ConvertYUVtoRGB(PixelOnFloats & pix) {
	Pixel outPix;
	outPix.R = new char;
	outPix.G = new char;
	outPix.B = new char;

	*outPix.R = *pix.Y + 1.402 * (*pix.V - 128);
	*outPix.G = *pix.Y - 0.34414 * (*pix.U - 128) - 0.71414 * (*pix.V - 128);
	*outPix.B = *pix.Y + 1.772 * (*pix.V - 128);

	return outPix;
}

ReductionChrominanceChannels::ReductionChrominanceChannels(string input, string output) : nameOfFile(input), nameToSave(output), ppmToRead(input) {
	ppmToRead.LoadFile();

	outputBitmap = new PixelOnFloats *[ppmToRead.width];
	for (int i = 0; i < ppmToRead.width; i++)
		outputBitmap[i] = new PixelOnFloats[ppmToRead.high];
};