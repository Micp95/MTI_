#include <iostream>
#include <string>
#include <fstream>

#include "Kwantyzacja.h"

using namespace std;




Kwantyzacja::Kwantyzacja(int ilejest, int probkowanie, int kwanty) :kwanty(kwanty){
	proba = ilejest / probkowanie;
	//krok = 1 / ((double)kwanty*2);
}

Kwantyzacja::Kwantyzacja() :proba(44100), kwanty(256){
	//krok = 1 / ((double)kwanty * 2);
}

Kwantyzacja::~Kwantyzacja(){

}


