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

#include <android_native_app_glue.h>
#include <android/log.h>
#include <stdlib.h>
#include "graf.h"

//---- buffer de video
ANativeWindow_Buffer buffergr;
int *XFB;
int *gr_buffer; 		// buffer de pantalla
int gr_realsize;

//---- variables internas
int gr_color1,gr_color2,col1,col2;
int MA,MB,MTX,MTY; // matrix de transformacion
int *mTex; // textura
int gr_alphav;

//---- variables para dibujo de poligonos
typedef struct { int y,x,yfin,deltax; } Segm;

int cntSegm=0;
Segm segmentos[1024];
int yMax,yMin;

int runlenscan[1024];
int *rl;

Segm seg0={-1,0x80000001,-1,0};
Segm *activelist[512];
Segm **activelast;

int ImplicitHeapY[1024];
int cntIHY;

void initIHY(void)
{
cntIHY=0;
activelist[0]=&seg0;
activelast=&activelist[1];
cntSegm=0;
yMax=-1;
}

void addIHY(int v)
{
int i,j;
cntIHY++;
for (i=cntIHY-1;i>0;) {
	j=(i-1)/2;
	if (ImplicitHeapY[j]<v) { ImplicitHeapY[i]=v;return; }
	ImplicitHeapY[i]=ImplicitHeapY[j];
	i=j; }
ImplicitHeapY[0]=v;
}

void moveDnY(int v,int n)
{
int i;
while (n<cntIHY/2) {
    i=(n*2)+1;
    if (i+1<cntIHY && ImplicitHeapY[i]>ImplicitHeapY[i+1])
       { i++; }
    if (ImplicitHeapY[i]>=v)
       { ImplicitHeapY[n]=v;return; }
    ImplicitHeapY[n]=ImplicitHeapY[i];
    n=i;
    }
ImplicitHeapY[n]=v;
}

int remIHY(void)
{
if (cntIHY==0) return -1;
int val=ImplicitHeapY[0];
moveDnY(ImplicitHeapY[cntIHY-1],0);
cntIHY--;
return val;
}

int heapIHY(void)
{
if (cntIHY==0) return -1;
return ImplicitHeapY[0];
}
//-----------------------------------------
#define GETPOS(a) (((a)>>20)&0xfff)
#define GETLEN(a) (((a)>>9)&0x7ff)
#define GETVAL(a) ((a)&0x1ff)
#define GETPOSF(a) ((((a)>>20)&0xfff)+(((a)>>9)&0x7ff))

#define SETPOS(a) ((a)<<20)
#define SETLEN(a) ((a)<<9)
#define SETVAL(a) (a)

#define FBASE 8

void gr_fin(void)
{
free(XFB);
free(gr_buffer);
}

//------------------------------------
#define GR_SET(X,Y) gr_pos=gr_buffer+(Y*buffergr.width)+X;
#define GR_X(X) gr_pos+=X;
#define GR_Y(Y) gr_pos+=Y*buffergr.width;

//#define ASM

#ifdef ASM
// ASM
static void blit32to565(const int *dst,const int *src, int cnt);
static void copymem32(const int *dst,const int *src, int cnt);
static void setmem32(const int *dst,int valor, int cnt);
#endif

#define RED5  0xF800
#define GRE6  0x07E0
#define BLU5  0x001F

inline static int to565(int c)
{
return ((c>>8)&RED5)|((c>>5)&GRE6)|((c>>3)&BLU5);
}

static void copia565(void)
{
#ifdef ASM
blit32to565((int*)buffergr.bits,(int*)gr_buffer,gr_realsize);
#else
register int *s=gr_buffer;
register int *d=(int*)buffergr.bits;
register int y,x;
for(y=buffergr.height;y>0;--y)
	for(x=buffergr.width;x>0;x-=8) {
        *d++=to565(*s++)|(to565(*s++)<<16);
        *d++=to565(*s++)|(to565(*s++)<<16);
        *d++=to565(*s++)|(to565(*s++)<<16);
        *d++=to565(*s++)|(to565(*s++)<<16);
        }
#endif
}

static void copia888(void)
{
#ifdef ASM
	copymem32((int*)buffergr.bits,gr_buffer,gr_realsize);
#else
register int *s=gr_buffer;
register int *d=(int*)buffergr.bits;
register int x,y;
for(y=buffergr.height;y>0;--y)
	for(x=buffergr.width;x>0;x-=8) {
    *d++=*s++;*d++=*s++;*d++=*s++;*d++=*s++;
    *d++=*s++;*d++=*s++;*d++=*s++;*d++=*s++; }
#endif
}

void (*copiabuffer)(void);

void gr_size(struct android_app* app)
{
ANativeWindow_lock(app->window, &buffergr, NULL);
gr_realsize=buffergr.width*buffergr.height;
ANativeWindow_unlockAndPost(app->window);
//LOGI("new size %d %d",buffergr.width,buffergr.height);
}

