#ifndef AUDIO_H
#define AUDIO_H
#define _CRT_SECURE_NO_WARNINGS

#include<string.h>
#include<fstream>
#include<iostream>
using namespace std;

class Wav_reader {
	string name;
public:
	int numberOfSamples;
	const int bufferSize = 1024;
	const int numberOfChannels = 1;
	const int numberOfBytesPerSample = 1;

	Wav_reader(string n) : name(n) {}
	Wav_reader() {
	}
	short** read(string, int);
	void save(string, string);

};

int get_file_size(std::string);

#endif