#include"HuffDrzewo.h"



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