//---- inicio
void gr_init(struct android_app* app)
{
//---- obtener info pantalla
ANativeWindow_lock(app->window, &buffergr, NULL);
if (buffergr.format==4) //565
	{ copiabuffer=copia565; }
else
	{ copiabuffer=copia888; }
gr_realsize=buffergr.width*buffergr.height;
int maxsize=(buffergr.width>buffergr.height?buffergr.width:buffergr.height);
maxsize*=maxsize;
ANativeWindow_unlockAndPost(app->window);

gr_buffer=(int*)malloc(maxsize<<2);
XFB=(int*)malloc(maxsize<<2);

//---- poligonos2
initIHY();
fillSol();

//---- colores
gr_color2=0;gr_color1=0xffffff;
col1=0;col2=0xffffff;
gr_solid();
}

inline void fillcent(int mx,int my)
{ MTX=mx;MTY=my; }
inline void fillmat(int a,int b)
{ MA=a;MB=b; }
inline void fillcol(unsigned int c1,unsigned int c2)
{ col1=c1;col2=c2; }

void gr_swap(struct android_app* app)
{
ANativeWindow_lock(app->window, &buffergr, NULL);
copiabuffer();
ANativeWindow_unlockAndPost(app->window);
}

void gr_clrscr(void)
{
#ifdef ASM
setmem32(gr_buffer,gr_color2,gr_realsize);
#else
register int *d=gr_buffer;
register int i,c=gr_color2;
//for(i=buffergr.height*buffergr.width;i>0;i-=8)
for(i=gr_realsize;i>0;i-=8)
	{ *d++=c;*d++=c;*d++=c;*d++=c;*d++=c;*d++=c;*d++=c;*d++=c; }
#endif
}

void gr_toxfb(void)
{
#ifdef ASM
copymem32(XFB,gr_buffer,gr_realsize);
#else
register int *d=XFB;
register int *s=gr_buffer;
register int i;
//for(i=buffergr.height*buffergr.width;i>0;i-=8)
for(i=gr_realsize;i>0;i-=8)
	{ *d++=*s++;*d++=*s++;*d++=*s++;*d++=*s++;*d++=*s++;*d++=*s++;*d++=*s++;*d++=*s++; }
#endif
}

void gr_xfbto(void)
{
#ifdef ASM
copymem32(gr_buffer,XFB,gr_realsize);
#else
register int *d=gr_buffer;
register int *s=XFB;
register int i;
//for(i=buffergr.height*buffergr.width;i>0;i-=8)
for(i=gr_realsize;i>0;i-=8)
	{ *d++=*s++;*d++=*s++;*d++=*s++;*d++=*s++;*d++=*s++;*d++=*s++;*d++=*s++;*d++=*s++; }
#endif
}

#define RED_MASK 0xFF0000
#define GRE_MASK 0xFF00
#define BLU_MASK 0xFF

#define MASK1 0xFF00FF
#define MASK2 0x00FF00

inline int gr_mix(int col,unsigned char alpha)
{
register int B=(col&MASK1);
register int RB=(((((gr_color1&MASK1)-B)*alpha)>>8)+B)&MASK1;
B=col&MASK2;
return ((((((gr_color1&MASK2)-B)*alpha)>>8)+B)&MASK2)|RB;
}
//--------------- RUTINAS DE DIBUJO
//---- solido
void _gr_pixels(int *gr_pos)		{*gr_pos=gr_color1;}
void _gr_pixela(int *gr_pos,unsigned char a){*gr_pos=gr_mix(*gr_pos,a);}

//---- solido con alpha
void _gr_pixelsa(int *gr_pos)		{*gr_pos=gr_mix(*gr_pos,gr_alphav);}
void _gr_pixelaa(int *gr_pos,unsigned char a) {*gr_pos=gr_mix(*gr_pos,(unsigned char)((unsigned int)(a*gr_alphav)>>8));}

//--------------- RUTINAS DE DIBUJO
void (*gr_pixel)(int *gr_pos);
void (*gr_pixela)(int *gr_pos,unsigned char a);

void gr_solid(void) {gr_pixel=_gr_pixels;gr_pixela=_gr_pixela;gr_alphav=255;}
void gr_alpha(int a)
{
if (a>256) { gr_solid();return; }
gr_alphav=a;gr_pixel=_gr_pixelsa;gr_pixela=_gr_pixelaa;
}

//--------------- DIBUJO DE POLIGONO
void runlenSolido(int *linea);
void runlenLineal(int *linea);
void runlenRadial(int *linea);
void runlenTextura(int *linea);

void (*runlen)(int *linea);

void fillSol(void) { runlen=runlenSolido; }
void fillLin(void) { runlen=runlenLineal; }
void fillRad(void) { runlen=runlenRadial; }
void fillTex(void) { runlen=runlenTextura; }

//------------------------------------
void gr_hline(int x1,int y1,int x2)
{
if (x1<0) x1=0;
if (x2>=buffergr.width) { x2=buffergr.width-1;if (x1>=buffergr.width) return; }
register int *gr_pos;
GR_SET(x1,y1);
int *pf=gr_pos+x2-x1+1;
do { gr_pixel(gr_pos);gr_pos++; } while (gr_pos<pf);
}

