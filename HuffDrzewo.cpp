#include"HuffDrzewo.h"

namespace _AHuffman{

	Node::Node(char znak, int wartosc) :znak(znak),wartosc(wartosc){
		right = NULL;
		left = NULL;
		CzyLisc = true;
	}

	Node::Node(int wartosc):wartosc(wartosc){
		right = NULL;
		left = NULL;
		znak = NULL;
		CzyLisc = false;
	}

	Node::~Node()
	{
		if (right != NULL)
			delete right;
		if (left != NULL)
			delete left;
	}
	Node::Node(){
		right = NULL;
		left = NULL;
		CzyLisc = true;
		wartosc = -1;
		znak = NULL;
	}


	Tree::Tree()
	{

	}

	Tree::~Tree()
	{


	}
}
