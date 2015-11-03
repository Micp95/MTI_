#ifndef ENTROPY_H
#define ENTROPY_H

#include <string>
using namespace std;

namespace AEntropy
{
	class Entropy
	{
	public:
		Entropy(string);
		~Entropy();
	private:
		double EntropyVal; // wartosc entropii
		string text; // tekst ktory kodujemy
		double EntropyFun(); // funkcja liczaca entropie
		int HowMany(char); // funkcja liczaca ilosc wystapien danego znaku
	};
}

#endif