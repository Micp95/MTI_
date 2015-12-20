#include "StopWatch.h"

StopWatch::StopWatch() {
	if (!::QueryPerformanceFrequency(&frequency_)) throw "Error with QueryPerformanceFrequency";
}

void StopWatch::Start() {
	::QueryPerformanceCounter(&startTime_);
}

void StopWatch::Stop() {
	::QueryPerformanceCounter(&stopTime_);
}

__int64 StopWatch::MilliSeconds() const {
	return (float)(stopTime_.QuadPart - startTime_.QuadPart) / (float)frequency_.QuadPart * 1000;

	float StopWatch::ActMiliSeconds() const {
		LARGE_INTEGER actTime_;
		::QueryPerformanceCounter(&actTime_);
		return (float)(actTime_.QuadPart - startTime_.QuadPart) / (float)frequency_.QuadPart * 1000;
	}
}