void gr_vline(int x1,int y1,int y2)
{
if (y1<0) y1=0;
if (y2>=buffergr.height) { y2=buffergr.height-1;if (y1>=buffergr.height) return; }
register int *gr_pos;
GR_SET(x1,y1);
int *pf=gr_pos+((y2-y1+1)*buffergr.width);
do { gr_pixel(gr_pos);gr_pos+=buffergr.width; } while (gr_pos<pf);
}

int gr_clipline(int *X1,int *Y1,int *X2,int *Y2)
{
int C1,C2,V;
if (*X1<0) C1=1; else C1=0;
if (*X1>=buffergr.width) C1|=0x2;
if (*Y1<0) C1|=0x4;
if (*Y1>=buffergr.height-1) C1|=0x8;
if (*X2<0) C2=1; else C2=0;
if (*X2>=buffergr.width) C2|=0x2;
if (*Y2<0) C2|=0x4;
if (*Y2>=buffergr.height-1) C2|=0x8;
if ((C1&C2)==0 && (C1|C2)!=0) {
	if ((C1&12)!=0) {
		if (C1<8) V=0; else V=buffergr.height-2;
		*X1+=(V-*Y1)*(*X2-*X1)/(*Y2-*Y1);*Y1=V;
		if (*X1<0) C1=1; else C1=0;
		if (*X1>=buffergr.width) C1|=0x2;
		}
    if ((C2&12)!=0) {
		if (C2<8) V=0; else V=buffergr.height-2;
		*X2+=(V-*Y2)*(*X2-*X1)/(*Y2-*Y1);*Y2=V;
		if (*X2<0) C2=1; else C2=0;
		if (*X2>=buffergr.width) C2|=0x2;
		}
    if ((C1&C2)==0 && (C1|C2)!=0) {
		if (C1!=0) {
			if (C1==1) V=0; else V=buffergr.width-1;
			*Y1+=(V-*X1)*(*Y2-*Y1)/(*X2-*X1);*X1=V;C1=0;
			}
		if (C2!=0) {
			if (C2==1) V=0; else V=buffergr.width-1;
			*Y2+=(V-*X2)*(*Y2-*Y1)/(*X2-*X1);*X2=V;C2=0;
			}
		}
	}
return (C1|C2)==0;
}

//---- con clip
inline void gr_setpixel(int x,int y)
{
if ((unsigned)x>=(unsigned)buffergr.width || (unsigned)y>=(unsigned)buffergr.height) return;
register int *gr_pos;
GR_SET(x,y);gr_pixel(gr_pos);
}

inline void gr_setpixela(int x,int y,unsigned char a)
{
if ((unsigned)x>=(unsigned)buffergr.width || (unsigned)y>=(unsigned)buffergr.height) return;
register int *gr_pos;
GR_SET(x,y);gr_pixela(gr_pos,a);
}

#define swap(a,b) { a^=b;b^=a;a^=b; }

void gr_line(int x1,int y1,int x2,int y2)
{
if (!gr_clipline(&x1,&y1,&x2,&y2)) return;
int dx,dy,sx,d;
if (x1==x2) { if (y1>y2) swap(y1,y2); gr_vline(x1,y1,y2);return; }
if (y1==y2) { if (x1>x2) swap(x1,x2); gr_hline(x1,y1,x2);return; }
if (y1>y2) { swap(x1,x2);swap(y1,y2); }
dx=x2-x1;dy=y2-y1;
if (dx>0) sx=1; else { sx=-1;dx=-dx; }
uint16_t ea,ec=0;unsigned char ci;
register int *gr_pos;
GR_SET(x1,y1);gr_pixel(gr_pos);
if (dy>dx) 	{
	ea=(dx<<16)/dy;
    while (dy>0) {
        dy--;d=ec;ec+=ea;if (ec<=d) x1+=sx;
        y1++;ci=ec>>8;
		GR_SET(x1,y1);gr_pixela(gr_pos,255-ci);GR_X(sx);gr_pixela(gr_pos,ci);
		}
} else {// DY <= DX
    ea=(dy<<16)/dx;
    while (dx>0) {
        dx--;d=ec;ec+=ea;if (ec<=d) y1++;
        x1+=sx;ci=ec>>8;
		GR_SET(x1,y1);gr_pixela(gr_pos,255-ci);
        GR_Y(1);gr_pixela(gr_pos,ci);
		}
	}
}

//inline int abs(int a ) { return (a+(a>>31))^(a>>31); }

void gr_spline(int x1,int y1,int x2,int y2,int x3,int y3)
{
int x11=(x1+x2)>>1,y11=(y1+y2)>>1;
int x21=(x2+x3)>>1,y21=(y2+y3)>>1;
int x22=(x11+x21)>>1,y22=(y11+y21)>>1;
if (abs(x22-x2)+abs(y22-y2)<4)
    { gr_line(x1,y1,x22,y22);gr_line(x22,y22,x3,y3); return; }
gr_spline(x1,y1,x11,y11,x22,y22);
gr_spline(x22,y22,x21,y21,x3,y3);
}

