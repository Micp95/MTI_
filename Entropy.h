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
		double EntropyVal; // wartosc entropii
	private:
		double EntropyFun(); // funkcja liczaca entropie
		string text; // tekst ktory kodujemy
		int HowMany(char); // funkcja liczaca ilosc wystapien danego znaku
	};
}

#endif