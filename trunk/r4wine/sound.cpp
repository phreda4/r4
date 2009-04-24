/*
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * ---------------------------------------------------------------------------
 * Copyright (c) 2006, Pablo Hugo Reda <pabloreda@gmail.com>, Mar del Plata, Argentina
 * All rights reserved.
*/
#define WIN32_LEAN_AND_MEAN
#define WIN32_EXTRA_LEAN

#include "sound.h"

#ifdef FMOD


#else

HWAVEOUT	WaveOut;
HWAVEIN     WaveIn;
WAVEHDR		wavHead[2];
WAVEHDR     wavHeadI;

int bSO[2][ABUFFERSIZE];
int bSI[ABUFFERSIZE];
int *bAct;
int bSOnro;
int evtsound;

void fillbuffer(void)
{
if (wavHead[bSOnro].dwFlags&WHDR_PREPARED) 
    waveOutUnprepareHeader(WaveOut,&wavHead[bSOnro],sizeof(WAVEHDR));
wavHead[bSOnro].lpData = (char*)bSO[bSOnro];
wavHead[bSOnro].dwBufferLength = ABUFFERSIZE*4;
waveOutPrepareHeader(WaveOut,&wavHead[bSOnro],sizeof(WAVEHDR));
waveOutWrite(WaveOut,&wavHead[bSOnro],sizeof(WAVEHDR));
bAct=bSO[bSOnro];
evtsound=1;
bSOnro=(bSOnro+1)&1;
}

static	void CALLBACK waveProcO(HWAVEOUT hwo,UINT uMsg,DWORD dwInstance,DWORD dwParam1,DWORD dwParam2)
{
if (uMsg==WOM_DONE) fillbuffer();
}

static	void CALLBACK waveProcI(HWAVEOUT hwo,UINT uMsg,DWORD dwInstance,DWORD dwParam1,DWORD dwParam2)
{
if (uMsg!=WIM_DATA) return;
waveInUnprepareHeader(WaveIn, &wavHeadI, sizeof(WAVEHDR));
}

int sound_open(HWND hWnd)
{
WAVEFORMATEX	wfx;
wfx.wFormatTag = 1;		// PCM standart.
wfx.nChannels = 2;		// Stereo
wfx.nBlockAlign = 4;
wfx.wBitsPerSample = 16;
wfx.nSamplesPerSec = 44100;
wfx.nAvgBytesPerSec = 44100*4;
wfx.cbSize = 0;

MMRESULT err;
//----------Sound OUT
err=waveOutOpen(&WaveOut,WAVE_MAPPER,&wfx,(DWORD)waveProcO,0,(DWORD)CALLBACK_FUNCTION);
if (err!=MMSYSERR_NOERROR) return -1;
memset(&wavHead[0],0,sizeof(WAVEHDR));
memset(&wavHead[1],0,sizeof(WAVEHDR));
bSOnro=0;
fillbuffer();fillbuffer();
evtsound=0;

//----------Sound IN

err=waveInOpen(&WaveIn,WAVE_MAPPER, &wfx,(DWORD)waveProcI,0,(DWORD)CALLBACK_FUNCTION);
if (err!=MMSYSERR_NOERROR) return -1;

memset(&wavHeadI,0,sizeof(WAVEHDR));
wavHeadI.lpData = (char*)bSI;
wavHeadI.dwBufferLength = ABUFFERSIZE*4;

err=waveInPrepareHeader(WaveIn,&wavHeadI,sizeof(WAVEHDR));
err=waveInAddBuffer(WaveIn,&wavHeadI,sizeof(WAVEHDR));
err=waveInStart(WaveIn);

return 0;
}

void sound_close(void)
{
waveOutClose(WaveOut);
}
#endif


