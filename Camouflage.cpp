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
	RAWFile<float> ACamo::MaskFreq(float roz)
	{
		fstream do_wykresu;
		do_wykresu.open("_pliki\\dane.txt", ios::out);
		RAWFile<float> plik;
		float* binarny = (plik.Wczytaj("_pliki\\test.raw"));
		float temp = 0;
		
		long size = plik.GetSize();

		for (int i = 0; i < size; i++)
		{
			temp = binarny[i] - binarny[i + 1];
			if (temp < 0)
			{
				temp *= -1;
			}
			if (temp > roz)
			{
				if (binarny[i] > binarny[i + 1])
				{
					binarny[i] -= roz / 3;
					binarny[i + 1] += roz / 3;
				}
				else
				{
					binarny[i + 1] -= roz / 3;
					binarny[i] += roz / 3;
				}
			}
		}
	
		
		for (int i = 0; i < size; i++)
		{
			do_wykresu << plik.dane[i] << endl;
		}
		plik.Zapis("_pliki\\test2.raw");
		return plik;
	}

	RAWFile<float> ACamo::MaskTime(float prog)
	{
		fstream do_wykresu;
		do_wykresu.open("_pliki\\dane.txt", ios::out);
		RAWFile<float> plik;
		float* binarny = (plik.Wczytaj("_pliki\\test.raw"));
		float temp = 0;
		long size = plik.GetSize();

		for (int i = 0; i < size; i++)
		{
			if (binarny[i] < 0)
			{
				if (-1 * binarny[i] >= prog)
				{
					temp = binarny[i];
				}
				else if(-1 * binarny[i] < prog)
				{
					binarny[i] += temp / 3;
					if (binarny[i] > 0) binarny[i] = 0;
				}
			}
			else
			{
				if (binarny[i] >= prog)
				{
					temp = binarny[i];
				}
				else if (binarny[i] == 0);
				else if (binarny[i] < prog)
				{
					binarny[i] -= temp / 3;
					if (binarny[i] < 0) binarny[i] = 0;
				}
			}
			
		}
		for (int i = 0; i < size; i++)
		{
			do_wykresu << plik.dane[i] << endl;
		}
		plik.Zapis("_pliki\\test2.raw");
		return plik;
	}
}