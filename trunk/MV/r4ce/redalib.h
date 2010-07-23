#ifndef REDALIB_H
#define REDALIB_H

#include "gx.h"
#include "windef.h"

extern HINSTANCE hInst;
extern HWND hWnd;

extern unsigned short mxpos, mypos;
extern bool mbutton;
extern int tecla;
extern int evento;
// nuevas interrupciones
extern int SYSirqlapiz;
extern int SYSirqteclado;
extern int SYSirqsonido;
extern int SYSirqred;
extern int SYSirqjoystick;


//------------------------------------------------------------
void update(void);

inline WORD xpen(void) { return mxpos; }
inline WORD ypen(void) { return mypos; }
inline bool pendown(void)	{return mbutton;}

#endif
