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

#ifndef GRAF_H
#define GRAF_H

#define WIN32_LEAN_AND_MEAN
#define WIN32_EXTRA_LEAN

#include <windows.h>
#include <mmsystem.h>

//#define NOMUL

extern HDC hDC;

extern DWORD *gr_buffer; //[1280*1024];		// buffer de pantalla
extern DWORD *XFB;

extern int gr_ancho,gr_alto;
extern DWORD gr_color1,gr_color2,col1,col2;
extern BYTE gr_alphav;
extern int MA,MB,MTX,MTY; // matrix de transformacion
extern int *mTex; // textura
#ifdef NOMUL
extern int (*setxyf)(int a,int b);
#endif

int gr_init(int XRES,int YRES);

void gr_fin(void);
void gr_clrscr(void);
void gr_redraw(void);
//---- lineas rectas
void gr_hline(int x1,int y1,int x2);
void gr_vline(int x1,int y1,int y2);
//---- basicas
void gr_setpixel(int x,int y);
void gr_setpixela(int x,int y);
void gr_line(int x1,int y1,int x2,int y2);
void gr_spline(int x1,int y1,int x2,int y2,int x3,int y3);
void gr_spline3(int x1,int y1,int x2,int y2,int x3,int y3,int x4,int y4);
//---- ALPHA
void gr_solid(void);
void gr_alpha(void);
//---- FILL POLY
void fillSol(void);
void fillLin(void);
void fillRad(void);
void fillTex(void);
//---- matriz transf
inline void fillcent(int mx,int my)     { MTX=mx;MTY=my; }
inline void fillmat(int a,int b)        { MA=a;MB=b; }
inline void fillcol(DWORD c1,DWORD c2)  { col1=c1;col2=c2; }
//---- poligono

void gr_psegmento(int x1,int y1,int x2,int y2);
void gr_pspline(int x1,int y1,int x2,int y2,int x3,int y3);
void gr_pspline3(int x1,int y1,int x2,int y2,int x3,int y3,int x4,int y4);

//////////////////////////////////////////////////////////////
#define BPP        4 // cambiar a 3 o a 2 para mas velocidad
#define VALUES     (1 << BPP)
#define MASK       (VALUES-1)
#define FTOI(v)    (((int)(v) << BPP) | (int) ((v) * (1 << BPP)))

inline void gr_pline(int x1,int y1,int x2,int y2)
{ gr_psegmento(FTOI(x1),FTOI(y1),FTOI(x2),FTOI(y2)); }
inline void gr_pcurve(int x1,int y1,int x2,int y2,int x3,int y3)
{ gr_pspline(FTOI(x1),FTOI(y1),FTOI(x2),FTOI(y2),FTOI(x3),FTOI(y3)); }
inline void gr_pcurve3(int x1,int y1,int x2,int y2,int x3,int y3,int x4,int y4)
{ gr_pspline3(FTOI(x1),FTOI(y1),FTOI(x2),FTOI(y2),FTOI(x3),FTOI(y3),FTOI(x4),FTOI(y4)); }

void gr_drawPoli(void);	

void gr_toxfb(void);
void gr_xfbto(void);

#endif
