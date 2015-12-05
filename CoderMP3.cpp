#include "CoderMP3.h"
#include <string>
#include <iostream>


#include "lameHelper.h"
#include <winsock.h>

using namespace std;

void CoderMP3::WAVtoMP3(char *in, char *out) {
	settings_t settings;
	lameHelper lhHandle;
	lhHandle.encode(in, out, settings);
}
void CoderMP3::MP3toWAV(char *in, char *out) {
	lameHelper lhHandle;
	lhHandle.decode(in, out);
}

