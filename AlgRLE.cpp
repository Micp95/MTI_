#include "AlgRLE.h"
#include <iostream>
#include <string>
#include <math.h>

using namespace std;

namespace _ARLE
{
	ARLE::ARLE()
	{

	}
	ARLE::~ARLE()
	{

	}
	string ARLE::Koduj(string tekstK)
	{
		tekst = tekstK;
		int counter;
		char current;
		for (int i = 0; i < tekst.length(); i++)
		{
			counter = 1;
			current = tekst[i];
			while (tekst[i] == tekst[i + 1])
			{
				counter++;
				current = tekst[i+1];
				i++;
			}
			this->zakodowany += to_string(counter);
			this->zakodowany += current;
		}

		return zakodowany;
	}
	string ARLE::Dekoduj(string dekodowany)
	{
		string odkodowany = "";
		int temp;
		int ile = 0;
		if (dekodowany == "") dekodowany = zakodowany;
		for (int i = 0; i < dekodowany.length(); i++)
		{
			ile = 0;
			temp = static_cast<int>(dekodowany[i]);
			if (temp < 58 && temp > 47)
			{
				temp -= 48;
				while (static_cast<int>(dekodowany[i+1]) < 58 && static_cast<int>(dekodowany[i+1]) > 47)
				{
					ile++;
					temp *= 10;
					temp += static_cast<int>(dekodowany[i + 1]) - 48;
					i++;
				}
				
				while (temp != 0)
				{
					odkodowany += dekodowany[i + 1];
					temp--;
				}
				i++;
			}
			else
			{
				cout << "Tego tekstu nie da sie odkodowac!" << endl;
				return dekodowany;
			}
		}

		return odkodowany;
	}
}