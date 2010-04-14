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
//  Version Java Applet

/*
  Example use :

  wine ../r4.exe cex1.txt iex1.r4x s
  javac R4_int.java 
  java R4_int ex1.r4x 
*/

import java.io.*;

class R4_int {

    public static final int FIN= 0,LIT= 1,ADR= 2,CALL= 3,JMP=4 ,JMPR= 5,EXEC=6 ,
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

    public static String[] bytecode = {
	"FIN","LIT","ADR","CALL","JMP","JMPR","EXEC",//hasta JMPR no es visible
	"IF","PIF","NIF","UIF","IFN","IFL","IFG","IFLE","IFGE","IFNO","IFAND","IFNAND",// condicionales 0 - y +  y no 0
	"DUP","DROP","OVER","PICK2","PICK3","PICK4","SWAP","NIP","ROT",
	"DUP2","DROP2","DROP3","DROP4","OVER2","SWAP2",//--- pila
	"TOR","RFROM","ERRE","ERREM","ERRFM","ERRSM","ERRDR",//--- pila direcciones
	"AND","OR","XOR","NOT",//--- logica
	"SUMA","RESTA","MUL","DIV","MULDIV","MULSHR","DIVMOD","MOD","ABS",
	"NEG","INC","INC4","DEC","DIV2","MUL2","SHL","SHR",//--- aritmetica
	"FECH","CFECH","WFECH","STOR","CSTOR","WSTOR","INCSTOR","CINCSTOR","WINCSTOR",//--- memoria
	"FECHPLUS","STOREPLUS","CFECHPLUS","CSTOREPLUS","WFECHPLUS","WSTOREPLUS",
	"MOVED","MOVEA","CMOVED","CMOVEA",
	"MEM","PATH","BFILE","BFSIZE","VOL","LOAD","SAVE",//--- bloques de memoria, bloques
	"UPDATE",
	"TPEN",
	"XYMOUSE","BMOUSE",
	"IRKEY","KEY",
	"CNTJOY","GETJOY",
	"MSEC","TIME","IDATE","SISEND","SISRUN",//--- sistema
	"WIDTH","HEIGHT","CLS","REDRAW","FRAMEV",//--- pantalla
	"SETXY","MPX","SPX","GPX",
	"VXFB","TOXFB","XFBTO",
	"COLORF","COLOR","COLORA","ALPHA",//--- color
	"OP","CP","LINE","CURVE","PLINE","PCURVE","POLI",//--- dibujo
	"FCOL","FCEN","FMAT","SFILL","LFILL","RFILL","TFILL", //--- pintado
	"SERVER","CLIENT","NSEND","RECV","CLOSE", //---- red
	"SYSTEM",
	"ULTIMAPRIMITIVA"// de aqui en mas.. apila los numeros 0..255-ULTIMAPRIMITIVA
    };

    public static byte[] getBytesFromFile(File file) throws IOException {

        InputStream is = new FileInputStream(file);
    
        long length = file.length();
    
        byte[] bytes = new byte[(int)length];
    
        int offset = 0;
        int numRead = 0;
        while (offset < bytes.length && (numRead=is.read(bytes, offset, bytes.length-offset)) >= 0) {
            offset += numRead;
        }
    
        if (offset < bytes.length) {
            throw new IOException("Could not completely read file "+file.getName());
        }
    
        is.close();
        return bytes;
    }

    public static void hexdump(byte[] arr) {
	int i ;

	System.out.print( "\nHex Dump of file :\n" ) ;

	for(i=0;i<arr.length;i++) {
	    
	    if ((i%16) == 0) {
		String str = String.format("\n%08x: ", i ) ;
		System.out.print( str);
	    }
	    
	    byte b = arr[i];
	    String str = String.format("%02x ", b ) ;
	    
	    System.out.print( str ) ;
	    
	}
    }

    public static int getw( byte[] prog, int idx) {

	int val ;

	// in Java, signed/unsigned is, errr, different

	val = (int)((prog[idx+1]) & 0xFF) << 8;
	val += (int)(prog[idx] & 0xFF);

	return val ;
    }

    public static int getb( byte[] prog, int idx) {

	int val ;

	// in Java, signed/unsigned is, errr, different

	val = (int)((prog[idx]) & 0xFF) ;

	return val ;
    }

    public static int getdw( byte[] prog, int idx) {

	int val ;

	// in Java, signed/unsigned is, errr, different

	val  = ((int)(prog[idx+3]) & 0xFF) << 24;
	val += ((int)(prog[idx+2]) & 0xFF) << 16;
	val += (int)((prog[idx+1]) & 0xFF) << 8;
	val += (int)(prog[idx] & 0xFF);

	return val ;
    }