void gr_spline3(int x1,int y1,int x2,int y2,int x3,int y3,int x4,int y4)
{
if (abs(x1+x3-x2-x2)+abs(y1+y3-y2-y2)+abs(x2+x4-x3-x3)+abs(y2+y4-y3-y3)<=4)
    { gr_line(x1,y1,x4,y4);return; }
int gx=(x2+x3)/2,gy=(y2+y3)/2;
int b2x=(x3+x4)/2,b2y=(y3+y4)/2;
int a1x=(x1+x2)/2,a1y=(y1+y2)/2;
int b1x=(gx+b2x)/2,b1y=(gy+b2y)/2;
int a2x=(gx+a1x)/2,a2y=(gy+a1y)/2;
int mx=(b1x+a2x)/2,my=(b1y+a2y)/2;
gr_spline3(x1,y1,a1x,a1y,a2x,a2y,mx,my);
gr_spline3(mx,my,b1x,b1y,b2x,b2y,x4,y4);
}

// poligono
void gr_psegmento(int x1,int y1,int x2,int y2)
{
if (y1==y2) return;
if (y1>y2) { swap(x1,x2);swap(y1,y2); }
if (y1>=(buffergr.height<<BPP) || y2<=0) return;
x1=x1<<FBASE;
x2=x2<<FBASE;
int t=(x2-x1)/(y2-y1);
if (y1<0) { x1+=t*(-y1);y1=0; }
if (yMax<y2) yMax=y2;
Segm *ii=&segmentos[cntSegm];
addIHY((y1<<16)|cntSegm);
ii->x=x1+t/2;
ii->y=y1;
ii->yfin=y2;
ii->deltax=t;
cntSegm++;
}

void gr_pspline(int x1,int y1,int x2,int y2,int x3,int y3)
{
int x11=(x1+x2)>>1,y11=(y1+y2)>>1;
int x21=(x2+x3)>>1,y21=(y2+y3)>>1;
int x22=(x11+x21)>>1,y22=(y11+y21)>>1;
if (abs(x22-x2)+abs(y22-y2)<4)
    { gr_psegmento(x1,y1,x22,y22);gr_psegmento(x22,y22,x3,y3); return; }
gr_pspline(x1,y1,x11,y11,x22,y22);
gr_pspline(x22,y22,x21,y21,x3,y3);
}

void gr_pspline3(int x1,int y1,int x2,int y2,int x3,int y3,int x4,int y4)
{
if (abs(x1+x3-x2-x2)+abs(y1+y3-y2-y2)+abs(x2+x4-x3-x3)+abs(y2+y4-y3-y3)<=4)
    { gr_psegmento(x1,y1,x4,y4);return; }
int gx=(x2+x3)/2,gy=(y2+y3)/2;
int b2x=(x3+x4)/2,b2y=(y3+y4)/2;
int a1x=(x1+x2)/2,a1y=(y1+y2)/2;
int b1x=(gx+b2x)/2,b1y=(gy+b2y)/2;
int a2x=(gx+a1x)/2,a2y=(gy+a1y)/2;
int mx=(b1x+a2x)/2,my=(b1y+a2y)/2;
gr_pspline3(x1,y1,a1x,a1y,a2x,a2y,mx,my);
gr_pspline3(mx,my,b1x,b1y,b2x,b2y,x4,y4);
}

//**************************************************
//***** DIBUJO DE POLIGONO
//**************************************************

//-------------------------------------------------
inline void mixcolor(int col1,int col2,int niv)
{
if (niv<1) { gr_color1=col2;return; }
gr_color1=col1;
if (niv>254) return;
gr_color1=gr_mix(col2,niv);
}

//---------------------------------------------------
inline int dist(int dx,int dy)
{
//return abs(dx)+abs(dy);
register int min,max;
dx=abs(dx);dy=abs(dy);
if (dx<dy) { min=dx;max=dy; } else { min=dy;max=dx; }
return ((max<<8)+(max<<3)-(max<<4)-(max<<1)+(min<<7)-(min<<5)+(min<<3)-(min<<1));
}

//---------------------------------------------------
inline void texture(int dx,int dy)
{
gr_color1=((int*)mTex)[(dx>>8)&0xff|(dy&0xff00)];
}

//----------------------------------------------
// hacer un buffer de covertura para optimizar el pintado

void runlenSolido(int *linea)
{
register int *gr_pos=linea;
int i,v,*s=runlenscan;
while ((v=*s++)!=0) {
      i=GETLEN(v);v=GETVAL(v);
      if (v==QFULL) // solido
         { while(i-->0) { gr_pixel(gr_pos);gr_pos++; } }
      else if (v!=0) // transparente
         { v=QALPHA(v);while(i-->0) { gr_pixela(gr_pos,v);gr_pos++; } }
      else { gr_pos+=i; } // saltea
      }
}

void runlenLineal(int *linea)
{
register int *gr_pos=linea;
int i,v,*s=runlenscan;
int r=MA*(-MTX)-MB*((yMin>>BPP)-MTY);
while ((v=*s++)!=0) {
      i=GETLEN(v);v=GETVAL(v);
      if (v==QFULL) // solido
         { while(i-->0) { mixcolor(col1,col2,r>>8);gr_pixel(gr_pos);r+=MA;gr_pos++; } }
      else if (v!=0)// transparente
         { v=QALPHA(v);while(i-->0) { mixcolor(col1,col2,r>>8);gr_pixela(gr_pos,v);r+=MA;gr_pos++; } }
      else  { gr_pos+=i;r+=i*MA; } // saltea
      }
}

