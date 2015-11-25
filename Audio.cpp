
#include "Audio.h"
#include<iostream>
#include"Global.h"
using namespace std;

short** Wav_reader::read(string name, int size) {
	ifstream file;
	file.open(name.c_str(), ios::in | ios::binary);
	if (file.good() == true) {
	
	//pobranie hedera
		char * header = new char[44];
		file.read(header, 44);
/*		for (int i = 1; i < 45; i++)
			cout << i << ": " << (int)(unsigned char)header[i-1] << "\n";
*/
	}

	//wyswietlenie probek
	char * sampleFromTwoChannels = new char[4];	//tablica na probki
	this->numberOfSamples = (size - 44) / 2 * 2;

/*
	for (int i = 0; i < numberOfSamples; i++) {
		file.read(sampleFromTwoChannels, 4);

		int firstChannelSample = (sampleFromTwoChannels[1] << 8) | sampleFromTwoChannels[0];	//kazda probka jest 2bitowa , przesowany o 8 w prawo i sumujemy bitowo
		cout << firstChannelSample << "\n";
	}
*/

	//wczytanie probek do tablicy
	short * samplesChanelA = new short[numberOfSamples];
	short * samplesChanelB = NULL;
	
	if (numberOfChannels == 2)
		samplesChanelB = new short[numberOfSamples];

	char * temp = new char[bufferSize];	//tablica pomocnicza do wczytywania
	int sampleIterator = 0;
	
	while (file.eof() != true) {

		file.read(temp, bufferSize);
		
		for (int i = 0; i < (file.gcount() / numberOfChannels * numberOfBytesPerSample); i += numberOfChannels * numberOfBytesPerSample) {
			
			if (numberOfBytesPerSample == 2) {
				samplesChanelA[sampleIterator] = (temp[i + 1] << 8) | temp[i];
				samplesChanelB[sampleIterator] = (temp[i + 3] << 8) | temp[i + 2];
			}
			else 
				samplesChanelA[sampleIterator] = temp[i];

			sampleIterator++;
		}
	}
	//____________________________wypisanie probek_______________________________
/*	cout << "samples:\n";
	for (int j = 0; j < Global::toPrint; j++) {
		cout << j << ": " << samplesChanelA[j] << endl; //<< "\t" << samplesChanelB[j] << "\n";
	}
*/	

	file.close();
	short ** tab = new short * [2]{samplesChanelA , samplesChanelB};
	 return tab;
}

void Wav_reader::save(string name, string text) {
	fstream file;
	file.open(name.c_str(), ios::out | ios::binary | ios::trunc);

	if (file.good()==true)
		file.write(text.c_str(), text.length());
	
	file.close();
}

int get_file_size(std::string filename) // path to file
{
	FILE *p_file = NULL;
	p_file = fopen(filename.c_str(), "rb");
	fseek(p_file, 0, SEEK_END);
	int size = ftell(p_file);
	fclose(p_file);
	return size;
}
