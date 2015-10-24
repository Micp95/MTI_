#ifndef HUFFDRZEWO_H
#define HUFFDRZEWO_H

#include <string>
#include <iostream>


using namespace std;

namespace _AHuffman{

	class Node
	{
	public:
		//Konstruktory i destruktory
		Node(char znak, int wartosc);	//Konstruktor dla liscia
		Node(int wartosc);				//Konstruktor dla wezla
		Node();							//Kostruktor do mozliwosci tworzenia tablicy
		~Node();


		void Odwiedz(string kod);		//Przypisanie kodu do znaku

		//Struktura przechowywanych danych
		bool CzyLisc;		//Czy element przechowuje znak? - czy jest lisciem
		Node* left, *right;	//Struktura drzewa BST

		int wartosc;		//Przechowywana waga wezla
		char znak;			//Przechowywany znak
		string kod;			//Przechowywany kod odpowiadajacy danemu znaku
	};


}





#endif