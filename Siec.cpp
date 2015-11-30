#include "Siec.h"

#include <stdio.h>
#include <windows.h>
#include <fstream>
#include <time.h>
#include <cstdlib>

#include "Spis.h"

#include "TCPClient.h"
#include "TCPServer.h"


using namespace std;
using namespace _MAIN;


int _Siec::PlatformaTestowaOgolna(){

	cout << "Siec." << endl;


	return 0;
}




int _Siec::PlatformaTestowaMichal(){

	return 0;
}

int _Siec::PlatformaTestowaMarysia(){

	return 0;
}

int _Siec::PlatformaTestowaKasia(){

	cout << "Siec!" << endl;
	//TCPServer server("192.168.1.5", 54345);
	TCPClient client("192.168.1.5", 54345);
	
	return 0;
}


