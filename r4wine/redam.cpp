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
//  Reda4 interprete y compilador  pabloreda@gmail.com
//  Version SDL (winylin)
//
// PHREDA 29/12/2005 Primera version
// SEBAS Desimone Correcciones Linux
// Charles Melice improve speed
// PHREDA 23/4/2007 Error para archivo (comentado)
// PHREDA 23/8/2007 AND? NAND? *>>
// PHREDA 18/3/2008 nuevas irq
// PHREDA 18/7/2008 bug lastcall fix
// PHREDA 1/8/2008  MOVE,MOVE>,CMOVE,CMOVE> por velocidad, decimales fixedpoint
// PHREDA 9/8/2008  separar line para runtime error, manejo de signal
// PHREDA 23/8/2008 switches
// PHREDA 13/12/2008 fuera DLL!! version WINE

#define WIN32_LEAN_AND_MEAN
#define WIN32_EXTRA_LEAN

#include <windows.h>
#include <winsock.h>
#include <stdio.h>
#include <time.h>

//#define OPENGL
#define FMOD

#include "graf.h"
#include "sound.h"
#include "joystick.h"

HWND        hWnd;
WNDCLASSA   wc;
MSG         msg;
DEVMODE     screenSettings;  
DWORD       dwExStyle, dwStyle;
RECT        rec; 
int         active;

struct hostent *host;
SOCKET      soc;
WSADATA     wsaData;
SOCKADDR_IN naddr; // the address structure for a TCP socket

char*        buffernet;
int     buffersize;

#define WM_WSAASYNC (WM_USER +5)

static const char wndclass[] = ":r4";

//#define LOGMEM
//#define ULTIMOMACRO 6
//char *macrose[]={ ";","LIT","ADR","CALL","JMP","JMPR" };

char *macros[]={// directivas del compilador     
";","(",")",")(","[","]","EXEC",
"0?","+?","-?","1?","=?","<?",">?","<=?",">=?","<>?","AND?","NAND?",
"DUP","DROP","OVER","PICK2","PICK3","PICK4","SWAP","NIP","ROT", //--- pila
"2DUP","2DROP","3DROP","4DROP","2OVER","2SWAP",
">R","R>","R","R+","R@+","R!+","RDROP",//--- pila direcciones
"AND","OR","XOR","NOT",                //--- logicas
"+","-","*","/","*/","*>>","/MOD","MOD","ABS", //--- aritmeticas
"NEG","1+","4+","1-","2/","2*","<<",">>",
"@","C@","W@","!","C!","W!","+!","C+!","W+!", //--- memoria
"@+","!+","C@+","C!+","W@+","W!+",
"MOVE","MOVE>","CMOVE","CMOVE>",//-- movimiento de memoria
"MEM","DIR","FILE","FSIZE","VOL","LOAD","SAVE",//--- memoria,bloques
"UPDATE","MSEC","TIME","DATE","END","RUN",//--- sistema
"SW","SH","CLS","REDRAW","FRAMEV",//--- pantalla
"SETXY","PX+!","PX!+","PX@",
"PAPER","INK","INK@","ALPHA", //--- color
"OP","CP","LINE","CURVE","PLINE","PCURVE","POLI",//--- dibujo
"FCOL","FCEN","FMAT","SFILL","LFILL","RFILL","TFILL",
"IPEN!",
"XYMOUSE","BMOUSE",//-------- mouse
"IKEY!","KEY", //"KEYX",          //-------- teclado
"IJOY!","CNTJOY","GETJOY",     //-------- joystick
#ifdef FMOD
"SLOAD","SPLAY","MLOAD","MPLAY",    //-------- sonido
#else
"ISON!","SBO","SBI",    // Sound Buffer Ouput/input   
#endif
"SERVER","CLIENT","SEND","RECV","CLOSE",
"TIMER",            //------- timer
""};

// instrucciones de maquina (son compilables a assembler)
enum {
FIN,LIT,ADR,CALL,JMP,JMPR, EXEC,//hasta JMPR no es visible
IF,PIF,NIF,UIF,IFN,IFL,IFG,IFLE,IFGE,IFNO,IFAND,IFNAND,// condicionales 0 - y +  y no 0
DUP,DROP,OVER,PICK2,PICK3,PICK4,SWAP,NIP,ROT,
DUP2,DROP2,DROP3,DROP4,OVER2,SWAP2,//--- pila
TOR,RFROM,ERRE,ERREM,ERRFM,ERRSM,ERRDR,//--- pila direcciones
AND,OR,XOR,NOT,//--- logica
SUMA,RESTA,MUL,DIV,MULDIV,MULSHR,DIVMOD,MOD,ABS,
NEG,INC,INC4,DEC,DIV2,MUL2,SHL,SHR,//--- aritmetica
FECH,CFECH,WFECH,STOR,CSTOR,WSTOR,INCSTOR,CINCSTOR,WINCSTOR,//--- memoria
FECHPLUS,STOREPLUS,CFECHPLUS,CSTOREPLUS,WFECHPLUS,WSTOREPLUS,
MOVED,MOVEA,CMOVED,CMOVEA,
MEM,PATH,BFILE,BFSIZE,VOL,LOAD,SAVE,//--- bloques de memoria, bloques
UPDATE,MSEC,TIME,IDATE,SISEND,SISRUN,//--- sistema
WIDTH,HEIGHT,CLS,REDRAW,FRAMEV,//--- pantalla
SETXY,MPX,SPX,GPX,
COLORF,COLOR,COLORA,ALPHA,//--- color
OP,CP,LINE,CURVE,PLINE,PCURVE,POLI,//--- dibujo
FCOL,FCEN,FMAT,SFILL,LFILL,RFILL,TFILL, //--- pintado
IRMOU,
XYMOUSE,BMOUSE,
IRKEY,KEY, //KEYX,
IRJOY,CNTJOY,GETJOY,
#ifdef FMOD
SLOAD,SPLAY,MLOAD,MPLAY,
#else
IRSON,SBO,SBI,
#endif
//---- nuevas interrups
SERVER,CLIENT,NSEND,RECV,CLOSE, //---- red
ITIMER,//--- timer
ULTIMAPRIMITIVA// de aqui en mas.. apila los numeros 0..255-ULTIMAPRIMITIVA
};

char *compilastr="";
char *bootstr="main.txt";
char *exestr="main.r4x";

//---------------------- Memoria de reda4
int gx1=0,gy1=0,gx2=0,gy2=0,gxc=0,gyc=0;// coordenadas de linea
BYTE *bootaddr;
FILE *file;
//---- eventos
//SDL_Event event;
char linea[1024];// 1k linea
char error[1024];
char pathdata[256];
//---- eventos teclado y raton
int SYSEVENT=0;

int SYSXYM=0;
int SYSBM=0;
int SYSKEY=0;
//int SYSKEYX=0;

// vectores de interrupciones
int SYSirqmouse=0;
int SYSirqteclado=0;
int SYSirqsonido=0;
int SYSirqred=0;
int SYSirqjoystick=0;
int SYSirqtime=0;

//----- Directorio 
char mindice[8192];// 8k de index 1024 archivos con nombres de 8 caracteres
char *indexdir[512];
int sizedir[512];
int cntindex;
char *subdirs[255]; 
int cntsubdirs;

