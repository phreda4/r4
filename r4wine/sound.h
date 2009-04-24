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
#ifndef	SOUND_H
#define SOUND_H

#include <windows.h>
#include <mmsystem.h>

#ifdef FMOD

#include <fmod/fmod.h>

#else

#define ABUFFERSIZE             4410
#define	REPLAY_RATE				44100
#define	REPLAY_DEPTH			16
#define	REPLAY_SAMPLELEN		(REPLAY_DEPTH/8)

extern int bSO[2][ABUFFERSIZE];
extern int *bAct;

extern int bSI[ABUFFERSIZE];

extern int evtsound;

inline int *bosound(void) { return bAct; }
inline int *bisound(void) { return bSI; }

int sound_open(HWND hWnd);
void sound_close(void);
#endif

#endif
