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
		RAWFile<float> MaskFreq(float,float);
		RAWFile<float> MaskTime(float, float);
	};
	
}

#endif
