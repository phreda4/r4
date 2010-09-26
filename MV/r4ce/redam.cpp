#include "stdafx.h"// evc
#include "redalib.h"
#include "graf.h"

//---------------------------------------------------------------
//---- el ultimo recurso
void ldebug(char *n)
{
FILE *stream;
if((stream=fopen("log.txt","a"))==NULL) return;
fputs(n,stream);
if(fclose(stream)) return;
}

#define FMOD
#define PRINTER
#define NET


//char *macrose[]={ ";","LIT","ADR","CALL","JMP","JMPR" };
char *macros[]={// directivas del compilador
";","(",")",")(","[","]","EXEC",
"0?","+?","-?","1?","=?","<?",">?","<=?",">=?","<>?","AND?","NAND?",

"DUP","DROP","OVER","PICK2","PICK3","PICK4","SWAP","NIP","ROT", //--- pila
"2DUP","2DROP","3DROP","4DROP","2OVER","2SWAP",
//--- pila direcciones
">R","R>","R","R+","R@+","R!+","RDROP",
"AND","OR","XOR","NOT", //--- logicas
"+","-","*","/","*/","*>>","/MOD","MOD","ABS", //--- aritmeticas
"NEG","1+","4+","1-","2/","2*","<<",">>",
"@","C@","W@","!","C!","W!","+!","C+!","W+!", //--- memoria
"@+","!+","C@+","C!+","W@+","W!+",


"MOVE","MOVE>","CMOVE","CMOVE>",//-- movimiento de memoria
"MEM","DIR","FILE","FSIZE","VOL","LOAD","SAVE",//--- memoria,bloques
"UPDATE",
"TPEN",
"XYMOUSE","BMOUSE",     //-------- mouse
"IKEY!","KEY",          //-------- teclado
"CNTJOY","GETJOY",     //-------- joystick

"MSEC","TIME","DATE","END","RUN",//--- sistema
"SW","SH","CLS","REDRAW","FRAMEV",//--- pantalla
"SETXY","PX+!","PX!+","PX@",
"XFB",">XFB","XFB>",
"PAPER","INK","INK@","ALPHA", //--- color
"OP","CP","LINE","CURVE","PLINE","PCURVE","POLI",//--- dibujo
"FCOL","FCEN","FMAT","SFILL","LFILL","RFILL","TFILL",
//---------------------
#ifdef FMOD
"SLOAD","SPLAY","MLOAD","MPLAY",    //-------- sonido
#else
"ISON!","SBO","SBI",    // Sound Buffer Ouput/input
#endif
//--------------------- red
#ifdef NET
"OPENURL",
#endif
//"TIMER",            //------- timer
//---------------------
#ifdef PRINTER
"DOCINI","DOCEND","DOCAT","DOCLINE","DOCTEXT","DOCFONT","DOCBIT","DOCRES","DOCSIZE", //-- impresora
#endif
"SYSTEM",
""};

