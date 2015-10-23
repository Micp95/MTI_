#ifndef ALGHUFF_H
#define ALGHUFF_H

#include <string>


using namespace std;

namespace _AHuffman{

	class AHuffman
	{
	public:
		AHuffman();
		~AHuffman();

		void Koduj(string tresc);
		void Dekoduj(string tresc = "");

	private:

		string zakodowane;
		
	};

}





#endif