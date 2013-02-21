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
typedef struct { int y,x,yfin,deltax; } Segm;

Segm segmentos[2048];
Segm **pact;
Segm *actual[256]; // segmentos actuales
Segm **xquisc;
Segm *xquis[256]; // cada linea
int cntSegm=0;
int yMax; // yMinel minimo es el primero(**quitar)
BYTE gr_alphav;

static int gr_sizescreen;	// tamanio de pantalla

int runlenscan[2048];

#define GETPOS(a) (((a)>>20)&0xfff)
#define GETLEN(a) (((a)>>9)&0x7ff)
#define GETVAL(a) ((a)&0x1ff)
#define GETPOSF(a) ((((a)>>20)&0xfff)+(((a)>>9)&0x7ff))

#define SETPOS(a) ((a)<<20)
#define SETLEN(a) ((a)<<9)
#define SETVAL(a) (a)

//////////////////////////////////////////////////////////////
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

inline void swap(int &a,int &b) { a^=b;b^=a;a^=b; }
inline int abs(int a ) { return (a+(a>>31))^(a>>31); }

//////////////////////////////////////////////////////////////
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
yMax=-1;
//minX=gr_ancho;maxX=0;
fillSol();

*runlenscan=SETLEN(gr_ancho-1);*(runlenscan+1)=0;

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
void runlenSolido(DWORD *linea,int y);
void runlenLineal(DWORD *linea,int y);
void runlenRadial(DWORD *linea,int y);
void runlenTextura(DWORD *linea,int y);

void (*runlen)(DWORD *linea,int y);

void fillSol(void) { runlen=runlenSolido; }
void fillLin(void) { runlen=runlenLineal; }
void fillRad(void) { runlen=runlenRadial; }
void fillTex(void) { runlen=runlenTextura; }

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
//if(abs(x1+x3-x2-x2)+abs(y1+y3-y2-y2)<TOLERANCE)
//    { gr_psegmento(x1,y1,x3,y3); return; }           
int x11=(x1+x2)>>1,y11=(y1+y2)>>1;
int x21=(x2+x3)>>1,y21=(y2+y3)>>1;
int x22=(x11+x21)>>1,y22=(y11+y21)>>1;
if (abs(x22-x2)+abs(y22-y2)<TOLERANCE)
    { gr_psegmento(x1,y1,x22,y22);gr_psegmento(x22,y22,x3,y3); return; }
gr_pspline(x1,y1,x11,y11,x22,y22);
gr_pspline(x22,y22,x21,y21,x3,y3);
}

void gr_pspline3(int x1,int y1,int x2,int y2,int x3,int y3,int x4,int y4)
{
if (abs(x1+x3-x2-x2)+abs(y1+y3-y2-y2)+abs(x2+x4-x3-x3)+abs(y2+y4-y3-y3)<TOLERANCE)
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
if (y1>y2) { swap(x1,x2);swap(y1,y2); }
if (y1>=(gr_alto<<BPP) || y2<=0) return;
x1=x1<<FBASE;
x2=x2<<FBASE;
t=(x2-x1)/(y2-y1);
if (y1<0) { x1+=t*(-y1);y1=0; }
if (yMax<y2) yMax=y2;
Segm *ii=&segmentos[cntSegm-1];
while (ii>=segmentos && ii->y>y1 ) { *(ii+1)=*(ii);ii--; }
ii++;
ii->x=x1+((1<<FBASE)>>1);
ii->y=y1;
ii->yfin=y2;
ii->deltax=t;
cntSegm++;
}

//-------------------------------------------------
inline void mixcolor(DWORD col1,DWORD col2,int niv)
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

//----------------------------------------------------------
void addlin(Segm *ii) 
{
register int xr=ii->x;
Segm **cursor=(xquisc-1);
while (cursor>=xquis && (*cursor)->x>xr) {
      *(cursor+1)=*cursor;cursor--;
      }
*(cursor+1)=ii;
xquisc++;
}

//----------------------------------------------
// hacer un buffer de covertura para optimizar el pintado

void runlenSolido(DWORD *linea,int y)
{
register DWORD *gr_pos=linea;
int i,v,*s=runlenscan;
while ((v=*s++)!=0) {
      i=GETLEN(v);v=GETVAL(v);
      if (v==0) // saltea
         { gr_pos+=i; }
      else if (v==QFULL) // solido
         { while(i-->0) { gr_pixel(gr_pos);gr_pos++; } }
      else // transparente
         { v=QALPHA(v);while(i-->0) { gr_pixela(gr_pos,v);gr_pos++; } }
      }
}