FIN,LIT,ADR,CALL,JMP,JMPR, EXEC,//hasta JMPR no es visible
IF,PIF,NIF,UIF,IFN,IFL,IFG,IFLE,IFGE,IFNO,IFAND,IFNAND,// condicionales 0 - y +  y no 0
DUP,DROP,OVER,PICK2,PICK3,PICK4,SWAP,NIP,ROT,
DUP2,DROP2,DROP3,DROP4,OVER2,SWAP2,//--- pila
TOR,RFROM,ERRE,ERREM,ERRFM,ERRSM,ERRDR,//--- pila direcciones
AND,OR,XOR,NOT,//--- logica
SUMA,RESTA,MUL,DIV,MULDIV,MULSHR,DIVMOD,MOD,ABS,
CSQRT,CLZ,CDIVSH,
NEG,INC,INC4,DEC,DIV2,MUL2,SHL,SHR,//--- aritmetica
FECH,CFECH,WFECH,STOR,CSTOR,WSTOR,INCSTOR,CINCSTOR,WINCSTOR,//--- memoria
FECHPLUS,STOREPLUS,CFECHPLUS,CSTOREPLUS,WFECHPLUS,WSTOREPLUS,
MOVED,MOVEA,CMOVED,CMOVEA,
MEM,PATH,BFILE,BFSIZE,VOL,LOAD,SAVE,//--- bloques de memoria, bloques
UPDATE,
TPEN,
XYMOUSE,BMOUSE,
IRKEY,KEY,
CNTJOY,GETJOY,
MSEC,TIME,IDATE,SISEND,SISRUN,//--- sistema
WIDTH,HEIGHT,CLS,REDRAW,FRAMEV,//--- pantalla
SETXY,MPX,SPX,GPX,
VXFB,TOXFB,XFBTO,
COLORF,COLOR,COLORA,ALPHA,//--- color
OP,CP,LINE,CURVE,PLINE,PCURVE,POLI,//--- dibujo
FCOL,FCEN,FMAT,SFILL,LFILL,RFILL,TFILL, //--- pintado
#ifdef FMOD
SLOAD,SPLAY,MLOAD,MPLAY,
#else
IRSON,SBO,SBI,
#endif
#ifdef NET
OPENURL,
#endif
#ifdef PRINTER  //-- impresora
DOCINI,DOCEND,DOCMOVE,DOCLINE,DOCTEXT,DOCFONT,DOCBIT,DOCRES,DOCSIZE,
#endif
SYSTEM,
ULTIMAPRIMITIVA// de aqui en mas.. apila los numeros 0..255-ULTIMAPRIMITIVA
};

// instrucciones de maquina (son compilables a assembler)

//----- PILAS
int PSP[2048];// 2k pila de datos
BYTE *RSP[2048];// 2k pila de direcciones
int gx1=0,gy1=0,gx2=0,gy2=0,gxc=0,gyc=0;// coordenadas de linea
BYTE *bootaddr;
FILE *file;
char pathprg[128],pathdata[128];
char linea[1024];// 1k linea
char error[1024];
//----- Directorios
char mindice[8192];// 8k de index 1024 archivos con nombres de 8 caracteres
char *indexdir[512];
int sizedir[512];
int cntindex;
char *subdirs[256];
int cntsubdirs;
//---- eventos teclado y raton
MSG msg;
SYSTEMTIME sitime;
WIN32_FIND_DATA FileData;   // Data structure describes the file found
HANDLE hSearch;             // Search handle returned by FindFirstFile
TCHAR szPath[255];
//---- dato y programa
BYTE ultimapalabra[]={ SISEND };
int cntdato;
int cntprog;
BYTE *memlibre;
BYTE prog[1024*256];
BYTE data[1024*1024*8];

void loaddir()
{
BOOL bFinished = FALSE;
wsprintf(szPath,_T("%hs*.*"),pathdata);// de char a charw
hSearch=FindFirstFile(szPath,&FileData);
char *act=mindice;cntindex=cntsubdirs=0;
if (hSearch!=INVALID_HANDLE_VALUE) { 
  while (!bFinished) {
	sprintf(act,"%lS",FileData.cFileName);//,FileData.dwFileAttributes
	if (FileData.dwFileAttributes==FILE_ATTRIBUTE_DIRECTORY)
		{
		subdirs[cntsubdirs]=act;
    	cntsubdirs++;
		}
	else
		{
		indexdir[cntindex]=act;
		sizedir[cntindex] = (FileData.nFileSizeHigh * MAXDWORD) + FileData.nFileSizeLow;
		cntindex++;
		}
    while (*act!=0) act++;act++;
	if (!FindNextFile(hSearch,&FileData)) bFinished = TRUE;
	} 
 FindClose(hSearch); 
 }
}
#ifdef __GNUC__
#define iclz32(x) __builtin_clz(x)
#else
static inline int popcnt(int x)
{
    x -= ((x >> 1) & 0x55555555);
    x = (((x >> 2) & 0x33333333) + (x & 0x33333333));
    x = (((x >> 4) + x) & 0x0f0f0f0f);
    x += (x >> 8);
    x += (x >> 16);
    return x & 0x0000003f;
}
static inline int iclz32(int x)
{
    x |= (x >> 1);
    x |= (x >> 2);
    x |= (x >> 4);
    x |= (x >> 8);
    x |= (x >> 16);
    return 32 - popcnt(x);
}
#endif

