/*
 * Copyright (C) 2013 r4 for Android
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 * ---------------------------------------------------------------------------
 * Copyright (c) 2013, Pablo Hugo Reda <pabloreda@gmail.com>, Mar del Plata, Argentina
 * All rights reserved.
 */

#ifndef GRAF_H
#define GRAF_H

#include <android_native_app_glue.h>

extern ANativeWindow_Buffer buffergr;

#define sizewh 1024
#define shiftwh 10

extern int *XFB;
extern int *gr_buffer; 		// buffer de pantalla

extern int gr_color1,gr_color2,col1,col2;
extern unsigned char gr_alphav;
extern int MA,MB,MTX,MTY; // matrix de transformacion
extern int *mTex; // textura

void gr_init();
void gr_fin(void);
void gr_clrscr(void);
void gr_swap(struct android_app* app);

//---- lineas rectas
void gr_hline(int x1,int y1,int x2);
void gr_vline(int x1,int y1,int y2);
//---- basicas
void gr_setpixel(int x,int y);
void gr_setpixela(int x,int y,unsigned char a);
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
void fillcent(int mx,int my);
void fillmat(int a,int b);
void fillcol(unsigned int c1,unsigned int c2);
//---- poligono
void gr_psegmento(int x1,int y1,int x2,int y2);
void gr_pspline(int x1,int y1,int x2,int y2,int x3,int y3);
void gr_pspline3(int x1,int y1,int x2,int y2,int x3,int y3,int x4,int y4);

void gr_drawPoli(void);

void gr_toxfb(void);
void gr_xfbto(void);

#endif