//---- Date & Time
time_t sit;
tm *sitime;
//---- dato y programa
int cntdato;
int cntprog;
BYTE *memlibre;
//----- PILAS
int PSP[2048];// 2k pila de datos
BYTE *RSP[2048];// 2k pila de direcciones
BYTE ultimapalabra[]={ SISEND };
//--- Memoria
BYTE prog[1024*256];// 256k de programa
BYTE data[1024*1024*32];// 32 MB de datos

//---- Graba y carga imagen
void saveimagen(char *nombre)
{
file=fopen(nombre,"wb");if (file==NULL) return;
fwrite(&bootaddr,sizeof(int),1,file); // -cntprog
fwrite(&cntdato,sizeof(int),1,file);
fwrite(&cntprog,sizeof(int),1,file);
fwrite((void*)prog,1,cntprog,file);
fwrite((void*)data,1,cntdato,file);
fclose(file);
}

void loadimagen(char *nombre)
{
bootaddr=0;     
file=fopen(nombre,"rb");if (file==NULL) return;
fread(&bootaddr,sizeof(int),1,file); // -cntprog
fread(&cntdato,sizeof(int),1,file);
fread(&cntprog,sizeof(int),1,file);
fread((void*)prog,1,cntprog,file);
fread((void*)data,1,cntdato,file);
memlibre=data+cntdato;
fclose(file);
}

//---- el ultimo recurso
#ifdef LOGMEM
void ldebug(char *n)
{ FILE *stream;
if((stream=fopen("log.txt","a"))==NULL) return;
fputs(n,stream); if(fclose(stream)) return; }

void dumpest(void) {ldebug(linea);}
#endif

void loaddir(void)
{
cntindex=cntsubdirs=0;
char *virtualName;
WIN32_FIND_DATA ffd;
char searchName[MAX_PATH + 3];
char *act=mindice;
strncpy(searchName,pathdata, MAX_PATH);
strcat(searchName, "\\*");
HANDLE hFind = FindFirstFile(searchName, &ffd);
if (hFind == INVALID_HANDLE_VALUE) { FindClose(hFind); return; }
do {
	virtualName = ffd.cFileName;
	if (((virtualName[0] == '.') && (virtualName[1] == '\0')) ||
		((virtualName[0] == '.') && (virtualName[1] == '.') && (virtualName[2] == '\0')))
		continue;
	if (ffd.dwFileAttributes&FILE_ATTRIBUTE_DIRECTORY) {
        subdirs[cntsubdirs] = act;
        cntsubdirs++;
	} else { // is a file
        indexdir[cntindex] = act;
		sizedir[cntindex] = ffd.nFileSizeHigh<<16 +	ffd.nFileSizeLow;
        cntindex++;
		}
    strcpy(act,virtualName); 
	while (*act!=0) act++;
	act++;
	} while (FindNextFile(hFind, &ffd) != 0);
FindClose(hFind);
}