    public static void setdw( byte[] prog, int idx, int value) {

	prog[idx] = (byte) (value & 0xFF );
	prog[idx+1] = (byte) ((value>>8) & 0xFF );
	prog[idx+2] = (byte) ((value>>16) & 0xFF) ;
	prog[idx+3] = (byte) ((value>>24) & 0xFF) ;

    }

    public static void codeline(int w) {
	System.out.print( bytecode[w] );
    }

    public static void codeline_v(int w, int value, String format ) {
	System.out.print( bytecode[w] + " " + String.format("$" + format, value ) ) ;
    }
    
    public static void itpt( byte[] prog) {

	int bootadr, cntdato, cntprog ;
	int idx=0;

	int ip;
	int nos, tos, rtos ;
	int start ;
	int memstart ;
	int [] dpila = new int[1024];
	int [] rpila = new int[1024];
	
	byte memcod[] = new byte[256*1024];
	byte memdat[] = new byte[1024*1024];

	System.out.print( "\n\nInterpreter :\n\n") ;

	bootadr = getdw(prog, idx);
	idx += 4;
	System.out.println( "Boot adress: " + String.format("$%04x ", bootadr ) ) ;

	cntdato = getdw(prog, idx);
	idx += 4;
	System.out.println("");
	System.out.println( "Cnt dato: " + String.format("%04x ", cntdato ) ) ;

	cntprog = getdw(prog, idx);
	idx += 4;
	System.out.println( "Cnt prog: " + String.format("%04x ", cntprog ) ) ;

	/* copy in memdat */

	System.arraycopy( prog, 12 + cntprog , memdat, 0, cntdato );

	System.out.println("");
	System.out.println("Start interpreter.") ;

	start =    0x20426ff0 ;
	memstart =   0x426ff0 ;
	ip = bootadr - start + 12 ;

	nos = tos = rtos = 0 ;

	int end=0;

	while(end==0) {

	    int value ;
	    int w = prog[ip++] & 0xff;

	    switch ( w ) {

	    case FIN :
		ip = rpila[rtos] ;
		rtos-- ;
		if (rtos<0)
		    end=1;
		break ;
		
	    case LIT :
		System.out.println("[" + bytecode[w] + "]") ;
		value = getdw(prog, ip) ;
		nos++ ;
		dpila[nos]=tos ;
		tos=value ;
		ip += 4 ;
		break;

	    case ADR:
		nos++;
		dpila[nos] = tos ;
		value = getdw(prog, ip) ;
		ip += 4 ;
		tos = getdw(memdat, value - memstart) ;

		break ;

	    case CALL:
		System.out.println("[" + bytecode[w] + "]") ;
		value = getdw(prog, ip) - start + 12 ;
		ip += 4 ;
		rtos ++ ;
		rpila[rtos] = ip ;
		ip = value ;
		break ;

	    case JMP:
		System.out.println("[" + bytecode[w] + "]") ;
		value = getdw(prog, ip) - start + 12 ;
		ip = value ;
		break ;
		
	    case JMPR:
		System.out.println("[" + bytecode[w] + "]") ;
		value = getb(prog, ip) ;
		value++;
		ip += value ;
		break ;

		/* condicionales */

	    case IF:
		System.out.println("[" + bytecode[w] + "]") ;
		value = getb(prog, ip) ;
		ip++;
		if (tos!=0)
		    ip+=value ;
		break ;

	    case PIF:
		System.out.println("[" + bytecode[w] + "]") ;
		value = getb(prog, ip) ;
		ip++;
		if (tos<=0)
		    ip+=value ;
		break ;

	    case NIF:
		System.out.println("[" + bytecode[w] + "]") ;
		value = getb(prog, ip) ;
		ip++;
		if (tos>=0)
		    ip+=value ;
		break ;

	    case UIF:
		System.out.println("[" + bytecode[w] + "]") ;
		value = getb(prog, ip) ;
		ip++;
		if (tos==0)
		    ip+=value ;
		break ;

	    case IFN:
		System.out.println("[" + bytecode[w] + "]") ;
		value = getb(prog, ip) ;
		ip++;
		if (tos!=dpila[nos])
		    ip+=value ;
		tos=dpila[nos];
		nos--;
		break ;

	    case IFNO:
		System.out.println("[" + bytecode[w] + "]") ;
		value = getb(prog, ip) ;
		ip++;
		if (tos==dpila[nos])
		    ip+=value ;
		tos=dpila[nos];
		nos--;
		break ;

	    case IFL:
		System.out.println("[" + bytecode[w] + "]") ;
		value = getb(prog, ip) ;
		ip++;
		if (tos<=dpila[nos])
		    ip+=value ;
		tos=dpila[nos];
		nos--;
		break ;

	    case IFG:
		System.out.println("[" + bytecode[w] + "]") ;
		value = getb(prog, ip) ;
		ip++;
		if (tos>=dpila[nos])
		    ip+=value ;
		tos=dpila[nos];
		nos--;
		break ;

	    case IFLE:
		System.out.println("[" + bytecode[w] + "]") ;
		value = getb(prog, ip) ;
		ip++;
		if (tos<dpila[nos])
		    ip+=value ;
		tos=dpila[nos];
		nos--;
		break ;

	    case IFGE:
		System.out.println("[" + bytecode[w] + "]") ;
		value = getb(prog, ip) ;
		ip++;
		if (tos>dpila[nos])
		    ip+=value ;
		tos=dpila[nos];
		nos--;
		break ;

	    case IFAND:
		System.out.println("[" + bytecode[w] + "]") ;
		value = getb(prog, ip) ;
		ip++;
		if ((tos>0) & (dpila[nos]>0))
		    ip+=value ;
		tos=dpila[nos];
		nos--;
		break ;

	    case IFNAND:
		System.out.println("[" + bytecode[w] + "]") ;
		value = getb(prog, ip) ;
		ip++;
		if (!((tos>0) & (dpila[nos]>0)))
		    ip+=value ;
		tos=dpila[nos];
		nos--;
		break ;

	    case FECH:
		tos = getdw(memdat, tos - memstart) ;
		break ;

	    case STOR:
		value = dpila[nos] ;
		setdw( memdat, tos - memstart, value ) ;
		nos--;
		tos=dpila[nos];
		nos--;
		break ;

	    case EXEC:
		System.out.println("[" + bytecode[w] + "]") ;
		value = tos ;
		tos = dpila[nos] ;
		nos -- ;
		if (value!=0) {
		    rtos++;
		    rpila[rtos] = ip;
		    ip = value - start + 12 ;
		}
		break ;

	    case DUP :
		System.out.println("[" + bytecode[w] + "]") ;
		nos++ ;
		dpila[nos] = tos ;
		break;

	    case DROP:
		System.out.println("[" + bytecode[w] + "]") ;
		tos=dpila[nos] ;
		nos-- ;
		break ;

	    case OVER:
		System.out.println("[" + bytecode[w] + "]") ;
		nos++ ;
		dpila[nos]= tos ;
		tos = dpila[nos-1];
		break ;

	    case PICK2 :
		System.out.println("[" + bytecode[w] + "]") ;
		nos++ ;
		dpila[nos] = tos ;
		tos = dpila[nos-2] ;
		break ;

	    case PICK3 :
		System.out.println("[" + bytecode[w] + "]") ;
		nos++ ;
		dpila[nos] = tos ;
		tos = dpila[nos-3] ;
		break ;

	    case PICK4 :
		System.out.println("[" + bytecode[w] + "]") ;
		nos++ ;
		dpila[nos] = tos ;
		tos = dpila[nos-4] ;
		break ;

	    case NIP :
		System.out.println("[" + bytecode[w] + "]") ;
		nos-- ;
		break ;

	    case SWAP:
		System.out.println("[" + bytecode[w] + "]") ;
		value = dpila[nos];
		dpila[nos] = tos ;
		tos = value ;
		break;

	    case ROT:
		System.out.println("[" + bytecode[w] + "]") ;
		value = tos ;
		tos = dpila[nos-1] ;
		dpila[nos-1] = dpila[nos] ;
		dpila[nos] = value ;
		break;

	    case SUMA :
		System.out.println("[" + bytecode[w] + "]") ;
		tos = dpila[nos] + tos ;
		nos-- ;
		break ;

	    case RESTA :
		System.out.println("[" + bytecode[w] + "]") ;
		tos = dpila[nos] - tos ;
		nos-- ;
		break ;

	    case MUL :
		System.out.println("[" + bytecode[w] + "]") ;
		tos = dpila[nos] * tos ;
		nos-- ;
		break ;

	    case DIV :
		System.out.println("[" + bytecode[w] + "]") ;
		tos = dpila[nos] / tos ;
		nos-- ;
		break ;

	    default :

		if ( w < bytecode.length ) {
		    System.out.println ( "Unknown bytecode...!" ) ;
		}
		else {
		    value = w - 150 ;
		    System.out.println("[Small lit: " + value + "]") ;
		    nos++ ;
		    dpila[nos]=tos ;
		    tos=value ;
		}

		break ;
	    }
	}
	System.out.println("Top of stack value : " + String.format("%04x ", tos ) ) ;
    }

    public static void main ( String[] args ) {

	// bytearray pour code
	// bytearray pour data
	
	int i ;
	byte[] test ;
	File file = new File(args[0]);

	System.out.println("Decompilando: " + args[0]) ;

	try {
	    test = getBytesFromFile( file );
	    hexdump(test);
	    itpt(test);
	}
	catch ( IOException iox ) {
	    System.out.println("Problem reading file" );
	}

	System.out.print( "\n" ) ;
    }
}
