#include "AlgHuff.h"

namespace _AHuffman{

	//Konstruktory i destruktory
	AHuffman::~AHuffman()
	{
		if (znaki != NULL)
			delete[] znaki;
	}


	//Tworzenie potrzebnych struktur
	void AHuffman::StworzListe(){
		string znalezione = "";
		int* wystapienia = new int[MaksZnakow];
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
	}

	void AHuffman::StworzDrzewo(){
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

	void AHuffman::StworzSlownik(){
		Przechodz(Drzewo,"");
	}


	//Algorytm kodujacy
	void AHuffman::Przechodz(Node* element, string kod){
		if (element == NULL)
			return;
		if (element->left)
			Przechodz(element->left,kod+"0");

		element->Odwiedz(kod);

		if (element->right)
			Przechodz(element->right, kod + "1");
	}

	string AHuffman::Translate(){
		string zwrot="";
		for (int k = 0; k < tekst.length(); k++){
			zwrot += znaki[tablica.find(tekst[k])].kod;
		}
		zakodowane = zwrot;
		return zwrot;
	}


	//Funkcje Glowne
	string AHuffman::Koduj(string tresc){
		tekst = tresc;
		StworzListe();
		StworzDrzewo();
		StworzSlownik();

		return Translate();
	}

	string AHuffman::Dekoduj(string tresc ){
		if (tresc == "")
			tresc = zakodowane;
		string zwrot = "";

		Node* tmp = Drzewo;
		for (int k = 0; k <= tresc.length(); k++){
			if (tmp->CzyLisc){
				zwrot += tmp->znak;
				tmp = Drzewo;
			}

			if (k == tresc.length())
				break;

			if (tresc[k] == '0')
				tmp = tmp->left;
			else
				tmp = tmp->right;
		}


		return zwrot;
	}


	//Funkcja pomocnicza
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