// http://www.devmaster.net/articles/fixed-point-optimizations/
static inline int isqrt32(int value) 
{
if (value==0) return 0;
int g = 0;
int bshft = (31-iclz32(value))>>1;  // spot the difference!
int b = 1<<bshft;
do {
	int temp = (g+g+b)<<bshft;
	if (value >= temp) { g += b;value -= temp;	}
	b>>=1;
} while (bshft--);
return g;
}


//---------------------------------------------------------------
int interprete(BYTE *codigo)// 1=recompilar con nombre en linea
{      
if (codigo==NULL) return -1;
register BYTE *IP=codigo;	// lugar del programa
register int TOS;			// Tope de la pila PSP
register int *NOS;			// Next of stack
register BYTE **R;			// return stack
register int W,W1;			// palabra actual y auxiliar
register WORD *vcursor;
R=RSP;*R=(BYTE*)&ultimapalabra;
NOS=PSP;*NOS=TOS=0;
while (true)  { 
    W=(BYTE)*IP++;
	switch (W) {// obtener codigo de ejecucion
	case FIN: IP=*R;R--;continue;
    case LIT: NOS++;*NOS=TOS;TOS=*(UNALIGNED DWORD*)IP;IP+=sizeof(int);continue;
    case ADR: NOS++;*NOS=TOS;W=*(UNALIGNED DWORD*)IP;IP+=sizeof(int);TOS=*(DWORD UNALIGNED *)W;continue;
    case CALL: W=*(UNALIGNED DWORD*)IP;IP+=sizeof(int);R++;*R=IP;IP=(BYTE*)W;continue;
	case JMP: W=*(int UNALIGNED *)IP;IP=(BYTE*)W;continue;
    case JMPR: W=*(char*)IP;W++;IP+=W;continue;
//-hasta aca solo lo escribe el compilador
//--- condicionales
	case IF: W=*(char*)IP;IP++;if (TOS!=0) IP+=W; continue;
    case PIF: W=*(char*)IP;IP++;if (TOS<=0) IP+=W; continue;
	case NIF: W=*(char*)IP;IP++;if (TOS>=0) IP+=W; continue;
    case UIF: W=*(char*)IP;IP++;if (TOS==0) IP+=W; continue;
    case IFN: W=*(char*)IP;IP++;if (TOS!=*NOS) IP+=W; TOS=*NOS;NOS--;continue;
    case IFNO: W=*(char*)IP;IP++;if (TOS==*NOS) IP+=W; TOS=*NOS;NOS--;continue;
    case IFL: W=*(char*)IP;IP++;if (TOS<=*NOS) IP+=W; TOS=*NOS;NOS--;continue;
    case IFG: W=*(char*)IP;IP++;if (TOS>=*NOS) IP+=W; TOS=*NOS;NOS--;continue;
    case IFLE: W=*(char*)IP;IP++;if (TOS<*NOS) IP+=W; TOS=*NOS;NOS--;continue;
    case IFGE: W=*(char*)IP;IP++;if (TOS>*NOS) IP+=W; TOS=*NOS;NOS--;continue;
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
	case ERREM: (*(int UNALIGNED *)R)+=TOS;TOS=*NOS;NOS--;continue;
    case ERRFM: NOS++;*NOS=TOS;TOS=**(int UNALIGNED **)R;(*(int UNALIGNED *)R)+=4;continue;
    case ERRSM: **(int UNALIGNED **)R=TOS;TOS=*NOS;NOS--;(*(int UNALIGNED *)R)+=4;continue;
    case ERRDR: R--;continue;
	case AND: TOS&=*NOS;NOS--;continue;
    case OR: TOS|=*NOS;NOS--;continue;
	case XOR: TOS^=*NOS;NOS--;continue;
    case NOT: TOS=~TOS;continue;
//--- aritmeticas
	case SUMA: TOS=(*NOS)+TOS;NOS--;continue;
    case RESTA: TOS=(*NOS)-TOS;NOS--;continue;
	case MUL: TOS=(*NOS)*TOS;NOS--;continue;
    case DIV: if (TOS==0) { TOS=*NOS;NOS--;continue; }
	     TOS=*NOS/TOS;NOS--;continue;
	case MULDIV: //if (TOS==0) { NOS--;TOS=*NOS;NOS--;continue; }
	     TOS=(*(NOS-1))*(*NOS)/TOS;NOS-=2;continue;
	case MULSHR: TOS=((__int64)(*(NOS-1))*(*NOS))>>TOS;NOS-=2;continue;
    case CDIVSH: TOS=((__int64)(*(NOS-1)<<TOS)/(*NOS));NOS-=2;continue;

    case DIVMOD: //if (TOS==0) { NOS--;TOS=*NOS;NOS--;continue; }
	     W=*NOS%TOS;*NOS=*NOS/TOS;TOS=W;continue;
	case MOD: TOS=*NOS%TOS;NOS--;continue;
    case ABS: W=(TOS>>31);TOS=(TOS+W)^W;continue;
    case CSQRT: TOS=isqrt32(TOS);continue;
    case CLZ: TOS=iclz32(TOS);continue;

    case NEG: TOS=-TOS;continue;
    case INC: TOS++;continue;	case INC4: TOS+=4;continue; case DEC: TOS--;continue;
    case DIV2: TOS>>=1;continue;	case MUL2: TOS<<=1;continue;
	case SHL: TOS=(*NOS)<<TOS;NOS--;continue;
    case SHR: TOS=(*NOS)>>TOS;NOS--;continue;
//--- memoria
	case FECH: TOS=*(int UNALIGNED *)TOS;continue;
    case CFECH: TOS=*(char*)TOS;continue;
    case WFECH: TOS=*(short UNALIGNED *)TOS;continue;
	case STOR: *(int UNALIGNED *)TOS=(int)*NOS;NOS--;TOS=*NOS;NOS--;continue;
    case CSTOR: *(char*)TOS=(char)*NOS;NOS--;TOS=*NOS;NOS--;continue;
    case WSTOR: *(short UNALIGNED *)TOS=(short)*NOS;NOS--;TOS=*NOS;NOS--;continue;
	case INCSTOR: *((int  UNALIGNED *)TOS)+=(int)*NOS;NOS--;TOS=*NOS;NOS--;continue;
    case CINCSTOR: *((char*)TOS)+=(char)*NOS;NOS--;TOS=*NOS;NOS--;continue;
    case WINCSTOR: *((short  UNALIGNED *)TOS)+=(short)*NOS;NOS--;TOS=*NOS;NOS--;continue;
    case FECHPLUS: NOS++;*NOS=TOS+4;TOS=*(int UNALIGNED *)TOS;continue; //@+ | adr -- adr' v
    case STOREPLUS: *(int UNALIGNED *)TOS=(int)*NOS;TOS+=4;NOS--;continue;//!+ | v adr -- adr'
    case CFECHPLUS: NOS++;*NOS=TOS+1;TOS=*(char *)TOS;continue;
    case CSTOREPLUS: *(char *)TOS=(char)*NOS;TOS++;NOS--;continue;
    case WFECHPLUS: NOS++;*NOS=TOS+2;TOS=*(short UNALIGNED *)TOS;continue;
    case WSTOREPLUS: *(short UNALIGNED *)TOS=(short)*NOS;TOS+=2;NOS--;continue;
//--- sistema
	case MSEC: NOS++;*NOS=TOS;TOS=GetTickCount();continue;
    case EDATE: GetLocalTime(&sitime);NOS++;*NOS=TOS;TOS=sitime.wYear;
		NOS++;*NOS=TOS;TOS=sitime.wMonth;NOS++;*NOS=TOS;TOS=sitime.wDay;continue;
    case TIME: GetLocalTime(&sitime);NOS++;*NOS=TOS;TOS=sitime.wHour;
		NOS++;*NOS=TOS;TOS=sitime.wMinute;NOS++;*NOS=TOS;TOS=sitime.wSecond;continue;
    case SISEND: return 0;
    case SISRUN: if (TOS!=0) strcpy(linea,(char*)TOS); return 1;

    case WIDTH: NOS++;*NOS=TOS;TOS=gr_ancho;continue;	// invirte xy
    case HEIGHT: NOS++;*NOS=TOS;TOS=gr_alto;continue;	//
	case CLS: gr_clrscr();continue;
    case REDRAW: gr_redraw();continue;
    case FRAMEV: NOS++;*NOS=TOS;TOS=(int)gr_buffer;continue;

	case UPDATE:
	  if (evento!=0) { R++;*(int*)R=(int)IP;IP=(BYTE*)evento;evento=0; }
	  if (PeekMessage(&msg,0,0,0,PM_NOREMOVE)==TRUE) {
		GetMessage(&msg,0,0,0);//TranslateMessage(&msg);
		DispatchMessage(&msg);
		if (evento!=0) { R++;*(int*)R=(int)IP;IP=(BYTE*)evento;evento=0; }	}
		continue;
    case XYMOUSE: NOS++;*NOS=TOS;NOS++;*NOS=mxpos;TOS=mypos;continue;// invierto
    case BMOUSE: NOS++;*NOS=TOS;TOS=pendown();continue;
	case KEY: NOS++;*NOS=TOS;TOS=tecla;continue;

	case SETXY:vcursor=(WORD*)gr_buffer+TOS*gr_ancho+(*NOS);
        NOS--;TOS=*NOS;NOS--;continue;
	case MPX:vcursor+=TOS;TOS=*NOS;NOS--;continue;
	case SPX:*(WORD*)(vcursor++)=gr_RGB(TOS);TOS=*NOS;NOS--;continue;
	case GPX:NOS++;*NOS=TOS;TOS=*(WORD*)(vcursor);continue;
//---- nuevas interrups
    case IRMOU: SYSirqlapiz=TOS;TOS=*NOS;NOS--;continue;
    case IRKEY: SYSirqteclado=TOS;TOS=*NOS;NOS--;continue;
    case IRJOY: SYSirqjoystick=TOS;TOS=*NOS;NOS--;continue;
    case IRSON: SYSirqsonido=TOS;TOS=*NOS;NOS--;continue;
    case IRNET: SYSirqred=TOS;TOS=*NOS;NOS--;continue;
//--- color
	case COLORF: gr_color2=gr_RGB(TOS);TOS=*NOS;NOS--;continue;
    case COLOR: gr_color1=gr_RGB(TOS);TOS=*NOS;NOS--;continue;
    case COLORA: NOS++;*NOS=TOS;TOS=RGB_gr(gr_color1);continue;// =>RGB
	case ALPHA: if (TOS>254) gr_solid(); else { gr_alphav=(BYTE)(TOS);gr_alpha(); }
		TOS=*NOS;NOS--;continue;
//--- dibujo
    case OP: gx1=*NOS;gy1=TOS;NOS--;TOS=*NOS;NOS--;continue;
    case CP: gxc=*NOS;gyc=TOS;NOS--;TOS=*NOS;NOS--;continue;
	case LINE: gx2=*NOS;gy2=TOS;NOS--;TOS=*NOS;NOS--;
		gr_line(gx1,gy1,gx2,gy2);gx1=gx2;gy1=gy2;continue;
    case CURVE: gx2=*NOS;gy2=TOS;NOS--;TOS=*NOS;NOS--;
		gr_spline(gx1,gy1,gxc,gyc,gx2,gy2);gx1=gx2;gy1=gy2;continue;
	case PLINE: gx2=*NOS;gy2=TOS;NOS--;TOS=*NOS;NOS--;
		gr_psegmento(gx1,gy1,gx2,gy2);gx1=gx2;gy1=gy2;continue;
    case PCURVE: gx2=*NOS;gy2=TOS;NOS--;TOS=*NOS;NOS--;
		gr_pspline(gx1,gy1,gxc,gyc,gx2,gy2);gx1=gx2;gy1=gy2;continue;
	case POLI: gr_drawPoli();continue;

	case FCOL: fillcol(*NOS,TOS);NOS--;TOS=*NOS;NOS--;continue;
    case FCEN: fillcent(*NOS,TOS);NOS--;TOS=*NOS;NOS--;continue;
    case FMAT: fillmat(*NOS,TOS);NOS--;TOS=*NOS;NOS--;continue;
    case SFILL: fillSol();continue;
    case LFILL: fillLin();continue;
    case RFILL: fillRad();continue;
    case TFILL: mTex=(int*)TOS;fillTex();TOS=*NOS;NOS--;continue;
//--- bloque de memoria
    case MEM: NOS++;*NOS=TOS;TOS=(int)memlibre;continue; // inicio memoria libre
//--- bloques
	case PATH: if (TOS==0) continue;
         strcpy(pathdata,(char*)TOS);TOS=*NOS;NOS--;loaddir();continue;
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
         if (TOS==0||*NOS==0) continue;
         sprintf(error,"%s%s",pathdata,(char*)TOS);
         TOS=*NOS;NOS--;
         file=fopen(error,"rb");if (file==NULL) continue;
         do { W=fread((void*)TOS,sizeof(char),1024,file); TOS+=W; } while (W==1024);
         fclose(file);continue;
    case SAVE: // 'from cnt "filename" --
         if (TOS==0||*NOS==0) continue;
         sprintf(error,"%s%s",pathdata,(char*)TOS);
         TOS=*NOS;NOS--;
         file=fopen(error,"wb");if (file==NULL) continue;
         fwrite((void*)*NOS,sizeof(char),TOS,file);
         fclose(file);loaddir();
         NOS--;TOS=*NOS;NOS--;continue;
// por velocidad         
    case MOVED: // | de sr cnt --
		 TOS=TOS<<2;
    case CMOVED: // | de sr cnt --
         W=*(NOS-1);W1=*NOS;    
         while (TOS--) { *(char*)W++=*(char*)W1++; }
         NOS-=2;TOS=*NOS;NOS--;
         continue;
	case MOVEA: // | de sr cnt --
		 TOS=TOS<<2;
    case CMOVEA: // | de sr cnt --
         W=(*(NOS-1))+TOS;W1=(*NOS)+TOS;
         while (TOS--) { *(char*)--W=*(char*)--W1; }         
         NOS-=2;TOS=*NOS;NOS--;
         continue;

#ifdef FMOD
case SLOAD: continue;
case SPLAY: continue;
case MLOAD: continue;
case MPLAY: continue;

#else
case IRSON: continue;
case SBO: continue;
case SBI: continue;
case
#endif
#ifdef NET
OPENURL: continue;
case
#endif
#ifdef PRINTER  //-- impresora
DOCINI: continue;
case DOCEND: continue;
case DOCMOVE: continue;
case DOCLINE: continue;
case DOCTEXT: continue;
case DOCFONT: continue;
case DOCBIT: continue;
case DOCRES: continue;
case DOCSIZE: continue;
case
#endif
SYSTEM,

	default: // completa los 8 bits con apila numeros 0...
        NOS++;*NOS=TOS;TOS=W-ULTIMAPRIMITIVA;continue;
	} }
};