//---------------------------------------------------------------
int interprete(BYTE *codigo)// 1=recompilar con nombre en linea
{      
if (codigo==NULL) return -1;
register int TOS;			// Tope de la pila PSP
register int *NOS;			// Next of stack
register BYTE **R;			// return stack
BYTE *IP=codigo;	// lugar del programa // ebx
int W,W1;			// palabra actual y auxiliar
int *vcursor;

SYSirqmouse=0;
SYSirqteclado=0;
SYSirqjoystick=0;
SYSirqsonido=0;
SYSirqred=0;
SYSEVENT=0;
vcursor=(int*)gr_buffer;

R=RSP;*R=(BYTE*)&ultimapalabra;
NOS=PSP;*NOS=TOS=0;
while (true)  {// Charles Melice  suggest next:... goto next; bye !
    W=(BYTE)*IP++;
	switch (W) {// obtener codigo de ejecucion
	case FIN: IP=*R;R--;continue;
    case LIT: NOS++;*NOS=TOS;TOS=*(DWORD*)IP;IP+=sizeof(int);continue;
    case ADR: NOS++;*NOS=TOS;W=*(DWORD*)IP;IP+=sizeof(int);TOS=*(DWORD*)W;continue;
    case CALL: W=*(DWORD*)IP;IP+=sizeof(int);R++;*R=IP;IP=(BYTE*)W;continue;
	case JMP: W=*(int*)IP;IP=(BYTE*)W;continue;
    case JMPR: W=*(char*)IP;W++;IP+=W;continue;
//-hasta aca solo lo escribe el compilador
//--- condicionales
	case IF: W=*(char*)IP;IP++;if (TOS!=0) IP+=W; continue;
    case PIF: W=*(char*)IP;IP++;if (TOS<=0) IP+=W; continue;
	case NIF: W=*(char*)IP;IP++;if (TOS>=0) IP+=W; continue;
    case UIF: W=*(char*)IP;IP++;if (TOS==0) IP+=W; continue;
    case IFN: W=*(char*)IP;IP++;if (TOS!=*NOS) IP+=W; 
		TOS=*NOS;NOS--;continue;
    case IFNO: W=*(char*)IP;IP++;if (TOS==*NOS) IP+=W; 
		TOS=*NOS;NOS--;continue;
    case IFL: W=*(char*)IP;IP++;if (TOS<=*NOS) IP+=W; 
		TOS=*NOS;NOS--;continue;
    case IFG: W=*(char*)IP;IP++;if (TOS>=*NOS) IP+=W; 
		TOS=*NOS;NOS--;continue;
    case IFLE: W=*(char*)IP;IP++;if (TOS<*NOS) IP+=W; 
		TOS=*NOS;NOS--;continue;
    case IFGE: W=*(char*)IP;IP++;if (TOS>*NOS) IP+=W; 
		TOS=*NOS;NOS--;continue;
    case IFAND: W=*(char*)IP;IP++;if (!(TOS&*NOS)) IP+=W; 
		TOS=*NOS;NOS--;continue;
    case IFNAND: W=*(char*)IP;IP++;if (TOS&*NOS) IP+=W; 
		TOS=*NOS;NOS--;continue;
//--- fin condicionales dependiente de bloques    
	case EXEC:W=TOS;TOS=*NOS;NOS--;if (W!=0) { R++;*R=IP;IP=(BYTE*)W; } continue;
//--- pila de datos
	case DUP: NOS++;*NOS=TOS;continue;
    case DROP: TOS=*NOS;NOS--;continue;
    case OVER: NOS++;*NOS=TOS;TOS=*(NOS-1); continue;
	case PICK2: NOS++;*NOS=TOS;TOS=*(NOS-2); continue;
    case PICK3: NOS++;*NOS=TOS;TOS=*(NOS-3);continue;
    case PICK4: NOS++;*NOS=TOS;TOS=*(NOS-4);continue;
	case SWAP: W=*NOS;*NOS=TOS;TOS=W;continue;
    case NIP: NOS--;continue;
    case ROT: W=TOS;TOS=*(NOS-1);*(NOS-1)=*NOS;*NOS=W;continue;
	case DUP2: W=*NOS;NOS++;*NOS=TOS;NOS++;*NOS=W;continue;// ( a b -- a b a b
    case DROP2: NOS--;TOS=*NOS;NOS--;continue;
    case DROP3: NOS-=2;TOS=*NOS;NOS--;continue;// ( a b c --
    case DROP4: NOS-=3;TOS=*NOS;NOS--;continue;// ( a b c d --
    case OVER2: NOS++;*NOS=TOS;TOS=*(NOS-3);// ( a b c d -- a b c d a b
		NOS++;*NOS=TOS;TOS=*(NOS-3);continue;
    case SWAP2: W=*NOS;*NOS=*(NOS-2);*(NOS-2)=W;// ( a b c d -- c d a b		
       W=TOS;TOS=*(NOS-1);*(NOS-1)=W;continue;
	case TOR: R++;*R=(BYTE*)TOS;TOS=*NOS;NOS--;continue;
    case RFROM: NOS++;*NOS=TOS;TOS=(int)*R;R--;continue;
    case ERRE: NOS++;*NOS=TOS;TOS=(int)*R;continue;
	case ERREM: (*(int*)R)+=TOS;TOS=*NOS;NOS--;continue;
    case ERRFM: NOS++;*NOS=TOS;TOS=**(int**)R;(*(int*)R)+=4;continue;
    case ERRSM: **(int**)R=TOS;TOS=*NOS;NOS--;(*(int*)R)+=4;continue;
    case ERRDR: R--;continue;
	case AND: TOS&=*NOS;NOS--;continue;
    case OR: TOS|=*NOS;NOS--;continue;
	case XOR: TOS^=*NOS;NOS--;continue;
    case NOT: TOS=~TOS;continue;
//--- aritmeticas	
	case SUMA: TOS=(*NOS)+TOS;NOS--;continue;
    case RESTA: TOS=(*NOS)-TOS;NOS--;continue;
	case MUL: TOS=(*NOS)*TOS;NOS--;continue;
    case DIV: //if (TOS==0) { TOS=*NOS;NOS--;continue; }
	     TOS=*NOS/TOS;NOS--;continue;
	case MULDIV: //if (TOS==0) { NOS--;TOS=*NOS;NOS--;continue; }
	     TOS=(*(NOS-1))*(*NOS)/TOS;NOS-=2;continue;
	case MULSHR: TOS=((long long)(*(NOS-1))*(*NOS))>>TOS;NOS-=2;continue;
    case DIVMOD: if (TOS==0) { NOS--;TOS=*NOS;NOS--;continue; }
	     W=*NOS%TOS;*NOS=*NOS/TOS;TOS=W;continue;
	case MOD: TOS=*NOS%TOS;NOS--;continue;
    case ABS: W=(TOS>>31);TOS=(TOS+W)^W;continue;
    case NEG: TOS=-TOS;continue;
    case INC: TOS++;continue;	case INC4: TOS+=4;continue; case DEC: TOS--;continue;	
    case DIV2: TOS>>=1;continue;	case MUL2: TOS<<=1;continue;
	case SHL: TOS=(*NOS)<<TOS;NOS--;continue;
    case SHR: TOS=(*NOS)>>TOS;NOS--;continue;
//--- memoria
	case FECH: TOS=*(int *)TOS;continue;
    case CFECH: TOS=*(char*)TOS;continue;
    case WFECH: TOS=*(short *)TOS;continue;
	case STOR: *(int *)TOS=(int)*NOS;NOS--;TOS=*NOS;NOS--;continue;
    case CSTOR: *(char*)TOS=(char)*NOS;NOS--;TOS=*NOS;NOS--;continue;
    case WSTOR: *(short *)TOS=(short)*NOS;NOS--;TOS=*NOS;NOS--;continue;
	case INCSTOR: *((int *)TOS)+=(int)*NOS;NOS--;TOS=*NOS;NOS--;continue;
    case CINCSTOR: *((char*)TOS)+=(char)*NOS;NOS--;TOS=*NOS;NOS--;continue;
    case WINCSTOR: *((short *)TOS)+=(short)*NOS;NOS--;TOS=*NOS;NOS--;continue;
    case FECHPLUS: NOS++;*NOS=TOS+4;TOS=*(int *)TOS;continue; //@+ | adr -- adr' v
    case STOREPLUS: *(int *)TOS=(int)*NOS;TOS+=4;NOS--;continue;//!+ | v adr -- adr'
    case CFECHPLUS: NOS++;*NOS=TOS+1;TOS=*(char *)TOS;continue;
    case CSTOREPLUS: *(char *)TOS=(char)*NOS;TOS++;NOS--;continue;
    case WFECHPLUS: NOS++;*NOS=TOS+2;TOS=*(short *)TOS;continue;
    case WSTOREPLUS: *(short *)TOS=(short)*NOS;TOS+=2;NOS--;continue;
//--- sistema
	case UPDATE: 
         if (PeekMessage(&msg,hWnd,0,0,PM_REMOVE)) // process messages
            {  //TranslateMessage(&msg); 
            DispatchMessage(&msg);
            if (SYSEVENT!=0) { R++;*(int*)R=(int)IP;IP=(BYTE*)SYSEVENT;SYSEVENT=0; }
/*
            if (active==WA_INACTIVE) {
               while (active==WA_INACTIVE) {    // cambiar esto para poder prender 2 r4
                Sleep(2);
                PeekMessage(&msg,hWnd,0,0,PM_REMOVE);
                TranslateMessage(&msg); DispatchMessage(&msg);
                }
//              gr_restore();
              }
*/
            }
#ifndef FMOD
        if (evtsound==1 && SYSirqsonido!=0) 
            { R++;*(int*)R=(int)IP;IP=(BYTE*)SYSirqsonido;evtsound=0; }
#endif
		break;
	case MSEC: NOS++;*NOS=TOS;TOS=timeGetTime();continue;
    case IDATE: time(&sit);sitime=localtime(&sit);NOS++;*NOS=TOS;TOS=sitime->tm_year; //+1900
  NOS++;*NOS=TOS;TOS=sitime->tm_mon;NOS++;*NOS=TOS;TOS=sitime->tm_wday;continue;
    case TIME: time(&sit);sitime=localtime(&sit);NOS++;*NOS=TOS;TOS=sitime->tm_hour; 
  NOS++;*NOS=TOS;TOS=sitime->tm_min;NOS++;*NOS=TOS;TOS=sitime->tm_sec;continue;
    case SISEND: return 0;  
    case SISRUN: if (TOS!=0) { bootstr=(char*)TOS;exestr=""; }return 1;
//    case SISIRUN: if (TOS!=0) exestr=(char*)TOS;return 1;
//--- pantalla
    case WIDTH: NOS++;*NOS=TOS;TOS=gr_ancho;continue;
    case HEIGHT: NOS++;*NOS=TOS;TOS=gr_alto;continue;
	case CLS: gr_clrscr();continue;
    case REDRAW:  gr_redraw();continue;
    case FRAMEV: NOS++;*NOS=TOS;TOS=(int)gr_buffer;continue;
	case SETXY:vcursor=(int*)gr_buffer+TOS*gr_ancho+(*NOS);
        NOS--;TOS=*NOS;NOS--;continue;
	case MPX:vcursor+=TOS;TOS=*NOS;NOS--;continue;
	case SPX:*(int*)(vcursor++)=TOS;TOS=*NOS;NOS--;continue;
	case GPX:NOS++;*NOS=TOS;TOS=*(int*)(vcursor);continue;
//--- color
	case COLORF: gr_color2=TOS;TOS=*NOS;NOS--;continue;
    case COLOR: gr_color1=TOS;TOS=*NOS;NOS--;continue;
    case COLORA: NOS++;*NOS=TOS;TOS=gr_color1;continue;
	case ALPHA: if (TOS>254) gr_solid(); else { gr_alphav=(BYTE)(TOS);gr_alpha(); }
		TOS=*NOS;NOS--;continue;
//--- dibujo
    case OP: gy1=TOS;gx1=*NOS;NOS--;TOS=*NOS;NOS--;continue;
    case CP: gyc=TOS;gxc=*NOS;NOS--;TOS=*NOS;NOS--;continue;
	case LINE: gy2=TOS;gx2=*NOS;NOS--;TOS=*NOS;NOS--;
		gr_line(gx1,gy1,gx2,gy2);gx1=gx2;gy1=gy2;continue;
    case CURVE: gy2=TOS;gx2=*NOS;NOS--;TOS=*NOS;NOS--;
		gr_spline(gx1,gy1,gxc,gyc,gx2,gy2);gx1=gx2;gy1=gy2;continue;
	case PLINE: gy2=TOS;gx2=*NOS;NOS--;TOS=*NOS;NOS--;
		gr_psegmento(gx1,gy1,gx2,gy2);gx1=gx2;gy1=gy2;continue;
    case PCURVE: gy2=TOS;gx2=*NOS;NOS--;TOS=*NOS;NOS--;
		gr_pspline(gx1,gy1,gxc,gyc,gx2,gy2);gx1=gx2;gy1=gy2;continue;
	case POLI: gr_drawPoli();continue;
    case FCOL: fillcol(*NOS,TOS);NOS--;TOS=*NOS;NOS--;continue;
    case FCEN: fillcent(*NOS,TOS);NOS--;TOS=*NOS;NOS--;continue;
    case FMAT: fillmat(*NOS,TOS);NOS--;TOS=*NOS;NOS--;continue;
    case SFILL: fillSol();continue;
    case LFILL: fillLin();continue;
    case RFILL: fillRad();continue;
    case TFILL: mTex=(int*)TOS;fillTex();TOS=*NOS;NOS--;continue;

//---- raton
    case IRMOU: SYSirqmouse=TOS;TOS=*NOS;NOS--;continue;
    case XYMOUSE: NOS++;*NOS=TOS;NOS++;*NOS=SYSXYM&0xffff;TOS=(SYSXYM>>16);continue;
    case BMOUSE: NOS++;*NOS=TOS;TOS=SYSBM;continue;
//----- teclado
    case IRKEY: SYSirqteclado=TOS;TOS=*NOS;NOS--;continue;
	case KEY: NOS++;*NOS=TOS;TOS=SYSKEY;continue;
//	case KEYX: NOS++;*NOS=TOS;TOS=SYSKEYX;continue;
//----- joy
    case IRJOY: SYSirqjoystick=TOS;TOS=*NOS;NOS--;continue;
    case CNTJOY: NOS++;*NOS=TOS;TOS=cntJoy;continue;
    case GETJOY: TOS=getjoy(TOS);continue;
//------- sonido
#ifdef FMOD
    case SLOAD: // "" -- pp
        TOS=(int)FSOUND_Sample_Load(FSOUND_FREE,(char *)TOS,FSOUND_NORMAL,0,0);
        continue;
    case SPLAY: // pp --
        if (TOS!=0) FSOUND_PlaySound(FSOUND_FREE,(FSOUND_SAMPLE *)TOS);
        else FSOUND_StopSound(FSOUND_ALL);
        TOS=*NOS;NOS--;
        continue;
    case MLOAD: // "" -- mm
        TOS=(int)FMUSIC_LoadSong((char*)TOS);
        continue;
    case MPLAY: // mm --
        if (TOS!=0) FMUSIC_PlaySong((FMUSIC_MODULE*)TOS); 
        else FMUSIC_StopAllSongs();
        TOS=*NOS;NOS--;continue;
#else
    case IRSON: SYSirqsonido=TOS;TOS=*NOS;NOS--;continue;
    case SBO: NOS++;*NOS=TOS;TOS=(int)bosound();continue;
    case SBI: NOS++;*NOS=TOS;TOS=(int)bisound();continue;
#endif

//--- bloque de memoria
    case MEM: NOS++;*NOS=TOS;TOS=(int)memlibre;continue; // inicio de n-MB de datos
//--- bloques
	case PATH: if (TOS!=0) { strcpy(pathdata,(char*)TOS);loaddir(); }
         TOS=*NOS;NOS--;continue;
    case BFILE: // nro -- "nombre" o 0
         if (TOS>=cntindex || TOS<0) TOS=0; else  TOS=(int)indexdir[TOS];
         continue;
    case BFSIZE: // nro --  size o 0
         if (TOS>=cntindex || TOS<0) TOS=0; else  TOS=sizedir[TOS];
         continue;
	case VOL:// nro -- "nombre" o 0
         if (TOS>=cntsubdirs || TOS<0) TOS=0; else TOS=(int)subdirs[TOS];
         continue;
	case LOAD: // 'from "filename" -- 'to
         if (TOS==0||*NOS==0) { TOS=*NOS;NOS--;continue; }
         sprintf(error,"%s%s",pathdata,(char*)TOS);
         TOS=*NOS;NOS--;
         file=fopen(error,"rb");if (file==NULL) continue;
         do { W=fread((void*)TOS,sizeof(char),1024,file); TOS+=W; } while (W==1024);
         fclose(file);continue;
    case SAVE: // 'from cnt "filename" --
         if (TOS==0||*NOS==0) { NOS-=2;TOS=*NOS;NOS--;continue; }
         sprintf(error,"%s%s",pathdata,(char*)TOS);
         TOS=*NOS;NOS--;
         file=fopen(error,"wb");if (file==NULL) { NOS--;TOS=*NOS;NOS--;continue; }
         fwrite((void*)*NOS,sizeof(char),TOS,file);
         fclose(file);//loaddir();
         NOS--;TOS=*NOS;NOS--;continue;
// por velocidad         
    case MOVED: // | de sr cnt --
         W=*(NOS-1);W1=*NOS;
         while (TOS--) { *(int *)W=*(int *)W1;W+=4;W1+=4; }
         NOS-=2;TOS=*NOS;NOS--;
         continue;
    case MOVEA: // | de sr cnt --
         W=(*(NOS-1))+(TOS<<2);W1=(*NOS)+(TOS<<2);
         while (TOS--) { W-=4;W1-=4;*(int *)W=*(int *)W1; }         
         NOS-=2;TOS=*NOS;NOS--;
         continue;
    case CMOVED: // | de sr cnt --
         W=*(NOS-1);W1=*NOS;    
         while (TOS--) { *(char*)W++=*(char*)W1++; }
         NOS-=2;TOS=*NOS;NOS--;
         continue;
    case CMOVEA: // | de sr cnt --
         W=(*(NOS-1))+TOS;W1=(*NOS)+TOS;
         while (TOS--) { *(char*)--W=*(char*)--W1; }         
         NOS-=2;TOS=*NOS;NOS--;         
         continue;
//--- red
    case SERVER: //  port -- err
        naddr.sin_family = AF_INET;      // Address family Internet
        naddr.sin_port = htons (TOS);   // Assign port to this socket
        naddr.sin_addr.s_addr = htonl (INADDR_ANY);   // No destination
        soc = socket (AF_INET, SOCK_STREAM, IPPROTO_TCP); // Create socket
        if (bind(soc, (LPSOCKADDR)&naddr, sizeof(naddr)) == SOCKET_ERROR) //Try binding
            { TOS=0;continue; }
        listen(soc, 10); //Start listening
        WSAAsyncSelect(soc,hWnd,WM_WSAASYNC, FD_READ | FD_ACCEPT | FD_CLOSE); //Switch to Non-Blocking mode
        continue;
    case CLIENT: // "dir" port -- err
        naddr.sin_family = AF_INET;           // address family Internet
        naddr.sin_port = htons(TOS);        // set server’s port number
        TOS=*NOS;NOS--;
    	if((host=gethostbyname((char*)TOS))==NULL)// Resolve IP address for hostname
        	{ TOS=0;continue; }
        naddr.sin_addr.s_addr = *((unsigned long*)host->h_addr);
        soc = socket (AF_INET, SOCK_STREAM, IPPROTO_TCP); // Create socket
        if (connect(soc, (SOCKADDR *)&naddr, sizeof(naddr)) == SOCKET_ERROR) //Try binding
          { TOS=0;continue; } 
        WSAAsyncSelect(soc,hWnd,WM_WSAASYNC, FD_READ | //FD_CONNECT | 
    FD_CLOSE);
        continue;
    case NSEND:  // buff len --
        send(soc,(char*)(*NOS), TOS, 0); //Send the string
        NOS--;TOS=*NOS;NOS--;
        continue;
    case RECV:  // 'vector 'buffer --       vector | buff len --
        buffernet=(char*)TOS;SYSirqred=*NOS;
        NOS--;TOS=*NOS;NOS--;
        continue; 
    case CLOSE:// --
        closesocket(soc); //Shut down socket
        continue;
//---- timer
    case ITIMER: // vector msecs --
        SetTimer(hWnd,0,TOS,0);
        SYSirqtime=*NOS;NOS--;TOS=*(NOS);NOS--;
        continue;
	default: // completa los 8 bits con apila numeros 0...
        NOS++;*NOS=TOS;TOS=W-ULTIMAPRIMITIVA;continue;
	} } };

