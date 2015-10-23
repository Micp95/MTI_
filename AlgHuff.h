#ifndef ALGHUFF_H
#define ALGHUFF_H

#include <string>
#include "HuffDrzewo.h"

using namespace std;

namespace _AHuffman{

	struct MM{
		int min, max;
	};

	class AHuffman
	{
	public:
		AHuffman();
		~AHuffman();

		void Koduj(string tresc);
		void Dekoduj(string tresc = "");

		

	private:
		string tekst;
		string tablica;


		Node* znaki;
		int size;

		void StworzListe();
		MM MinMin(Node**tab, int size);
		Node* Drzewo;
		
		string zakodowane;
	};



}





#endif