//----------------------
struct Indice { char *nombre;BYTE *codigo;int tipo; };
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

//---- pila de compilador** reemplazar por pila de datos
int cntpila;
int pila[256];

void apila(int n) { 
//if (cntpila>255) { sprintf(error,"apila error");ldebug(error);return; }
pila[cntpila++]=n; }

int desapila(void) { 
//if (cntpila==0) { sprintf(error,"desapila error");ldebug(error);return 0; }
return pila[--cntpila]; }

//---- espacio de dato
void adato(const char *p) 
{ strcpy((char*)&data[cntdato],p);cntdato+=strlen(p)+1; } 

void adatonro(int n,int u)
{ BYTE *p=&data[cntdato];     
switch(u) {
  case 1:*(char*)p=(char)n;break;// char
  case 2:*(short UNALIGNED *)p=(short)n;break;// short
  case 4:*(int UNALIGNED *)p=(int)n;break;// int
  };
cntdato+=u; }

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
  *p=LIT;p++;*(int UNALIGNED *)p=(int)n;
  cntprog+=5; } }

void aprog(int n) // grabo primitiva
{ BYTE *p=&prog[cntprog];*p=(BYTE)n;
if (n==CALL) lastcall=p; else lastcall=NULL;
cntprog++; }

void aprogint(int n)
{ BYTE *p=&prog[cntprog]; *(DWORD UNALIGNED *)p=(DWORD)&prog[n]; cntprog+=4; }

