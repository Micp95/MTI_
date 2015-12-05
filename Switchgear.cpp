#include "Switchgear.h"
#include <iostream>
#include <string>
#include <winsock.h> 


#include "ComProtocol.h"
#include "ComProtocolSend.h"
#include "ComProtocolListen.h"

using namespace std;


void Switchgear::Server() {
	ComProtocolListen moj(port);
	Package* zwrot;

//	ComProtocolSend wysylanie[4];
	sockaddr_in clients[4];
	int actualy[4];
	for (int k = 0; k < 4; k++)
		actualy[k] = -1;

	while (true) {

		//Polaczenie nowych klientow
		moj.Connection();
		for (int k = 0; k < 4; k++)
			if (actualy[k] == -1) {
				actualy[k] = 1;
				clients[k] = moj.their_addr;
			}
		zwrot = moj.Listen();	//Tresc wiadomosci: np. login


		//Rozglaszanie


	}



}
void Switchgear::Client(string ip){

}