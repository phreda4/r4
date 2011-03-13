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
//
// MC 26/03/2010 De-compilador v1, this program de-compiles the bytecode file passed on the command line. This is not an applet.
// MC 13/03/2011 De-compilador v2, adapted to new bytecodes, changed output format

import java.io.*;

class R4_decompilador {

    public static final int
	FIN= 0,LIT= 1,ADR= 2,CALL= 3,JMP=4 ,JMPR= 5,EXEC=6 , IF=7 ,PIF= 8,NIF= 9,UIF=10 ,
	IFN= 11,IFL= 12,IFG=13 ,IFLE= 14,IFGE= 15,IFNO=16 ,IFAND=17 ,IFNAND=18 , DUP= 19,DROP=20 ,
	OVER= 21,PICK2=22 ,PICK3= 23,PICK4= 24,SWAP= 25,NIP= 26,ROT= 27, DUP2= 28,DROP2=29 ,DROP3=30 ,
	DROP4=31 ,OVER2=32 ,SWAP2=33 , TOR=34 ,RFROM=35 ,ERRE=36 ,ERREM=37 ,ERRFM=38 ,ERRSM=39 ,ERRDR=40 ,
	AND=41 ,OR= 42,XOR=43 ,NOT=44 , SUMA=45 ,RESTA=46 ,MUL= 47,DIV=48 ,MULDIV=49 ,MULSHR= 50,
	DIVMOD=51 ,MOD=52 ,ABS=53 , CSQRT=54,CLZ=55,CDIVSH=56, NEG= 57,INC=58 ,INC4=59 ,DEC=60 ,
	DIV2=61 ,MUL2=62 ,SHL=63 ,SHR=64 , FECH= 65,CFECH=66 ,WFECH=67 ,STOR=68 ,CSTOR=69 ,WSTOR=70 ,
	INCSTOR=71 ,CINCSTOR=72 ,WINCSTOR=73 , FECHPLUS=74 ,STOREPLUS=75 ,CFECHPLUS= 76,CSTOREPLUS=77 ,WFECHPLUS=78 ,WSTOREPLUS= 79, MOVED=80 ,
	MOVEA=81 ,CMOVED= 82,CMOVEA=83 , MEM=84 ,PATH=85 ,BFILE=86 ,BFSIZE= 87,VOL= 88,LOAD= 89,SAVE=90 ,
	UPDATE=91 , XYMOUSE=92 ,BMOUSE=93 , SKEY=94 , KEY=95 , CNTJOY=96 ,GETJOY=97 , MSEC= 98,TIME=99 ,IDATE=100 ,
	SISEND=101 ,SISRUN=102 , WIDTH=103 ,HEIGHT=104 ,CLS=105 ,REDRAW=106 ,FRAMEV=107 , SETXY=108 ,MPX= 109,SPX=110 ,
	GPX= 111, VXFB=112 ,TOXFB= 113,XFBTO=114 , COLORF=115 ,COLOR=116 ,COLORA=117 ,ALPHA= 118, OP=119 ,CP= 120,
	LINE=121 ,CURVE=122 ,PLINE=123 ,PCURVE=124 ,POLI=125 , FCOL=126 ,FCEN=127 ,FMAT=128 ,SFILL=129 ,LFILL= 130,
	RFILL=131 ,TFILL=132, SYSTEM=133,

	ULTIMAPRIMITIVA= 148 ;

