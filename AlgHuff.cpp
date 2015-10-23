#include "AlgHuff.h"

namespace _AHuffman{

	AHuffman::AHuffman()
	{
	}

	AHuffman::~AHuffman()
	{

	}
	void AHuffman::StworzListe(){
		string znalezione = "";
		int* wystapienia = new int[100];
		int size = 0;

		int tmp;
		char znak;
		for (int k = 0; k < tekst.length(); k++){
			znak = tekst[k];
			tmp = znalezione.find(znak);
			if (tmp == -1){
				znalezione += znak;
				wystapienia[size++] = 1;
			}
			else
				wystapienia[tmp] ++;
		}
		znaki = new Node[size];

		for (int k = 0; k < size; k++){
			znaki[k] = Node(znalezione[k],wystapienia[k]);
		}

		this->size = size;
		tablica = znalezione;
		delete[] wystapienia;
		//return 0;
	}
	void AHuffman::Koduj(string tresc){
		tekst = tresc;
		StworzListe();
		
		Node** drzewa = new Node*[size];
		for (int k = 0; k < size; k++){
			drzewa[k] = &znaki[k];
		}


		int zmsize = size;
		MM indeksy;
		Node* tmp;
		while (zmsize > 1){
			indeksy = MinMin(drzewa, zmsize);
			for (int k = 0; k < zmsize; k++){
				drzewa[k] = drzewa[k];
			}
			if (indeksy.max != indeksy.min){
				tmp = new Node(drzewa[indeksy.min]->wartosc + drzewa[indeksy.max]->wartosc);
				tmp->left = drzewa[indeksy.min];
				tmp->right = drzewa[indeksy.max];
				drzewa[indeksy.min] = tmp;
				swap(drzewa[indeksy.max], drzewa[zmsize - 1]);
				zmsize--;
			}
		}

		
		Drzewo = drzewa[0];
		delete[] drzewa;
	}
	void AHuffman::Dekoduj(string tresc ){

	}

	MM AHuffman::MinMin(Node**tab, int size){
		MM MiMa, zwrot; // min = min1, max = min2
		zwrot.min = 0;
		zwrot.max = 0;
		MiMa.max = -1;
		MiMa.min = -1;

		int tmp;
		for (int k = 0; k < size; k++){
			tmp = tab[k]->wartosc;
			if (tmp < MiMa.max || MiMa.max == -1){
				zwrot.max = k;
				MiMa.max = tmp;
			}
			else if (tmp <= MiMa.min || MiMa.min == -1){
				zwrot.min = k;
				MiMa.min = tmp;
			}
		}

		return zwrot;
	}

}