void runlenRadial(int *linea)
{
register int *gr_pos=linea;
int i,v,*s=runlenscan;
int rx = MA*(-MTX)-MB*((yMin>>BPP)-MTY);
int ry = MB*(-MTX)+MA*((yMin>>BPP)-MTY);
while ((v=*s++)!=0) {
      i=GETLEN(v);v=GETVAL(v);
      if (v==QFULL) // solido
         { while(i-->0) { mixcolor(col1,col2,dist(rx,ry)>>16);gr_pixel(gr_pos);rx+=MA;ry+=MB;gr_pos++; } }
      else if (v!=0)// transparente
         { v=QALPHA(v);while(i-->0) { mixcolor(col1,col2,dist(rx,ry)>>16);gr_pixela(gr_pos,v);rx+=MA;ry+=MB;gr_pos++; } }
      else  { gr_pos+=i;rx+=i*MA;ry+=i*MB; } // saltea
      }
}

void runlenTextura(int *linea)
{
register int *gr_pos=linea;
int i,v,*s=runlenscan;
int rx = MA*(-MTX)-MB*((yMin>>BPP)-MTY);
int ry = MB*(-MTX)+MA*((yMin>>BPP)-MTY);
while ((v=*s++)!=0) {
      i=GETLEN(v);v=GETVAL(v);
      if (v==QFULL) // solido
         { while(i-->0) { texture(rx,ry);gr_pixel(gr_pos);rx+=MA;ry+=MB;gr_pos++; } }
      else if (v!=0) // transparente
         { v=QALPHA(v);while(i-->0) { texture(rx,ry);gr_pixela(gr_pos,v);rx+=MA;ry+=MB;gr_pos++; } }
      else { gr_pos+=i;rx+=i*MA;ry+=i*MB; } // saltea
      }
}

void inserta(int *a) // inserta una copia de a
{
int i,j=*a++;
while ((i=*a)!=0) { *a++=j;j=i; }
*a++=j;*a=0;
}

void inserta2(int *a) // inserta dos copias de a
{
int i,j=*a++,k=j;
while ((i=*a)!=0) { *a++=j;j=k;k=i; }
*a++=j;*a++=k;*a=0;
}

//--------- puntero global
void add1pxr(int pos,int val)
{
if (val==0) return;
int v=*rl;
if (GETLEN(v)==1) {
   *rl=v+val;
   rl++;
} else if (GETPOS(v)==pos) {
   inserta(rl);
   *rl=SETPOS(pos)|SETLEN(1)|GETVAL(v)+val;
   rl++;*rl=v+0x100000-0x200;
} else if (GETPOSF(v)-1==pos) {
   inserta(rl);
   *rl=v-0x200;
   rl++;*rl=SETPOS(pos)|SETLEN(1)|GETVAL(v)+val;
   rl++;
} else {
   inserta2(rl);
   *rl=(v&0xfff001ff)|SETLEN(pos-GETPOS(v));
   rl++;*rl=SETPOS(pos)|SETLEN(1)|GETVAL(v)+val;
   rl++;*rl=SETPOS(pos+1)|SETLEN(GETPOSF(v)-(pos+1))|GETVAL(v);
   }
}

void addrlr(int pos,int len,int val)
{
again:
if (len==1) { add1pxr(pos,val);return; }
int v=*rl;
//if (v==0) { *rl=(pos<<20)|(len<<9)|val;rl++;*rl=0;return; } // al final
if (GETPOS(v)==pos) {               // empieza igual          *****
   if (GETLEN(v)>len ) {            // ocupa menos            ***   OK
     inserta(rl);
     *rl=SETPOS(pos)|SETLEN(len)|GETVAL(v)+val;
     rl++;*rl=SETPOS(pos+len)|SETLEN(GETLEN(v)-len)|GETVAL(v);
   } else if (GETLEN(v)<len ) {     // ocupa mas              ******* OK
     *rl=v+val;
     rl++;
     pos+=GETLEN(v);len-=GETLEN(v);
     goto again;
     //addrlr(GETLEN(v)+pos,len-GETLEN(v),val);
   } else {                         // ocupa igual            ***** OK
     *rl=v+val;
     rl++;
   }
} else {                             // empieza adentro       *****
   if (GETPOSF(v)>len+pos ) {        // ocupa menos             ** OK
      inserta2(rl);
      *rl=(v&0xfff001ff)|SETLEN(pos-GETPOS(v));
      rl++;*rl=SETPOS(pos)|SETLEN(len)|GETVAL(v)+val;
      rl++;*rl=SETPOS(pos+len)|SETLEN(GETPOSF(v)-(pos+len))|GETVAL(v);
   } else if (GETPOSF(v)<len+pos ) { // ocupa mas               *****ok
      inserta(rl);
      *rl=(v&0xfff001ff)|SETLEN(pos-GETPOS(v));
      rl++;*rl=SETPOS(pos)|SETLEN(GETPOSF(v)-pos)|GETVAL(v)+val;
      rl++;
      pos=GETPOSF(v);len=pos+len-GETPOSF(v);
      goto again;
//      addrlr(GETPOSF(v),pos+len-GETPOSF(v),val);
   } else {                         // ocupa igual             **** OK
      inserta(rl);
      *rl=(v&0xfff001ff)|SETLEN(pos-GETPOS(v));
      rl++;*rl=SETPOS(pos)|SETLEN(len)|GETVAL(v)+val;
      rl++;
   }
  }
}

