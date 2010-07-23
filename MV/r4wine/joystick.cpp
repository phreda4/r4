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

#include "joystick.h"

#define MAX_JOYSTICKS	16
#define MAX_AXES	6       /* each joystick can have up to 6 axes */
#define MAX_BUTTONS	32      /* and 32 buttons                      */

int cntJoy;

JOYCAPS joy_caps[MAX_JOYSTICKS];       
JOYINFOEX joy_info[MAX_JOYSTICKS];       

///////////////////////////////////////
// Initialize Joystick
///////////////////////////////////////
void InitJoystick(HWND hWnd)
{
int i,result;
cntJoy=0;
int maxdevs=joyGetNumDevs();
if (maxdevs>MAX_JOYSTICKS) maxdevs=MAX_JOYSTICKS;
for (i=JOYSTICKID1;i<maxdevs;++i) {
    joy_info[i].dwSize=sizeof(JOYINFOEX);
    joy_info[i].dwFlags=JOY_RETURNALL;
    result = joyGetPosEx(i, &joy_info[i]);
    if (result == JOYERR_NOERROR) {
        result = joyGetDevCaps(i, &joy_caps[i], sizeof(JOYCAPS));
        if (result == JOYERR_NOERROR) cntJoy++; 
        }
    }
for (i=JOYSTICKID1;i<cntJoy;i++) 
    {
    if (joyGetPosEx(i,&joy_info[i])!=JOYERR_UNPLUGGED) 
        {
        joyGetDevCaps(i, &joy_caps[i], sizeof(JOYCAPS));
        //joySetCapture(hWnd, i, NULL, TRUE);
        }
    }
} 

/////////////////////////////////////////////
// Quit and Release Joystick
/////////////////////////////////////////////
void ReleaseJoystick()
{
int i;
for (i=JOYSTICKID1;i<cntJoy;i++) 
    joyReleaseCapture(i);// release joystick
}

/*
typedef struct joyinfoex_tag {
	DWORD dwSize;
	DWORD dwFlags;
	DWORD dwXpos;
	DWORD dwYpos;
	DWORD dwZpos;
	DWORD dwRpos;
	DWORD dwUpos;
	DWORD dwVpos;
	DWORD dwButtons;
	DWORD dwButtonNumber;
	DWORD dwPOV;
	DWORD dwReserved1;
	DWORD dwReserved2;
} JOYINFOEX,*PJOYINFOEX,*LPJOYINFOEX;
*/

int getjoy(int j)
{
joyGetPosEx(j, &joy_info[j]);
return (int)&joy_info[j];
}

