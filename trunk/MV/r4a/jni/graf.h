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

#define  LOG_TAG    "r4a"
#define  LOGI(...)  __android_log_print(ANDROID_LOG_INFO,LOG_TAG,__VA_ARGS__)
#define  LOGW(...)  __android_log_print(ANDROID_LOG_WARN,LOG_TAG,__VA_ARGS__)
#define  LOGE(...)  __android_log_print(ANDROID_LOG_ERROR,LOG_TAG,__VA_ARGS__)

extern ANativeWindow_Buffer buffergr;

extern int *XFB;
extern int *gr_buffer; 		// buffer de pantalla
extern int gr_color1,gr_color2,col1,col2;
extern int MA,MB,MTX,MTY; // matrix de transformacion
extern int *mTex; // textura

void gr_init(struct android_app* app);
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
void gr_alpha(int a);
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

#define LLQ
//#define LOWQ
//#define MEDQ
//#define HIQ

//////////////////////////////////////////////////////////////
#ifdef HIQ
      #define BPP        4
      #define TOLERANCE  24
      #define QALPHA(a)  (a)
#elif defined(MEDQ)
      #define BPP        3
      #define TOLERANCE  16
      #define QALPHA(a)  ((a)&0x3|(a)<<2)
#elif defined(LOWQ)
      #define BPP        2
      #define TOLERANCE  8
      #define QALPHA(a)  ((a)<<4|(a))
#else
      #define BPP        1
      #define TOLERANCE  4
      #define QALPHA(a)  ((a)<<6|(a)<<4|(a)<<2|(a))
#endif

#define VALUES     (1<<BPP)
#define QFULL       VALUES*VALUES
#define MASK       (VALUES-1)
#define FTOI(v)    (v<<BPP)

void gr_pline(int x1,int y1,int x2,int y2);
void gr_pcurve(int x1,int y1,int x2,int y2,int x3,int y3);
void gr_pcurve3(int x1,int y1,int x2,int y2,int x3,int y3,int x4,int y4);

void gr_drawPoli(void);

void gr_toxfb(void);
void gr_xfbto(void);

#endif
