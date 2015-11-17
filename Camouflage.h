#ifndef COMOUFLAGE_H
#define COMOUFLAGE_H

#include "RAWFile.h"

namespace _Camouflage
{
	class ACamo
	{

	public:
		ACamo();
		~ACamo();
		RAWFile<float> MaskFreq(float);
		RAWFile<float> MaskTime(float);
	};
	
}

#endif
