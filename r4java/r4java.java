/* * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * ---------------------------------------------------------------------------
 * Copyright (c) 2006, Pablo Hugo Reda <pabloreda@gmail.com>, Mar del Plata, Argentina
 * All rights reserved.
 */
//  Reda4 interprete y compilador  pabloreda@gmail.com

// Version Java Applet
// MC 27/3/2010: screen blitting tests, events in a simple applet.

import java.awt.event.*;
import java.util.Calendar;

public class r4java extends tinyptc implements KeyListener, MouseListener, MouseMotionListener {

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
SLOAD,SPLAY,MLOAD,MPLAY,
SERVER,CLIENT,NSEND,RECV,CLOSE, //---- red
DOCINI,DOCEND,DOCMOVE,DOCLINE,DOCTEXT,DOCFONT,DOCBIT,DOCRES,DOCSIZE,
SYSTEM,
ULTIMAPRIMITIVA// de aqui en mas.. apila los numeros 0..255-ULTIMAPRIMITIVA
};

	int ip;
	int [] dpila = new int[1024];
	int [] rpila = new int[1024];
	int sizefb = width * height;
	int FB[] = new int[sizefb];
	int XFB[] = new int[sizefb];

	char memcod[] = new char[256*1024];
	char memdat[] = new char[1024*1024];

	public void interprete()
	{
	int TOS,NOS,RTOS;
	char op;
	TOS=NOS=RTOS=0;
	while (true) {
		op=memcod[ip];
		ip=ip+1;
		switch(op) {
			case FIN: ip=rpila[RTOS];RTOS--;break
			case LIT: NOS++;dpila[NOS]=TOS;TOS=memcod[ip]|memcod[ip+1]<<8|memcod[ip+2]<<16|memcod[ip+3]<<24;ip=ip+4;break;
			case ADR: NOS++;dpila[NOS]=TOS;TOS=memcod[ip]|memcod[ip+1]<<8|memcod[ip+2]<<16|memcod[ip+3]<<24;ip=ip+4;TOS=... break;
			case CALL:
			case JMP:
			case JMPR:
			case EXEC://hasta JMPR no es visible
			case IF:	// condicionales 0 - y +  y no 0
			case PIF:
			case NIF:
			case UIF:
			case IFN:
			case IFL:
			case IFG:
			case IFLE:
			case IFGE:
			case IFNO:
			case IFAND:
			case IFNAND:
			case DUP: NOS++;dpila[NOS]=TOS;break;//--- pila
			case DROP:
			case OVER:
			case PICK2:
			case PICK3:
			case PICK4:
			case SWAP:
			case NIP:
			case ROT:
			case DUP2:
			case DROP2:
			case DROP3:
			case DROP4:
			case OVER2:
			case SWAP2:
			case TOR:	break;//--- pila direcciones
			case RFROM:
			case ERRE:
			case ERREM:
			case ERRFM:
			case ERRSM:
			case ERRDR:
			case AND:	TOS=dpila[NOS]&TOS;NOS--;break; //--- aritmetica
			case OR:	TOS=dpila[NOS]|TOS;NOS--;break;
			case XOR:	TOS=dpila[NOS]^TOS;NOS--;break;
			case NOT:	TOS=not TOS;break;
			case SUMA:	TOS=dpila[NOS]+TOS;NOS--;break;
			case RESTA:	TOS=dpila[NOS]-TOS;NOS--;break;
			case MUL:	TOS=dpila[NOS]*TOS;NOS--;break;
			case DIV:	TOS=dpila[NOS]/TOS;NOS--;break;
			case MULDIV:
			case MULSHR:
			case DIVMOD:
			case MOD:
			case ABS:
			case NEG:
			case INC:
			case INC4:
			case DEC:
			case DIV2:	TOS=TOS/2;break;
			case MUL2:	TOS=TOS*2;break;
			case SHL:
			case SHR:
			case FECH:break;//--- memoria
			case CFECH:
			case WFECH:
			case STOR:
			case CSTOR:
			case WSTOR:
			case INCSTOR:
			case CINCSTOR:
			case WINCSTOR:
			case FECHPLUS:
			case STOREPLUS:
			case CFECHPLUS:
			case CSTOREPLUS:
			case WFECHPLUS:
			case WSTOREPLUS:
			case MOVED://--- bloques de memoria: bloques
			case MOVEA:
			case CMOVED:
			case CMOVEA:
			case MEM:
			case PATH:
			case BFILE:
			case BFSIZE:
			case VOL:
			case LOAD:
			case SAVE:
			case UPDATE://--- sistema
			case TPEN:
			case XYMOUSE:
			case BMOUSE:
			case IRKEY:
			case KEY:
			case CNTJOY:
			case GETJOY:
			case MSEC:
			case TIME:
			case IDATE:
			case SISEND:
			case SISRUN:
			case WIDTH:
			case HEIGHT:
			case CLS:
			case REDRAW: update(FB);break;
			case FRAMEV://--- pantalla
			case SETXY:
			case MPX:
			case SPX:
			case GPX:
			case VXFB:
			case TOXFB:
			case XFBTO:
			case COLORF:
			case COLOR:
			case COLORA:
			case ALPHA://--- color
			case OP:
			case CP:
			case LINE:
			case CURVE:
			case PLINE:
			case PCURVE:
			case POLI://--- dibujo
			case FCOL:
			case FCEN:
			case FMAT:
			case SFILL:
			case LFILL:
			case RFILL:
			case TFILL: //--- pintado
			case SLOAD:
			case SPLAY:
			case MLOAD:
			case MPLAY:
			case SERVER:
			case CLIENT:
			case NSEND:
			case RECV:
			case CLOSE: //---- red
			case DOCINI:
			case DOCEND:
			case DOCMOVE:
			case DOCLINE:
			case DOCTEXT:
			case DOCFONT:
			case DOCBIT:
			case DOCRES:
			case DOCSIZE:
			case SYSTEM:

			  }
		}
	}

    public void main(int width,int height) {

        int size = width * height;
        int pixel[] = new int[size];
        int seed = 0x12345;

	int cnt = 0 ;

	long now = Calendar.getInstance().getTimeInMillis();

	addKeyListener( this ) ;
	addMouseListener( this ) ;
	addMouseMotionListener( this ) ;

        while (true) {

            for (int index=0; index<size; index++) {

                int noise = seed;
                noise >>= 3;
                noise ^= seed;
                int carry = noise & 1;
                noise >>= 1;
                seed >>= 1;
                seed |= (carry << 30);
                noise &= 0xFF;

                pixel[index] = (noise<<16) | (noise<<8) | noise;

            }
            update(pixel);
	    cnt++ ;

	    if ( cnt % 100 == 0 ) {
		long dur = Calendar.getInstance().getTimeInMillis() - now ;
		System.out.println ( "fps = " + 1000.0*(100.0/dur) ) ;
		now = Calendar.getInstance().getTimeInMillis() ;
	    }
	}
    }

    public void keyTyped(KeyEvent e) {
        displayInfo(e, "KEY TYPED: ");
    }
    
    public void keyPressed(KeyEvent e) {
        displayInfo(e, "KEY PRESSED: ");
    }

    public void keyReleased(KeyEvent e) {
        displayInfo(e, "KEY RELEASED: ");
    }

    public void mousePressed(MouseEvent e) {
       saySomething("Mouse pressed; # of clicks: " + e.getClickCount(), e);
    }

    public void mouseReleased(MouseEvent e) {
       saySomething("Mouse released; # of clicks: " + e.getClickCount(), e);
    }

    public void mouseEntered(MouseEvent e) {
       saySomething("Mouse entered", e);
    }

    public void mouseExited(MouseEvent e) {
       saySomething("Mouse exited", e);
    }

    public void mouseClicked(MouseEvent e) {
       saySomething("Mouse clicked (# of clicks: " + e.getClickCount() + ")", e);
    }

    public void mouseMoved(MouseEvent e) {
       saySomething_move("Mouse moved", e);
    }

    public void mouseDragged(MouseEvent e) {
       saySomething_move("Mouse dragged", e);
    }

    void saySomething(String eventDescription, MouseEvent e) {
        System.out.println(eventDescription + " detected on " + e.getComponent().getClass().getName() + ".\n");
    }

    void saySomething_move(String eventDescription, MouseEvent e) {
         System.out.println(eventDescription + " (" + e.getX() + "," + e.getY() + ")" + " detected on " + e.getComponent().getClass().getName() + "\n");
    }

    private void displayInfo(KeyEvent e, String keyStatus){
        
        int id = e.getID();

        String keyString;

	keyString = keyStatus + " " ;

        if (id == KeyEvent.KEY_TYPED) {
            char c = e.getKeyChar();
            keyString += "key character = '" + c + "'";
        }
	else {
            int keyCode = e.getKeyCode();
            keyString += "key code = " + keyCode + " (" + KeyEvent.getKeyText(keyCode) + ")";
        }

	System.out.println( keyString ) ;
    }
}