//----------------------------------------------
struct Indice {	char *nombre;BYTE *codigo;int tipo;	 };
//---- diccionario local
int cntindice;
Indice indice[2048];
int cntnombre;
char nombre[1024*16];
//---- diccionario exportados
int cntindiceex;
Indice indiceex[2048];
int cntnombreex;
char nombreex[1024*32];
//---- includes
int cntincludes;
Indice includes[25];
//---- pila de compilador
int cntpilaA;
int cntpila;
int pila[256];

void apila(int n) { //if (cntpila>255) { sprintf(error,"apila error");ldebug(error);return; }
pila[cntpila++]=n; }

int desapila(void) {//if (cntpila==0) { sprintf(error,"desapila error");ldebug(error);return 0; }
return pila[--cntpila]; }

void iniA(void) { cntpilaA=0; }
void pushA(int n) { PSP[cntpilaA++]=n; }
int popA(void) { return PSP[--cntpilaA]; }

#ifdef LOGMEM
void dumplocal(char *nombre)
{
FILE *stream;
if((stream=fopen("log.txt","a"))==NULL) return;
fprintf(stream,"**** %s ****\n", nombre);
for (int i=0;i<cntindice;i++)
    fprintf(stream,"%s %d\n",indice[i].nombre,indice[i].codigo-prog);
if(fclose(stream)) return; 
}    

