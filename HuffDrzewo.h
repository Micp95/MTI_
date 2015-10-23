#ifndef HUFFDRZEWO_H
#define HUFFDRZEWO_H

#include <string>
#include <iostream>


using namespace std;

namespace _AHuffman{

	class Node
	{
	public:
		Node(char znak, int wartosc);
		Node(int wartosc);
		Node();
		~Node();

		bool CzyLisc;
		char znak;
		int wartosc;
		Node* left, *right;

		string kod;
	};

	class Tree
	{
	public:
		Tree();
		~Tree();
		int wartosc;

	private:

	};

}





#endif