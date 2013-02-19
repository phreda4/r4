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
// rutinas graficas
//#include <string.h>
#include "graf.h"

#ifdef OPENGL
#include <GL/gl.h>
#endif

HDC     hDC;
HGLRC   hRC;

//---- buffer de video
DWORD *gr_buffer; //[1280*1024] = { 0 };
DWORD *XFB;

//---- variables internas
int gr_ancho,gr_alto;
DWORD gr_color1,gr_color2,col1,col2;
int gr_ypitch;
int MA,MB,MTX,MTY; // matrix de transformacion
int *mTex; // textura

//---- variables para dibujo de poligonos
//typedef struct { int y,x,yfin,deltax; } Segm;
typedef struct { int y,x,yfin,deltax,da; } Segm;

Segm segmentos[1024];
Segm **pact;
Segm *actual[256]; // segmentos actuales
Segm **xquisc;
Segm *xquis[256]; // cada linea
int cntSegm=0;
int yMin,yMax;
BYTE gr_alphav;

static int gr_sizescreen;	// tamanio de pantalla

#define FBASE 8
#define RED_MASK 0xFF0000
#define GRE_MASK 0xFF00
#define BLU_MASK 0xFF

#ifdef OPENGL
static const PIXELFORMATDESCRIPTOR pfd = {
    sizeof(PIXELFORMATDESCRIPTOR),1,PFD_DRAW_TO_WINDOW|PFD_SUPPORT_OPENGL|PFD_DOUBLEBUFFER,
    PFD_TYPE_RGBA,32,0, 0, 0, 0, 0, 0, 0, 0,0, 0, 0, 0, 0,
    32,             // zbuffer
    0,              // stencil!
    0,PFD_MAIN_PLANE,0, 0, 0, 0 };
#else
BITMAPINFO bmi = {{sizeof(BITMAPINFOHEADER),800,-600,1,32,BI_RGB,0,0,0,0,0},{0,0,0,0}};
#endif

#ifdef NOMUL
int (*setxyf)(int a,int b);

int setxy(int a,int b) { return (int)gr_buffer+((b*gr_ancho+a)<<2); }
int setxy640(int a,int b) { return (int)gr_buffer+(((b<<7)+(b<<9)+a)<<2); } // 128 + 512
int setxy800(int a,int b) { return (int)gr_buffer+(((b<<5)+(b<<8)+(b<<9)+a)<<2); }
int setxy1024(int a,int b) { return (int)gr_buffer+(((b<<10)+a)<<2); }
int setxy1280(int a,int b) { return (int)gr_buffer+(((b<<10)+(b<<8)+a)<<2); }
int setxy1366(int a,int b) { return (int)gr_buffer+(((b*1366)+a)<<2); }
#endif

void gr_fin(void) 
{ 
VirtualFree(XFB, 0, MEM_RELEASE);
VirtualFree(gr_buffer, 0, MEM_RELEASE);
}

