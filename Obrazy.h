#pragma once
#ifndef OBRAZY_H
#define OBRAZY_H

#include "Spis.h"
#include <string>
#include <fstream>

using namespace std;


namespace _Obrazy {

	int PlatformaTestowaOgolna();

	int PlatformaTestowaMichal();
	int PlatformaTestowaKasia();
	int PlatformaTestowaMarysia();

	void WykonajKonwersje(string name);
	void PoliczRozmiary(string name);
	void DopiszPlik(const string& name, fstream &plik);
}

#endif