void coverpixels(int xa,int xb)
{
int x0=xa>>BPP,x1=xb>>BPP;
if (x0>=buffergr.width||x1<0) return;
while (*rl!=0 && GETPOS(*rl)<=x0) rl++; // puede ser binaria??
rl--;
if (x0==x1)
   {
   add1pxr(x0,(xb&MASK)-(xa&MASK));
   return;
   }
int m1;
if (x0>=0) { add1pxr(x0,VALUES-(xa&MASK));x0++;if(x0>=buffergr.width) return; }
else { x0=0;rl=runlenscan; }
int largo;
if (x1>buffergr.width) largo=buffergr.width-x0; else largo=x1-x0;
if (largo>0) addrlr(x0,largo,VALUES);
if (x1<buffergr.width) add1pxr(x1,xb&MASK);
}


//-----------------------------------------------------------------------
//-----------------------------------------------------------------------
void sortactive(Segm **j) // ordena ultimo elemento
{
Segm *v=*j;
int vx=v->x;
if ((*(j-1))->x<=vx) return;
*j=*(j-1);j--;
while ((*(j-1))->x>vx) { *j=*(j-1);j--; }
*j=v;
}

void addactive(Segm *s)
{
*activelast=s;
sortactive(activelast);
activelast++;
}

void remactive(void)
{
Segm **j=&activelist[1];
while (j<activelast)  {
    if (yMin==(*j)->yfin) {
    	Segm **h=j+1;
    	while (h<activelast)  {
    	    if (yMin<(*h)->yfin)
    	       { *j=*h;j++; }
    	    h++; }
    	activelast=j;
    	break;
    	}
    j++; }
}

void gr_drawPoli(void)
{
if (cntSegm<2)  { initIHY();return; }
Segm **jj;
yMin=segmentos[(heapIHY()&0xffff)].y;
int i;
if (yMax>buffergr.height<<BPP) { yMax=buffergr.height<<BPP; }
int *gr_pant=(int*)gr_buffer+(yMin>>BPP)*buffergr.width;
for (;yMin<yMax;) {
  *runlenscan=SETLEN(buffergr.width+1);*(runlenscan+1)=0;
  for (i=VALUES;i!=0;--i) {
    while (heapIHY()>>16==yMin)
      { addactive(&segmentos[remIHY()&0xffff]); }
    rl=runlenscan;
    for (jj=&activelist[1];jj+1<activelast;jj+=2) {
        coverpixels(((*jj)->x)>>FBASE,((*(jj+1))->x)>>FBASE);
        }
    yMin++;
    // quita los que se terminaron
    remactive();
    // avanza y ordena
    for(jj=&activelist[1];jj<activelast;jj++) {
        (*jj)->x+=(*jj)->deltax;sortactive(jj);
        }
    }
  while (*rl!=0) rl++;rl--;*rl=0;  // quito el ultimo espacio
  runlen(gr_pant);
  gr_pant+=buffergr.width;
  }
initIHY();
}

void gr_pline(int x1,int y1,int x2,int y2)
{ gr_psegmento(FTOI(x1),FTOI(y1),FTOI(x2),FTOI(y2)); }
void gr_pcurve(int x1,int y1,int x2,int y2,int x3,int y3)
{ gr_pspline(FTOI(x1),FTOI(y1),FTOI(x2),FTOI(y2),FTOI(x3),FTOI(y3)); }
void gr_pcurve3(int x1,int y1,int x2,int y2,int x3,int y3,int x4,int y4)
{ gr_pspline3(FTOI(x1),FTOI(y1),FTOI(x2),FTOI(y2),FTOI(x3),FTOI(y3),FTOI(x4),FTOI(y4)); }