//---- inicio
int gr_init(int XRES,int YRES)
{
gr_sizescreen=XRES*YRES;// tamanio en DWORD

gr_buffer=(DWORD*)VirtualAlloc(0,gr_sizescreen<<2, MEM_COMMIT, PAGE_READWRITE);
XFB=(DWORD*)VirtualAlloc(0,gr_sizescreen<<2, MEM_COMMIT, PAGE_READWRITE);

gr_ypitch=gr_ancho=XRES;
gr_alto=YRES;
#ifdef NOMUL
switch(XRES) {
    case 640:   setxyf=setxy640;break;
    case 800:   setxyf=setxy800;break;
    case 1024:  setxyf=setxy1024;break;
    case 1280:  setxyf=setxy1280;break;
    case 1366:  setxyf=setxy1366;break;
    default:    setxyf=setxy;
    }
#endif
//---- poligonos2
cntSegm=0;
yMin=gr_alto+1;
yMax=-1;
fillSol();
//---- colores
gr_color2=0;gr_color1=0xffffff;
col1=0;col2=0xffffff;
gr_solid();

#ifdef OPENGL //....................gl
unsigned int PixelFormat;

if(!(PixelFormat=ChoosePixelFormat(hDC,&pfd)))  return( 0 );
if(!SetPixelFormat(hDC,PixelFormat,&pfd))       return( 0 );
if(!(hRC=wglCreateContext(hDC)) )         return( 0 );
if(!wglMakeCurrent(hDC,hRC) )             return( 0 );

glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
glViewport(0,0,gr_ancho,gr_alto);
glMatrixMode(GL_PROJECTION);glLoadIdentity();
//glOrtho(0,XRES,YRES,0,-1,1);
glOrtho(0,gr_ancho,0,gr_alto,-1,1);
glMatrixMode(GL_MODELVIEW);glLoadIdentity();
glShadeModel(GL_FLAT);
glDisable(GL_ALPHA_TEST);
glDisable(GL_BLEND);
glDisable(GL_DEPTH_TEST);
glDisable(GL_FOG);
glDisable(GL_LIGHTING);
glDisable(GL_LOGIC_OP);
glDisable(GL_STENCIL_TEST);
glDisable(GL_TEXTURE_1D);
glDisable(GL_TEXTURE_2D);
glPixelTransferi(GL_MAP_COLOR, GL_FALSE);
glPixelTransferi(GL_RED_SCALE, 1);
glPixelTransferi(GL_RED_BIAS, 0);
glPixelTransferi(GL_GREEN_SCALE, 1);
glPixelTransferi(GL_GREEN_BIAS, 0);
glPixelTransferi(GL_BLUE_SCALE, 1);
glPixelTransferi(GL_BLUE_BIAS, 0);
glPixelTransferi(GL_ALPHA_SCALE, 1);
glPixelTransferi(GL_ALPHA_BIAS, 0);
glPixelZoom(1.0, -1.0);
#else
bmi.bmiHeader.biWidth=XRES;
bmi.bmiHeader.biHeight=-YRES;
#endif

return 0;
}

#define GL_BGRA                                 0x80E1

void gr_redraw(void)
{
#ifdef OPENGL
glRasterPos2i(0,gr_alto);
glDrawPixels(gr_ancho,gr_alto,GL_BGRA,GL_UNSIGNED_BYTE,gr_buffer);
SwapBuffers(hDC);
#else
//HBITMAP hBitmap = (HBITMAP )GetCurrentObject(hDC, OBJ_BITMAP);
// GDI_ReleaseObj( hBitmap );
//SetBitmapBits(hBitmap,gr_sizescreen,gr_buffer);

//SetDIBits(hDC,hBitmap,0,gr_alto,gr_buffer,&bmi,DIB_RGB_COLORS);
//StretchDIBits(hDC,0,0,gr_ancho,gr_alto,0,0,gr_ancho,gr_alto,gr_buffer,&bmi,DIB_RGB_COLORS,SRCCOPY);
SetDIBitsToDevice(hDC,0,0,gr_ancho,gr_alto,0,0,0,gr_alto,gr_buffer,&bmi,DIB_RGB_COLORS);
#endif
}

void gr_clrscr(void) 
{
register DWORD *PGR=gr_buffer;
register int c=gr_sizescreen;
for (;c>0;c--,PGR++) *PGR=gr_color2;
}

void gr_toxfb(void)
{
register DWORD *bgr=gr_buffer,*xgr=XFB;
register int c=gr_sizescreen;
while (c>0) { c--;*xgr++=*bgr++; }
}

void gr_xfbto(void)
{
register DWORD *bgr=gr_buffer,*xgr=XFB;
register int c=gr_sizescreen;
while (c>0) { c--;*bgr++=*xgr++; }
}


#define MASK1 (RED_MASK|BLU_MASK)
#define MASK2 (GRE_MASK)

inline DWORD gr_mix(DWORD col,BYTE alpha)
{
register DWORD B=(col & MASK1);
register DWORD RB=(((((gr_color1&MASK1)-B)*alpha)>>8)+B)&MASK1;
B=col&MASK2;
return ((((((gr_color1&MASK2)-B)*alpha)>>8)+B)&MASK2)|RB;
}

//--------------- RUTINAS DE DIBUJO
//---- solido
void _gr_pixels(DWORD *gr_pos)		{*gr_pos=gr_color1;}
void _gr_pixela(DWORD *gr_pos,BYTE a){*gr_pos=gr_mix(*gr_pos,a);}

