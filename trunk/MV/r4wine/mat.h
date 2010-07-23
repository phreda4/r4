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
#ifndef MAT_H
#define MAT_H

#include <stdlib.h>

#define DWORD unsigned int
#define WORD unsigned short
#define BYTE unsigned char

#define SAME_SIGNS(a,b) (((long)((WORD)a^(WORD) b))>=0)
//#define interpola(a,b,t1,t2) ((t2>t1)?(a*t1/t2+b*(t2-t1)/t2):(a*t1/t2+b*(t1-t2)/t2))
// intervalo 0..t2
#define interpola(a,b,t1,t2) (a*t1/t2+b*(t2-t1)/t2)
//#define interpolate(v1,v2,mix) (v1*mix+v2*(1-mix))
 
inline int distance(int dx,int dy)
{
int min,max;
if (dx<0) dx=-dx;
if (dy<0) dy=-dy;
if (dx<dy) { min=dx;max=dy; } else { min=dy;max=dx; }
return (((max<<8)+(max<<3)-(max<<4)-(max<<1)+(min<<7)-(min<<5)+(min<<3)-(min<<1))>>8);
}

inline int dist(int x1,int y1,int x2,int y2)
{
return distance(x1-x2,y1-y2);
}

inline long recta(int x1,int y1,int x2,int y2,int x3,int y3)
{
int dx1=x2-x1,dy1=y2-y1;
int dx2=x3-x1,dy2=y3-y1;
return abs(dx1*dy2-dx2*dy1);
}

inline int recta2(int x1,int y1,int x2,int y2,int x3,int y3)
{
int dx1=x2-x1,dy1=y2-y1;
int dx2=x3-x1,dy2=y3-y1;
if (abs(dx1)>abs(dx2) || abs(dy1)>abs(dy2))
	return 1000;
return abs(dx1*dy2-dx2*dy1);
}

inline int recta4(int x1,int y1,int x2,int y2,int x3,int y3,int x4,int y4)
{
long dx1=x2-x1,dy1=y2-y1;
long dx2=x3-x1,dy2=y3-y1;
long dx3=x4-x1,dy3=y4-y1;
return abs(dx1*dy2-dx2*dy1)+abs(dx1*dy3-dx3*dy1);
}

inline int teta(int x1,int y1,int x2,int y2)// angulo del vector
{
int dx=x2-x1,ax=abs(dx);
int dy=y2-y1,ay=abs(dy);
if (ax+ay==0) return 0;
int t=(dy*900)/(ax+ay);
if (dx<0) t=(2*900)-t; else if (dy<0) t=(4*900)+t;
return t;
}

inline int angle(int x1,int y1,int x2,int y2,int x3,int y3) // angulo entre vectores
{
return abs(teta(x1,y1,x2,y2)-teta(x2,y2,x3,y3));
}

inline int cocurva(int x1,int y1,int x2,int y2,int x3,int y3,int x4,int y4,int *rx,int *ry)
{
int ax=(x1+x2)>>1,ay=(y1+y2)>>1;
int b1x=(x2+x3)>>1,b1y=(y2+y3)>>1;
int b2x=(ax+b1x)>>1,b2y=(ay+b1y)>>1;
int b3x=(b1x+b2x)>>1,b3y=(b1y+b2y)>>1;
int b4x=(b1x+x3)>>1,b4y=(b1y+y3)>>1;
int b5x=(b3x+b4x)>>1,b5y=(b3y+b4y)>>1;
int m1x=(x4+x1)>>1,m1y=(y4+y1)>>1;
*rx=m1x+(b5x-m1x)*2;*ry=m1y+(b5y-m1y)*2;
return angle(x1,y1,x2,y2,*rx,*ry);
}

// x2 y2 no es punto de control, es punto en la curva
inline short cospl(int x1,int y1,int x2,int y2,int x3,int y3,int x4,int y4,short *rx,short *ry)
{
int m1x=(x3+x1)>>1,m1y=(y3+y1)>>1;
int ax=m1x+(x2-m1x)*2,ay=m1y+(y2-m1y)*2;
int m2x=(x4+x1)>>1,m2y=(y4+y1)>>1;
int b1x=(ax+x3)>>1,b1y=(ay+y3)>>1;
int b2x=(x2+b1x)>>1,b2y=(y2+b1y)>>1;
int b3x=(x3+b1x)>>1,b3y=(y3+b1y)>>1;
*rx=(b1x+b2x)>>1;*ry=(b1y+b2y)>>1;
int bx=m2x+(*rx-m2x)*2,by=m2y+(*ry-m2y)*2;
return angle(x1,y1,ax,ay,bx,by);
}

#endif