//---------------------------------------------------------------
// Optimizacion de rutinas
#ifdef ASM
static void blit32to565v1(const int *dst,const int *src, int cnt)
{
asm volatile (
"1:							\n\t"
	"ldr r3,[%[src]],#4		\n\t"
	"mov r4,r3, lsr #3		\n\t"
	"and r5,r4,#0x1f		\n\t"
	"mov r4,r3, lsr #5		\n\t"
	"and r4,r4,#0x7e0		\n\t"
	"orr r5,r5,r4			\n\t"
	"mov r4,r3, lsr #8		\n\t"
	"and r4,r4,#0xf800		\n\t"
	"orr r5,r5,r4			\n\t"

	"ldr r3,[%[src]],#4		\n\t"
	"mov r4,r3, lsr #3		\n\t"
	"and r4,r4,#0x1f		\n\t"
	"orr r5,r5,r4, lsl #16	\n\t"
	"mov r4,r3, lsr #5		\n\t"
	"and r4,r4,#0x7e0		\n\t"
	"orr r5,r5,r4, lsl #16	\n\t"
	"mov r4,r3, lsr #8		\n\t"
	"and r4,r4,#0xf800		\n\t"
	"orr r5,r5,r4, lsl #16	\n\t"

	"str r5,[%[dst]],#4		\n\t"
	"subs %[cnt],%[cnt],#2	\n\t"
	"bne    1b				\n\t"
: [dst] "+r" (dst), [src] "+r" (src), [cnt] "+r" (cnt)
: : "memory", "cc", "r3", "r4", "r5" );
}

static void blit32to565(const int *dst,const int *src, int cnt)
{
asm volatile (
"1:							\n\t"
	"ldmia %[src]!,{r3,r4}	\n\t"

	"mov r5,r3, lsr #3		\n\t"
	"mov r6,r4, lsr #3		\n\t"
	"and r7,r5,#0x1f		\n\t"
	"and r6,r6,#0x1f 		\n\t"
	"orr r7,r7,r6, lsl #16	\n\t"
	"mov r5,r3, lsr #5		\n\t"
	"mov r6,r4, lsr #5		\n\t"
	"and r5,r5,#0x7e0		\n\t"
	"and r6,r6,#0x7e0		\n\t"
	"orr r7,r7,r5			\n\t"
	"orr r7,r7,r6, lsl #16	\n\t"
	"and r3,r3,#0xf80000	\n\t"
	"and r4,r4,#0xf80000	\n\t"
	"orr r7,r7,r3, lsr #8	\n\t"
	"orr r7,r7,r4, lsl #8	\n\t"

	"str r7,[%[dst]],#4		\n\t"
	"subs %[cnt],%[cnt],#2	\n\t"
	"bge    1b				\n\t"
: [dst] "+r" (dst), [src] "+r" (src), [cnt] "+r" (cnt)
: : "memory", "cc", "r3", "r4", "r5","r6","r7" );
}

//--------------------------------------------------------------
static void copymem32v1(const int *dst,const int *src, int cnt)
{
	asm volatile (
"1:								\n\t"
	"LDMIA %[src]!, {r3 - r10}	\n\t"
    "STMIA %[dst]!, {r3 - r10}	\n\t"
    "SUBS %[cnt],%[cnt], #8		\n\t"
    "BGE 1b					\n\t"
: [dst] "+r" (dst), [src] "+r" (src), [cnt] "+r" (cnt)
: : "memory", "cc","r3","r4","r5","r6","r7","r8","r9","r10" );
}

// NEON
static void copymem32(const int *dst,const int *src, int cnt)
{
	asm volatile (
"1:               	    \n\t"
"      PLD [%[src], #0xC0]	\n\t"
"      VLDM %[src]!,{d0-d7}	\n\t"
"      VSTM %[dst]!,{d0-d7}	\n\t"
"      SUBS %[cnt],%[cnt],#16	\n\t"
"      BGE 1b	        \n\t"
: [dst] "+r" (dst), [src] "+r" (src), [cnt] "+r" (cnt)
: : "memory", "cc","d0","d1","d2","d3","d4","d5","d6","d7" );
}

//--------------------------------------------------------------
static void setmem32v1(const int *dst,int valor, int cnt)
{
asm volatile (
"1:							\n\t"
	"str %[valor],[%[dst]],#4	\n\t"
	"subs %[cnt],%[cnt],#1	\n\t"
	"bne    1b				\n\t"
: [dst] "+r" (dst), [valor] "+r" (valor), [cnt] "+r" (cnt)
: : "memory", "cc" );
}

static void setmem32v2(const int *dst,int valor, int cnt)
{
asm volatile (
"   mov r3, %[valor]\n"
"   mov r4, %[valor]\n"
"   mov r5, %[valor]\n"
"1:\n"
"   subs %[cnt], %[cnt], #8\n"
"   stmhsia %[dst]!, {%[valor], r3, r4, r5}\n"
"   stmhsia %[dst]!, {%[valor], r3, r4, r5}\n"
"   bhs 1b\n"
"   add %[cnt], %[cnt], #8\n"
"   movs %[cnt], %[cnt], lsl #30\n"
"   stmcsia %[dst]!, {%[valor], r3, r4, r5}\n"
"   stmmiia %[dst]!, {r4, r5}\n"
"   movs %[cnt], %[cnt], lsl #2\n"
"   strcs %[valor], [%[dst]]\n"
: [dst] "+r" (dst), [valor] "+r" (valor), [cnt] "+r" (cnt)
: : "memory", "cc","r3","r4","r5" );
}