void runlenLineal(DWORD *linea,int y)
{
register DWORD *gr_pos=linea;
int i,v,*s=runlenscan;
int r=MA*(-MTX)-MB*(y-MTY);
while ((v=*s++)!=0) {
      i=GETLEN(v);v=GETVAL(v);
      if (v==0) // saltea
         { gr_pos+=i;r+=i*MA; }
      else if (v==QFULL) // solido
         { while(i-->0) { mixcolor(col1,col2,r>>8);gr_pixel(gr_pos);r+=MA;gr_pos++; } }
      else // transparente
         { v=QALPHA(v);while(i-->0) { mixcolor(col1,col2,r>>8);gr_pixela(gr_pos,v);r+=MA;gr_pos++; } }
      }
}

void runlenRadial(DWORD *linea,int y)
{
register DWORD *gr_pos=linea;
int i,v,*s=runlenscan;
int rx = MA*(-MTX)-MB*(y-MTY);
int ry = MB*(-MTX)+MA*(y-MTY);
while ((v=*s++)!=0) {
      i=GETLEN(v);v=GETVAL(v);
      if (v==0) // saltea
         { gr_pos+=i;rx+=i*MA;ry+=i*MB; }
      else if (v==QFULL) // solido
         { while(i-->0) { mixcolor(col1,col2,dist(rx,ry)>>16);gr_pixel(gr_pos);rx+=MA;ry+=MB;gr_pos++; } }
      else // transparente
         { v=QALPHA(v);while(i-->0) { mixcolor(col1,col2,dist(rx,ry)>>16);gr_pixela(gr_pos,v);rx+=MA;ry+=MB;gr_pos++; } }
      }
}

void runlenTextura(DWORD *linea,int y)
{
register DWORD *gr_pos=linea;
int i,v,*s=runlenscan;
int rx = MA*(-MTX)-MB*(y-MTY);
int ry = MB*(-MTX)+MA*(y-MTY);
while ((v=*s++)!=0) {
      i=GETLEN(v);v=GETVAL(v);
      if (v==0) // saltea
         { gr_pos+=i;rx+=i*MA;ry+=i*MB; }
      else if (v==QFULL) // solido
         { while(i-->0) { texture(rx,ry);gr_pixel(gr_pos);rx+=MA;ry+=MB;gr_pos++; } }
      else // transparente
         { v=QALPHA(v);while(i-->0) { texture(rx,ry);gr_pixela(gr_pos,v);rx+=MA;ry+=MB;gr_pos++; } }
      }
}

void inserta(int *a) // inserta una copia de a
{
int i,j=*a++;
while ((i=*a)!=0) { *a++=j;j=i; }
*a++=j;*a=0;
}

void addrla(int *a,int pos,int len,int val)
{
if (*a==0) { *a=(pos<<20)|(len<<9)|val;*(a+1)=0;return; } // al final
int v=*a;
if (GETPOS(v)==pos) {               // empieza igual          *****
   if (GETLEN(v)>len ) {            // ocupa menos            ***   OK
     inserta(a);
     *a=SETPOS(pos)|SETLEN(len)|GETVAL(v)+val;
     *(a+1)=SETPOS(pos+len)|SETLEN(GETLEN(v)-len)|GETVAL(v);
   } else if (GETLEN(v)<len ) {     // ocupa mas              ******* OK
     *a=(v&0xfffffe00)|val+(v&0x1ff);
     addrla(a+1,((v>>9)&0x7ff)+pos,len-((v>>9)&0x7ff),val);
   } else                           // ocupa igual            ***** OK
     *a=(v&0xfffffe00)|GETVAL(v)+val;
} else {                             // empieza adentro       *****
   if (GETPOSF(v)>len+pos ) {        // ocupa menos             ** OK
      inserta(a);inserta(a);
      *a=(v&0xfff001ff)|SETLEN(pos-GETPOS(v));
      *(a+1)=SETPOS(pos)|SETLEN(len)|GETVAL(v)+val;
      *(a+2)=SETPOS(pos+len)|SETLEN(GETPOSF(v)-(pos+len));
   } else if (GETPOSF(v)<len+pos ) { // ocupa mas               *****ok
      inserta(a);
      *a=(v&0xfff001ff)|SETLEN(pos-GETPOS(v));
      *(a+1)=SETPOS(pos)|SETLEN(GETPOSF(v)-pos)|GETVAL(v)+val;
      addrla(a+2,GETPOSF(v),pos+len-GETPOSF(v),val);
   } else {                         // ocupa igual             **** OK
      inserta(a);
      *a=(v&0xfff001ff)|SETLEN(pos-GETPOS(v));
      *(a+1)=SETPOS(pos)|SETLEN(len)|GETVAL(v)+val;
   }
  } 
}

