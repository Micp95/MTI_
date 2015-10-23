#ifndef HUFFDRZEWO_H
#define HUFFDRZEWO_H

#include <string>
#include <iostream>

class Node
{
public:
	Node(char znak, int wartosc);
	Node(int wartosc);
	~Node();

	bool CzyLisc;
	char znak;
	int wartosc;
	Node* left, *right;
};





#endif