void aprogaddr(int n) // grabo direccion
{ BYTE *p=&prog[cntprog]; *(DWORD UNALIGNED *)p=(DWORD)indice[n].codigo;cntprog+=4; }

void aprogaddrex(int n) // grabo direccion exportada
{ BYTE *p=&prog[cntprog];*(DWORD UNALIGNED *)p=(DWORD)indiceex[n].codigo;cntprog+=4;}

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
actual->codigo=(actual->tipo==':')?&prog[cntprog]:&data[cntdato];
}

void compilofin(void)
{
if (lastcall!=NULL) { *lastcall=JMP;lastcall=NULL; }
    else aprog(FIN);
}

void endefine(void)
{
Indice *actual=&indice[cntindice-1];     
if (actual->tipo==':') { compilofin();
  //if (lastcall!=NULL) { *lastcall=JMP;lastcall=NULL; } else aprog(FIN);
  } else { if (&data[cntdato]==actual->codigo) adatonro(0,4); } }


void endefinesin(void)
{
Indice *actual=&indice[cntindice-1];     
if (actual->tipo!=':' && &data[cntdato]==actual->codigo) 
   adatonro(0,4); }


//---- parse de fuente
long numero;

int esnumero(char *p)
{//if (*p=='&') { p++;numero=*p;return 1;} // codigo ascii
int base,dig=0;    
int signo=0;
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
return 1;
};

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
//num=(0x10000*numero/decim);
numero=((0x10000*numero/decim)&0xffff)|(parte0<<16);
if (signo==1) numero=-numero;  
return 1; };