void dumpex(void)
{
FILE *stream;
if((stream=fopen("log.txt","a"))==NULL) return;
fprintf(stream,"-------\n");
for (int i=0;i<cntindiceex;i++)
    fprintf(stream,"%s %d\n",indiceex[i].nombre,indiceex[i].codigo-prog);
fprintf(stream,"-------\n");    
if(fclose(stream)) return;
}    
#endif
//---- espacio de dato
void adato(const char *p) 
{ strcpy((char*)&data[cntdato],p);cntdato+=strlen(p)+1; } 

void adatonro(int n,int u)
{ BYTE *p=&data[cntdato];     
switch(u) {
  case 1:*(char *)p=(char)n;break;// char
  case 2:*(short *)p=(short)n;break;// short
  case 4:*(int  *)p=(int)n;break;// int
  };
cntdato+=u;  }

void adatocnt(int n)
{ BYTE *p=&data[cntdato];
for (int i=0;i<n;i++,p++) *p=0;
cntdato+=n; }

//---- espacio de codigo
BYTE *lastcall=NULL;

void aprognro(int n) // graba nro como literal
{ BYTE *p=&prog[cntprog];lastcall=NULL;
if (n>=0 && n<255-ULTIMAPRIMITIVA) { 
  *p=ULTIMAPRIMITIVA+n;cntprog++;
} else {
  *p=LIT;p++;*(int *)p=(int)n;
  cntprog+=5; } }

void aprog(int n) // grabo primitiva
{ BYTE *p=&prog[cntprog];*p=(BYTE)n;
if (n==CALL) lastcall=p; else lastcall=NULL;
cntprog++; }

void aprogint(int n)
{ BYTE *p=&prog[cntprog];*(DWORD*)p=(DWORD)&prog[n];cntprog+=4; }

void aprogaddr(int n) // grabo direccion
{ BYTE *p=&prog[cntprog];*(DWORD*)p=(DWORD)indice[n].codigo;cntprog+=4; }

void aprogaddrex(int n) // grabo direccion exportada
{ BYTE *p=&prog[cntprog];*(DWORD*)p=(DWORD)indiceex[n].codigo;cntprog+=4; }

//---- definicion
void define(char *p) 
{
Indice *actualex,*actual=&indice[cntindice++];
char *n;
actual->tipo=*p;
p++;
if (*p==':') { p++;// nombre exportado
    actualex=&indiceex[cntindiceex++];
	n=&nombreex[cntnombreex];
	strcpy(n,p);cntnombreex+=strlen(p)+1;
	actualex->tipo=actual->tipo;
	actualex->nombre=n;
	actualex->codigo=(actual->tipo==':')?&prog[cntprog]:&data[cntdato];
	};
n=&nombre[cntnombre];
strcpy(n,p);cntnombre+=strlen(p)+1;//---- espacio de nombres
actual->nombre=n;
actual->codigo=(actual->tipo==':')?&prog[cntprog]:&data[cntdato]; }

void compilofin(void)
{
if (lastcall!=NULL) { *lastcall=JMP;lastcall=NULL; }
    else aprog(FIN);
}

void endefine(void)
{
Indice *actual=&indice[cntindice-1];     
if (actual->tipo==':') {
   compilofin();                        
//  if (lastcall!=NULL) { *lastcall=JMP;lastcall=NULL; } else aprog(FIN);
  } else { if (&data[cntdato]==actual->codigo) adatonro(0,4); } }

void endefinesin(void)
{
Indice *actual=&indice[cntindice-1];
//if (cntPilaA>0)
if (actual->tipo!=':' && &data[cntdato]==actual->codigo) adatonro(0,4); 
}

//---- parse de fuente
long numero;

int esnumero(char *p)
{//if (*p=='&') { p++;numero=*p;return 1;} // codigo ascii
int base,dig=0,signo=0;
if (*p=='-') { p++;signo=1; } else if (*p=='+') p++;
if (*p==0) return 0;// no es numero
switch(*p) {
  case '$': base=16;p++;break;// hexa
  case '%': base=2;p++;break;// binario
  default:  base=10;break; }; 
numero=0;if (*p==0) return 0;// no es numero
while (*p!=0) {
  if (*p<='9') dig=*p-'0'; else if (*p>='A') dig=*p-'A'+10;
  else return 0;
  if (dig<0 || dig>=base) return 0;
  numero*=base;numero+=dig;
  p++;
  };
if (signo==1) numero=-numero;  
return 1; };

