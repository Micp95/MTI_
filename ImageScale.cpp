#include "ImageScale.h"

ConvertToGrey::ConvertToGrey(string namefile)
{
	PPMFile plik("_pliki\\" + namefile );
	plik.LoadFile();
	Pixel temp;

	for (int k = 0; k < plik.high; k++) {
		for (int j = 0; j < plik.width;j++)
		{
			temp = plik.GetPixel(j, k);

			int tempik = 0;
			tempik = (((int)*temp.B) * 0.114) + (((int)*temp.G) * 0.587) + (((int)*temp.R) * 0.299);
			plik.GetPixel(j, k).Set(tempik, tempik, tempik);
		}
	}
	plik.SaveFile("_pliki\\przerobiony_" + namefile);
}

ConvertToBaW::ConvertToBaW(string namefile)
{
	PPMFile plik("_pliki\\" + namefile );
	plik.LoadFile();
	Pixel temp;

	for (int k = 0; k < plik.high; k++) 
	{
		for (int j = 0; j < plik.width; j++)
		{
			temp = plik.GetPixel(j, k);

			int tempik = 0;
			tempik = (((int)*temp.B) * 0.114) + (((int)*temp.G) * 0.587) + (((int)*temp.R) * 0.299);
			if(tempik > 60) plik.GetPixel(j, k).Set(0, 0, 0);
			else plik.GetPixel(j, k).Set(255, 255, 255);
		}
	}
	plik.SaveFile("_pliki\\przerobiony2_" + namefile);
	
}