int esmacro(char *p)
{    
numero=0;
char **m=macros;
while (**m!=0) {
  if (!strcmp(*m,p)) return 1;
  *m++;numero++; }    
return 0; }

int espalabra(char *p)
{
numero=cntindice-1;
Indice *actual=&indice[numero];
while (actual>=indice) {
  if (!strcmp(actual->nombre,p)) return 1;
  actual--;numero--; }
return 0;  };

int espalabraex(char *p)
{
numero=cntindiceex-1;
Indice *actual=&indiceex[numero];
while (actual>=indiceex) {
  if (!strcmp(actual->nombre,p)) return 1;
  actual--;numero--; }
return 0;    
};
//----- Include
int estainclude(char *palabra)
{
if (cntincludes==0) return 0;
Indice *actual=&includes[cntincludes-1];
while (actual>=includes) {
	if (!strcmp(actual->nombre,palabra)) return 1;
	actual--;
	}
return 0;
}

void agregainclude(char *palabra)
{
Indice *act=&includes[cntincludes++];
char *n=&nombreex[cntnombreex];
strcpy(n,palabra);cntnombreex+=strlen(palabra)+1;
act->nombre=n;// solamente guardo nombre
}

//-------------------------------
#define E_DATO 1
#define E_PROG 2

#define COMPILAOK 0
#define OPENERROR 1
#define CLOSEERROR 2
#define CODIGOERROR 3