//---- solido con alpha
void _gr_pixelsa(DWORD *gr_pos)		{*gr_pos=gr_mix(*gr_pos,gr_alphav);}
void _gr_pixelaa(DWORD *gr_pos,BYTE a) {*gr_pos=gr_mix(*gr_pos,(BYTE)((DWORD)(a*gr_alphav)>>8));}

//--------------- RUTINAS DE DIBUJO
void (*gr_pixel)(DWORD *gr_pos);
void (*gr_pixela)(DWORD *gr_pos,BYTE a);

void gr_solid(void) {gr_pixel=_gr_pixels;gr_pixela=_gr_pixela;gr_alphav=255;}
void gr_alpha(void) {gr_pixel=_gr_pixelsa;gr_pixela=_gr_pixelaa;}

//--------------- DIBUJO DE POLIGONO
void _FlineaSolido(int y,Segm *m1,Segm *m2);
void _FlineaDL(int y,Segm *m1,Segm *m2);
void _FlineaDR(int y,Segm *m1,Segm *m2);
void _FlineaTX(int y,Segm *m1,Segm *m2);

void (*fillpoly)(int y,Segm *m1,Segm *m2);

void fillSol(void) { fillpoly=_FlineaSolido; }
void fillLin(void) { fillpoly=_FlineaDL; }
void fillRad(void) { fillpoly=_FlineaDR; }
void fillTex(void) { fillpoly=_FlineaTX; }

//------------------------------------
#ifdef NOMUL
#define GR_SET(X,Y) gr_pos=(DWORD*)setxyf(X,Y);
#else
#define GR_SET(X,Y) gr_pos=(DWORD*)gr_buffer+Y*gr_ypitch+X;
#endif

#define GR_X(X) gr_pos+=X;
#define GR_Y(Y) gr_pos+=gr_ypitch*Y;

//------------------------------------
void gr_hline(int x1,int y1,int x2)
{
if (x1<0) x1=0;
if (x2>=gr_ancho) { x2=gr_ancho-1;if (x1>=gr_ancho) return; }
register DWORD *gr_pos;
GR_SET(x1,y1);
DWORD *pf=gr_pos+x2-x1+1;
do { gr_pixel(gr_pos);gr_pos++; } while (gr_pos<pf);
}

void gr_vline(int x1,int y1,int y2)
{
if (y1<0) y1=0;
if (y2>=gr_alto) { y2=gr_alto-1;if (y1>=gr_alto) return; }
register DWORD *gr_pos;
GR_SET(x1,y1);
DWORD *pf=gr_pos+((y2-y1+1)*gr_ancho);
do { gr_pixel(gr_pos);gr_pos+=gr_ypitch; } while (gr_pos<pf);
}

bool gr_clipline(int *X1,int *Y1,int *X2,int *Y2)
{
int C1,C2,V;
if (*X1<0) C1=1; else C1=0;
if (*X1>=gr_ancho) C1|=0x2;
if (*Y1<0) C1|=0x4;
if (*Y1>=gr_alto-1) C1|=0x8;
if (*X2<0) C2=1; else C2=0;
if (*X2>=gr_ancho) C2|=0x2;
if (*Y2<0) C2|=0x4;
if (*Y2>=gr_alto-1) C2|=0x8;
if ((C1&C2)==0 && (C1|C2)!=0) {
	if ((C1&12)!=0) {
		if (C1<8) V=0; else V=gr_alto-2;
		*X1+=(V-*Y1)*(*X2-*X1)/(*Y2-*Y1);*Y1=V;
		if (*X1<0) C1=1; else C1=0;
		if (*X1>=gr_ancho) C1|=0x2;
		}
    if ((C2&12)!=0) {
		if (C2<8) V=0; else V=gr_alto-2;
		*X2+=(V-*Y2)*(*X2-*X1)/(*Y2-*Y1);*Y2=V;
		if (*X2<0) C2=1; else C2=0;
		if (*X2>=gr_ancho) C2|=0x2;
		}
    if ((C1&C2)==0 && (C1|C2)!=0) {
		if (C1!=0) {
			if (C1==1) V=0; else V=gr_ancho-1;
			*Y1+=(V-*X1)*(*Y2-*Y1)/(*X2-*X1);*X1=V;C1=0;
			}
		if (C2!=0) {
			if (C2==1) V=0; else V=gr_ancho-1;
			*Y2+=(V-*X2)*(*Y2-*Y1)/(*X2-*X1);*X2=V;C2=0;
			}
		}
	}
return (C1|C2)==0;
}

