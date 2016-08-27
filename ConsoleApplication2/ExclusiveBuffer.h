#pragma once
#include "windows.h"
class ExclusiveBuffer
{
public:
	ExclusiveBuffer(void);
	~ExclusiveBuffer(void);
	int ReadBuffer(void *);
	int WriteBuffer(void *);
private:
	float *buffer; /* the protected buffer */
	HANDLE mutex; /* lock protecting object */
};