    public static String[] bytecode = {
	"FIN","LIT","ADR","CALL","JMP","JMPR","EXEC",//hasta JMPR no es visible
	"IF","PIF","NIF","UIF","IFN","IFL","IFG","IFLE","IFGE","IFNO","IFAND","IFNAND",// condicionales 0 - y +  y no 0
	"DUP","DROP","OVER","PICK2","PICK3","PICK4","SWAP","NIP","ROT",
	"DUP2","DROP2","DROP3","DROP4","OVER2","SWAP2",//--- pila
	"TOR","RFROM","ERRE","ERREM","ERRFM","ERRSM","ERRDR",//--- pila direcciones
	"AND","OR","XOR","NOT",//--- logica
	"SUMA","RESTA","MUL","DIV","MULDIV","MULSHR","DIVMOD","MOD","ABS",
	"CSQRT", "CLZ", "CDIVSH", 
	"NEG","INC","INC4","DEC","DIV2","MUL2","SHL","SHR",//--- aritmetica
	"FECH","CFECH","WFECH","STOR","CSTOR","WSTOR","INCSTOR","CINCSTOR","WINCSTOR",//--- memoria
	"FECHPLUS","STOREPLUS","CFECHPLUS","CSTOREPLUS","WFECHPLUS","WSTOREPLUS",
	"MOVED","MOVEA","CMOVED","CMOVEA",
	"MEM","PATH","BFILE","BFSIZE","VOL","LOAD","SAVE",//--- bloques de memoria, bloques
	"UPDATE", "XYMOUSE","BMOUSE", "SKEY","KEY", "CNTJOY","GETJOY",
	"MSEC","TIME","IDATE","SISEND","SISRUN",//--- sistema
	"WIDTH","HEIGHT","CLS","REDRAW","FRAMEV",//--- pantalla
	"SETXY","MPX","SPX","GPX",
	"VXFB","TOXFB","XFBTO",
	"COLORF","COLOR","COLORA","ALPHA",//--- color
	"OP","CP","LINE","CURVE","PLINE","PCURVE","POLI",//--- dibujo
	"FCOL","FCEN","FMAT","SFILL","LFILL","RFILL","TFILL", //--- pintado
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

    public static int getb( byte[] prog, int idx) {

	int val ;

	val = (int)((prog[idx]) & 0xFF) ;

	return val ;
    }

    public static int getw( byte[] prog, int idx) {

	int val ;

	val = (int)((prog[idx+1]) & 0xFF) << 8;
	val += (int)(prog[idx] & 0xFF);

	return val ;
    }

    public static int getdw( byte[] prog, int idx) {

	int val ;

	val  = ((int)(prog[idx+3]) & 0xFF) << 24;
	val += ((int)(prog[idx+2]) & 0xFF) << 16;
	val += (int)((prog[idx+1]) & 0xFF) << 8;
	val += (int)(prog[idx] & 0xFF);

	return val ;
    }

    public static void codeline(int w) {
	System.out.print( " = " + bytecode[w] ) ;
    }

    public static void codeline_v(int w, int value, String format ) {
	System.out.print( "| " + bytecode[w] + " " + String.format( format, value ) ) ;
    }
    
    public static void itpt( byte[] prog) {

	int bootadr, cntdato, cntprog ;
	int idx=0;

	System.out.println("\n") ;

	bootadr = getdw(prog, idx);
	idx += 4;
	System.out.println( "Boot adress: " + String.format("%04x ", bootadr ) ) ;

	System.out.println( "") ;

	cntdato = getdw(prog, idx);
	idx += 4;
	System.out.println( "# of bytes of data : " + String.format("%04x ", cntdato ) ) ;

	cntprog = getdw(prog, idx);
	idx += 4;
	System.out.println( "# of bytes of code : " + String.format("%04x ", cntprog ) ) ;

	System.out.println( "" ) ;

	for (int i=idx; i<idx+cntprog; i++) {

	    int value ;
	    int w = prog[i] & 0xff;
	    int ip_print = 0x20426ff0 + i -12 ;
	    String flag ;

	    flag = "   " ;
	    if (ip_print == bootadr)
		flag = "-> " ;

	    System.out.print ( flag + String.format("%04x", ip_print) + " : " + String.format("%02x ", w) ) ;

	    switch ( w ) {
		
	    case LIT :
	    case ADR :
	    case CALL :
	    case JMP :

		for(int j=1;j<5;j++) {
		    int val = getb(prog, i+j);
		    System.out.print ( String.format("%02x ", val) ) ;
		}
		
		value = getdw(prog, i+1);
		i += 4 ;
		    
		codeline_v(w, value, "%04x" ) ;

		break ;

	    case JMPR :
	    case IF :
	    case PIF :
	    case NIF :
	    case UIF :
	    case IFN :
	    case IFL :
	    case IFG :
	    case IFLE :
	    case IFGE :
	    case IFNO :
	    case IFAND :
	    case IFNAND :
		
		int val = getb(prog, i+1);
		System.out.print ( String.format("%02x ", val) ) ;

		value = getb(prog, i+1) + 1 ; /* ?? */
		i += 1 ;
		System.out.print ( "         ") ;
		codeline_v(w, value, "%01x" ) ;
		
		break ;

	    default :

		if ( w < bytecode.length )
		    System.out.print ( "            | " + bytecode[ w ] ) ;
		else
		    System.out.print ( String.format( "            | %02x ", w - ULTIMAPRIMITIVA ) ) ;

		break ;

	    }

	    System.out.println("") ;

	}
    }

    public static void main ( String[] args ) {

	int i ;
	byte[] test ;
	File file = new File(args[0]);

	try {
	    test = getBytesFromFile( file );
	    //	    hexdump(test);
	    itpt(test);
	}
	catch ( IOException iox ) {
	    System.out.println("Problem reading file" );
	}

	System.out.print( "\n" ) ;
    }
}