int esnumerof(char *p)         // decimal punto fijo 16.16
{
int parte0,dig=0,signo=0;
if (*p=='-') { p++;signo=1; } else if (*p=='+') p++;
if (*p==0) return 0;// no es numero
numero=0;
while (*p!=0) {
  if (*p=='.') { parte0=numero;numero=1;if (numero==0 && *(p+1)<33) return 0; } else 
  {
  if (*p<='9') dig=*p-'0'; else dig=-1;
  if (dig<0 || dig>=10) return 0;
  numero=(numero*10)+dig;
  }
  p++;
  };  
int decim=1,num=numero;
while (num>1) { decim*=10;num/=10; }
num=0x10000*numero/decim;
numero=(num&0xffff)|(parte0<<16);
if (signo==1) numero=-numero;  
return 1; };

int esmacro(char *p)
{    
numero=0;
char **m=macros;
while (**m!=0) {
  if (!strcmp(*m,p)) return 1;
  *m++;numero++; }    
return 0;  }

int espalabra(char *p)
{
numero=cntindice-1;
Indice *actual=&indice[numero];
while (actual>=indice) {
  if (!strcmp(actual->nombre,p)) return 1;
  actual--;numero--;  }
return 0;  }

int espalabraex(char *p)
{
numero=cntindiceex-1;
Indice *actual=&indiceex[numero];
while (actual>=indiceex) {
  if (!strcmp(actual->nombre,p)) return 1;
  actual--;numero--; }
return 0; }

//----- Include
int estainclude(char *palabra)
{
if (cntincludes==0) return 0;
Indice *actual=&includes[cntincludes-1];
while (actual>=includes) {
	if (!strcmp(actual->nombre,palabra)) return 1;
	actual--; }
return 0; }

void agregainclude(char *palabra)
{
Indice *act=&includes[cntincludes++];
char *n=&nombreex[cntnombreex];
strcpy(n,palabra);cntnombreex+=strlen(palabra)+1;
act->nombre=n; }

//-------------------------------
#define E_DATO 1
#define E_PROG 2

#define COMPILAOK 0
#define OPENERROR 1
#define CLOSEERROR 2
#define CODIGOERROR 3

char tolower(char c)
{
if (c>0x40 && c<0x5b) c+=0x20;
return c;
}

char toupper(char c)
{
if (c>0x60 && c<0x7b) c-=0x20;
return c;
}

//---------------------------------------------------------------
// compila el archivo
int compilafile(char *name)
{
FILE *stream;
char *ahora,*palabra,*copia;
char lineat[512];
// SEBAS: 2006-10-14 
ahora=name;
while (*ahora>32) { *ahora=tolower(*ahora);ahora++; }

sprintf(lineat,"%s%s",pathdata,name);
if((stream=fopen(lineat,"rb"))==NULL) {
  sprintf(error,"%s|0|0|no existe %s",linea,lineat);
  return OPENERROR;
  }
int estado=E_PROG;int unidad=4;int salto=0;
int aux,nrolinea=1;// convertir a nro de linea local
cntpila=0;
while(!feof(stream)) {
  *lineat=0;fgets(lineat,512,stream);ahora=lineat;// ldebug(ahora);
otrapalabra:
  while (*ahora!=0 && *ahora<33) ahora++;
  if (*ahora==0) goto otralinea;
  palabra=ahora;
  if (*ahora=='"') { ahora++;copia=ahora;
     while (*copia!=0) { 
           if (*copia=='"') { if (*(copia+1)!='"') break; copia++; }
           *ahora=*copia;ahora++;copia++; }
     if (ahora!=copia) { *ahora=0;ahora=copia; } }
  else { while (*ahora>32) { *ahora=toupper(*ahora);ahora++; } }
  if (*ahora==0) *(ahora+1)=0;
  *ahora=0;
  if (*palabra=='|') *(ahora+1)=0;// comentario
  else if (*palabra=='"') // string
    { 
    palabra++;// graba str
    switch (estado) {
      case E_DATO:	
            adato(palabra);break;
//              pushA((int)&data[cntdato]);
//              adato(palabra);break;
      case E_PROG:	aux=(int)&data[cntdato];adato(palabra);aprognro(aux);break; 
      };
    }
  else if (*palabra==':'||*palabra=='#')// define codigo y dato
    {
	if (cntpila>0) { sprintf(error,"bloque mal cerrado");goto error; }
	endefinesin();
	iniA();
	if (*(palabra+1)==0) { bootaddr=&prog[cntprog]; // : con espacio
    } else {
    	if (esnumero(palabra)==1) { sprintf(error,"nro invalido");goto error; }
	  // avisa palabra repetida?
       define(palabra); }
   estado=(*palabra==':')?E_PROG:E_DATO;unidad=4;
    }
  else if (*palabra=='^')// include
	{
	palabra++;
	if (estainclude(palabra)==0) {// si esta en la lista no se incluye
		agregainclude(palabra);// agrega a la lista
		aux=compilafile(palabra);// inclusion recursiva
        if (aux==OPENERROR) { sprintf(error,"no existe %s",palabra);goto error; } 
		if (aux!=COMPILAOK) { return aux; }
#ifdef LOGMEM		
		dumplocal(palabra);
#endif
		cntindice=cntnombre=0;// espacio de nombres reset
		}
	}
  else if (esnumero(palabra)==1 || esnumerof(palabra)==1) // numero
    {
    switch (estado) {
      case E_DATO: 
        if (unidad==0) adatocnt(numero); else adatonro(numero,unidad);
        break; // graba numero 
      case E_PROG: 
		aprognro(numero);break; // compila apila numero
      };
    }    
  else if (esmacro(palabra)==1)  // macro
    {
    switch (estado) {
      case E_DATO:
        switch (numero) {
          case 0: endefine();break;// fin de dato
          case 1: apila(unidad);unidad=1;break;	 // { cuenta bytes
          case 2: unidad=desapila();break;		 // }
          case 3: unidad=0;break;				 // }{ cantidad bytes
 		  case 4: apila(unidad);unidad=2;break;	 // [ cuenta words
		  case 5: unidad=desapila();break;		 // ]
          default: 
			sprintf(error,"palabra %s en dato ?",palabra);goto error;  }           
        break; // graba numero
      case E_PROG:// ? ( . )( . )  ( . ? )  ( . ? )( . )  ( . ) 
        switch (numero) {
          case 0:// ; fin de dato
            if (cntpila>0) compilofin();// anidamiento compilo fin
            else { endefine(); }// termino palabra
            break;
          case 1: // (
            if (salto==1)
              { apila(cntprog);apila(1);cntprog++;salto=0; }
            else 
              { apila(cntprog);apila(2); } 
            break;               
          case 2: // )
            aux=desapila();lastcall=NULL;
            if (aux==1) {
              aux=desapila();
              if (salto==0) { prog[aux]=cntprog-aux-1; }  
                else { sprintf(error,"? ) no valido ");goto error; }
            } else if (aux==2) { // repeticion
              aux=desapila();
              if (salto==1) { prog[cntprog]=aux-cntprog-1;cntprog++;salto=0; } 
                else { // repeat
                  aprog(JMPR);prog[cntprog]=aux-cntprog-1;cntprog++;
                   }
            } else if (aux==3) { // rep cond
              aux=desapila();
              if (salto==0) { 
                  aprog(JMPR);prog[cntprog]=aux-cntprog-1;cntprog++; 
                  aux=desapila();prog[aux]=cntprog-aux-1;
                  } 
                else { sprintf(error,") mal cerrado");goto error; }
              } else
                { sprintf(error,") mal cerrado");goto error; }
            break;
          case 3: // )(
            aux=desapila();
		    if (aux==1) { // else del if
				aux=desapila();// direccion
				if (salto==0) { 
                  aprog(JMPR);apila(cntprog);apila(1);cntprog++;
                  prog[aux]=cntprog-aux-1;
                 } else { sprintf(error,"? )( no valido");goto error; }
            } else if (aux==2) {
                aux=desapila();
                if (salto==1)  
                   { apila(cntprog);cntprog++;apila(aux);apila(3);salto=0; } 
                else { sprintf(error,")( falta condicion");goto error; }
            } else  
                { sprintf(error,")( mal cerrado");goto error; }
            break;               
		  case 4:// [ palabra anonima
			aprog(LIT);aprogint(cntprog+4+2);
			aprog(JMPR);apila(cntprog);apila(4);cntprog++;
		    break;
		  case 5:// ]
			if (desapila()!=4) { sprintf(error,"[] mal cerrado");goto error; }
			aux=desapila();prog[aux]=cntprog-aux-1;
		    break;
		  default:
		    aprog(numero);// compila primitiva
            if (numero>=IF && numero<=IFNAND) salto=1; else salto=0;
		    break;
          };
        break; 
        };
  } else { // palabra
    aux=0;if (*palabra=='\'') { 
		palabra++;aux=1;// aux=direccion de
		if (esnumero(palabra)==1) { strcpy(error,"nro ?");goto error; }
		}
    if (espalabra(palabra)==1) {
      switch (estado) {
        case E_DATO: // siempre es direcion
             adatonro((int)indice[numero].codigo,4);
             break;
        case E_PROG:
             if (aux==0) {
               if (indice[numero].tipo=='#') aprog(ADR); else aprog(CALL);
             } else aprog(LIT);// apila direccion
             aprogaddr(numero);
             break;
        };
    } else if (espalabraex(palabra)==1) {
	  switch (estado) {
        case E_DATO: // siempre es direcion
             adatonro((int)indiceex[numero].codigo,4);
             break;
        case E_PROG:
             if (aux==0) {
               if (indiceex[numero].tipo=='#') aprog(ADR); else aprog(CALL);
             } else aprog(LIT);// apila direccion
             aprogaddrex(numero);
             break;
		};
	} else { sprintf(error,"no existe %s",palabra);goto error;} }    
  ahora++; goto otrapalabra;
otralinea:
  nrolinea++; }
if (prog[cntprog-1]!=FIN) aprog(FIN);
if (fclose(stream)) return CLOSEERROR;
return COMPILAOK;

error:
  sprintf(lineat,"%s|%d|%d|%s",name,nrolinea,ahora-lineat,error);
  strcpy(error,lineat);
return CODIGOERROR;
}

