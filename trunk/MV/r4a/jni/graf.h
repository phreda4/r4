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

#include <android_native_app_glue.h>

#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <jni.h>
#include <sys/time.h>
#include <time.h>
#include <android/log.h>

#include <sys/resource.h>
#include <sys/syscall.h>
#include <sys/mman.h>

#include <linux/fb.h>

#include <stdio.h>
#include <stdlib.h>

extern ANativeWindow_Buffer buffergr;
extern void *XFB;


//extern void *gr_buffer; 		// buffer de pantalla
//extern int gr_ancho,gr_alto;

extern unsigned int gr_color1,gr_color2,col1,col2;
extern unsigned char gr_alphav;
extern int MA,MB,MTX,MTY; // matrix de transformacion
extern int *mTex; // textura

int gr_init(int w,int h);
void gr_fin(void);
void gr_gr();
void gr_clrscr(void);

//---- lineas rectas
void gr_hline(int x1,int y1,int x2);
void gr_vline(int x1,int y1,int y2);
//---- basicas
void gr_setpixel(int x,int y);
void gr_setpixela(int x,int y,unsigned char a);
void gr_line(int x1,int y1,int x2,int y2);
void gr_spline(int x1,int y1,int x2,int y2,int x3,int y3);
//---- ALPHA
void gr_solid(void);
void gr_alpha(void);
//---- FILL POLY
void fillSol(void);
void fillLin(void);
void fillRad(void);
void fillTex(void);
//---- matriz transf
void fillcent(int mx,int my);
void fillmat(int a,int b);
void fillcol(unsigned int c1,unsigned int c2);
//---- poligono
void gr_psegmento(int x1,int y1,int x2,int y2);
void gr_pspline(int x1,int y1,int x2,int y2,int x3,int y3);
void gr_drawPoli(void);

void gr_toxfb(void);
void gr_xfbto(void);

#endif
