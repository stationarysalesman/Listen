#pragma once
#include <Audioclient.h>
#include "MyAudioSink.h"
class MyAudioSink
{
public:
	MyAudioSink(void);
	MyAudioSink(float *);
	~MyAudioSink(void);
	HRESULT SetFormat(WAVEFORMATEX *);
	HRESULT CopyData(BYTE *, UINT32, BOOL *);
private:
	WAVEFORMATEX *pwfx;
	float *sharedBuffer; /* Location of shared buffer for sampled signal */
};

