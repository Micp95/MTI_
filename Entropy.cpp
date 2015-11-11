#include "Entropy.h"
#include <math.h>
#include <iostream>
using namespace std;


namespace AEntropy
{

	Entropy::Entropy(string tekst)
	{
		this->text = tekst;
		this->EntropyVal = EntropyFun();
	//	cout << "Entropia tekstu wynosi " << this->EntropyVal << endl;
	}
	Entropy::~Entropy()
	{

	}
	double Entropy::EntropyFun()
	{
		double Entr = 0;
		double EachEntr = 0;
		string findL = "";
		int temp = 0;
		double tempLog = 0;
		double tempLog2 = 0;
		for (int i = 0; i < text.length(); i++)
		{
			if (findL.find(text[i]) == -1)
			{
				temp = HowMany(text[i]);
				tempLog = 1.0000 * temp / text.length();
				tempLog2 = 1.0000 * text.length() / temp;
				EachEntr = (tempLog) * (log2(tempLog2)); // entropia dla okreslonego znaku
				findL += text[i];
				Entr +=  EachEntr; // suma entropii znakow
			}
		}
		return Entr;
	}
	int Entropy::HowMany(char letter)
	{
		int ile = 0;
		for (int i = 0; i < text.length();i++)
		{
			if (text[i] == letter)
				ile++;
		}
		return ile;
	}
}