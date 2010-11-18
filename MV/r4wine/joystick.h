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
#ifndef JOY_H
#define JOY_H

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <mmsystem.h> //Joystick support

#define MAX_JOYSTICKS	16
#define MAX_AXES	6       /* each joystick can have up to 6 axes */
#define MAX_BUTTONS	32      /* and 32 buttons                      */

extern int cntJoy;
extern JOYINFOEX joy_info[MAX_JOYSTICKS];       

void InitJoystick(HWND hWnd);
void ReleaseJoystick();

inline int getjoy(int j)
{
joyGetPosEx(j, &joy_info[j]);
return (int)&joy_info[j];
}


#endif