void grabalinea(void)
{
FILE *stream;
if((stream=fopen("debug.err","w+"))==NULL) return;
fputs(error,stream); 
if(fclose(stream)) return; 
}

//----------------- PRINCIPAL

 #ifdef WIN32
LONG WINAPI MyUnhandledExceptionFilter(LPEXCEPTION_POINTERS e) 
{
int i,j;     

FILE *stream;
stream=fopen("runtime.err","w+");
fprintf(stream,"%s\r",linea);

fprintf(stream,"IP: %d %d\r",(int)e->ContextRecord->Ebx-(int)prog-1,(int)e->ContextRecord->Edx);// ebx=IP
fprintf(stream,"D: ");
i=(int)PSP;
j=(int)e->ContextRecord->Esi;
if ((j-i)>32) 
   {
   i=j-32;
   }
for (;i<j;i+=4)
    fprintf(stream,"%d ",*(int*)i);
fprintf(stream,"%d )\r",e->ContextRecord->Edi);    // edi=TOS    
fprintf(stream,"R: ");
i=(int)RSP;
j=*(int*)(e->ContextRecord->Ebp-16); // es variable local 
if ((j-i)>32) 
   {
   i=j-32;
   }
for (;i<=j;i+=4)
    fprintf(stream,"%d ",*(int*)i);
fprintf(stream,")\r");

fprintf(stream,"code:%d cnt:%d\r",&prog,cntprog);
fprintf(stream,"data:%d cnt:%d\r",&data,cntdato);
/*
fprintf(stream,"Esi:%d\r",(int)e->ContextRecord->Esi);
fprintf(stream,"Edi:%d\r",(int)e->ContextRecord->Edi);
fprintf(stream,"Eax:%d\r",(int)e->ContextRecord->Eax);
fprintf(stream,"Ebx:%d\r",(int)e->ContextRecord->Ebx);
fprintf(stream,"Ecx:%d\r",(int)e->ContextRecord->Ecx);
fprintf(stream,"Edx:%d\r",(int)e->ContextRecord->Edx);
fprintf(stream,"local:%d\r",*(int*)(e->ContextRecord->Ebp-16));
fprintf(stream,"PSP:%d\r",(int)PSP);
fprintf(stream,"RSP:%d\r",(int)RSP);
*/
fclose(stream);
return SHUTDOWN_NORETRY; //return EXCEPTION_CONTINUE_SEARCH;
}
#endif

static void print_usage(void) {
  printf(":R4 console\n"
  "  c<CODIGO> compile\n"
  "  i<IMAGEN> build\n"
  "  x<IMAGEN> exec\n"
  "  w<SCRW>\n"
  "  h<SCRH>\n"
  "  f fullscreen \n"
  "  s without screen\n"
  "  ? help\n" , "r4");
}

//char *NDEBUG="debug.txt";
char *DEBUGR4X="debug.r4x";

