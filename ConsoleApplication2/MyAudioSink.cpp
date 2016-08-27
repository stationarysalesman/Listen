#include "MyAudioSink.h"
#include <stdio.h>

MyAudioSink::MyAudioSink(void)
{
	MyAudioSink::sharedBuffer = NULL;
}

MyAudioSink::MyAudioSink(float *sharedBuff)
{
	/* Store location of buffer */
	MyAudioSink::sharedBuffer = sharedBuff;
}

MyAudioSink::~MyAudioSink(void)
{

}


HRESULT MyAudioSink::SetFormat(WAVEFORMATEX *pwfx)
{
	//literally do nothing
	return 0;
}

HRESULT MyAudioSink::CopyData(BYTE *pData, UINT32 numFramesAvailable, BOOL *bDone)
{
	/* Get the lock */
	memcpy((void *)MyAudioSink::buff, (void *)pData, numFramesAvailable);
	printf("%f\n", buff[0]);
	return 0;
}