//---- con clip
inline void gr_setpixel(int x,int y)
{
if ((unsigned)x>=(unsigned)gr_ancho || (unsigned)y>=(unsigned)gr_alto) return;
register DWORD *gr_pos;
GR_SET(x,y);gr_pixel(gr_pos);
}

inline void gr_setpixela(int x,int y,BYTE a)
{
if ((unsigned)x>=(unsigned)gr_ancho || (unsigned)y>=(unsigned)gr_alto) return;
register DWORD *gr_pos;
GR_SET(x,y);gr_pixela(gr_pos,a);
}

inline void swap(int &a,int &b)//int t=a;a=b;b=t;
{ a^=b;b^=a;a^=b; }

void gr_line(int x1,int y1,int x2,int y2)
{
if (!gr_clipline(&x1,&y1,&x2,&y2)) return;
int dx,dy,sx,d;
if (x1==x2) { if (y1>y2) swap(y1,y2); gr_vline(x1,y1,y2);return; }
if (y1==y2) { if (x1>x2) swap(x1,x2); gr_hline(x1,y1,x2);return; }
if (y1>y2) { swap(x1,x2);swap(y1,y2); }            
dx=x2-x1;dy=y2-y1;
if (dx>0) sx=1; else { sx=-1;dx=-dx; }
//if (dy>0) sy=1; else { sy=-1;dy=-dy; }
WORD ea,ec=0;BYTE ci;
register DWORD *gr_pos;
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

inline int abs(int a ) { return (a+(a>>31))^(a>>31); }

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
void gr_psegmento(int x1,int y1,int x2,int y2)
{
int t;
if (y1==y2) return;
if (y1>y2) { t=x1;x1=x2;x2=t;t=y1;y1=y2;y2=t; }
if (y1>=gr_alto || y2<=0) return;
x1=x1<<FBASE;
x2=x2<<FBASE;
t=(x2-x1)/(y2-y1);
if (y1<0) { x1+=t*(-y1);y1=0; }
if (yMin>y1) yMin=y1;
if (yMax<y2) yMax=y2;
Segm *ii=&segmentos[cntSegm-1];
while (ii>=segmentos && ii->y>y1 ) {
  *(ii+1)=*(ii);ii--;
  }
ii++;
ii->x=x1+((1<<FBASE)>>1);
ii->y=y1;
ii->yfin=y2;
ii->deltax=t;
t=abs(t>>FBASE)+1;ii->da=0xff00/t; // remove div
cntSegm++;
}

//-------------------------------------------------
void _FlineaSolido(int y,Segm *m1,Segm *m2)
{
register DWORD *gr_pos;
register int cnt,alpha,da;
int x1,x2,x3,x4;
if (m1->x==m2->x&&m1->deltax>m2->deltax) { Segm *t=m1;m1=m2;m2=t; }

if (m1->deltax<0)
   { x1=m1->x+m1->deltax;x2=m1->x; }
else
   { x1=m1->x;x2=m1->x+m1->deltax; }
if (m2->deltax<0)
   { x3=m2->x+m2->deltax;x4=m2->x; }
else
   { x3=m2->x;x4=m2->x+m2->deltax; }
int ex1=x1>>FBASE,ex2=x2>>FBASE;
int ex3=x3>>FBASE,ex4=x4>>FBASE;
if (ex4<=0 || ex1>=gr_ancho ) return;
if (ex1>0) GR_SET(ex1,y) else GR_SET(0,y)

if (ex2>0) { // entrada anti
  if (ex1==ex2) { // punto solo
    gr_pixela(gr_pos,255-(BYTE)((x1+x2)>>1));gr_pos++;
  } else { // degrade
    alpha=0;
      da=m1->da;
//    da=(255<<8)/(ex2-ex1);
    if (ex1<0) { alpha+=da*(-ex1);ex1=0; }
    if (ex2>=gr_ancho) ex2=gr_ancho-1;
    cnt=ex2-ex1+1;
    while (cnt--) { gr_pixela(gr_pos,alpha>>8);gr_pos++;alpha+=da; }
    }
  }

if (ex3<=ex2) return;
if (ex3>0) { // lleno
    if (ex2<0) ex2=0;
    if (ex3>gr_ancho) ex3=gr_ancho;
    cnt=ex3-ex2-1;
    while (cnt--) { gr_pixel(gr_pos);gr_pos++; }
    }
if (ex4==ex3) { // punto solo
   if (ex4>=gr_ancho) return;
  gr_pixela(gr_pos,(BYTE)((x3+x4)>>1));
} else { // degrade
  alpha=255<<8;
  da=-m2->da;
//  da=(-255<<8)/(ex4-ex3);
  if (ex3<0) { alpha+=da*(-ex3);ex3=0; }    
  if (ex4>gr_ancho) ex4=gr_ancho;
  cnt=ex4-ex3;
  while (cnt--) { gr_pixela(gr_pos,alpha>>8);gr_pos++;alpha+=da; }
  }
}

//-------------------------------------------------
inline void mixcolor(DWORD col1,DWORD col2,int niv)
{
//niv=niv&0xff;
//niv=abs(niv);
if (niv<1) { gr_color1=col2;return; }
gr_color1=col1;
if (niv>254) return;
gr_color1=gr_mix(col2,niv);
}

void _FlineaDL(int y,Segm *m1,Segm *m2)
{
register DWORD *gr_pos;
register int cnt,alpha,da;
int x1,x2,x3,x4;
if (m1->x==m2->x&&m1->deltax>m2->deltax)
    { Segm *t=m1;m1=m2;m2=t; }

if (m1->deltax<0)
   { x1=m1->x+m1->deltax;x2=m1->x; }
else
   { x2=m1->x+m1->deltax;x1=m1->x; }
if (m2->deltax<0)
   { x3=m2->x+m2->deltax;x4=m2->x; }
else
   { x4=m2->x+m2->deltax;x3=m2->x; }
int ex1=x1>>FBASE,ex2=x2>>FBASE;
int ex3=x3>>FBASE,ex4=x4>>FBASE;
if (ex4<=0 || ex1>=gr_ancho ) return;
int r=MA*(ex2-MTX)-MB*(y-MTY);
mixcolor(col1,col2,r>>8);
if (ex1>0) GR_SET(ex1,y) else GR_SET(0,y)

if (ex2>0) { // entrada anti
  if (ex1==ex2) { // punto solo
    gr_pixela(gr_pos,255-(BYTE)((x1+x2)>>1));gr_pos++;
  } else { // degrade
    alpha=0;
    da=m1->da;
//    da=(255<<8)/(ex2-ex1);
    if (ex1<0) { alpha+=da*(-ex1);ex1=0; }
    if (ex2>=gr_ancho) ex2=gr_ancho-1;
    cnt=ex2-ex1+1;
    while (cnt--) { gr_pixela(gr_pos,alpha>>8);gr_pos++;alpha+=da; }
    }
  }

if (ex3<=ex2) return;
if (ex3>0) { // lleno
    if (ex2<0) { r+=MA*(-ex2);ex2=0; }
    if (ex3>gr_ancho) ex3=gr_ancho;
    cnt=ex3-ex2-1;
    while (cnt--) { 
        mixcolor(col1,col2,r>>8);
        gr_pixel(gr_pos);gr_pos++; 
        r+=MA;
        }
  }
if (ex4==ex3) { // punto solo
  if (ex4>=gr_ancho) return;
  gr_pixela(gr_pos,(BYTE)((x3+x4)>>1));
} else { // degrade
  alpha=255<<8;
  da=-m2->da;
//  da=(-255<<8)/(ex4-ex3);
  if (ex3<0) { alpha+=da*(-ex3);ex3=0; }
  if (ex4>gr_ancho) ex4=gr_ancho;
  cnt=ex4-ex3;
  while (cnt--) { gr_pixela(gr_pos,alpha>>8);gr_pos++;alpha+=da; }
  }
}

//---------------------------------------------------
inline int dist(int dx,int dy)
{
//return abs(dx)+abs(dy);
register int min,max;
dx=abs(dx);dy=abs(dy);
if (dx<dy) { min=dx;max=dy; } else { min=dy;max=dx; }
return ((max<<8)+(max<<3)-(max<<4)-(max<<1)+
        (min<<7)-(min<<5)+(min<<3)-(min<<1));
}

void _FlineaDR(int y,Segm *m1,Segm *m2)
{
register DWORD *gr_pos;
register int cnt,alpha,da;
int x1,x2,x3,x4;
if (m1->x==m2->x&&m1->deltax>m2->deltax)
    { Segm *t=m1;m1=m2;m2=t; }

if (m1->deltax<0)
   { x1=m1->x+m1->deltax;x2=m1->x; }
else
   { x2=m1->x+m1->deltax;x1=m1->x; }
if (m2->deltax<0)
   { x3=m2->x+m2->deltax;x4=m2->x; }
else
   { x4=m2->x+m2->deltax;x3=m2->x; }
int ex1=x1>>FBASE,ex2=x2>>FBASE;
int ex3=x3>>FBASE,ex4=x4>>FBASE;
if (ex4<=0 || ex1>=gr_ancho ) return;
int rx = MA*(ex2-MTX)-MB*(y-MTY);
int ry = MB*(ex2-MTX)+MA*(y-MTY);
mixcolor(col1,col2,dist(rx,ry)>>16);
if (ex1>0) GR_SET(ex1,y) else GR_SET(0,y)
if (ex2>0) { // entrada anti
  if (ex1==ex2) { // punto solo
    gr_pixela(gr_pos,255-(BYTE)((x1+x2)>>1));gr_pos++;
  } else { // degrade
    alpha=0;
        da=m1->da;

//    da=(255<<8)/(ex2-ex1);
/*
    da=(ex2-ex1);
    if (da>0xff) da=tablainc[(da>>8)&0xff]>>8; else da=tablainc[da];
*/

    if (ex1<0) { alpha+=da*(-ex1);ex1=0; }
    if (ex2>=gr_ancho) ex2=gr_ancho-1;
    cnt=ex2-ex1+1;
    while (cnt--) { gr_pixela(gr_pos,alpha>>8);gr_pos++;alpha+=da; }
    }
  }
if (ex3<=ex2) return;
if (ex3>0) { // lleno
    if (ex2<0) { rx+=MA*(-ex2);ry+=MB*(-ex2);ex2=0; }
    if (ex3>gr_ancho) ex3=gr_ancho;
    cnt=ex3-ex2-1;
    while (cnt--) {
        mixcolor(col1,col2,dist(rx,ry)>>16);
        gr_pixel(gr_pos);gr_pos++; 
        rx+=MA;
        ry+=MB;
        }
  }
if (ex4==ex3) { // punto solo
  if (ex4>=gr_ancho) return;
  gr_pixela(gr_pos,(BYTE)((x3+x4)>>1));
} else { // degrade
  alpha=255<<8;
   da=-m2->da;
//  da=(-255<<8)/(ex4-ex3);
  if (ex3<0) { alpha+=da*(-ex3);ex3=0; }    
  if (ex4>gr_ancho) ex4=gr_ancho;
  cnt=ex4-ex3;
  while (cnt--) { gr_pixela(gr_pos,alpha>>8);gr_pos++;alpha+=da; }
  }
}

//---------------------------------------------------
inline void texture(int dx,int dy)
{
gr_color1=((int*)mTex)[(dx>>8)&0xff|(dy&0xff00)];
}

void _FlineaTX(int y,Segm *m1,Segm *m2)
{
register DWORD *gr_pos;
register int cnt,alpha,da;
int x1,x2,x3,x4;
if (m1->x==m2->x&&m1->deltax>m2->deltax)
    { Segm *t=m1;m1=m2;m2=t; }

if (m1->deltax<0)
   { x1=m1->x+m1->deltax;x2=m1->x; }
else
   { x2=m1->x+m1->deltax;x1=m1->x; }
if (m2->deltax<0)
   { x3=m2->x+m2->deltax;x4=m2->x; }
else
   { x4=m2->x+m2->deltax;x3=m2->x; }
int ex1=x1>>FBASE,ex2=x2>>FBASE;
int ex3=x3>>FBASE,ex4=x4>>FBASE;
if (ex4<=0 || ex1>=gr_ancho ) return;
int rx = MA*(ex2-MTX)-MB*(y-MTY);
int ry = MB*(ex2-MTX)+MA*(y-MTY);
texture(rx,ry);
if (ex1>0) GR_SET(ex1,y) else GR_SET(0,y)
if (ex2>0) { // entrada anti
  if (ex1==ex2) { // punto solo
    gr_pixela(gr_pos,255-(BYTE)((x1+x2)>>1));gr_pos++;
  } else { // degrade
    alpha=0;
        da=m1->da;

//    da=(255<<8)/(ex2-ex1);
    if (ex1<0) { alpha+=da*(-ex1);ex1=0; }
    if (ex2>=gr_ancho) ex2=gr_ancho-1;
    cnt=ex2-ex1+1;
    while (cnt--) { gr_pixela(gr_pos,alpha>>8);gr_pos++;alpha+=da; }
    }
  }
if (ex3<=ex2) return;
if (ex3>0) { // lleno
    if (ex2<0) { rx+=MA*(-ex2);ry+=MB*(-ex2);ex2=0; }
    if (ex3>gr_ancho) ex3=gr_ancho;
    cnt=ex3-ex2-1;
    while (cnt--) {
        texture(rx,ry);
        gr_pixel(gr_pos);gr_pos++; 
        rx+=MA;
        ry+=MB;
        }
  }
if (ex4==ex3) { // punto solo
  if (ex4>=gr_ancho) return;
  gr_pixela(gr_pos,(BYTE)((x3+x4)>>1));
} else { // degrade
  alpha=255<<8;
      da=-m2->da;

//  da=(-255<<8)/(ex4-ex3);
  if (ex3<0) { alpha+=da*(-ex3);ex3=0; }    
  if (ex4>gr_ancho) ex4=gr_ancho;
  cnt=ex4-ex3;
  while (cnt--) { gr_pixela(gr_pos,alpha>>8);gr_pos++;alpha+=da; }
  }
}

//----------------------------------------------------------
void addlin(Segm *ii) 
{
register int xr=ii->x;
Segm **cursor=(xquisc-1);
while (cursor>=xquis && (*cursor)->x>xr) {
      *(cursor+1)=*cursor;cursor--;
      }
//if (cursor>=xquis && (*cursor)->x+(*cursor)->deltax > ii->x+ii->deltax) {
//    *(cursor+1)=*cursor;cursor--; }    
*(cursor+1)=ii;
xquisc++;
}

void gr_drawPoli(void)
{
Segm **jj;
Segm *scopia=segmentos;
pact=actual;
segmentos[cntSegm].y=-1;
if (yMax>gr_alto) { yMax=gr_alto; }
for (;yMin<yMax;) {
    while (scopia->y==yMin) {
          *pact=scopia;pact++;scopia++;
          }
    xquisc=xquis;
    jj=actual;
    while (jj<pact) {
          addlin(*jj);
          jj++;
          }
    for (jj=xquis;jj+1<xquisc;jj+=2) {
/*
        gr_color1=0xff00;
        gr_hline(((*jj)->x+(*jj)->deltax)>>FBASE,yMin,((*(jj+1))->x+(*(jj+1))->deltax)>>FBASE);
        gr_color1=0xff;
        gr_hline((*jj)->x>>FBASE,yMin,(*(jj+1))->x>>FBASE);
*/
          fillpoly(yMin,*jj,*(jj+1));
          }
    jj=actual;
    yMin++;
    while (jj<pact) {
          if (yMin<(*jj)->yfin) {
             (*jj)->x+=(*jj)->deltax;
             jj++;
          } else {
            *jj=*(pact-1);
             pact--;
             }
          }
    }
yMin=gr_alto+1;
yMax=-1;
cntSegm=0;
}