///////////////////////////////////////////////////////////////////////
//...............................................................................
LRESULT CALLBACK WndProc(HWND hWnd,UINT message,WPARAM wParam,LPARAM lParam)
{
switch (message) {     // handle message
    case WM_TIMER:
        SYSEVENT=SYSirqtime;
        break;
    case WM_MOUSEMOVE:
         if (SYSXYM==lParam) break;
         SYSXYM=lParam;
         SYSEVENT=SYSirqmouse;//         SYSEVENT=SYSMM;
         break;
    case WM_LBUTTONUP: case WM_MBUTTONUP: case WM_RBUTTONUP:
    case WM_LBUTTONDOWN: case WM_MBUTTONDOWN: case WM_RBUTTONDOWN:         
         SYSBM=wParam;//&3;
         SYSEVENT=SYSirqmouse;
         break;
    case WM_MOUSEWHEEL:         
         SYSBM=((short)HIWORD(wParam)<0)?4:5;
         SYSEVENT=SYSirqmouse;
         break;
    case WM_KEYUP:        // (lparam>>24)     ==1 keypad
//         SYSKEYX=lParam;
//         SYSKEY=((lParam&0x1000000)?0x10:0)+((lParam>>16)&0x7f)|0x80;
         lParam>>=16;
         SYSKEY=(((lParam&0x100)>>4)+(lParam&0x7f))|0x80;
         SYSEVENT=SYSirqteclado;
         break;
    case WM_KEYDOWN:
//         SYSKEYX=lParam;
//         SYSKEY=((lParam&0x1000000)?0x10:0)+(lParam>>16)&0x7f;
         lParam>>=16;
         SYSKEY=(((lParam&0x100)>>4)+(lParam&0x7f));
         SYSEVENT=SYSirqteclado;
         break;
//---------Winsock related message...
    case WM_WSAASYNC:
        switch(WSAGETSELECTEVENT(lParam)) {
        case FD_CLOSE: //Lost connection
            closesocket(soc);
            break;
        case FD_READ: //Incoming data to receive
            buffersize=recv(soc,buffernet,1024, 0);
            buffernet[buffersize]=0;
            SYSEVENT=SYSirqred;
            break;
//        case FD_CONNECT:

        case FD_ACCEPT: //Connection request
            soc=accept(wParam,0,0);
            break;
        }
        break;
//---------System
    case WM_ACTIVATEAPP:
         active=wParam&0xff;
         if (active==WA_INACTIVE)
            {
            ChangeDisplaySettings(NULL,0);
//            ShowWindow(hWnd,SW_MINIMIZE);
         } else {
            ShowWindow(hWnd,SW_NORMAL);//SW_RESTORE);
            UpdateWindow(hWnd);
            }
         break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
  default:
       return DefWindowProc(hWnd,message,wParam,lParam);
  }
return 0;
	// salvapantallas
//	if( uMsg==WM_SYSCOMMAND && (wParam==SC_SCREENSAVE || wParam==SC_MONITORPOWER) )	return( 0 );
}

void updevt(void)
{
while (PeekMessage(&msg,0,0,0,PM_REMOVE)) {   // TraslateMessage...
     DispatchMessage(&msg);
     while (active==WA_INACTIVE) {
         Sleep(10);
         PeekMessage(&msg,hWnd,0,0,PM_REMOVE);
         TranslateMessage(&msg);DispatchMessage(&msg);
         }
     }
}

void waitclick(void)
{
while(SYSBM!=0) { updevt(); }
while(SYSBM==0) { updevt(); }
}

void mimemset(char *p,char v,int c)
{
for (;c>0;c--,p++) *p=v;
}

///////////////////////////////////////////////////////////////////////////////////////////

//----------------- PRINCIPAL
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
SetUnhandledExceptionFilter(&MyUnhandledExceptionFilter);

int w=640,h=480,fullscreen=0,silent=0;
int i=0;
char *aa=(char*)lpCmdLine;
while (*aa!=0) {
      if ('i'==*aa) { compilastr=aa+1; }
      if ('c'==*aa) { bootstr=aa+1;exestr=""; }
      if ('x'==*aa) { exestr=aa+1; }
      if ('w'==*aa) { esnumero(aa+1);w=numero; }
      if ('h'==*aa) { esnumero(aa+1);h=numero; }
      if ('f'==*aa) { fullscreen=1; }      
      if ('s'==*aa) { silent=1; }
      if ('?'==*aa) { print_usage();return 0; }
      while (*aa!=32) aa++;
      if (32==*aa) *aa=0;
      aa++; }
    
mimemset((char*)&wc,0,sizeof(WNDCLASSA));
wc.style         = 0; //CS_OWNDC;
wc.lpfnWndProc   = WndProc;
wc.hInstance     = GetModuleHandle(0);
wc.lpszClassName = wndclass;
if(!RegisterClass((WNDCLASSA*)&wc)) return -1;

if(fullscreen==1)    {
    mimemset((char*)&screenSettings,0,sizeof(screenSettings));
#if _MSC_VER < 1400
    screenSettings.dmSize=148;
#else
    screenSettings.dmSize=156;
#endif
    screenSettings.dmFields=0x1c0000;
    screenSettings.dmBitsPerPel=32;screenSettings.dmPelsWidth=w;screenSettings.dmPelsHeight=h; 
    if(ChangeDisplaySettings(&screenSettings,CDS_FULLSCREEN)!=DISP_CHANGE_SUCCESSFUL) return -4;
    dwExStyle = WS_EX_APPWINDOW;
    dwStyle   = WS_VISIBLE | WS_POPUP | WS_CLIPSIBLINGS | WS_CLIPCHILDREN;
} else {
    dwExStyle = WS_EX_APPWINDOW;// | WS_EX_WINDOWEDGE;
    dwStyle   = WS_VISIBLE | WS_CAPTION | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | WS_SYSMENU;
    }
ShowCursor(0);
rec.left=rec.top=0;rec.right=w;rec.bottom=h;
AdjustWindowRect(&rec,dwStyle,0);
hWnd=CreateWindowEx( dwExStyle,wc.lpszClassName, wc.lpszClassName,dwStyle,
     (GetSystemMetrics(SM_CXSCREEN)-rec.right+rec.left)>>1,(GetSystemMetrics(SM_CYSCREEN)-rec.bottom+rec.top)>>1,
     rec.right-rec.left, rec.bottom-rec.top,0,0,wc.hInstance,0);
if(!hWnd) return -2;
if(!(hDC=GetDC(hWnd)))  return -3;

if (gr_init(w,h)<0) return -1;

InitJoystick(hWnd);
#ifdef FMOD
    if (!FSOUND_Init(44100, 32, 0)) return -4;
#else
    if (sound_open(hWnd)!=0) return -4;
#endif
strcpy(pathdata,".//");  // SEBAS win-linux
loaddir();
//--------------------------------------------------------------------------
WSAStartup(2, &wsaData);

//--------------------------------------------------------------------------
recompila:

bootaddr=0;
if (exestr[0]!=0) {
   #ifdef LOGMEM		
   ldebug("LOAD IMA:");ldebug(exestr);
   #endif
   loadimagen(exestr);
   } 
if (bootaddr==0 && bootstr[0]!=0){
   #ifdef LOGMEM
   ldebug("BOOTSTR:");ldebug(bootstr);
   #endif
   strcpy(linea,bootstr);
   cntindiceex=cntnombreex=cntincludes=0;// espacio de nombres reset
   cntdato=cntprog=0;cntindice=cntnombre=0;
   if (compilafile(linea)!=COMPILAOK) { 
      grabalinea();
//    return 1;
      if (exestr==DEBUGR4X) return 1;
      exestr=DEBUGR4X;goto recompila;
      }
   if (compilastr[0]!=0) {
      #ifdef LOGMEM		                                
      ldebug("SAVE IMA:");ldebug(compilastr);
      #endif
      saveimagen(compilastr);
      }
   }       
if (bootaddr==0) {
   sprintf(error,"%s|0|0|NO BOOT",linea);                    
   grabalinea();
//    return 1;
    if (exestr==DEBUGR4X) return 1;
   exestr=DEBUGR4X;goto recompila;//   strcpy(linea,NDEBUG);
   }
#ifdef LOGMEM		
dumpex();dumplocal("BOOT");
#endif
memlibre=data+cntdato; // comienzo memoria libre
if (silent!=1 && interprete(bootaddr)==1) goto recompila;
//--------------------------------------------------------------------------
#ifdef FMOD
   FSOUND_Close();
#else
   sound_close();
#endif
ReleaseJoystick();
closesocket(soc); //Shut down socket
WSACleanup(); //Clean up Winsock
gr_fin();
ReleaseDC(hWnd,hDC);
DestroyWindow(hWnd);
ExitProcess(0);
return 0;
}
