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


		//Zliczenie wystepujacych znakow
		int tmp;
		char znak;
		for (int k = 0; k < tekst.length(); k++){
			znak = tekst[k];
			tmp = znalezione.find(znak);
			if (tmp == -1){						//Jeœli nie znaleziono, dodajemy nowy znak do s³ownika/sringa
				znalezione += znak;
				wystapienia[size++] = 1;		//Zwiêkszamy indeks wystapienia danego znaku(nowego)
			}
			else
				wystapienia[tmp] ++;			//Zwiekszamy indeks znalezionego znaku
		}


		//Tworzenie podstawowych jednostek drzew
		znaki = new Node[size];

		for (int k = 0; k < size; k++){
			znaki[k] = Node(znalezione[k],wystapienia[k]);
		}

		//Porzadki
		this->size = size;
		tablica = znalezione;
		delete[] wystapienia;
	}

	void AHuffman::StworzDrzewo(){

		//Zapisywanie adresow wszystkich lisci
		Node** drzewa = new Node*[size];
		for (int k = 0; k < size; k++){
			drzewa[k] = &znaki[k];
		}

		//Zmienne pomocnicze
		int zmsize = size;
		MM indeksy;
		Node* tmp;
		while (zmsize > 1){		//Dopoki mamy wiecej niz jeden element w tablicy
			indeksy = MinMin(drzewa, zmsize);		//Znalezienie najmniejszych elementow
			
			
			if (indeksy.max != indeksy.min){	//dodatkowe zabezpieczenie - nie potrzebne
				tmp = new Node(drzewa[indeksy.min]->wartosc + drzewa[indeksy.max]->wartosc);	//Tworzenie nowego wezla

				//Ustawianie zmiennych wezla
				tmp->left = drzewa[indeksy.min];
				tmp->right = drzewa[indeksy.max];


				drzewa[indeksy.min] = tmp;		//Podmiana starego elementu na wezel
				swap(drzewa[indeksy.max], drzewa[--zmsize]);	//Podmiana i usuniecie ostatniego elementu z tabliy (zmiejszenie rozmiaru)
\
			}
		}

		Drzewo = drzewa[0];			//Zapamietanie adresu drzewa
		delete[] drzewa;			//Usuniecie pomocniczej tablicy



	}

	void AHuffman::StworzSlownik(){
		Przechodz(Drzewo,"");			//Aktualizacja elementow drzewa - zapamietuje sciezki do kazdego nodea - tworzy slownik
	}


	//Algorytm kodujacy
	void AHuffman::Przechodz(Node* element, string kod){		//Przejscie przez drzewo typem (?)
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

		//Pomocnicze wypisanie slownika
		for (int k = 0; k < size; k++)
			cout << znaki[k].znak << " " << znaki[k].kod << endl;

		return Translate();
	}

	string AHuffman::Dekoduj(string tresc ){
		if (tresc == "")
			tresc = zakodowane;
		string zwrot = "";


		//Odczytywanie liter ze slownika - przechodzenie przez drzewo za pomoca podanego schamatu
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
		swap(zwrot.max, zwrot.#include "AlgHuff.h"

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


		//Zliczenie wystepujacych znakow
		int tmp;
		char znak;
		for (int k = 0; k < tekst.length(); k++){
			znak = tekst[k];
			tmp = znalezione.find(znak);
			if (tmp == -1){						//Jeœli nie znaleziono, dodajemy nowy znak do s³ownika/sringa
				znalezione += znak;
				wystapienia[size++] = 1;		//Zwiêkszamy indeks wystapienia danego znaku(nowego)
			}
			else
				wystapienia[tmp] ++;			//Zwiekszamy indeks znalezionego znaku
		}


		//Tworzenie podstawowych jednostek drzew
		znaki = new Node[size];

		for (int k = 0; k < size; k++){
			znaki[k] = Node(znalezione[k],wystapienia[k]);
		}

		//Porzadki
		this->size = size;
		tablica = znalezione;
		delete[] wystapienia;
	}

	void AHuffman::StworzDrzewo(){

		//Zapisywanie adresow wszystkich lisci
		Node** drzewa = new Node*[size];
		for (int k = 0; k < size; k++){
			drzewa[k] = &znaki[k];
		}

		//Zmienne pomocnicze
		int zmsize = size;
		MM indeksy;
		Node* tmp;
		while (zmsize > 1){		//Dopoki mamy wiecej niz jeden element w tablicy
			indeksy = MinMin(drzewa, zmsize);		//Znalezienie najmniejszych elementow
			
			
			if (indeksy.max != indeksy.min){	//dodatkowe zabezpieczenie - nie potrzebne
				tmp = new Node(drzewa[indeksy.min]->wartosc + drzewa[indeksy.max]->wartosc);	//Tworzenie nowego wezla

				//Ustawianie zmiennych wezla
				tmp->left = drzewa[indeksy.min];
				tmp->right = drzewa[indeksy.max];


				drzewa[indeksy.min] = tmp;		//Podmiana starego elementu na wezel
				swap(drzewa[indeksy.max], drzewa[--zmsize]);	//Podmiana i usuniecie ostatniego elementu z tabliy (zmiejszenie rozmiaru)
\
			}
		}

		Drzewo = drzewa[0];			//Zapamietanie adresu drzewa
		delete[] drzewa;			//Usuniecie pomocniczej tablicy



	}

	void AHuffman::StworzSlownik(){
		Przechodz(Drzewo,"");			//Aktualizacja elementow drzewa - zapamietuje sciezki do kazdego nodea - tworzy slownik
	}


	//Algorytm kodujacy
	void AHuffman::Przechodz(Node* element, string kod){		//Przejscie przez drzewo typem (?)
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

		//Pomocnicze wypisanie slownika
		for (int k = 0; k < size; k++)
			cout << znaki[k].znak << " " << znaki[k].kod << endl;

		return Translate();
	}

	string AHuffman::Dekoduj(string tresc ){
		if (tresc == "")
			tresc = zakodowane;
		string zwrot = "";


		//Odczytywanie liter ze slownika - przechodzenie przez drzewo za pomoca podanego schamatu
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
		swap(zwrot.max, zwrot.min);

		return zwrot;
	}

}#include "AlgHuff.h"

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


		//Zliczenie wystepujacych znakow
		int tmp;
		char znak;
		for (int k = 0; k < tekst.length(); k++){
			znak = tekst[k];
			tmp = znalezione.find(znak);
			if (tmp == -1){						//Jeœli nie znaleziono, dodajemy nowy znak do s³ownika/sringa
				znalezione += znak;
				wystapienia[size++] = 1;		//Zwiêkszamy indeks wystapienia danego znaku(nowego)
			}
			else
				wystapienia[tmp] ++;			//Zwiekszamy indeks znalezionego znaku
		}


		//Tworzenie podstawowych jednostek drzew
		znaki = new Node[size];

		for (int k = 0; k < size; k++){
			znaki[k] = Node(znalezione[k],wystapienia[k]);
		}

		//Porzadki
		this->size = size;
		tablica = znalezione;
		delete[] wystapienia;
	}

	void AHuffman::StworzDrzewo(){

		//Zapisywanie adresow wszystkich lisci
		Node** drzewa = new Node*[size];
		for (int k = 0; k < size; k++){
			drzewa[k] = &znaki[k];
		}

		//Zmienne pomocnicze
		int zmsize = size;
		MM indeksy;
		Node* tmp;
		while (zmsize > 1){		//Dopoki mamy wiecej niz jeden element w tablicy
			indeksy = MinMin(drzewa, zmsize);		//Znalezienie najmniejszych elementow
			
			
			if (indeksy.max != indeksy.min){	//dodatkowe zabezpieczenie - nie potrzebne
				tmp = new Node(drzewa[indeksy.min]->wartosc + drzewa[indeksy.max]->wartosc);	//Tworzenie nowego wezla

				//Ustawianie zmiennych wezla
				tmp->left = drzewa[indeksy.min];
				tmp->right = drzewa[indeksy.max];


				drzewa[indeksy.min] = tmp;		//Podmiana starego elementu na wezel
				swap(drzewa[indeksy.max], drzewa[--zmsize]);	//Podmiana i usuniecie ostatniego elementu z tabliy (zmiejszenie rozmiaru)
\
			}
		}

		Drzewo = drzewa[0];			//Zapamietanie adresu drzewa
		delete[] drzewa;			//Usuniecie pomocniczej tablicy



	}

	void AHuffman::StworzSlownik(){
		Przechodz(Drzewo,"");			//Aktualizacja elementow drzewa - zapamietuje sciezki do kazdego nodea - tworzy slownik
	}


	//Algorytm kodujacy
	void AHuffman::Przechodz(Node* element, string kod){		//Przejscie przez drzewo typem (?)
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

		//Pomocnicze wypisanie slownika
		for (int k = 0; k < size; k++)
			cout << znaki[k].znak << " " << znaki[k].kod << endl;

		return Translate();
	}

	string AHuffman::Dekoduj(string tresc ){
		if (tresc == "")
			tresc = zakodowane;
		string zwrot = "";


		//Odczytywanie liter ze slownika - przechodzenie przez drzewo za pomoca podanego schamatu
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
		swap(zwrot.max, zwrot.min);

		return zwrot;
	}

}#include "AlgHuff.h"

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


		//Zliczenie wystepujacych znakow
		int tmp;
		char znak;
		for (int k = 0; k < tekst.length(); k++){
			znak = tekst[k];
			tmp = znalezione.find(znak);
			if (tmp == -1){						//Jeœli nie znaleziono, dodajemy nowy znak do s³ownika/sringa
				znalezione += znak;
				wystapienia[size++] = 1;		//Zwiêkszamy indeks wystapienia danego znaku(nowego)
			}
			else
				wystapienia[tmp] ++;			//Zwiekszamy indeks znalezionego znaku
		}


		//Tworzenie podstawowych jednostek drzew
		znaki = new Node[size];

		for (int k = 0; k < size; k++){
			znaki[k] = Node(znalezione[k],wystapienia[k]);
		}

		//Porzadki
		this->size = size;
		tablica = znalezione;
		delete[] wystapienia;
	}

	void AHuffman::StworzDrzewo(){

		//Zapisywanie adresow wszystkich lisci
		Node** drzewa = new Node*[size];
		for (int k = 0; k < size; k++){
			drzewa[k] = &znaki[k];
		}

		//Zmienne pomocnicze
		int zmsize = size;
		MM indeksy;
		Node* tmp;
		while (zmsize > 1){		//Dopoki mamy wiecej niz jeden element w tablicy
			indeksy = MinMin(drzewa, zmsize);		//Znalezienie najmniejszych elementow
			
			
			if (indeksy.max != indeksy.min){	//dodatkowe zabezpieczenie - nie potrzebne
				tmp = new Node(drzewa[indeksy.min]->wartosc + drzewa[indeksy.max]->wartosc);	//Tworzenie nowego wezla

				//Ustawianie zmiennych wezla
				tmp->left = drzewa[indeksy.min];
				tmp->right = drzewa[indeksy.max];


				drzewa[indeksy.min] = tmp;		//Podmiana starego elementu na wezel
				swap(drzewa[indeksy.max], drzewa[--zmsize]);	//Podmiana i usuniecie ostatniego elementu z tabliy (zmiejszenie rozmiaru)
\
			}
		}

		Drzewo = drzewa[0];			//Zapamietanie adresu drzewa
		delete[] drzewa;			//Usuniecie pomocniczej tablicy



	}

	void AHuffman::StworzSlownik(){
		Przechodz(Drzewo,"");			//Aktualizacja elementow drzewa - zapamietuje sciezki do kazdego nodea - tworzy slownik
	}


	//Algorytm kodujacy
	void AHuffman::Przechodz(Node* element, string kod){		//Przejscie przez drzewo typem (?)
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

		//Pomocnicze wypisanie slownika
		for (int k = 0; k < size; k++)
			cout << znaki[k].znak << " " << znaki[k].kod << endl;

		return Translate();
	}

	string AHuffman::Dekoduj(string tresc ){
		if (tresc == "")
			tresc = zakodowane;
		string zwrot = "";


		//Odczytywanie liter ze slownika - przechodzenie przez drzewo za pomoca podanego schamatu
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
		swap(zwrot.max, zwrot.min);

		return zwrot;
	}

}#include "AlgHuff.h"

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


		//Zliczenie wystepujacych znakow
		int tmp;
		char znak;
		for (int k = 0; k < tekst.length(); k++){
			znak = tekst[k];
			tmp = znalezione.find(znak);
			if (tmp == -1){						//Jeœli nie znaleziono, dodajemy nowy znak do s³ownika/sringa
				znalezione += znak;
				wystapienia[size++] = 1;		//Zwiêkszamy indeks wystapienia danego znaku(nowego)
			}
			else
				wystapienia[tmp] ++;			//Zwiekszamy indeks znalezionego znaku
		}


		//Tworzenie podstawowych jednostek drzew
		znaki = new Node[size];

		for (int k = 0; k < size; k++){
			znaki[k] = Node(znalezione[k],wystapienia[k]);
		}

		//Porzadki
		this->size = size;
		tablica = znalezione;
		delete[] wystapienia;
	}

	void AHuffman::StworzDrzewo(){

		//Zapisywanie adresow wszystkich lisci
		Node** drzewa = new Node*[size];
		for (int k = 0; k < size; k++){
			drzewa[k] = &znaki[k];
		}

		//Zmienne pomocnicze
		int zmsize = size;
		MM indeksy;
		Node* tmp;
		while (zmsize > 1){		//Dopoki mamy wiecej niz jeden element w tablicy
			indeksy = MinMin(drzewa, zmsize);		//Znalezienie najmniejszych elementow
			
			
			if (indeksy.max != indeksy.min){	//dodatkowe zabezpieczenie - nie potrzebne
				tmp = new Node(drzewa[indeksy.min]->wartosc + drzewa[indeksy.max]->wartosc);	//Tworzenie nowego wezla

				//Ustawianie zmiennych wezla
				tmp->left = drzewa[indeksy.min];
				tmp->right = drzewa[indeksy.max];


				drzewa[indeksy.min] = tmp;		//Podmiana starego elementu na wezel
				swap(drzewa[indeksy.max], drzewa[--zmsize]);	//Podmiana i usuniecie ostatniego elementu z tabliy (zmiejszenie rozmiaru)
\
			}
		}

		Drzewo = drzewa[0];			//Zapamietanie adresu drzewa
		delete[] drzewa;			//Usuniecie pomocniczej tablicy



	}

	void AHuffman::StworzSlownik(){
		Przechodz(Drzewo,"");			//Aktualizacja elementow drzewa - zapamietuje sciezki do kazdego nodea - tworzy slownik
	}


	//Algorytm kodujacy
	void AHuffman::Przechodz(Node* element, string kod){		//Przejscie przez drzewo typem (?)
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

		//Pomocnicze wypisanie slownika
		for (int k = 0; k < size; k++)
			cout << znaki[k].znak << " " << znaki[k].kod << endl;

		return Translate();
	}

	string AHuffman::Dekoduj(string tresc ){
		if (tresc == "")
			tresc = zakodowane;
		string zwrot = "";


		//Odczytywanie liter ze slownika - przechodzenie przez drzewo za pomoca podanego schamatu
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
		swap(zwrot.max, zwrot.min);

		return zwrot;
	}

}#include "AlgHuff.h"

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


		//Zliczenie wystepujacych znakow
		int tmp;
		char znak;
		for (int k = 0; k < tekst.length(); k++){
			znak = tekst[k];
			tmp = znalezione.find(znak);
			if (tmp == -1){						//Jeœli nie znaleziono, dodajemy nowy znak do s³ownika/sringa
				znalezione += znak;
				wystapienia[size++] = 1;		//Zwiêkszamy indeks wystapienia danego znaku(nowego)
			}
			else
				wystapienia[tmp] ++;			//Zwiekszamy indeks znalezionego znaku
		}


		//Tworzenie podstawowych jednostek drzew
		znaki = new Node[size];

		for (int k = 0; k < size; k++){
			znaki[k] = Node(znalezione[k],wystapienia[k]);
		}

		//Porzadki
		this->size = size;
		tablica = znalezione;
		delete[] wystapienia;
	}

	void AHuffman::StworzDrzewo(){

		//Zapisywanie adresow wszystkich lisci
		Node** drzewa = new Node*[size];
		for (int k = 0; k < size; k++){
			drzewa[k] = &znaki[k];
		}

		//Zmienne pomocnicze
		int zmsize = size;
		MM indeksy;
		Node* tmp;
		while (zmsize > 1){		//Dopoki mamy wiecej niz jeden element w tablicy
			indeksy = MinMin(drzewa, zmsize);		//Znalezienie najmniejszych elementow
			
			
			if (indeksy.max != indeksy.min){	//dodatkowe zabezpieczenie - nie potrzebne
				tmp = new Node(drzewa[indeksy.min]->wartosc + drzewa[indeksy.max]->wartosc);	//Tworzenie nowego wezla

				//Ustawianie zmiennych wezla
				tmp->left = drzewa[indeksy.min];
				tmp->right = drzewa[indeksy.max];


				drzewa[indeksy.min] = tmp;		//Podmiana starego elementu na wezel
				swap(drzewa[indeksy.max], drzewa[--zmsize]);	//Podmiana i usuniecie ostatniego elementu z tabliy (zmiejszenie rozmiaru)
\
			}
		}

		Drzewo = drzewa[0];			//Zapamietanie adresu drzewa
		delete[] drzewa;			//Usuniecie pomocniczej tablicy



	}

	void AHuffman::StworzSlownik(){
		Przechodz(Drzewo,"");			//Aktualizacja elementow drzewa - zapamietuje sciezki do kazdego nodea - tworzy slownik
	}


	//Algorytm kodujacy
	void AHuffman::Przechodz(Node* element, string kod){		//Przejscie przez drzewo typem (?)
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

		//Pomocnicze wypisanie slownika
		for (int k = 0; k < size; k++)
			cout << znaki[k].znak << " " << znaki[k].kod << endl;

		return Translate();
	}

	string AHuffman::Dekoduj(string tresc ){
		if (tresc == "")
			tresc = zakodowane;
		string zwrot = "";


		//Odczytywanie liter ze slownika - przechodzenie przez drzewo za pomoca podanego schamatu
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
		swap(zwrot.max, zwrot.min);

		return zwrot;
	}

}#include "AlgHuff.h"

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


		//Zliczenie wystepujacych znakow
		int tmp;
		char znak;
		for (int k = 0; k < tekst.length(); k++){
			znak = tekst[k];
			tmp = znalezione.find(znak);
			if (tmp == -1){						//Jeœli nie znaleziono, dodajemy nowy znak do s³ownika/sringa
				znalezione += znak;
				wystapienia[size++] = 1;		//Zwiêkszamy indeks wystapienia danego znaku(nowego)
			}
			else
				wystapienia[tmp] ++;			//Zwiekszamy indeks znalezionego znaku
		}


		//Tworzenie podstawowych jednostek drzew
		znaki = new Node[size];

		for (int k = 0; k < size; k++){
			znaki[k] = Node(znalezione[k],wystapienia[k]);
		}

		//Porzadki
		this->size = size;
		tablica = znalezione;
		delete[] wystapienia;
	}

	void AHuffman::StworzDrzewo(){

		//Zapisywanie adresow wszystkich lisci
		Node** drzewa = new Node*[size];
		for (int k = 0; k < size; k++){
			drzewa[k] = &znaki[k];
		}

		//Zmienne pomocnicze
		int zmsize = size;
		MM indeksy;
		Node* tmp;
		while (zmsize > 1){		//Dopoki mamy wiecej niz jeden element w tablicy
			indeksy = MinMin(drzewa, zmsize);		//Znalezienie najmniejszych elementow
			
			
			if (indeksy.max != indeksy.min){	//dodatkowe zabezpieczenie - nie potrzebne
				tmp = new Node(drzewa[indeksy.min]->wartosc + drzewa[indeksy.max]->wartosc);	//Tworzenie nowego wezla

				//Ustawianie zmiennych wezla
				tmp->left = drzewa[indeksy.min];
				tmp->right = drzewa[indeksy.max];


				drzewa[indeksy.min] = tmp;		//Podmiana starego elementu na wezel
				swap(drzewa[indeksy.max], drzewa[--zmsize]);	//Podmiana i usuniecie ostatniego elementu z tabliy (zmiejszenie rozmiaru)
\
			}
		}

		Drzewo = drzewa[0];			//Zapamietanie adresu drzewa
		delete[] drzewa;			//Usuniecie pomocniczej tablicy



	}

	void AHuffman::StworzSlownik(){
		Przechodz(Drzewo,"");			//Aktualizacja elementow drzewa - zapamietuje sciezki do kazdego nodea - tworzy slownik
	}


	//Algorytm kodujacy
	void AHuffman::Przechodz(Node* element, string kod){		//Przejscie przez drzewo typem (?)
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

		//Pomocnicze wypisanie slownika
		for (int k = 0; k < size; k++)
			cout << znaki[k].znak << " " << znaki[k].kod << endl;

		return Translate();
	}

	string AHuffman::Dekoduj(string tresc ){
		if (tresc == "")
			tresc = zakodowane;
		string zwrot = "";


		//Odczytywanie liter ze slownika - przechodzenie przez drzewo za pomoca podanego schamatu
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
		swap(zwrot.max, zwrot.min);

		return zwrot;
	}

}#include "AlgHuff.h"

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


		//Zliczenie wystepujacych znakow
		int tmp;
		char znak;
		for (int k = 0; k < tekst.length(); k++){
			znak = tekst[k];
			tmp = znalezione.find(znak);
			if (tmp == -1){						//Jeœli nie znaleziono, dodajemy nowy znak do s³ownika/sringa
				znalezione += znak;
				wystapienia[size++] = 1;		//Zwiêkszamy indeks wystapienia danego znaku(nowego)
			}
			else
				wystapienia[tmp] ++;			//Zwiekszamy indeks znalezionego znaku
		}


		//Tworzenie podstawowych jednostek drzew
		znaki = new Node[size];

		for (int k = 0; k < size; k++){
			znaki[k] = Node(znalezione[k],wystapienia[k]);
		}

		//Porzadki
		this->size = size;
		tablica = znalezione;
		delete[] wystapienia;
	}

	void AHuffman::StworzDrzewo(){

		//Zapisywanie adresow wszystkich lisci
		Node** drzewa = new Node*[size];
		for (int k = 0; k < size; k++){
			drzewa[k] = &znaki[k];
		}

		//Zmienne pomocnicze
		int zmsize = size;
		MM indeksy;
		Node* tmp;
		while (zmsize > 1){		//Dopoki mamy wiecej niz jeden element w tablicy
			indeksy = MinMin(drzewa, zmsize);		//Znalezienie najmniejszych elementow
			
			
			if (indeksy.max != indeksy.min){	//dodatkowe zabezpieczenie - nie potrzebne
				tmp = new Node(drzewa[indeksy.min]->wartosc + drzewa[indeksy.max]->wartosc);	//Tworzenie nowego wezla

				//Ustawianie zmiennych wezla
				tmp->left = drzewa[indeksy.min];
				tmp->right = drzewa[indeksy.max];


				drzewa[indeksy.min] = tmp;		//Podmiana starego elementu na wezel
				swap(drzewa[indeksy.max], drzewa[--zmsize]);	//Podmiana i usuniecie ostatniego elementu z tabliy (zmiejszenie rozmiaru)
\
			}
		}

		Drzewo = drzewa[0];			//Zapamietanie adresu drzewa
		delete[] drzewa;			//Usuniecie pomocniczej tablicy



	}

	void AHuffman::StworzSlownik(){
		Przechodz(Drzewo,"");			//Aktualizacja elementow drzewa - zapamietuje sciezki do kazdego nodea - tworzy slownik
	}


	//Algorytm kodujacy
	void AHuffman::Przechodz(Node* element, string kod){		//Przejscie przez drzewo typem (?)
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

		//Pomocnicze wypisanie slownika
		for (int k = 0; k < size; k++)
			cout << znaki[k].znak << " " << znaki[k].kod << endl;

		return Translate();
	}

	string AHuffman::Dekoduj(string tresc ){
		if (tresc == "")
			tresc = zakodowane;
		string zwrot = "";


		//Odczytywanie liter ze slownika - przechodzenie przez drzewo za pomoca podanego schamatu
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
		swap(zwrot.max, zwrot.min);

		return zwrot;
	}

}#include "AlgHuff.h"

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


		//Zliczenie wystepujacych znakow
		int tmp;
		char znak;
		for (int k = 0; k < tekst.length(); k++){
			znak = tekst[k];
			tmp = znalezione.find(znak);
			if (tmp == -1){						//Jeœli nie znaleziono, dodajemy nowy znak do s³ownika/sringa
				znalezione += znak;
				wystapienia[size++] = 1;		//Zwiêkszamy indeks wystapienia danego znaku(nowego)
			}
			else
				wystapienia[tmp] ++;			//Zwiekszamy indeks znalezionego znaku
		}


		//Tworzenie podstawowych jednostek drzew
		znaki = new Node[size];

		for (int k = 0; k < size; k++){
			znaki[k] = Node(znalezione[k],wystapienia[k]);
		}

		//Porzadki
		this->size = size;
		tablica = znalezione;
		delete[] wystapienia;
	}

	void AHuffman::StworzDrzewo(){

		//Zapisywanie adresow wszystkich lisci
		Node** drzewa = new Node*[size];
		for (int k = 0; k < size; k++){
			drzewa[k] = &znaki[k];
		}

		//Zmienne pomocnicze
		int zmsize = size;
		MM indeksy;
		Node* tmp;
		while (zmsize > 1){		//Dopoki mamy wiecej niz jeden element w tablicy
			indeksy = MinMin(drzewa, zmsize);		//Znalezienie najmniejszych elementow
			
			
			if (indeksy.max != indeksy.min){	//dodatkowe zabezpieczenie - nie potrzebne
				tmp = new Node(drzewa[indeksy.min]->wartosc + drzewa[indeksy.max]->wartosc);	//Tworzenie nowego wezla

				//Ustawianie zmiennych wezla
				tmp->left = drzewa[indeksy.min];
				tmp->right = drzewa[indeksy.max];


				drzewa[indeksy.min] = tmp;		//Podmiana starego elementu na wezel
				swap(drzewa[indeksy.max], drzewa[--zmsize]);	//Podmiana i usuniecie ostatniego elementu z tabliy (zmiejszenie rozmiaru)
\
			}
		}

		Drzewo = drzewa[0];			//Zapamietanie adresu drzewa
		delete[] drzewa;			//Usuniecie pomocniczej tablicy



	}

	void AHuffman::StworzSlownik(){
		Przechodz(Drzewo,"");			//Aktualizacja elementow drzewa - zapamietuje sciezki do kazdego nodea - tworzy slownik
	}


	//Algorytm kodujacy
	void AHuffman::Przechodz(Node* element, string kod){		//Przejscie przez drzewo typem (?)
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

		//Pomocnicze wypisanie slownika
		for (int k = 0; k < size; k++)
			cout << znaki[k].znak << " " << znaki[k].kod << endl;

		return Translate();
	}

	string AHuffman::Dekoduj(string tresc ){
		if (tresc == "")
			tresc = zakodowane;
		string zwrot = "";


		//Odczytywanie liter ze slownika - przechodzenie przez drzewo za pomoca podanego schamatu
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
		swap(zwrot.max, zwrot.min);

		return zwrot;
	}

}#include "AlgHuff.h"

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


		//Zliczenie wystepujacych znakow
		int tmp;
		char znak;
		for (int k = 0; k < tekst.length(); k++){
			znak = tekst[k];
			tmp = znalezione.find(znak);
			if (tmp == -1){						//Jeœli nie znaleziono, dodajemy nowy znak do s³ownika/sringa
				znalezione += znak;
				wystapienia[size++] = 1;		//Zwiêkszamy indeks wystapienia danego znaku(nowego)
			}
			else
				wystapienia[tmp] ++;			//Zwiekszamy indeks znalezionego znaku
		}


		//Tworzenie podstawowych jednostek drzew
		znaki = new Node[size];

		for (int k = 0; k < size; k++){
			znaki[k] = Node(znalezione[k],wystapienia[k]);
		}

		//Porzadki
		this->size = size;
		tablica = znalezione;
		delete[] wystapienia;
	}

	void AHuffman::StworzDrzewo(){

		//Zapisywanie adresow wszystkich lisci
		Node** drzewa = new Node*[size];
		for (int k = 0; k < size; k++){
			drzewa[k] = &znaki[k];
		}

		//Zmienne pomocnicze
		int zmsize = size;
		MM indeksy;
		Node* tmp;
		while (zmsize > 1){		//Dopoki mamy wiecej niz jeden element w tablicy
			indeksy = MinMin(drzewa, zmsize);		//Znalezienie najmniejszych elementow
			
			
			if (indeksy.max != indeksy.min){	//dodatkowe zabezpieczenie - nie potrzebne
				tmp = new Node(drzewa[indeksy.min]->wartosc + drzewa[indeksy.max]->wartosc);	//Tworzenie nowego wezla

				//Ustawianie zmiennych wezla
				tmp->left = drzewa[indeksy.min];
				tmp->right = drzewa[indeksy.max];


				drzewa[indeksy.min] = tmp;		//Podmiana starego elementu na wezel
				swap(drzewa[indeksy.max], drzewa[--zmsize]);	//Podmiana i usuniecie ostatniego elementu z tabliy (zmiejszenie rozmiaru)
\
			}
		}

		Drzewo = drzewa[0];			//Zapamietanie adresu drzewa
		delete[] drzewa;			//Usuniecie pomocniczej tablicy



	}

	void AHuffman::StworzSlownik(){
		Przechodz(Drzewo,"");			//Aktualizacja elementow drzewa - zapamietuje sciezki do kazdego nodea - tworzy slownik
	}


	//Algorytm kodujacy
	void AHuffman::Przechodz(Node* element, string kod){		//Przejscie przez drzewo typem (?)
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

		//Pomocnicze wypisanie slownika
		for (int k = 0; k < size; k++)
			cout << znaki[k].znak << " " << znaki[k].kod << endl;

		return Translate();
	}

	string AHuffman::Dekoduj(string tresc ){
		if (tresc == "")
			tresc = zakodowane;
		string zwrot = "";


		//Odczytywanie liter ze slownika - przechodzenie przez drzewo za pomoca podanego schamatu
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
		swap(zwrot.max, zwrot.min);

		return zwrot;
	}

}#include "AlgHuff.h"

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


		//Zliczenie wystepujacych znakow
		int tmp;
		char znak;
		for (int k = 0; k < tekst.length(); k++){
			znak = tekst[k];
			tmp = znalezione.find(znak);
			if (tmp == -1){						//Jeœli nie znaleziono, dodajemy nowy znak do s³ownika/sringa
				znalezione += znak;
				wystapienia[size++] = 1;		//Zwiêkszamy indeks wystapienia danego znaku(nowego)
			}
			else
				wystapienia[tmp] ++;			//Zwiekszamy indeks znalezionego znaku
		}


		//Tworzenie podstawowych jednostek drzew
		znaki = new Node[size];

		for (int k = 0; k < size; k++){
			znaki[k] = Node(znalezione[k],wystapienia[k]);
		}

		//Porzadki
		this->size = size;
		tablica = znalezione;
		delete[] wystapienia;
	}

	void AHuffman::StworzDrzewo(){

		//Zapisywanie adresow wszystkich lisci
		Node** drzewa = new Node*[size];
		for (int k = 0; k < size; k++){
			drzewa[k] = &znaki[k];
		}

		//Zmienne pomocnicze
		int zmsize = size;
		MM indeksy;
		Node* tmp;
		while (zmsize > 1){		//Dopoki mamy wiecej niz jeden element w tablicy
			indeksy = MinMin(drzewa, zmsize);		//Znalezienie najmniejszych elementow
			
			
			if (indeksy.max != indeksy.min){	//dodatkowe zabezpieczenie - nie potrzebne
				tmp = new Node(drzewa[indeksy.min]->wartosc + drzewa[indeksy.max]->wartosc);	//Tworzenie nowego wezla

				//Ustawianie zmiennych wezla
				tmp->left = drzewa[indeksy.min];
				tmp->right = drzewa[indeksy.max];


				drzewa[indeksy.min] = tmp;		//Podmiana starego elementu na wezel
				swap(drzewa[indeksy.max], drzewa[--zmsize]);	//Podmiana i usuniecie ostatniego elementu z tabliy (zmiejszenie rozmiaru)
\
			}
		}

		Drzewo = drzewa[0];			//Zapamietanie adresu drzewa
		delete[] drzewa;			//Usuniecie pomocniczej tablicy



	}

	void AHuffman::StworzSlownik(){
		Przechodz(Drzewo,"");			//Aktualizacja elementow drzewa - zapamietuje sciezki do kazdego nodea - tworzy slownik
	}


	//Algorytm kodujacy
	void AHuffman::Przechodz(Node* element, string kod){		//Przejscie przez drzewo typem (?)
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

		//Pomocnicze wypisanie slownika
		for (int k = 0; k < size; k++)
			cout << znaki[k].znak << " " << znaki[k].kod << endl;

		return Translate();
	}

	string AHuffman::Dekoduj(string tresc ){
		if (tresc == "")
			tresc = zakodowane;
		string zwrot = "";


		//Odczytywanie liter ze slownika - przechodzenie przez drzewo za pomoca podanego schamatu
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
		swap(zwrot.max, zwrot.min);

		return zwrot;
	}

}#include "AlgHuff.h"

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


		//Zliczenie wystepujacych znakow
		int tmp;
		char znak;
		for (int k = 0; k < tekst.length(); k++){
			znak = tekst[k];
			tmp = znalezione.find(znak);
			if (tmp == -1){						//Jeœli nie znaleziono, dodajemy nowy znak do s³ownika/sringa
				znalezione += znak;
				wystapienia[size++] = 1;		//Zwiêkszamy indeks wystapienia danego znaku(nowego)
			}
			else
				wystapienia[tmp] ++;			//Zwiekszamy indeks znalezionego znaku
		}


		//Tworzenie podstawowych jednostek drzew
		znaki = new Node[size];

		for (int k = 0; k < size; k++){
			znaki[k] = Node(znalezione[k],wystapienia[k]);
		}

		//Porzadki
		this->size = size;
		tablica = znalezione;
		delete[] wystapienia;
	}

	void AHuffman::StworzDrzewo(){

		//Zapisywanie adresow wszystkich lisci
		Node** drzewa = new Node*[size];
		for (int k = 0; k < size; k++){
			drzewa[k] = &znaki[k];
		}

		//Zmienne pomocnicze
		int zmsize = size;
		MM indeksy;
		Node* tmp;
		while (zmsize > 1){		//Dopoki mamy wiecej niz jeden element w tablicy
			indeksy = MinMin(drzewa, zmsize);		//Znalezienie najmniejszych elementow
			
			
			if (indeksy.max != indeksy.min){	//dodatkowe zabezpieczenie - nie potrzebne
				tmp = new Node(drzewa[indeksy.min]->wartosc + drzewa[indeksy.max]->wartosc);	//Tworzenie nowego wezla

				//Ustawianie zmiennych wezla
				tmp->left = drzewa[indeksy.min];
				tmp->right = drzewa[indeksy.max];


				drzewa[indeksy.min] = tmp;		//Podmiana starego elementu na wezel
				swap(drzewa[indeksy.max], drzewa[--zmsize]);	//Podmiana i usuniecie ostatniego elementu z tabliy (zmiejszenie rozmiaru)
\
			}
		}

		Drzewo = drzewa[0];			//Zapamietanie adresu drzewa
		delete[] drzewa;			//Usuniecie pomocniczej tablicy



	}

	void AHuffman::StworzSlownik(){
		Przechodz(Drzewo,"");			//Aktualizacja elementow drzewa - zapamietuje sciezki do kazdego nodea - tworzy slownik
	}


	//Algorytm kodujacy
	void AHuffman::Przechodz(Node* element, string kod){		//Przejscie przez drzewo typem (?)
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

		//Pomocnicze wypisanie slownika
		for (int k = 0; k < size; k++)
			cout << znaki[k].znak << " " << znaki[k].kod << endl;

		return Translate();
	}

	string AHuffman::Dekoduj(string tresc ){
		if (tresc == "")
			tresc = zakodowane;
		string zwrot = "";


		//Odczytywanie liter ze slownika - przechodzenie przez drzewo za pomoca podanego schamatu
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
		swap(zwrot.max, zwrot.min);

		return zwrot;
	}

}#include "AlgHuff.h"

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


		//Zliczenie wystepujacych znakow
		int tmp;
		char znak;
		for (int k = 0; k < tekst.length(); k++){
			znak = tekst[k];
			tmp = znalezione.find(znak);
			if (tmp == -1){						//Jeœli nie znaleziono, dodajemy nowy znak do s³ownika/sringa
				znalezione += znak;
				wystapienia[size++] = 1;		//Zwiêkszamy indeks wystapienia danego znaku(nowego)
			}
			else
				wystapienia[tmp] ++;			//Zwiekszamy indeks znalezionego znaku
		}


		//Tworzenie podstawowych jednostek drzew
		znaki = new Node[size];

		for (int k = 0; k < size; k++){
			znaki[k] = Node(znalezione[k],wystapienia[k]);
		}

		//Porzadki
		this->size = size;
		tablica = znalezione;
		delete[] wystapienia;
	}

	void AHuffman::StworzDrzewo(){

		//Zapisywanie adresow wszystkich lisci
		Node** drzewa = new Node*[size];
		for (int k = 0; k < size; k++){
			drzewa[k] = &znaki[k];
		}

		//Zmienne pomocnicze
		int zmsize = size;
		MM indeksy;
		Node* tmp;
		while (zmsize > 1){		//Dopoki mamy wiecej niz jeden element w tablicy
			indeksy = MinMin(drzewa, zmsize);		//Znalezienie najmniejszych elementow
			
			
			if (indeksy.max != indeksy.min){	//dodatkowe zabezpieczenie - nie potrzebne
				tmp = new Node(drzewa[indeksy.min]->wartosc + drzewa[indeksy.max]->wartosc);	//Tworzenie nowego wezla

				//Ustawianie zmiennych wezla
				tmp->left = drzewa[indeksy.min];
				tmp->right = drzewa[indeksy.max];


				drzewa[indeksy.min] = tmp;		//Podmiana starego elementu na wezel
				swap(drzewa[indeksy.max], drzewa[--zmsize]);	//Podmiana i usuniecie ostatniego elementu z tabliy (zmiejszenie rozmiaru)
\
			}
		}

		Drzewo = drzewa[0];			//Zapamietanie adresu drzewa
		delete[] drzewa;			//Usuniecie pomocniczej tablicy



	}

	void AHuffman::StworzSlownik(){
		Przechodz(Drzewo,"");			//Aktualizacja elementow drzewa - zapamietuje sciezki do kazdego nodea - tworzy slownik
	}


	//Algorytm kodujacy
	void AHuffman::Przechodz(Node* element, string kod){		//Przejscie przez drzewo typem (?)
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

		//Pomocnicze wypisanie slownika
		for (int k = 0; k < size; k++)
			cout << znaki[k].znak << " " << znaki[k].kod << endl;

		return Translate();
	}

	string AHuffman::Dekoduj(string tresc ){
		if (tresc == "")
			tresc = zakodowane;
		string zwrot = "";


		//Odczytywanie liter ze slownika - przechodzenie przez drzewo za pomoca podanego schamatu
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
		swap(zwrot.max, zwrot.min);

		return zwrot;
	}

}#include "AlgHuff.h"

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


		//Zliczenie wystepujacych znakow
		int tmp;
		char znak;
		for (int k = 0; k < tekst.length(); k++){
			znak = tekst[k];
			tmp = znalezione.find(znak);
			if (tmp == -1){						//Jeœli nie znaleziono, dodajemy nowy znak do s³ownika/sringa
				znalezione += znak;
				wystapienia[size++] = 1;		//Zwiêkszamy indeks wystapienia danego znaku(nowego)
			}
			else
				wystapienia[tmp] ++;			//Zwiekszamy indeks znalezionego znaku
		}


		//Tworzenie podstawowych jednostek drzew
		znaki = new Node[size];

		for (int k = 0; k < size; k++){
			znaki[k] = Node(znalezione[k],wystapienia[k]);
		}

		//Porzadki
		this->size = size;
		tablica = znalezione;
		delete[] wystapienia;
	}

	void AHuffman::StworzDrzewo(){

		//Zapisywanie adresow wszystkich lisci
		Node** drzewa = new Node*[size];
		for (int k = 0; k < size; k++){
			drzewa[k] = &znaki[k];
		}

		//Zmienne pomocnicze
		int zmsize = size;
		MM indeksy;
		Node* tmp;
		while (zmsize > 1){		//Dopoki mamy wiecej niz jeden element w tablicy
			indeksy = MinMin(drzewa, zmsize);		//Znalezienie najmniejszych elementow
			
			
			if (indeksy.max != indeksy.min){	//dodatkowe zabezpieczenie - nie potrzebne
				tmp = new Node(drzewa[indeksy.min]->wartosc + drzewa[indeksy.max]->wartosc);	//Tworzenie nowego wezla

				//Ustawianie zmiennych wezla
				tmp->left = drzewa[indeksy.min];
				tmp->right = drzewa[indeksy.max];


				drzewa[indeksy.min] = tmp;		//Podmiana starego elementu na wezel
				swap(drzewa[indeksy.max], drzewa[--zmsize]);	//Podmiana i usuniecie ostatniego elementu z tabliy (zmiejszenie rozmiaru)
\
			}
		}

		Drzewo = drzewa[0];			//Zapamietanie adresu drzewa
		delete[] drzewa;			//Usuniecie pomocniczej tablicy



	}

	void AHuffman::StworzSlownik(){
		Przechodz(Drzewo,"");			//Aktualizacja elementow drzewa - zapamietuje sciezki do kazdego nodea - tworzy slownik
	}


	//Algorytm kodujacy
	void AHuffman::Przechodz(Node* element, string kod){		//Przejscie przez drzewo typem (?)
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

		//Pomocnicze wypisanie slownika
		for (int k = 0; k < size; k++)
			cout << znaki[k].znak << " " << znaki[k].kod << endl;

		return Translate();
	}

	string AHuffman::Dekoduj(string tresc ){
		if (tresc == "")
			tresc = zakodowane;
		string zwrot = "";


		//Odczytywanie liter ze slownika - przechodzenie przez drzewo za pomoca podanego schamatu
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
		swap(zwrot.max, zwrot.min);

		return zwrot;
	}

}#include "AlgHuff.h"

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


		//Zliczenie wystepujacych znakow
		int tmp;
		char znak;
		for (int k = 0; k < tekst.length(); k++){
			znak = tekst[k];
			tmp = znalezione.find(znak);
			if (tmp == -1){						//Jeœli nie znaleziono, dodajemy nowy znak do s³ownika/sringa
				znalezione += znak;
				wystapienia[size++] = 1;		//Zwiêkszamy indeks wystapienia danego znaku(nowego)
			}
			else
				wystapienia[tmp] ++;			//Zwiekszamy indeks znalezionego znaku
		}


		//Tworzenie podstawowych jednostek drzew
		znaki = new Node[size];

		for (int k = 0; k < size; k++){
			znaki[k] = Node(znalezione[k],wystapienia[k]);
		}

		//Porzadki
		this->size = size;
		tablica = znalezione;
		delete[] wystapienia;
	}

	void AHuffman::StworzDrzewo(){

		//Zapisywanie adresow wszystkich lisci
		Node** drzewa = new Node*[size];
		for (int k = 0; k < size; k++){
			drzewa[k] = &znaki[k];
		}

		//Zmienne pomocnicze
		int zmsize = size;
		MM indeksy;
		Node* tmp;
		while (zmsize > 1){		//Dopoki mamy wiecej niz jeden element w tablicy
			indeksy = MinMin(drzewa, zmsize);		//Znalezienie najmniejszych elementow
			
			
			if (indeksy.max != indeksy.min){	//dodatkowe zabezpieczenie - nie potrzebne
				tmp = new Node(drzewa[indeksy.min]->wartosc + drzewa[indeksy.max]->wartosc);	//Tworzenie nowego wezla

				//Ustawianie zmiennych wezla
				tmp->left = drzewa[indeksy.min];
				tmp->right = drzewa[indeksy.max];


				drzewa[indeksy.min] = tmp;		//Podmiana starego elementu na wezel
				swap(drzewa[indeksy.max], drzewa[--zmsize]);	//Podmiana i usuniecie ostatniego elementu z tabliy (zmiejszenie rozmiaru)
\
			}
		}

		Drzewo = drzewa[0];			//Zapamietanie adresu drzewa
		delete[] drzewa;			//Usuniecie pomocniczej tablicy



	}

	void AHuffman::StworzSlownik(){
		Przechodz(Drzewo,"");			//Aktualizacja elementow drzewa - zapamietuje sciezki do kazdego nodea - tworzy slownik
	}


	//Algorytm kodujacy
	void AHuffman::Przechodz(Node* element, string kod){		//Przejscie przez drzewo typem (?)
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

		//Pomocnicze wypisanie slownika
		for (int k = 0; k < size; k++)
			cout << znaki[k].znak << " " << znaki[k].kod << endl;

		return Translate();
	}

	string AHuffman::Dekoduj(string tresc ){
		if (tresc == "")
			tresc = zakodowane;
		string zwrot = "";


		//Odczytywanie liter ze slownika - przechodzenie przez drzewo za pomoca podanego schamatu
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
		swap(zwrot.max, zwrot.min);

		return zwrot;
	}

}#include "AlgHuff.h"

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


		//Zliczenie wystepujacych znakow
		int tmp;
		char znak;
		for (int k = 0; k < tekst.length(); k++){
			znak = tekst[k];
			tmp = znalezione.find(znak);
			if (tmp == -1){						//Jeœli nie znaleziono, dodajemy nowy znak do s³ownika/sringa
				znalezione += znak;
				wystapienia[size++] = 1;		//Zwiêkszamy indeks wystapienia danego znaku(nowego)
			}
			else
				wystapienia[tmp] ++;			//Zwiekszamy indeks znalezionego znaku
		}


		//Tworzenie podstawowych jednostek drzew
		znaki = new Node[size];

		for (int k = 0; k < size; k++){
			znaki[k] = Node(znalezione[k],wystapienia[k]);
		}

		//Porzadki
		this->size = size;
		tablica = znalezione;
		delete[] wystapienia;
	}

	void AHuffman::StworzDrzewo(){

		//Zapisywanie adresow wszystkich lisci
		Node** drzewa = new Node*[size];
		for (int k = 0; k < size; k++){
			drzewa[k] = &znaki[k];
		}

		//Zmienne pomocnicze
		int zmsize = size;
		MM indeksy;
		Node* tmp;
		while (zmsize > 1){		//Dopoki mamy wiecej niz jeden element w tablicy
			indeksy = MinMin(drzewa, zmsize);		//Znalezienie najmniejszych elementow
			
			
			if (indeksy.max != indeksy.min){	//dodatkowe zabezpieczenie - nie potrzebne
				tmp = new Node(drzewa[indeksy.min]->wartosc + drzewa[indeksy.max]->wartosc);	//Tworzenie nowego wezla

				//Ustawianie zmiennych wezla
				tmp->left = drzewa[indeksy.min];
				tmp->right = drzewa[indeksy.max];


				drzewa[indeksy.min] = tmp;		//Podmiana starego elementu na wezel
				swap(drzewa[indeksy.max], drzewa[--zmsize]);	//Podmiana i usuniecie ostatniego elementu z tabliy (zmiejszenie rozmiaru)
\
			}
		}

		Drzewo = drzewa[0];			//Zapamietanie adresu drzewa
		delete[] drzewa;			//Usuniecie pomocniczej tablicy



	}

	void AHuffman::StworzSlownik(){
		Przechodz(Drzewo,"");			//Aktualizacja elementow drzewa - zapamietuje sciezki do kazdego nodea - tworzy slownik
	}


	//Algorytm kodujacy
	void AHuffman::Przechodz(Node* element, string kod){		//Przejscie przez drzewo typem (?)
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

		//Pomocnicze wypisanie slownika
		for (int k = 0; k < size; k++)
			cout << znaki[k].znak << " " << znaki[k].kod << endl;

		return Translate();
	}

	string AHuffman::Dekoduj(string tresc ){
		if (tresc == "")
			tresc = zakodowane;
		string zwrot = "";


		//Odczytywanie liter ze slownika - przechodzenie przez drzewo za pomoca podanego schamatu
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
		swap(zwrot.max, zwrot.min);

		return zwrot;
	}

}#include "AlgHuff.h"

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


		//Zliczenie wystepujacych znakow
		int tmp;
		char znak;
		for (int k = 0; k < tekst.length(); k++){
			znak = tekst[k];
			tmp = znalezione.find(znak);
			if (tmp == -1){						//Jeœli nie znaleziono, dodajemy nowy znak do s³ownika/sringa
				znalezione += znak;
				wystapienia[size++] = 1;		//Zwiêkszamy indeks wystapienia danego znaku(nowego)
			}
			else
				wystapienia[tmp] ++;			//Zwiekszamy indeks znalezionego znaku
		}


		//Tworzenie podstawowych jednostek drzew
		znaki = new Node[size];

		for (int k = 0; k < size; k++){
			znaki[k] = Node(znalezione[k],wystapienia[k]);
		}

		//Porzadki
		this->size = size;
		tablica = znalezione;
		delete[] wystapienia;
	}

	void AHuffman::StworzDrzewo(){

		//Zapisywanie adresow wszystkich lisci
		Node** drzewa = new Node*[size];
		for (int k = 0; k < size; k++){
			drzewa[k] = &znaki[k];
		}

		//Zmienne pomocnicze
		int zmsize = size;
		MM indeksy;
		Node* tmp;
		while (zmsize > 1){		//Dopoki mamy wiecej niz jeden element w tablicy
			indeksy = MinMin(drzewa, zmsize);		//Znalezienie najmniejszych elementow
			
			
			if (indeksy.max != indeksy.min){	//dodatkowe zabezpieczenie - nie potrzebne
				tmp = new Node(drzewa[indeksy.min]->wartosc + drzewa[indeksy.max]->wartosc);	//Tworzenie nowego wezla

				//Ustawianie zmiennych wezla
				tmp->left = drzewa[indeksy.min];
				tmp->right = drzewa[indeksy.max];


				drzewa[indeksy.min] = tmp;		//Podmiana starego elementu na wezel
				swap(drzewa[indeksy.max], drzewa[--zmsize]);	//Podmiana i usuniecie ostatniego elementu z tabliy (zmiejszenie rozmiaru)
\
			}
		}

		Drzewo = drzewa[0];			//Zapamietanie adresu drzewa
		delete[] drzewa;			//Usuniecie pomocniczej tablicy



	}

	void AHuffman::StworzSlownik(){
		Przechodz(Drzewo,"");			//Aktualizacja elementow drzewa - zapamietuje sciezki do kazdego nodea - tworzy slownik
	}


	//Algorytm kodujacy
	void AHuffman::Przechodz(Node* element, string kod){		//Przejscie przez drzewo typem (?)
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

		//Pomocnicze wypisanie slownika
		for (int k = 0; k < size; k++)
			cout << znaki[k].znak << " " << znaki[k].kod << endl;

		return Translate();
	}

	string AHuffman::Dekoduj(string tresc ){
		if (tresc == "")
			tresc = zakodowane;
		string zwrot = "";


		//Odczytywanie liter ze slownika - przechodzenie przez drzewo za pomoca podanego schamatu
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
		swap(zwrot.max, zwrot.min);

		return zwrot;
	}

}#include "AlgHuff.h"

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


		//Zliczenie wystepujacych znakow
		int tmp;
		char znak;
		for (int k = 0; k < tekst.length(); k++){
			znak = tekst[k];
			tmp = znalezione.find(znak);
			if (tmp == -1){						//Jeœli nie znaleziono, dodajemy nowy znak do s³ownika/sringa
				znalezione += znak;
				wystapienia[size++] = 1;		//Zwiêkszamy indeks wystapienia danego znaku(nowego)
			}
			else
				wystapienia[tmp] ++;			//Zwiekszamy indeks znalezionego znaku
		}


		//Tworzenie podstawowych jednostek drzew
		znaki = new Node[size];

		for (int k = 0; k < size; k++){
			znaki[k] = Node(znalezione[k],wystapienia[k]);
		}

		//Porzadki
		this->size = size;
		tablica = znalezione;
		delete[] wystapienia;
	}

	void AHuffman::StworzDrzewo(){

		//Zapisywanie adresow wszystkich lisci
		Node** drzewa = new Node*[size];
		for (int k = 0; k < size; k++){
			drzewa[k] = &znaki[k];
		}

		//Zmienne pomocnicze
		int zmsize = size;
		MM indeksy;
		Node* tmp;
		while (zmsize > 1){		//Dopoki mamy wiecej niz jeden element w tablicy
			indeksy = MinMin(drzewa, zmsize);		//Znalezienie najmniejszych elementow
			
			
			if (indeksy.max != indeksy.min){	//dodatkowe zabezpieczenie - nie potrzebne
				tmp = new Node(drzewa[indeksy.min]->wartosc + drzewa[indeksy.max]->wartosc);	//Tworzenie nowego wezla

				//Ustawianie zmiennych wezla
				tmp->left = drzewa[indeksy.min];
				tmp->right = drzewa[indeksy.max];


				drzewa[indeksy.min] = tmp;		//Podmiana starego elementu na wezel
				swap(drzewa[indeksy.max], drzewa[--zmsize]);	//Podmiana i usuniecie ostatniego elementu z tabliy (zmiejszenie rozmiaru)
\
			}
		}

		Drzewo = drzewa[0];			//Zapamietanie adresu drzewa
		delete[] drzewa;			//Usuniecie pomocniczej tablicy



	}

	void AHuffman::StworzSlownik(){
		Przechodz(Drzewo,"");			//Aktualizacja elementow drzewa - zapamietuje sciezki do kazdego nodea - tworzy slownik
	}


	//Algorytm kodujacy
	void AHuffman::Przechodz(Node* element, string kod){		//Przejscie przez drzewo typem (?)
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

		//Pomocnicze wypisanie slownika
		for (int k = 0; k < size; k++)
			cout << znaki[k].znak << " " << znaki[k].kod << endl;

		return Translate();
	}

	string AHuffman::Dekoduj(string tresc ){
		if (tresc == "")
			tresc = zakodowane;
		string zwrot = "";


		//Odczytywanie liter ze slownika - przechodzenie przez drzewo za pomoca podanego schamatu
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
		swap(zwrot.max, zwrot.min);

		return zwrot;
	}

}#include "AlgHuff.h"

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


		//Zliczenie wystepujacych znakow
		int tmp;
		char znak;
		for (int k = 0; k < tekst.length(); k++){
			znak = tekst[k];
			tmp = znalezione.find(znak);
			if (tmp == -1){						//Jeœli nie znaleziono, dodajemy nowy znak do s³ownika/sringa
				znalezione += znak;
				wystapienia[size++] = 1;		//Zwiêkszamy indeks wystapienia danego znaku(nowego)
			}
			else
				wystapienia[tmp] ++;			//Zwiekszamy indeks znalezionego znaku
		}


		//Tworzenie podstawowych jednostek drzew
		znaki = new Node[size];

		for (int k = 0; k < size; k++){
			znaki[k] = Node(znalezione[k],wystapienia[k]);
		}

		//Porzadki
		this->size = size;
		tablica = znalezione;
		delete[] wystapienia;
	}

	void AHuffman::StworzDrzewo(){

		//Zapisywanie adresow wszystkich lisci
		Node** drzewa = new Node*[size];
		for (int k = 0; k < size; k++){
			drzewa[k] = &znaki[k];
		}

		//Zmienne pomocnicze
		int zmsize = size;
		MM indeksy;
		Node* tmp;
		while (zmsize > 1){		//Dopoki mamy wiecej niz jeden element w tablicy
			indeksy = MinMin(drzewa, zmsize);		//Znalezienie najmniejszych elementow
			
			
			if (indeksy.max != indeksy.min){	//dodatkowe zabezpieczenie - nie potrzebne
				tmp = new Node(drzewa[indeksy.min]->wartosc + drzewa[indeksy.max]->wartosc);	//Tworzenie nowego wezla

				//Ustawianie zmiennych wezla
				tmp->left = drzewa[indeksy.min];
				tmp->right = drzewa[indeksy.max];


				drzewa[indeksy.min] = tmp;		//Podmiana starego elementu na wezel
				swap(drzewa[indeksy.max], drzewa[--zmsize]);	//Podmiana i usuniecie ostatniego elementu z tabliy (zmiejszenie rozmiaru)
\
			}
		}

		Drzewo = drzewa[0];			//Zapamietanie adresu drzewa
		delete[] drzewa;			//Usuniecie pomocniczej tablicy



	}

	void AHuffman::StworzSlownik(){
		Przechodz(Drzewo,"");			//Aktualizacja elementow drzewa - zapamietuje sciezki do kazdego nodea - tworzy slownik
	}


	//Algorytm kodujacy
	void AHuffman::Przechodz(Node* element, string kod){		//Przejscie przez drzewo typem (?)
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

		//Pomocnicze wypisanie slownika
		for (int k = 0; k < size; k++)
			cout << znaki[k].znak << " " << znaki[k].kod << endl;

		return Translate();
	}

	string AHuffman::Dekoduj(string tresc ){
		if (tresc == "")
			tresc = zakodowane;
		string zwrot = "";


		//Odczytywanie liter ze slownika - przechodzenie przez drzewo za pomoca podanego schamatu
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
		swap(zwrot.max, zwrot.min);

		return zwrot;
	}

}#include "AlgHuff.h"

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


		//Zliczenie wystepujacych znakow
		int tmp;
		char znak;
		for (int k = 0; k < tekst.length(); k++){
			znak = tekst[k];
			tmp = znalezione.find(znak);
			if (tmp == -1){						//Jeœli nie znaleziono, dodajemy nowy znak do s³ownika/sringa
				znalezione += znak;
				wystapienia[size++] = 1;		//Zwiêkszamy indeks wystapienia danego znaku(nowego)
			}
			else
				wystapienia[tmp] ++;			//Zwiekszamy indeks znalezionego znaku
		}


		//Tworzenie podstawowych jednostek drzew
		znaki = new Node[size];

		for (int k = 0; k < size; k++){
			znaki[k] = Node(znalezione[k],wystapienia[k]);
		}

		//Porzadki
		this->size = size;
		tablica = znalezione;
		delete[] wystapienia;
	}

	void AHuffman::StworzDrzewo(){

		//Zapisywanie adresow wszystkich lisci
		Node** drzewa = new Node*[size];
		for (int k = 0; k < size; k++){
			drzewa[k] = &znaki[k];
		}

		//Zmienne pomocnicze
		int zmsize = size;
		MM indeksy;
		Node* tmp;
		while (zmsize > 1){		//Dopoki mamy wiecej niz jeden element w tablicy
			indeksy = MinMin(drzewa, zmsize);		//Znalezienie najmniejszych elementow
			
			
			if (indeksy.max != indeksy.min){	//dodatkowe zabezpieczenie - nie potrzebne
				tmp = new Node(drzewa[indeksy.min]->wartosc + drzewa[indeksy.max]->wartosc);	//Tworzenie nowego wezla

				//Ustawianie zmiennych wezla
				tmp->left = drzewa[indeksy.min];
				tmp->right = drzewa[indeksy.max];


				drzewa[indeksy.min] = tmp;		//Podmiana starego elementu na wezel
				swap(drzewa[indeksy.max], drzewa[--zmsize]);	//Podmiana i usuniecie ostatniego elementu z tabliy (zmiejszenie rozmiaru)
\
			}
		}

		Drzewo = drzewa[0];			//Zapamietanie adresu drzewa
		delete[] drzewa;			//Usuniecie pomocniczej tablicy



	}

	void AHuffman::StworzSlownik(){
		Przechodz(Drzewo,"");			//Aktualizacja elementow drzewa - zapamietuje sciezki do kazdego nodea - tworzy slownik
	}


	//Algorytm kodujacy
	void AHuffman::Przechodz(Node* element, string kod){		//Przejscie przez drzewo typem (?)
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

		//Pomocnicze wypisanie slownika
		for (int k = 0; k < size; k++)
			cout << znaki[k].znak << " " << znaki[k].kod << endl;

		return Translate();
	}

	string AHuffman::Dekoduj(string tresc ){
		if (tresc == "")
			tresc = zakodowane;
		string zwrot = "";


		//Odczytywanie liter ze slownika - przechodzenie przez drzewo za pomoca podanego schamatu
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
		swap(zwrot.max, zwrot.min);

		return zwrot;
	}

}#include "AlgHuff.h"

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


		//Zliczenie wystepujacych znakow
		int tmp;
		char znak;
		for (int k = 0; k < tekst.length(); k++){
			znak = tekst[k];
			tmp = znalezione.find(znak);
			if (tmp == -1){						//Jeœli nie znaleziono, dodajemy nowy znak do s³ownika/sringa
				znalezione += znak;
				wystapienia[size++] = 1;		//Zwiêkszamy indeks wystapienia danego znaku(nowego)
			}
			else
				wystapienia[tmp] ++;			//Zwiekszamy indeks znalezionego znaku
		}


		//Tworzenie podstawowych jednostek drzew
		znaki = new Node[size];

		for (int k = 0; k < size; k++){
			znaki[k] = Node(znalezione[k],wystapienia[k]);
		}

		//Porzadki
		this->size = size;
		tablica = znalezione;
		delete[] wystapienia;
	}

	void AHuffman::StworzDrzewo(){

		//Zapisywanie adresow wszystkich lisci
		Node** drzewa = new Node*[size];
		for (int k = 0; k < size; k++){
			drzewa[k] = &znaki[k];
		}

		//Zmienne pomocnicze
		int zmsize = size;
		MM indeksy;
		Node* tmp;
		while (zmsize > 1){		//Dopoki mamy wiecej niz jeden element w tablicy
			indeksy = MinMin(drzewa, zmsize);		//Znalezienie najmniejszych elementow
			
			
			if (indeksy.max != indeksy.min){	//dodatkowe zabezpieczenie - nie potrzebne
				tmp = new Node(drzewa[indeksy.min]->wartosc + drzewa[indeksy.max]->wartosc);	//Tworzenie nowego wezla

				//Ustawianie zmiennych wezla
				tmp->left = drzewa[indeksy.min];
				tmp->right = drzewa[indeksy.max];


				drzewa[indeksy.min] = tmp;		//Podmiana starego elementu na wezel
				swap(drzewa[indeksy.max], drzewa[--zmsize]);	//Podmiana i usuniecie ostatniego elementu z tabliy (zmiejszenie rozmiaru)
\
			}
		}

		Drzewo = drzewa[0];			//Zapamietanie adresu drzewa
		delete[] drzewa;			//Usuniecie pomocniczej tablicy



	}

	void AHuffman::StworzSlownik(){
		Przechodz(Drzewo,"");			//Aktualizacja elementow drzewa - zapamietuje sciezki do kazdego nodea - tworzy slownik
	}


	//Algorytm kodujacy
	void AHuffman::Przechodz(Node* element, string kod){		//Przejscie przez drzewo typem (?)
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

		//Pomocnicze wypisanie slownika
		for (int k = 0; k < size; k++)
			cout << znaki[k].znak << " " << znaki[k].kod << endl;

		return Translate();
	}

	string AHuffman::Dekoduj(string tresc ){
		if (tresc == "")
			tresc = zakodowane;
		string zwrot = "";


		//Odczytywanie liter ze slownika - przechodzenie przez drzewo za pomoca podanego schamatu
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
		swap(zwrot.max, zwrot.min);

		return zwrot;
	}

}#include "AlgHuff.h"

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


		//Zliczenie wystepujacych znakow
		int tmp;
		char znak;
		for (int k = 0; k < tekst.length(); k++){
			znak = tekst[k];
			tmp = znalezione.find(znak);
			if (tmp == -1){						//Jeœli nie znaleziono, dodajemy nowy znak do s³ownika/sringa
				znalezione += znak;
				wystapienia[size++] = 1;		//Zwiêkszamy indeks wystapienia danego znaku(nowego)
			}
			else
				wystapienia[tmp] ++;			//Zwiekszamy indeks znalezionego znaku
		}


		//Tworzenie podstawowych jednostek drzew
		znaki = new Node[size];

		for (int k = 0; k < size; k++){
			znaki[k] = Node(znalezione[k],wystapienia[k]);
		}

		//Porzadki
		this->size = size;
		tablica = znalezione;
		delete[] wystapienia;
	}

	void AHuffman::StworzDrzewo(){

		//Zapisywanie adresow wszystkich lisci
		Node** drzewa = new Node*[size];
		for (int k = 0; k < size; k++){
			drzewa[k] = &znaki[k];
		}

		//Zmienne pomocnicze
		int zmsize = size;
		MM indeksy;
		Node* tmp;
		while (zmsize > 1){		//Dopoki mamy wiecej niz jeden element w tablicy
			indeksy = MinMin(drzewa, zmsize);		//Znalezienie najmniejszych elementow
			
			
			if (indeksy.max != indeksy.min){	//dodatkowe zabezpieczenie - nie potrzebne
				tmp = new Node(drzewa[indeksy.min]->wartosc + drzewa[indeksy.max]->wartosc);	//Tworzenie nowego wezla

				//Ustawianie zmiennych wezla
				tmp->left = drzewa[indeksy.min];
				tmp->right = drzewa[indeksy.max];


				drzewa[indeksy.min] = tmp;		//Podmiana starego elementu na wezel
				swap(drzewa[indeksy.max], drzewa[--zmsize]);	//Podmiana i usuniecie ostatniego elementu z tabliy (zmiejszenie rozmiaru)
\
			}
		}

		Drzewo = drzewa[0];			//Zapamietanie adresu drzewa
		delete[] drzewa;			//Usuniecie pomocniczej tablicy



	}

	void AHuffman::StworzSlownik(){
		Przechodz(Drzewo,"");			//Aktualizacja elementow drzewa - zapamietuje sciezki do kazdego nodea - tworzy slownik
	}


	//Algorytm kodujacy
	void AHuffman::Przechodz(Node* element, string kod){		//Przejscie przez drzewo typem (?)
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

		//Pomocnicze wypisanie slownika
		for (int k = 0; k < size; k++)
			cout << znaki[k].znak << " " << znaki[k].kod << endl;

		return Translate();
	}

	string AHuffman::Dekoduj(string tresc ){
		if (tresc == "")
			tresc = zakodowane;
		string zwrot = "";


		//Odczytywanie liter ze slownika - przechodzenie przez drzewo za pomoca podanego schamatu
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
		swap(zwrot.max, zwrot.min);

		return zwrot;
	}

}#include "AlgHuff.h"

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


		//Zliczenie wystepujacych znakow
		int tmp;
		char znak;
		for (int k = 0; k < tekst.length(); k++){
			znak = tekst[k];
			tmp = znalezione.find(znak);
			if (tmp == -1){						//Jeœli nie znaleziono, dodajemy nowy znak do s³ownika/sringa
				znalezione += znak;
				wystapienia[size++] = 1;		//Zwiêkszamy indeks wystapienia danego znaku(nowego)
			}
			else
				wystapienia[tmp] ++;			//Zwiekszamy indeks znalezionego znaku
		}


		//Tworzenie podstawowych jednostek drzew
		znaki = new Node[size];

		for (int k = 0; k < size; k++){
			znaki[k] = Node(znalezione[k],wystapienia[k]);
		}

		//Porzadki
		this->size = size;
		tablica = znalezione;
		delete[] wystapienia;
	}

	void AHuffman::StworzDrzewo(){

		//Zapisywanie adresow wszystkich lisci
		Node** drzewa = new Node*[size];
		for (int k = 0; k < size; k++){
			drzewa[k] = &znaki[k];
		}

		//Zmienne pomocnicze
		int zmsize = size;
		MM indeksy;
		Node* tmp;
		while (zmsize > 1){		//Dopoki mamy wiecej niz jeden element w tablicy
			indeksy = MinMin(drzewa, zmsize);		//Znalezienie najmniejszych elementow
			
			
			if (indeksy.max != indeksy.min){	//dodatkowe zabezpieczenie - nie potrzebne
				tmp = new Node(drzewa[indeksy.min]->wartosc + drzewa[indeksy.max]->wartosc);	//Tworzenie nowego wezla

				//Ustawianie zmiennych wezla
				tmp->left = drzewa[indeksy.min];
				tmp->right = drzewa[indeksy.max];


				drzewa[indeksy.min] = tmp;		//Podmiana starego elementu na wezel
				swap(drzewa[indeksy.max], drzewa[--zmsize]);	//Podmiana i usuniecie ostatniego elementu z tabliy (zmiejszenie rozmiaru)
\
			}
		}

		Drzewo = drzewa[0];			//Zapamietanie adresu drzewa
		delete[] drzewa;			//Usuniecie pomocniczej tablicy



	}

	void AHuffman::StworzSlownik(){
		Przechodz(Drzewo,"");			//Aktualizacja elementow drzewa - zapamietuje sciezki do kazdego nodea - tworzy slownik
	}


	//Algorytm kodujacy
	void AHuffman::Przechodz(Node* element, string kod){		//Przejscie przez drzewo typem (?)
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

		//Pomocnicze wypisanie slownika
		for (int k = 0; k < size; k++)
			cout << znaki[k].znak << " " << znaki[k].kod << endl;

		return Translate();
	}

	string AHuffman::Dekoduj(string tresc ){
		if (tresc == "")
			tresc = zakodowane;
		string zwrot = "";


		//Odczytywanie liter ze slownika - przechodzenie przez drzewo za pomoca podanego schamatu
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
		swap(zwrot.max, zwrot.min);

		return zwrot;
	}

}#include "AlgHuff.h"

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


		//Zliczenie wystepujacych znakow
		int tmp;
		char znak;
		for (int k = 0; k < tekst.length(); k++){
			znak = tekst[k];
			tmp = znalezione.find(znak);
			if (tmp == -1){						//Jeœli nie znaleziono, dodajemy nowy znak do s³ownika/sringa
				znalezione += znak;
				wystapienia[size++] = 1;		//Zwiêkszamy indeks wystapienia danego znaku(nowego)
			}
			else
				wystapienia[tmp] ++;			//Zwiekszamy indeks znalezionego znaku
		}


		//Tworzenie podstawowych jednostek drzew
		znaki = new Node[size];

		for (int k = 0; k < size; k++){
			znaki[k] = Node(znalezione[k],wystapienia[k]);
		}

		//Porzadki
		this->size = size;
		tablica = znalezione;
		delete[] wystapienia;
	}

	void AHuffman::StworzDrzewo(){

		//Zapisywanie adresow wszystkich lisci
		Node** drzewa = new Node*[size];
		for (int k = 0; k < size; k++){
			drzewa[k] = &znaki[k];
		}

		//Zmienne pomocnicze
		int zmsize = size;
		MM indeksy;
		Node* tmp;
		while (zmsize > 1){		//Dopoki mamy wiecej niz jeden element w tablicy
			indeksy = MinMin(drzewa, zmsize);		//Znalezienie najmniejszych elementow
			
			
			if (indeksy.max != indeksy.min){	//dodatkowe zabezpieczenie - nie potrzebne
				tmp = new Node(drzewa[indeksy.min]->wartosc + drzewa[indeksy.max]->wartosc);	//Tworzenie nowego wezla

				//Ustawianie zmiennych wezla
				tmp->left = drzewa[indeksy.min];
				tmp->right = drzewa[indeksy.max];


				drzewa[indeksy.min] = tmp;		//Podmiana starego elementu na wezel
				swap(drzewa[indeksy.max], drzewa[--zmsize]);	//Podmiana i usuniecie ostatniego elementu z tabliy (zmiejszenie rozmiaru)
\
			}
		}

		Drzewo = drzewa[0];			//Zapamietanie adresu drzewa
		delete[] drzewa;			//Usuniecie pomocniczej tablicy



	}

	void AHuffman::StworzSlownik(){
		Przechodz(Drzewo,"");			//Aktualizacja elementow drzewa - zapamietuje sciezki do kazdego nodea - tworzy slownik
	}


	//Algorytm kodujacy
	void AHuffman::Przechodz(Node* element, string kod){		//Przejscie przez drzewo typem (?)
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

		//Pomocnicze wypisanie slownika
		for (int k = 0; k < size; k++)
			cout << znaki[k].znak << " " << znaki[k].kod << endl;

		return Translate();
	}

	string AHuffman::Dekoduj(string tresc ){
		if (tresc == "")
			tresc = zakodowane;
		string zwrot = "";


		//Odczytywanie liter ze slownika - przechodzenie przez drzewo za pomoca podanego schamatu
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
		swap(zwrot.max, zwrot.min);

		return zwrot;
	}

}#include "AlgHuff.h"

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


		//Zliczenie wystepujacych znakow
		int tmp;
		char znak;
		for (int k = 0; k < tekst.length(); k++){
			znak = tekst[k];
			tmp = znalezione.find(znak);
			if (tmp == -1){						//Jeœli nie znaleziono, dodajemy nowy znak do s³ownika/sringa
				znalezione += znak;
				wystapienia[size++] = 1;		//Zwiêkszamy indeks wystapienia danego znaku(nowego)
			}
			else
				wystapienia[tmp] ++;			//Zwiekszamy indeks znalezionego znaku
		}


		//Tworzenie podstawowych jednostek drzew
		znaki = new Node[size];

		for (int k = 0; k < size; k++){
			znaki[k] = Node(znalezione[k],wystapienia[k]);
		}

		//Porzadki
		this->size = size;
		tablica = znalezione;
		delete[] wystapienia;
	}

	void AHuffman::StworzDrzewo(){

		//Zapisywanie adresow wszystkich lisci
		Node** drzewa = new Node*[size];
		for (int k = 0; k < size; k++){
			drzewa[k] = &znaki[k];
		}

		//Zmienne pomocnicze
		int zmsize = size;
		MM indeksy;
		Node* tmp;
		while (zmsize > 1){		//Dopoki mamy wiecej niz jeden element w tablicy
			indeksy = MinMin(drzewa, zmsize);		//Znalezienie najmniejszych elementow
			
			
			if (indeksy.max != indeksy.min){	//dodatkowe zabezpieczenie - nie potrzebne
				tmp = new Node(drzewa[indeksy.min]->wartosc + drzewa[indeksy.max]->wartosc);	//Tworzenie nowego wezla

				//Ustawianie zmiennych wezla
				tmp->left = drzewa[indeksy.min];
				tmp->right = drzewa[indeksy.max];


				drzewa[indeksy.min] = tmp;		//Podmiana starego elementu na wezel
				swap(drzewa[indeksy.max], drzewa[--zmsize]);	//Podmiana i usuniecie ostatniego elementu z tabliy (zmiejszenie rozmiaru)
\
			}
		}

		Drzewo = drzewa[0];			//Zapamietanie adresu drzewa
		delete[] drzewa;			//Usuniecie pomocniczej tablicy



	}

	void AHuffman::StworzSlownik(){
		Przechodz(Drzewo,"");			//Aktualizacja elementow drzewa - zapamietuje sciezki do kazdego nodea - tworzy slownik
	}


	//Algorytm kodujacy
	void AHuffman::Przechodz(Node* element, string kod){		//Przejscie przez drzewo typem (?)
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

		//Pomocnicze wypisanie slownika
		for (int k = 0; k < size; k++)
			cout << znaki[k].znak << " " << znaki[k].kod << endl;

		return Translate();
	}

	string AHuffman::Dekoduj(string tresc ){
		if (tresc == "")
			else
				wystapienia[tmp] ++;			//Zwiekszamy indeks znalezionego znaku
		}


		//Tworzenie podstawowych jednostek drzew
		znaki = new Node[size];

		for (int k = 0; k < size; k++){
			znaki[k] = Node(znalezione[k],wystapienia[k]);
		}

		//Porzadki
		this->size = size;
		tablica = znalezione;
		delete[] wystapienia;
	}

	void AHuffman::StworzDrzewo(){

		//Zapisywanie adresow wszystkich lisci
		Node** drzewa = new Node*[size];
		for (int k = 0; k < size; k++){
			drzewa[k] = &znaki[k];
		}

		//Zmienne pomocnicze
		int zmsize = size;
		MM indeksy;
		Node* tmp;
		while (zmsize > 1){		//Dopoki mamy wiecej niz jeden element w tablicy
			indeksy = MinMin(drzewa, zmsize);		//Znalezienie najmniejszych elementow
			
			
			if (indeksy.max != indeksy.min){	//dodatkowe zabezpieczenie - nie potrzebne
				tmp = new Node(drzewa[indeksy.min]->wartosc + drzewa[indeksy.max]->wartosc);	//Tworzenie nowego wezla
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
		swap(zwrot.max, zwrot.min);

		return zwrot;
	}

}#include "AlgHuff.h"

namespace _AHuffman{



		return zwrot;
	}

}