//---------------------------------------------------------------
// compila el archivo
int compilafile(char *name)
{
FILE *stream;
char *ahora,*palabra,*copia;
char lineat[512];
sprintf(lineat,"%s%s",pathprg,name);
if((stream=fopen(lineat,"rb"))==NULL) return OPENERROR;
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
      case E_DATO://aux=(int)&dato[cntdato];adato(palabra);adatonro(aux,4);
		adato(palabra);break;
      case E_PROG:// graba str y compila apila direccion
		aux=(int)&data[cntdato];adato(palabra);aprognro(aux);break; 
      };
    }
  else if (*palabra==':'||*palabra=='#')// define codigo y dato
    {
	if (cntpila>0) { sprintf(error,"bloque mal cerrado");goto error; }
	endefinesin();
	if (*(palabra+1)==0) { bootaddr=&prog[cntprog]; // : con espacio
    } else {
    	if (esnumero(palabra)==1) { sprintf(error,"nro invalido");goto error; }
	  // avisa palabra repetida
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
               if (indice[numero].tipo=='#') aprog(ADR);
               else aprog(CALL);
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
               if (indiceex[numero].tipo=='#') aprog(ADR);
               else aprog(CALL);
             } else aprog(LIT);// apila direccion
             aprogaddrex(numero);
             break;
		};
	} else { sprintf(error,"no existe %s",palabra);goto error;} }    
  ahora++; goto otrapalabra;
