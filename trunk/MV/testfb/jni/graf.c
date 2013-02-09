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

#include "graf.h"

//---- buffer de video
ANativeWindow_Buffer buffergr;
void *XFB;


//extern void *buffergr.bits; 		// buffer de pantalla
//extern int buffergr.width,buffergr.height;

//---- variables internas
unsigned int gr_color1,gr_color2,col1,col2;
int MA,MB,MTX,MTY; // matrix de transformacion
int *mTex; // textura

//---- variables para dibujo de poligonos
typedef struct { int y,x,yfin,deltax; } Segm;
Segm segmentos[1024];
Segm **pact;
Segm *actual[256]; // segmentos actuales
Segm **xquisc;
Segm *xquis[256]; // cada linea
int cntSegm=0;
int yMin,yMax;
unsigned char gr_alphav;

static int gr_sizescreen;	// tamanio de pantalla

#define FBASE 8
#define RED_MASK 0xFF0000
#define GRE_MASK 0xFF00
#define BLU_MASK 0xFF

void gr_fin(void)
{
free(XFB);
}

//---- inicio
int gr_init(int XRES,int YRES)
{
gr_sizescreen=XRES*YRES;// tamanio en WORD
XFB=(void*)malloc(gr_sizescreen*2);

//buffergr.width=buffergr.width=XRES;
//buffergr.height=YRES;
//---- poligonos2
cntSegm=0;
yMin=buffergr.height+1;
yMax=-1;
fillSol();
//---- colores
gr_color2=0;gr_color1=0xffffff;
col1=0;col2=0xffffff;
gr_solid();
return 0;
}

inline void fillcent(int mx,int my)
{ MTX=mx;MTY=my; }
inline void fillmat(int a,int b)
{ MA=a;MB=b; }
inline void fillcol(unsigned int c1,unsigned int c2)
{ col1=c1;col2=c2; }


void gr_clrscr(void)
{
register unsigned int *PGR=buffergr.bits;
register int c=gr_sizescreen/2;
for (;c>0;c--,PGR++) *PGR=gr_color2;
}

void gr_toxfb(void)
{
register unsigned int *bgr=buffergr.bits,*xgr=XFB;
register int c=gr_sizescreen/2;
while (c>0) { c--;*xgr++=*bgr++; }
}

void gr_xfbto(void)
{
register unsigned int *bgr=buffergr.bits,*xgr=XFB;
register int c=gr_sizescreen/2;
while (c>0) { c--;*bgr++=*xgr++; }
}


#define MASK1 (RED_MASK|BLU_MASK)
#define MASK2 (GRE_MASK)

inline unsigned int gr_mix(unsigned int col,unsigned char alpha)
{
register unsigned int B=(col & MASK1);
register unsigned int RB=(((((gr_color1&MASK1)-B)*alpha)>>8)+B)&MASK1;
B=col&MASK2;
return ((((((gr_color1&MASK2)-B)*alpha)>>8)+B)&MASK2)|RB;
}

//--------------- RUTINAS DE DIBUJO
//---- solido
void _gr_pixels(uint16_t *gr_pos)		{*gr_pos=gr_color1;}
void _gr_pixela(uint16_t *gr_pos,unsigned char a){*gr_pos=gr_mix(*gr_pos,a);}

//---- solido con alpha
void _gr_pixelsa(uint16_t *gr_pos)		{*gr_pos=gr_mix(*gr_pos,gr_alphav);}
void _gr_pixelaa(uint16_t *gr_pos,unsigned char a) {*gr_pos=gr_mix(*gr_pos,(unsigned char)((unsigned int)(a*gr_alphav)>>8));}

//--------------- RUTINAS DE DIBUJO
void (*gr_pixel)(uint16_t *gr_pos);
void (*gr_pixela)(uint16_t *gr_pos,unsigned char a);

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
#define GR_SET(X,Y) gr_pos=(uint16_t*)buffergr.bits+Y*buffergr.width+X;
#define GR_X(X) gr_pos+=X;
#define GR_Y(Y) gr_pos+=buffergr.width*Y;

