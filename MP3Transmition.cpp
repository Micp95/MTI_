#include "MP3Transmition.h"
#include <string>
#include <iostream>

//#include "lame\lame.h"

#include "ComProtocol.h"
#include "ComProtocolSend.h"
#include "lame.h"

#pragma warning(disable:4996)

//#include "lameHelper.h"

MP3Trasmition::~MP3Trasmition()
{
}

void MP3Trasmition::Transmition()
{
	ComProtocolSend strumien(port,IP);
	strumien.Connection();

	int read, write;

	FILE *pcm = fopen(File.c_str(), "rb");
	//FILE *mp3 = fopen("file.mp3", "wb");

	const int PCM_SIZE = 8192;
	const int MP3_SIZE = 8192;

	short int pcm_buffer[PCM_SIZE * 2];
	char mp3_buffer[MP3_SIZE];


	lame_t lame = lame_init();
	lame_set_in_samplerate(lame, 44100);
	lame_set_VBR(lame, vbr_default);
	lame_init_params(lame);
	
	do {
		read = fread(pcm_buffer, 2 * sizeof(short int), PCM_SIZE, pcm);
		if (read == 0)
			write = lame_encode_flush(lame, (unsigned char*)mp3_buffer, MP3_SIZE);
		else
			write = lame_encode_buffer_interleaved(lame, pcm_buffer, read, (unsigned char*)mp3_buffer, MP3_SIZE);
		strumien.Send(mp3_buffer, write);
	} while (read != 0);
	

	strumien.WaitForSendingAndEnding();
	strumien.Disconection();
}