otralinea:
  nrolinea++; }
//if (prog[cntprog-1]!=FIN) aprog(FIN);
if (fclose(stream)) return CLOSEERROR;
cntindice=cntnombre=0;// espacio de nombres reset
return COMPILAOK;
error:
  sprintf(lineat,"(%s) %d : %s",name,nrolinea,error);
  strcpy(error,lineat);return CODIGOERROR;
}


//---------------------------------------------------------------
void waitaclick(void)
{
//gr_solid();
gr_color1=0x4F4;
gr_textc(gr_ancho>>1,10,"________________________________________");
gr_textc(gr_ancho>>1,26,":r4ce - pabloreda@gmail.com");
gr_color1=0xF44;gr_textc(gr_ancho>>1,42,linea);
gr_textc(gr_ancho>>1,58,error);
gr_color1=0x4F4;
gr_textc(gr_ancho>>1,64,"________________________________________");
gr_redraw();
while (!pendown()) update();
};

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
memlibre=&data[cntdato];
fclose(file);
}

//---------------------------------------------------------------
void main(void)
{
strcpy(pathprg,"\\r4\\");
strcpy(pathdata,pathprg);loaddir();
strcpy(linea,"main.txt");
recompila:
  cntindiceex=0;cntnombreex=0;cntincludes=0;
  cntdato=0;cntprog=0;
  cntindice=cntnombre=0;// espacio de nombres reset
  bootaddr=NULL;
  if (compilafile(linea)!=COMPILAOK) { waitaclick();return; }
  if (bootaddr==NULL) {
		strcpy(error,"NO HAY BOOT");
		waitaclick();
		return;
		}
  memlibre=&data[cntdato]; // comienzo memoria libre      
  saveimagen("\\mgps\\main.r4c");

if (interprete(bootaddr)==1) goto recompila;

}