/* r0 = buffer, r1 = value, r2 = times to write */
static void setmem32(const int *dst,int valor, int cnt)
{
asm volatile (
"memset32_neon:						\n"
"cmp		%[cnt], #1				\n"
"streq		%[valor], [%[dst]], #4	\n"
"bxeq		lr						\n"
"cmp		%[cnt], #4				\n"
"bgt		memset32_neon_start		\n"
"cmp		%[cnt], #0				\n"
"bxeq		lr						\n"
"memset32_neon_small:				\n"
"str		%[valor], [%[dst]], #4	\n"
"subs		%[cnt], %[cnt], #1		\n"
"bne		memset32_neon_small		\n"
"bx		lr							\n"
"memset32_neon_start:				\n"
"cmp		%[cnt], #16				\n"
"blt		memset32_dropthru		\n"
"vdup.32		q0, %[valor]		\n"
"vmov		q1, q0					\n"
"cmp		%[cnt], #32				\n"
"blt		memset32_16				\n"
"cmp		%[cnt], #64				\n"
"blt		memset32_32				\n"
"cmp		%[cnt], #128			\n"
"blt		memset32_64				\n"
"memset32_128:						\n"
"movs		r12, %[cnt], lsr #7		\n"
"memset32_loop128:					\n"
"subs		r12, r12, #1			\n"
"vst1.64		{q0, q1}, [%[dst]]!	\n"
"vst1.64		{q0, q1}, [%[dst]]!	\n"
"vst1.64		{q0, q1}, [%[dst]]!	\n"
"vst1.64		{q0, q1}, [%[dst]]!	\n"
"vst1.64		{q0, q1}, [%[dst]]!	\n"
"vst1.64		{q0, q1}, [%[dst]]!	\n"
"vst1.64		{q0, q1}, [%[dst]]!	\n"
"vst1.64		{q0, q1}, [%[dst]]!	\n"
"vst1.64		{q0, q1}, [%[dst]]!	\n"
"vst1.64		{q0, q1}, [%[dst]]!	\n"
"vst1.64		{q0, q1}, [%[dst]]!	\n"
"vst1.64		{q0, q1}, [%[dst]]!	\n"
"vst1.64		{q0, q1}, [%[dst]]!	\n"
"vst1.64		{q0, q1}, [%[dst]]!	\n"
"vst1.64		{q0, q1}, [%[dst]]!	\n"
"vst1.64		{q0, q1}, [%[dst]]!	\n"
"bne		memset32_loop128		\n"
"ands		%[cnt], %[cnt], #0x7f	\n"
"bxeq		lr						\n"
"memset32_64:						\n"
"movs		r12, %[cnt], lsr #6		\n"
"beq		memset32_32				\n"
"vst1.64		{q0, q1}, [%[dst]]!	\n"
"vst1.64		{q0, q1}, [%[dst]]!	\n"
"vst1.64		{q0, q1}, [%[dst]]!	\n"
"vst1.64		{q0, q1}, [%[dst]]!	\n"
"vst1.64		{q0, q1}, [%[dst]]!	\n"
"vst1.64		{q0, q1}, [%[dst]]!	\n"
"vst1.64		{q0, q1}, [%[dst]]!	\n"
"vst1.64		{q0, q1}, [%[dst]]!	\n"
"ands		%[cnt], %[cnt], #0x3f	\n"
"bxeq		lr						\n"
"memset32_32:						\n"
"movs		r12, %[cnt], lsr #5		\n"
"beq		memset32_16				\n"
"vst1.64		{q0, q1}, [%[dst]]!	\n"
"vst1.64		{q0, q1}, [%[dst]]!	\n"
"vst1.64		{q0, q1}, [%[dst]]!	\n"
"vst1.64		{q0, q1}, [%[dst]]!	\n"
"ands		%[cnt], %[cnt], #0x1f	\n"
"bxeq		lr						\n"
"memset32_16:						\n"
"movs		r12, %[cnt], lsr #4		\n"
"beq		memset32_dropthru		\n"
"and		%[cnt], %[cnt], #0xf	\n"
"vst1.64		{q0, q1}, [%[dst]]!	\n"
"vst1.64		{q0, q1}, [%[dst]]!	\n"
"memset32_dropthru:					\n"
"rsb		%[cnt], %[cnt], #15		\n"
"add		pc, pc, %[cnt], lsl #2	\n"
"nop								\n"
"str		%[valor], [%[dst], #56]	\n"
"str		%[valor], [%[dst], #52]	\n"
"str		%[valor], [%[dst], #48]	\n"
"str		%[valor], [%[dst], #44]	\n"
"str		%[valor], [%[dst], #40]	\n"
"str		%[valor], [%[dst], #36]	\n"
"str		%[valor], [%[dst], #32]	\n"
"str		%[valor], [%[dst], #28]	\n"
"str		%[valor], [%[dst], #24]	\n"
"str		%[valor], [%[dst], #20]	\n"
"str		%[valor], [%[dst], #16]	\n"
"str		%[valor], [%[dst], #12]	\n"
"str		%[valor], [%[dst], #8]	\n"
"str		%[valor], [%[dst], #4]	\n"
"str		%[valor], [%[dst], #0]	\n"
"bx		lr							\n"
: [dst] "+r" (dst), [valor] "+r" (valor), [cnt] "+r" (cnt)
: : "memory", "cc","r12","q0","q1" );
}

#endif