//------------------------------------
void gr_hline(int x1,int y1,int x2)
{
if (x1<0) x1=0;
if (x2>=buffergr.width) { x2=buffergr.width-1;if (x1>=buffergr.width) return; }
register uint16_t *gr_pos;
GR_SET(x1,y1);
uint16_t *pf=gr_pos+x2-x1+1;
do { gr_pixel(gr_pos);gr_pos++; } while (gr_pos<pf);
}

void gr_vline(int x1,int y1,int y2)
{
if (y1<0) y1=0;
if (y2>=buffergr.height) { y2=buffergr.height-1;if (y1>=buffergr.height) return; }
register uint16_t *gr_pos;
GR_SET(x1,y1);
uint16_t *pf=gr_pos+((y2-y1+1)*buffergr.width);
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
register uint16_t *gr_pos;
GR_SET(x,y);gr_pixel(gr_pos);
}

inline void gr_setpixela(int x,int y,unsigned char a)
{
if ((unsigned)x>=(unsigned)buffergr.width || (unsigned)y>=(unsigned)buffergr.height) return;
register uint16_t *gr_pos;
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
register uint16_t *gr_pos;
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

void gr_splineiter(int x1,int y1,int x2,int y2,int x3,int y3)
{
int x11=(x1+x2)>>1,y11=(y1+y2)>>1;
int x21=(x2+x3)>>1,y21=(y2+y3)>>1;
int x22=(x11+x21)>>1,y22=(y11+y21)>>1;
if (abs(x22-x2)+abs(y22-y2)<4)
    { gr_line(x1,y1,x22,y22);gr_line(x22,y22,x3,y3); return; }
gr_splineiter(x1,y1,x11,y11,x22,y22);
gr_splineiter(x22,y22,x21,y21,x3,y3);
}

void gr_spline(int x1,int y1,int x2,int y2,int x3,int y3)
{
gr_splineiter(x1,y1,x2,y2,x3,y3);
}

// poligono
void gr_iteracionSP(long x1,long y1,long x2,long y2,long x3,long y3)
{
long x11=(x1+x2)>>1,y11=(y1+y2)>>1;
long x21=(x2+x3)>>1,y21=(y2+y3)>>1;
long x22=(x11+x21)>>1,y22=(y11+y21)>>1;
if (abs(x22-x2)+abs(y22-y2)<4)
    { gr_psegmento(x1,y1,x22,y22);gr_psegmento(x22,y22,x3,y3); return; }
gr_iteracionSP(x1,y1,x11,y11,x22,y22);
gr_iteracionSP(x22,y22,x21,y21,x3,y3);
}

void gr_pspline(int x1,int y1,int x2,int y2,int x3,int y3)
{
gr_iteracionSP(x1,y1,x2,y2,x3,y3);
}

//**************************************************
//***** DIBUJO DE POLIGONO
//**************************************************
void gr_psegmento(int x1,int y1,int x2,int y2)
{
int t;
if (y1==y2) return;
if (y1>y2) { t=x1;x1=x2;x2=t;t=y1;y1=y2;y2=t; }
if (y1>=buffergr.height || y2<=0) return;
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
cntSegm++;
}

//-------------------------------------------------
void _FlineaSolido(int y,Segm *m1,Segm *m2)
{
register uint16_t *gr_pos;
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
if (ex4<=0 || ex1>=buffergr.width ) return;
if (ex1>0) GR_SET(ex1,y) else GR_SET(0,y)

if (ex2>0) { // entrada anti
  if (ex1==ex2) { // punto solo
    gr_pixela(gr_pos,255-(unsigned char)((x1+x2)>>1));gr_pos++;
  } else { // degrade
    alpha=0;

    da=(255<<8)/(ex2-ex1);
    if (ex1<0) { alpha+=da*(-ex1);ex1=0; }
    if (ex2>=buffergr.width) ex2=buffergr.width-1;
    cnt=ex2-ex1+1;
    while (cnt--) { gr_pixela(gr_pos,alpha>>8);gr_pos++;alpha+=da; }
    }
  }

if (ex3<=ex2) return;
if (ex3>0) { // lleno
    if (ex2<0) ex2=0;
    if (ex3>buffergr.width) ex3=buffergr.width;
    cnt=ex3-ex2-1;
    while (cnt--) { gr_pixel(gr_pos);gr_pos++; }
    }
if (ex4==ex3) { // punto solo
   if (ex4>=buffergr.width) return;
  gr_pixela(gr_pos,(unsigned char)((x3+x4)>>1));
} else { // degrade
  alpha=255<<8;
  da=(-255<<8)/(ex4-ex3);
  if (ex3<0) { alpha+=da*(-ex3);ex3=0; }
  if (ex4>buffergr.width) ex4=buffergr.width;
  cnt=ex4-ex3;
  while (cnt--) { gr_pixela(gr_pos,alpha>>8);gr_pos++;alpha+=da; }
  }
}

//-------------------------------------------------
inline void mixcolor(unsigned int col1,unsigned int col2,int niv)
{
if (niv<1) { gr_color1=col2;return; }
gr_color1=col1;
if (niv>254) return;
gr_color1=gr_mix(col2,niv);
}

void _FlineaDL(int y,Segm *m1,Segm *m2)
{
register uint16_t *gr_pos;
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
if (ex4<=0 || ex1>=buffergr.width ) return;
int r=MA*(ex2-MTX)-MB*(y-MTY);
mixcolor(col1,col2,r>>8);
if (ex1>0) GR_SET(ex1,y) else GR_SET(0,y)

if (ex2>0) { // entrada anti
  if (ex1==ex2) { // punto solo
    gr_pixela(gr_pos,255-(unsigned char)((x1+x2)>>1));gr_pos++;
  } else { // degrade
    alpha=0;
    da=(255<<8)/(ex2-ex1);
    if (ex1<0) { alpha+=da*(-ex1);ex1=0; }
    if (ex2>=buffergr.width) ex2=buffergr.width-1;
    cnt=ex2-ex1+1;
    while (cnt--) { gr_pixela(gr_pos,alpha>>8);gr_pos++;alpha+=da; }
    }
  }

if (ex3<=ex2) return;
if (ex3>0) { // lleno
    if (ex2<0) { r+=MA*(-ex2);ex2=0; }
    if (ex3>buffergr.width) ex3=buffergr.width;
    cnt=ex3-ex2-1;
    while (cnt--) {
        mixcolor(col1,col2,r>>8);
        gr_pixel(gr_pos);gr_pos++;
        r+=MA;
        }
  }
if (ex4==ex3) { // punto solo
  if (ex4>=buffergr.width) return;
  gr_pixela(gr_pos,(unsigned char)((x3+x4)>>1));
} else { // degrade
  alpha=255<<8;
  da=(-255<<8)/(ex4-ex3);
  if (ex3<0) { alpha+=da*(-ex3);ex3=0; }
  if (ex4>buffergr.width) ex4=buffergr.width;
  cnt=ex4-ex3;
  while (cnt--) { gr_pixela(gr_pos,alpha>>8);gr_pos++;alpha+=da; }
  }
}

//---------------------------------------------------
inline int dist(int dx,int dy)
{
register int min,max;
dx=abs(dx);dy=abs(dy);
if (dx<dy) { min=dx;max=dy; } else { min=dy;max=dx; }
return ((max<<8)+(max<<3)-(max<<4)-(max<<1)+
        (min<<7)-(min<<5)+(min<<3)-(min<<1));
}

void _FlineaDR(int y,Segm *m1,Segm *m2)
{
register uint16_t *gr_pos;
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
if (ex4<=0 || ex1>=buffergr.width ) return;
int rx = MA*(ex2-MTX)-MB*(y-MTY);
int ry = MB*(ex2-MTX)+MA*(y-MTY);
mixcolor(col1,col2,dist(rx,ry)>>16);
if (ex1>0) GR_SET(ex1,y) else GR_SET(0,y)
if (ex2>0) { // entrada anti
  if (ex1==ex2) { // punto solo
    gr_pixela(gr_pos,255-(unsigned char)((x1+x2)>>1));gr_pos++;
  } else { // degrade
    alpha=0;
    da=(255<<8)/(ex2-ex1);
    if (ex1<0) { alpha+=da*(-ex1);ex1=0; }
    if (ex2>=buffergr.width) ex2=buffergr.width-1;
    cnt=ex2-ex1+1;
    while (cnt--) { gr_pixela(gr_pos,alpha>>8);gr_pos++;alpha+=da; }
    }
  }
if (ex3<=ex2) return;
if (ex3>0) { // lleno
    if (ex2<0) { rx+=MA*(-ex2);ry+=MB*(-ex2);ex2=0; }
    if (ex3>buffergr.width) ex3=buffergr.width;
    cnt=ex3-ex2-1;
    while (cnt--) {
        mixcolor(col1,col2,dist(rx,ry)>>16);
        gr_pixel(gr_pos);gr_pos++;
        rx+=MA;
        ry+=MB;
        }
  }
if (ex4==ex3) { // punto solo
  if (ex4>=buffergr.width) return;
  gr_pixela(gr_pos,(unsigned char)((x3+x4)>>1));
} else { // degrade
  alpha=255<<8;
  da=(-255<<8)/(ex4-ex3);
  if (ex3<0) { alpha+=da*(-ex3);ex3=0; }
  if (ex4>buffergr.width) ex4=buffergr.width;
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
register uint16_t *gr_pos;
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
if (ex4<=0 || ex1>=buffergr.width ) return;
int rx = MA*(ex2-MTX)-MB*(y-MTY);
int ry = MB*(ex2-MTX)+MA*(y-MTY);
texture(rx,ry);
if (ex1>0) GR_SET(ex1,y) else GR_SET(0,y)
if (ex2>0) { // entrada anti
  if (ex1==ex2) { // punto solo
    gr_pixela(gr_pos,255-(unsigned char)((x1+x2)>>1));gr_pos++;
  } else { // degrade
    alpha=0;
    da=(255<<8)/(ex2-ex1);
    if (ex1<0) { alpha+=da*(-ex1);ex1=0; }
    if (ex2>=buffergr.width) ex2=buffergr.width-1;
    cnt=ex2-ex1+1;
    while (cnt--) { gr_pixela(gr_pos,alpha>>8);gr_pos++;alpha+=da; }
    }
  }
if (ex3<=ex2) return;
if (ex3>0) { // lleno
    if (ex2<0) { rx+=MA*(-ex2);ry+=MB*(-ex2);ex2=0; }
    if (ex3>buffergr.width) ex3=buffergr.width;
    cnt=ex3-ex2-1;
    while (cnt--) {
        texture(rx,ry);
        gr_pixel(gr_pos);gr_pos++;
        rx+=MA;
        ry+=MB;
        }
  }
if (ex4==ex3) { // punto solo
  if (ex4>=buffergr.width) return;
  gr_pixela(gr_pos,(unsigned char)((x3+x4)>>1));
} else { // degrade
  alpha=255<<8;
  da=(-255<<8)/(ex4-ex3);
  if (ex3<0) { alpha+=da*(-ex3);ex3=0; }
  if (ex4>buffergr.width) ex4=buffergr.width;
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
if (yMax>buffergr.height) { yMax=buffergr.height; }
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
yMin=buffergr.height+1;
yMax=-1;
cntSegm=0;
}
