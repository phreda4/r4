#ifndef GRAF_H
#define GRAF_H

#include "mat.h"
#include "redalib.h"

// variables internas
extern DWORD *gr_buffer;		// buffer de pantalla
extern int gr_ancho,gr_alto;
extern int gr_sizescreen;	// tamanio de pantalla
//extern int gr_extra,gr_offset;
extern WORD gr_color1,gr_color2,col1,col2;
extern BYTE gr_alphav;
extern int MA,MB,MTX,MTY; // matrix de transformacion
extern int *mTex; // textura

int gr_init(void);
void gr_fin(void);
extern void (*gr_redraw)(void);
extern void (*gr_drawre)(void);

WORD gr_RGB(DWORD c);
WORD gr_565(WORD c);
DWORD RGB_gr(WORD c);

void gr_clrscr(void);

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
inline void fillcol(DWORD c1,DWORD c2)  { col1=gr_RGB(c1);col2=gr_RGB(c2); }

void gr_hlined(int x1,int y1,int x2,BYTE a1,BYTE a2);
void gr_vlined(int x1,int y1,int x2,BYTE a1,BYTE a2);
void gr_hline(int x1,int y1,int x2);
void gr_vline(int x1,int y1,int y2);

//---- basicas
void gr_setpixel(int x,int y);
void gr_setpixela(int x,int y);
void gr_line(int x1,int y1,int x2,int y2);

void gr_pline(int x1,int y1,int x2,int y2,WORD t);
void gr_spline(int x1,int y1,int x2,int y2,int x3,int y3);
void gr_splinec(int x1,int y1,int x2,int y2,int x3,int y3);
void gr_box(int x1,int y1,int x2,int y2);
void gr_fbox(int x1,int y1,int x2,int y2);
void gr_fboxv(int x1,int y1,int x2,int y2);
void gr_fboxh(int x1,int y1,int x2,int y2);
void gr_circle(int x,int y,int r);
void gr_fillcircle(int x,int y,int r);

//---- poligono
void gr_psegmento(int x1,int y1,int x2,int y2);
void gr_pspline(int x1,int y1,int x2,int y2,int x3,int y3);
void gr_psplinec(int x1,int y1,int x2,int y2,int x3,int y3);

void gr_drawPoli(void);	
//void gr_drawLines(WORD gr);// lineas con grosor

//---- texto estatico
char gr_char(int x,int y,BYTE c);
char gr_charc(int x,int y,BYTE c);
void gr_textsize(char *t,int *x,int *y);
void gr_text(int x,int y,char *t);
void gr_textc(int x,int y,char *t);

#endif