void addrl(int pos,int len,int val)
{
int *a=runlenscan;
while (*a!=0 && GETPOSF(*a)<=pos) a++; // puede ser binaria??
addrla(a,pos,len,val);
}

void add1px(int pos,int val)
{
if (val==0) return;
int v,*a=runlenscan;
while (*a!=0 && GETPOS(*a)<=pos) a++; // puede ser binaria??
a--;v=*a;
if (GETLEN(v)==1) { 
   *a=(v&0xfffffe00)|GETVAL(v)+val;
   }
else if (GETPOS(v)==pos) { 
   inserta(a);
   *a=SETPOS(pos)|SETLEN(1)|GETVAL(v)+val;
   *(a+1)=v+0x100000-0x200;
   }
else if (GETPOSF(v)-1==pos) {
   inserta(a);
   *a=v-0x200;
   *(a+1)=SETPOS(pos)|SETLEN(1)|GETVAL(v)+val;
   }
else {
   inserta(a);inserta(a);     
   *a=(v&0xfff001ff)|SETLEN(pos-GETPOS(v));
   *(a+1)=SETPOS(pos)|SETLEN(1)|GETVAL(v)+val;
   *(a+2)=SETPOS(pos+1)|SETLEN(GETPOSF(v)-(pos+1))|GETVAL(v);
   }
}

void coverpixels(int xa,int xb)
{
int x0 = xa>>BPP;
int x1 = xb>>BPP;
if (x0>gr_ancho||x1<0) return;
if (x0>=0) add1px(x0,VALUES-(xa&MASK));  
else x0=-1;
if (x1<gr_ancho) add1px(x1,(x0==x1? (xb&MASK)-VALUES : xb&MASK)); 
else x1=gr_ancho;
x1=x1-x0-1;
if (x1<1) return; 
if (x1==1) add1px(x0+1,VALUES); else addrl(x0+1,x1,VALUES);
}

//-----------------------------------------------------------------------
void gr_drawPoli(void)
{
Segm **jj;
Segm *scopia=segmentos;
pact=actual;
segmentos[cntSegm].y=-1;
if (yMax>gr_alto<<BPP) { yMax=gr_alto<<BPP; }
int i,yMin=scopia->y;

DWORD *gr_pant=(DWORD*)gr_buffer+(yMin>>BPP)*gr_ypitch;
for (;yMin<yMax;) {
    
  for (i=MASK;i>=0;--i) {
    while (scopia->y==yMin) { *pact=scopia;pact++;scopia++; }
    xquisc=xquis;
    jj=actual;
    while (jj<pact) { addlin(*jj);jj++; }
    for (jj=xquis;jj+1<xquisc;jj+=2) {
        coverpixels(((*jj)->x)>>FBASE,((*(jj+1))->x)>>FBASE);
//      coverpixels(((*jj)->x+(*jj)->deltax)>>FBASE,((*(jj+1))->x+(*(jj+1))->deltax)>>FBASE);
        }
    jj=actual;
    yMin++;
    while (jj<pact) {
          if (yMin<(*jj)->yfin) { (*jj)->x+=(*jj)->deltax;jj++; } 
          else { *jj=*(pact-1);pact--; }
          }
    }              

  int *a=runlenscan;while (*a!=0) a++;a--;if (GETVAL(*a)==0) *a=0;
  runlen(gr_pant,yMin>>BPP);  
  *runlenscan=SETLEN(gr_ancho+1);
  *(runlenscan+1)=0;
  
  gr_pant+=gr_ypitch;  
  }
yMax=-1;
cntSegm=0;
}

