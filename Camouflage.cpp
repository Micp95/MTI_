#include "Camouflage.h"
#include <stdio.h>
#include <Windows.h>
#include <iostream>
#include <fstream>

namespace _Camouflage
{

	ACamo::ACamo()
	{
		
	}
	ACamo::~ACamo()
	{

	}
	RAWFile<float> ACamo::MaskFreq(float max,float min)
	{
		fstream do_wykresu;
		do_wykresu.open("_pliki\\dane.txt", ios::out);
		RAWFile<float> plik;
		float* binarny = (plik.Wczytaj("_pliki\\test.raw"));
		float temp = 0;
		
		long size = plik.GetSize();

		for (int i = 0; i < size; i++)
		{
			if ((binarny[i] < max && binarny[i] > 0) ||( binarny[i] > min && binarny[i] < 0))
			{
				for (int j = 0; j < 30; j++)
				{
					if (i + j < size) binarny[i + j] = 0;
					if (i - j > 0) binarny[i - j] = 0;
				}
			}
			
		}
	
		
		for (int i = 0; i < size; i++)
		{
			do_wykresu << plik.dane[i] << endl;
		}
		plik.Zapis("_pliki\\przerobionyFreq.raw");
		return plik;
	}

	RAWFile<float> ACamo::MaskTime(float max, float min)
	{
		fstream do_wykresu;
		do_wykresu.open("_pliki\\dane.txt", ios::out);
		RAWFile<float> plik;
		float* binarny = (plik.Wczytaj("_pliki\\test.raw"));
		float temp = 0;
		long size = plik.GetSize();
		float freq = 44100;
		float timeMask = freq * 0.001;

		for (int i = 0; i < size; i++)
		{
			if ((binarny[i] > max && binarny[i] > 0) || (binarny[i] < min && binarny[i] < 0)) 
			{
				for (int j = 0; j < timeMask * 15; j++) //Maskowanie w przod
				{
					if ((binarny[i + j] < max && binarny[i + j] > 0) || (binarny[i + j] > min && binarny[i + j] < 0))
					{
						if ((i + j) < size)
						{
							binarny[i + j] = binarny[i + j] /4;
							
						}
					}
				}
				for (int j = 0; j < timeMask * 2; j++) //Maskowanie w tyl
				{
					if ((binarny[i - j] < max && binarny[i - j] > 0) || (binarny[i - j] > min && binarny[i - j] < 0)) //sprawdzenie czy kolejna probka miesci sie w wymogu
					{
						if ((i - j) > 0) 
						{ 
							binarny[i - j] = binarny[i - j] / 4;
						}
					}
				}
			}
			
		}
		for (int i = 0; i < size; i++)
		{
			do_wykresu << plik.dane[i] << endl;
		}
		plik.Zapis("_pliki\\przerobionyTime.raw");
		return plik;
	}
}