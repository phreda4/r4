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

public static final int NOP=0,LIT= 1,ADR= 2,CALL= 3,JMP=4 ,FIN= 5,EXEC=6 ,
       IF=7 ,PIF= 8,NIF= 9,UIF=10 ,IFN= 11,IFL= 12,IFG=13 ,IFLE= 14,IFGE= 15,IFNO=16 ,IFAND=17 ,IFNAND=18 ,
       DUP= 19,DROP=20 ,OVER= 21,PICK2=22 ,PICK3= 23,PICK4= 24,SWAP= 25,NIP= 26,ROT= 27,
       DUP2= 28,DROP2=29 ,DROP3=30 ,DROP4=31 ,OVER2=32 ,SWAP2=33 ,
       TOR=34 ,RFROM=35 ,ERRE=36 ,ERREM=37 ,ERRFM=38 ,ERRSM=39 ,ERRDR=40 ,
       AND=41 ,OR= 42,XOR=43 ,NOT=44 ,
       SUMA=45 ,RESTA=46 ,MUL= 47,DIV=48 ,MULDIV=49 ,MULSHR= 50,DIVMOD=51 ,MOD=52 ,ABS=53 ,
       NEG= 54,INC=55 ,INC4=56 ,DEC=57 ,DIV2=58 ,MUL2=59 ,SHL=60 ,SHR=61 ,
       FECH= 62,CFECH=63 ,WFECH=64 ,STOR=65 ,CSTOR=66 ,WSTOR=67 ,INCSTOR=68 ,CINCSTOR=69 ,WINCSTOR=70 ,
       FECHPLUS=71 ,STOREPLUS=72 ,CFECHPLUS= 73,CSTOREPLUS=74 ,WFECHPLUS=75 ,WSTOREPLUS= 76,
       MOVED=77 ,MOVEA=78 ,CMOVED= 79,CMOVEA=80 ,
       MEM=81 ,PATH=82 ,BFILE=83 ,BFSIZE= 84,VOL= 85,LOAD= 86,SAVE=87 ,
       UPDATE=88 ,
       TPEN=89 ,
       XYMOUSE=90 ,BMOUSE=91 ,
       IRKEY=92 ,KEY=93 ,
       CNTJOY=94 ,GETJOY=95 ,
       MSEC= 96,TIME=97 ,IDATE=98 ,SISEND=99 ,SISRUN=100 ,
       WIDTH=101 ,HEIGHT=102 ,CLS=103 ,REDRAW=104 ,FRAMEV=105 ,
       SETXY=106 ,MPX= 107,SPX=108 ,GPX= 109,
       VXFB=110 ,TOXFB= 111,XFBTO=112 ,
       COLORF=113 ,COLOR=114 ,COLORA=115 ,ALPHA= 116,
       OP=117 ,CP= 118,LINE=119 ,CURVE=120 ,PLINE=121 ,PCURVE=122 ,POLI=123 ,
       FCOL=124 ,FCEN=125 ,FMAT=126 ,SFILL=127 ,LFILL= 128,RFILL=129 ,TFILL=130 ;

	int ip;
	int [] dpila = new int[1024];
	int [] rpila = new int[1024];
	int sizefb = width * height;
	int FB[] = new int[sizefb];
	int XFB[] = new int[sizefb];

	char mem[] = new int[16*1024*1024];

	public void interprete()
	{
	int TOS,NOS,RTOS,W;
	TOS=NOS=RTOS=0;
	while (true) {
		W=mem[IP];IP++;
		while (w!=0) {
		switch(W&0xff) {
			case FIN: IP=rpila[RTOS];RTOS--;W=0;break
			case LIT: NOS++;dpila[NOS]=TOS;TOS=mem[IP];IP++;break;
			case ADR: NOS++;dpila[NOS]=TOS;TOS=mem[W>>8];break;
			case CALL: rtos++;rpila[RTOS]=IP;IP=W>>8;W=0;break;
			case JMP: IP=W>>8;W=0;break;
			case EXEC://hasta JMPR no es visible
			case IF: if (TOS!=0) IP+=(W>>8);W=0;break;	// condicionales 0 - y +  y no 0
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
			W=W>>8;
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
