	.file	"redam.cpp"
	.section .rdata,"dr"
LC0:
	.ascii "debug.r4x\0"
.globl _DEBUGR4X
	.data
	.align 4
_DEBUGR4X:
	.long	LC0
.globl _lastcall
	.bss
	.align 4
_lastcall:
	.space 4
.globl _pila
	.align 32
_pila:
	.space 1024
.globl _cntpila
	.align 4
_cntpila:
	.space 4
.globl _cntpilaA
	.align 4
_cntpilaA:
	.space 4
.globl _includes
	.align 32
_includes:
	.space 600
.globl _cntincludes
	.align 4
_cntincludes:
	.space 4
.globl _nombreex
	.align 32
_nombreex:
	.space 32768
.globl _cntnombreex
	.align 4
_cntnombreex:
	.space 4
.globl _indiceex
	.align 32
_indiceex:
	.space 24576
.globl _cntindiceex
	.align 4
_cntindiceex:
	.space 4
.globl _nombre
	.align 32
_nombre:
	.space 16384
.globl _cntnombre
	.align 4
_cntnombre:
	.space 4
.globl _indice
	.align 32
_indice:
	.space 24576
.globl _cntindice
	.align 4
_cntindice:
	.space 4
.globl _numero
	.align 4
_numero:
	.space 4
.globl _data
	.align 32
_data:
	.space 536870912
.globl _prog
	.align 32
_prog:
	.space 262144
.globl _ultimapalabra
	.data
_ultimapalabra:
	.byte	99
.globl _RSP
	.bss
	.align 32
_RSP:
	.space 8192
.globl _PSP
	.align 32
_PSP:
	.space 8192
.globl _memlibre
	.align 4
_memlibre:
	.space 4
.globl _cntprog
	.align 4
_cntprog:
	.space 4
.globl _cntdato
	.align 4
_cntdato:
	.space 4
.globl _sitime
	.align 4
_sitime:
	.space 4
.globl _sit
	.align 4
_sit:
	.space 4
.globl _cntsubdirs
	.align 4
_cntsubdirs:
	.space 4
.globl _subdirs
	.align 32
_subdirs:
	.space 1020
.globl _cntindex
	.align 4
_cntindex:
	.space 4
.globl _sizedir
	.align 32
_sizedir:
	.space 2048
.globl _indexdir
	.align 32
_indexdir:
	.space 2048
.globl _mindice
	.align 32
_mindice:
	.space 8192
.globl _mbuff
	.align 32
_mbuff:
	.space 512
.globl _mcnt
	.align 4
_mcnt:
	.space 4
.globl _SYSirqred
	.align 4
_SYSirqred:
	.space 4
.globl _SYSirqsonido
	.align 4
_SYSirqsonido:
	.space 4
.globl _SYSirqteclado
	.align 4
_SYSirqteclado:
	.space 4
.globl _SYSKEY
	.align 4
_SYSKEY:
	.space 4
.globl _SYSBM
	.align 4
_SYSBM:
	.space 4
.globl _SYSXYM
	.align 4
_SYSXYM:
	.space 4
.globl _SYSEVENT
	.align 4
_SYSEVENT:
	.space 4
.globl _pathdata
	.align 32
_pathdata:
	.space 256
.globl _error
	.align 32
_error:
	.space 1024
.globl _linea
	.align 32
_linea:
	.space 1024
.globl _file
	.align 4
_file:
	.space 4
.globl _bootaddr
	.align 4
_bootaddr:
	.space 4
.globl _gyc
	.align 4
_gyc:
	.space 4
.globl _gxc
	.align 4
_gxc:
	.space 4
.globl _gy2
	.align 4
_gy2:
	.space 4
.globl _gx2
	.align 4
_gx2:
	.space 4
.globl _gy1
	.align 4
_gy1:
	.space 4
.globl _gx1
	.align 4
_gx1:
	.space 4
	.section .rdata,"dr"
LC1:
	.ascii "main.r4x\0"
.globl _exestr
	.data
	.align 4
_exestr:
	.long	LC1
	.section .rdata,"dr"
LC2:
	.ascii "main.txt\0"
.globl _bootstr
	.data
	.align 4
_bootstr:
	.long	LC2
	.section .rdata,"dr"
LC3:
	.ascii "\0"
.globl _compilastr
	.data
	.align 4
_compilastr:
	.long	LC3
.globl _pilaexecl
	.bss
	.align 4
_pilaexecl:
	.space 4
.globl _pilaexec
	.align 32
_pilaexec:
	.space 1024
	.section .rdata,"dr"
LC4:
	.ascii ";\0"
LC5:
	.ascii "(\0"
LC6:
	.ascii ")\0"
LC7:
	.ascii ")(\0"
LC8:
	.ascii "[\0"
LC9:
	.ascii "]\0"
LC10:
	.ascii "EXEC\0"
LC11:
	.ascii "0?\0"
LC12:
	.ascii "+?\0"
LC13:
	.ascii "-?\0"
LC14:
	.ascii "1?\0"
LC15:
	.ascii "=?\0"
LC16:
	.ascii "<?\0"
LC17:
	.ascii ">?\0"
LC18:
	.ascii "<=?\0"
LC19:
	.ascii ">=?\0"
LC20:
	.ascii "<>?\0"
LC21:
	.ascii "AND?\0"
LC22:
	.ascii "NAND?\0"
LC23:
	.ascii "DUP\0"
LC24:
	.ascii "DROP\0"
LC25:
	.ascii "OVER\0"
LC26:
	.ascii "PICK2\0"
LC27:
	.ascii "PICK3\0"
LC28:
	.ascii "PICK4\0"
LC29:
	.ascii "SWAP\0"
LC30:
	.ascii "NIP\0"
LC31:
	.ascii "ROT\0"
LC32:
	.ascii "2DUP\0"
LC33:
	.ascii "2DROP\0"
LC34:
	.ascii "3DROP\0"
LC35:
	.ascii "4DROP\0"
LC36:
	.ascii "2OVER\0"
LC37:
	.ascii "2SWAP\0"
LC38:
	.ascii ">R\0"
LC39:
	.ascii "R>\0"
LC40:
	.ascii "R\0"
LC41:
	.ascii "R+\0"
LC42:
	.ascii "R@+\0"
LC43:
	.ascii "R!+\0"
LC44:
	.ascii "RDROP\0"
LC45:
	.ascii "AND\0"
LC46:
	.ascii "OR\0"
LC47:
	.ascii "XOR\0"
LC48:
	.ascii "NOT\0"
LC49:
	.ascii "+\0"
LC50:
	.ascii "-\0"
LC51:
	.ascii "*\0"
LC52:
	.ascii "/\0"
LC53:
	.ascii "*/\0"
LC54:
	.ascii "*>>\0"
LC55:
	.ascii "/MOD\0"
LC56:
	.ascii "MOD\0"
LC57:
	.ascii "ABS\0"
LC58:
	.ascii "NEG\0"
LC59:
	.ascii "1+\0"
LC60:
	.ascii "4+\0"
LC61:
	.ascii "1-\0"
LC62:
	.ascii "2/\0"
LC63:
	.ascii "2*\0"
LC64:
	.ascii "<<\0"
LC65:
	.ascii ">>\0"
LC66:
	.ascii "@\0"
LC67:
	.ascii "C@\0"
LC68:
	.ascii "W@\0"
LC69:
	.ascii "!\0"
LC70:
	.ascii "C!\0"
LC71:
	.ascii "W!\0"
LC72:
	.ascii "+!\0"
LC73:
	.ascii "C+!\0"
LC74:
	.ascii "W+!\0"
LC75:
	.ascii "@+\0"
LC76:
	.ascii "!+\0"
LC77:
	.ascii "C@+\0"
LC78:
	.ascii "C!+\0"
LC79:
	.ascii "W@+\0"
LC80:
	.ascii "W!+\0"
LC81:
	.ascii "MOVE\0"
LC82:
	.ascii "MOVE>\0"
LC83:
	.ascii "CMOVE\0"
LC84:
	.ascii "CMOVE>\0"
LC85:
	.ascii "MEM\0"
LC86:
	.ascii "DIR\0"
LC87:
	.ascii "FILE\0"
LC88:
	.ascii "FSIZE\0"
LC89:
	.ascii "VOL\0"
LC90:
	.ascii "LOAD\0"
LC91:
	.ascii "SAVE\0"
LC92:
	.ascii "UPDATE\0"
LC93:
	.ascii "TPEN\0"
LC94:
	.ascii "XYMOUSE\0"
LC95:
	.ascii "BMOUSE\0"
LC96:
	.ascii "IKEY!\0"
LC97:
	.ascii "KEY\0"
LC98:
	.ascii "CNTJOY\0"
LC99:
	.ascii "GETJOY\0"
LC100:
	.ascii "MSEC\0"
LC101:
	.ascii "TIME\0"
LC102:
	.ascii "DATE\0"
LC103:
	.ascii "END\0"
LC104:
	.ascii "RUN\0"
LC105:
	.ascii "SW\0"
LC106:
	.ascii "SH\0"
LC107:
	.ascii "CLS\0"
LC108:
	.ascii "REDRAW\0"
LC109:
	.ascii "FRAMEV\0"
LC110:
	.ascii "SETXY\0"
LC111:
	.ascii "PX+!\0"
LC112:
	.ascii "PX!+\0"
LC113:
	.ascii "PX@\0"
LC114:
	.ascii "XFB\0"
LC115:
	.ascii ">XFB\0"
LC116:
	.ascii "XFB>\0"
LC117:
	.ascii "PAPER\0"
LC118:
	.ascii "INK\0"
LC119:
	.ascii "INK@\0"
LC120:
	.ascii "ALPHA\0"
LC121:
	.ascii "OP\0"
LC122:
	.ascii "CP\0"
LC123:
	.ascii "LINE\0"
LC124:
	.ascii "CURVE\0"
LC125:
	.ascii "PLINE\0"
LC126:
	.ascii "PCURVE\0"
LC127:
	.ascii "POLI\0"
LC128:
	.ascii "FCOL\0"
LC129:
	.ascii "FCEN\0"
LC130:
	.ascii "FMAT\0"
LC131:
	.ascii "SFILL\0"
LC132:
	.ascii "LFILL\0"
LC133:
	.ascii "RFILL\0"
LC134:
	.ascii "TFILL\0"
LC135:
	.ascii "SLOAD\0"
LC136:
	.ascii "SPLAY\0"
LC137:
	.ascii "MLOAD\0"
LC138:
	.ascii "MPLAY\0"
LC139:
	.ascii "SERVER\0"
LC140:
	.ascii "CLIENT\0"
LC141:
	.ascii "SEND\0"
LC142:
	.ascii "RECV\0"
LC143:
	.ascii "CLOSE\0"
LC144:
	.ascii "DOCINI\0"
LC145:
	.ascii "DOCEND\0"
LC146:
	.ascii "DOCAT\0"
LC147:
	.ascii "DOCLINE\0"
LC148:
	.ascii "DOCTEXT\0"
LC149:
	.ascii "DOCFONT\0"
LC150:
	.ascii "DOCBIT\0"
LC151:
	.ascii "DOCRES\0"
LC152:
	.ascii "DOCSIZE\0"
LC153:
	.ascii "SYSTEM\0"
.globl _macros
	.data
	.align 32
_macros:
	.long	LC4
	.long	LC5
	.long	LC6
	.long	LC7
	.long	LC8
	.long	LC9
	.long	LC10
	.long	LC11
	.long	LC12
	.long	LC13
	.long	LC14
	.long	LC15
	.long	LC16
	.long	LC17
	.long	LC18
	.long	LC19
	.long	LC20
	.long	LC21
	.long	LC22
	.long	LC23
	.long	LC24
	.long	LC25
	.long	LC26
	.long	LC27
	.long	LC28
	.long	LC29
	.long	LC30
	.long	LC31
	.long	LC32
	.long	LC33
	.long	LC34
	.long	LC35
	.long	LC36
	.long	LC37
	.long	LC38
	.long	LC39
	.long	LC40
	.long	LC41
	.long	LC42
	.long	LC43
	.long	LC44
	.long	LC45
	.long	LC46
	.long	LC47
	.long	LC48
	.long	LC49
	.long	LC50
	.long	LC51
	.long	LC52
	.long	LC53
	.long	LC54
	.long	LC55
	.long	LC56
	.long	LC57
	.long	LC58
	.long	LC59
	.long	LC60
	.long	LC61
	.long	LC62
	.long	LC63
	.long	LC64
	.long	LC65
	.long	LC66
	.long	LC67
	.long	LC68
	.long	LC69
	.long	LC70
	.long	LC71
	.long	LC72
	.long	LC73
	.long	LC74
	.long	LC75
	.long	LC76
	.long	LC77
	.long	LC78
	.long	LC79
	.long	LC80
	.long	LC81
	.long	LC82
	.long	LC83
	.long	LC84
	.long	LC85
	.long	LC86
	.long	LC87
	.long	LC88
	.long	LC89
	.long	LC90
	.long	LC91
	.long	LC92
	.long	LC93
	.long	LC94
	.long	LC95
	.long	LC96
	.long	LC97
	.long	LC98
	.long	LC99
	.long	LC100
	.long	LC101
	.long	LC102
	.long	LC103
	.long	LC104
	.long	LC105
	.long	LC106
	.long	LC107
	.long	LC108
	.long	LC109
	.long	LC110
	.long	LC111
	.long	LC112
	.long	LC113
	.long	LC114
	.long	LC115
	.long	LC116
	.long	LC117
	.long	LC118
	.long	LC119
	.long	LC120
	.long	LC121
	.long	LC122
	.long	LC123
	.long	LC124
	.long	LC125
	.long	LC126
	.long	LC127
	.long	LC128
	.long	LC129
	.long	LC130
	.long	LC131
	.long	LC132
	.long	LC133
	.long	LC134
	.long	LC135
	.long	LC136
	.long	LC137
	.long	LC138
	.long	LC139
	.long	LC140
	.long	LC141
	.long	LC142
	.long	LC143
	.long	LC144
	.long	LC145
	.long	LC146
	.long	LC147
	.long	LC148
	.long	LC149
	.long	LC150
	.long	LC151
	.long	LC152
	.long	LC153
	.long	LC3
.globl _mapex
	.align 32
_mapex:
	.byte	0
	.byte	1
	.byte	2
	.byte	3
	.byte	4
	.byte	5
	.byte	6
	.byte	7
	.byte	8
	.byte	9
	.byte	10
	.byte	11
	.byte	12
	.byte	13
	.byte	14
	.byte	15
	.byte	16
	.byte	17
	.byte	18
	.byte	19
	.byte	20
	.byte	21
	.byte	22
	.byte	23
	.byte	24
	.byte	25
	.byte	26
	.byte	27
	.byte	28
	.byte	29
	.byte	30
	.byte	31
	.byte	32
	.byte	33
	.byte	34
	.byte	35
	.byte	36
	.byte	37
	.byte	38
	.byte	39
	.byte	40
	.byte	41
	.byte	42
	.byte	43
	.byte	44
	.byte	45
	.byte	46
	.byte	47
	.byte	48
	.byte	49
	.byte	50
	.byte	51
	.byte	52
	.byte	69
	.byte	70
	.byte	71
	.byte	56
	.byte	73
	.byte	74
	.byte	75
	.byte	76
	.byte	77
	.byte	78
	.byte	79
	.byte	80
	.byte	81
	.byte	82
	.byte	83
	.byte	84
	.byte	85
	.byte	86
	.byte	103
	.byte	104
	.byte	89
	.byte	90
	.byte	91
	.byte	92
	.byte	93
	.byte	94
	.byte	95
	.byte	96
	.byte	97
	.byte	98
	.byte	99
	.byte	84
	.byte	85
	.byte	86
	.byte	87
	.byte	88
	.byte	89
	.byte	90
	.byte	91
	.byte	92
	.byte	93
	.byte	94
	.byte	95
	.byte	96
	.byte	97
	.byte	98
	.byte	99
	.byte	100
	.byte	101
	.byte	102
	.byte	103
	.byte	104
	.byte	105
	.byte	106
	.byte	107
	.byte	108
	.byte	109
	.byte	110
	.byte	111
	.byte	112
	.byte	113
	.byte	114
	.byte	115
	.byte	116
	.byte	117
	.byte	118
	.byte	119
	.byte	120
	.byte	121
	.byte	122
	.byte	123
	.byte	124
	.byte	125
	.byte	126
	.byte	127
.globl _rebotea
	.bss
	.align 4
_rebotea:
	.space 4
.globl _setings
	.align 32
_setings:
	.space 256
.globl _StartupInfo
	.align 32
_StartupInfo:
	.space 68
.globl _ProcessInfo
	.align 4
_ProcessInfo:
	.space 16
.globl _tsize
	.align 4
_tsize:
	.space 8
.globl _cHeightPels
	.align 4
_cHeightPels:
	.space 4
.globl _cWidthPels
	.align 4
_cWidthPels:
	.space 4
.globl _hfntPrev
	.align 4
_hfntPrev:
	.space 4
.globl _hfnt
	.align 4
_hfnt:
	.space 4
.globl _plf
	.align 32
_plf:
	.space 60
.globl _phDC
	.align 4
_phDC:
	.space 4
.globl _lpError
	.align 4
_lpError:
	.space 4
.globl _di
	.align 4
_di:
	.space 20
.globl _buffersize
	.align 4
_buffersize:
	.space 4
.globl _buffernet
	.align 4
_buffernet:
	.space 4
.globl _naddr
	.align 4
_naddr:
	.space 16
.globl _wsaData
	.align 32
_wsaData:
	.space 400
.globl _soc
	.align 4
_soc:
	.space 4
.globl _host
	.align 4
_host:
	.space 4
.globl _active
	.align 4
_active:
	.space 4
.globl _rec
	.align 4
_rec:
	.space 16
.globl _dwStyle
	.align 4
_dwStyle:
	.space 4
.globl _dwExStyle
	.align 4
_dwExStyle:
	.space 4
.globl _screenSettings
	.align 32
_screenSettings:
	.space 156
.globl _msg
	.align 4
_msg:
	.space 28
.globl _wc
	.align 32
_wc:
	.space 40
.globl _hWnd
	.align 4
_hWnd:
	.space 4
	.section .rdata,"dr"
_wndclass:
	.ascii ":r4\0"
	.text
	.align 2
	.p2align 4,,15
.globl __Z8mimemsetPcci
	.def	__Z8mimemsetPcci;	.scl	2;	.type	32;	.endef
__Z8mimemsetPcci:
	pushl	%ebp
	movl	%esp, %ebp
	movl	8(%ebp), %edx
	movl	16(%ebp), %eax
	movb	12(%ebp), %cl
	jmp	L8
	.p2align 4,,7
L10:
	movb	%cl, (%edx)
	decl	%eax
	incl	%edx
L8:
	testl	%eax, %eax
	jg	L10
	popl	%ebp
	ret
	.align 2
	.p2align 4,,15
.globl __Z7WndProcP6HWND__jjl@16
	.def	__Z7WndProcP6HWND__jjl@16;	.scl	2;	.type	32;	.endef
__Z7WndProcP6HWND__jjl@16:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%esi
	pushl	%ebx
	movl	12(%ebp), %edx
	movl	8(%ebp), %esi
	movl	16(%ebp), %ebx
	movl	20(%ebp), %ecx
	cmpl	$514, %edx
	ja	L42
	cmpl	$513, %edx
	jb	L50
L20:
	movl	%ebx, _SYSBM
L12:
	leal	-8(%ebp), %esp
	xorl	%eax, %eax
	popl	%ebx
	popl	%esi
	popl	%ebp
	ret	$16
	.p2align 4,,7
L42:
	cmpl	$520, %edx
	ja	L46
	cmpl	$519, %edx
	jae	L20
	leal	-516(%edx), %eax
	cmpl	$1, %eax
	ja	L41
	jmp	L20
	.p2align 4,,7
L50:
	cmpl	$257, %edx
	je	L25
	ja	L43
	cmpl	$28, %edx
	je	L38
	jbe	L51
	cmpl	$256, %edx
L47:
	jne	L41
	sarl	$16, %ecx
	testb	$1, %ch
	je	L29
	movl	%ecx, %eax
	andl	$127, %eax
	movsbl	_mapex(%eax),%ecx
L29:
	andl	$127, %ecx
	jmp	L49
	.p2align 4,,7
L46:
	cmpl	$522, %edx
	je	L21
	cmpl	$1029, %edx
	je	L30
L41:
	movl	%ecx, 20(%ebp)
	movl	%ebx, 16(%ebp)
	movl	%edx, 12(%ebp)
	movl	%esi, 8(%ebp)
	leal	-8(%ebp), %esp
	popl	%ebx
	popl	%esi
	popl	%ebp
	jmp	_DefWindowProcA@16
L25:
	sarl	$16, %ecx
	testb	$1, %ch
	jne	L52
L26:
	andl	$127, %ecx
	orb	$-128, %cl
L49:
	movl	_SYSirqteclado, %eax
	movl	%ecx, _SYSKEY
	movl	%eax, _SYSEVENT
	leal	-8(%ebp), %esp
	xorl	%eax, %eax
	popl	%ebx
	popl	%esi
	popl	%ebp
	ret	$16
L21:
	movl	%ebx, %eax
	sarl	$31, %eax
	addl	$5, %eax
	movl	%eax, _SYSBM
	jmp	L12
L43:
	cmpl	$261, %edx
	je	L25
	jbe	L53
	cmpl	$512, %edx
	jne	L41
	movl	_SYSXYM, %edx
	cmpl	%ecx, %edx
	je	L12
	movl	_mcnt, %eax
	movl	%ecx, _SYSXYM
	movl	%edx, _mbuff(,%eax,4)
	incl	%eax
	andl	$127, %eax
	movl	%eax, _mcnt
	jmp	L12
L30:
	movl	%ecx, %eax
	andl	$65535, %eax
	cmpl	$8, %eax
	je	L35
	jg	L36
	decl	%eax
	jne	L12
	pushl	$0
	pushl	$1024
	movl	_buffernet, %eax
	pushl	%eax
	movl	_soc, %eax
	pushl	%eax
	call	_recv@16
	movl	_buffernet, %edx
	movl	%eax, _buffersize
	movb	$0, (%eax,%edx)
	jmp	L12
	.p2align 4,,7
L52:
	movl	%ecx, %eax
	andl	$127, %eax
	movsbl	_mapex(%eax),%ecx
	jmp	L26
L51:
	cmpl	$2, %edx
	jne	L41
	subl	$12, %esp
	movl	$_ultimapalabra, _SYSEVENT
	movl	$2, _rebotea
	pushl	$0
	call	_PostQuitMessage@4
	addl	$12, %esp
	jmp	L12
L53:
	cmpl	$260, %edx
	jmp	L47
L35:
	pushl	%eax
	pushl	$0
	pushl	$0
	pushl	%ebx
	call	_accept@12
	movl	%eax, _soc
	popl	%eax
	jmp	L12
L38:
	movzbl	%bl,%eax
	movl	%eax, _active
	testl	%eax, %eax
	jne	L39
	pushl	%esi
	pushl	%esi
	pushl	$0
	pushl	$0
	call	_ChangeDisplaySettingsA@8
	popl	%ecx
	popl	%ebx
	jmp	L12
L36:
	cmpl	$16, %eax
	je	L35
	cmpl	$32, %eax
	jne	L12
	subl	$12, %esp
	movl	_soc, %eax
	pushl	%eax
	call	_closesocket@4
	addl	$12, %esp
	jmp	L12
L39:
	pushl	%edx
	pushl	%edx
	pushl	$1
	pushl	%esi
	call	_ShowWindow@8
	pushl	%eax
	pushl	%esi
	call	_UpdateWindow@4
	addl	$12, %esp
	jmp	L12
	.section .rdata,"dr"
LC154:
	.ascii "wb\0"
	.text
	.align 2
	.p2align 4,,15
.globl __Z10saveimagenPc
	.def	__Z10saveimagenPc;	.scl	2;	.type	32;	.endef
__Z10saveimagenPc:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$16, %esp
	pushl	$LC154
	movl	8(%ebp), %eax
	pushl	%eax
	call	_fopen
	addl	$16, %esp
	movl	%eax, _file
	testl	%eax, %eax
	jne	L56
	leave
	ret
	.p2align 4,,7
L56:
	pushl	%eax
	pushl	$1
	pushl	$4
	pushl	$_bootaddr
	call	_fwrite
	movl	_file, %eax
	pushl	%eax
	pushl	$1
	pushl	$4
	pushl	$_cntdato
	call	_fwrite
	addl	$32, %esp
	movl	_file, %eax
	pushl	%eax
	pushl	$1
	pushl	$4
	pushl	$_cntprog
	call	_fwrite
	movl	_file, %eax
	pushl	%eax
	movl	_cntprog, %ecx
	pushl	%ecx
	pushl	$1
	pushl	$_prog
	call	_fwrite
	addl	$32, %esp
	movl	_file, %edx
	pushl	%edx
	movl	_cntdato, %eax
	pushl	%eax
	pushl	$1
	pushl	$_data
	call	_fwrite
	movl	_file, %eax
	addl	$16, %esp
	movl	%eax, 8(%ebp)
	leave
	jmp	_fclose
	.section .rdata,"dr"
LC155:
	.ascii "rb\0"
	.text
	.align 2
	.p2align 4,,15
.globl __Z10loadimagenPc
	.def	__Z10loadimagenPc;	.scl	2;	.type	32;	.endef
__Z10loadimagenPc:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$16, %esp
	movl	$0, _bootaddr
	pushl	$LC155
	movl	8(%ebp), %eax
	pushl	%eax
	call	_fopen
	addl	$16, %esp
	movl	%eax, _file
	testl	%eax, %eax
	jne	L59
	leave
	ret
	.p2align 4,,7
L59:
	pushl	%eax
	pushl	$1
	pushl	$4
	pushl	$_bootaddr
	call	_fread
	movl	_file, %eax
	pushl	%eax
	pushl	$1
	pushl	$4
	pushl	$_cntdato
	call	_fread
	addl	$32, %esp
	movl	_file, %eax
	pushl	%eax
	pushl	$1
	pushl	$4
	pushl	$_cntprog
	call	_fread
	movl	_file, %ecx
	pushl	%ecx
	movl	_cntprog, %edx
	pushl	%edx
	pushl	$1
	pushl	$_prog
	call	_fread
	addl	$32, %esp
	movl	_file, %eax
	pushl	%eax
	movl	_cntdato, %eax
	pushl	%eax
	pushl	$1
	pushl	$_data
	call	_fread
	movl	_cntdato, %eax
	addl	$16, %esp
	addl	$_data, %eax
	movl	%eax, _memlibre
	movl	_file, %eax
	movl	%eax, 8(%ebp)
	leave
	jmp	_fclose
	.align 2
	.p2align 4,,15
.globl __Z7loaddirv
	.def	__Z7loaddirv;	.scl	2;	.type	32;	.endef
__Z7loaddirv:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%edi
	pushl	%esi
	pushl	%ebx
	subl	$608, %esp
	leal	-616(%ebp), %ebx
	movl	$0, _cntsubdirs
	movl	$0, _cntindex
	pushl	$260
	pushl	$_pathdata
	pushl	%ebx
	call	_strncpy
	subl	$12, %esp
	leal	-344(%ebp), %edi
	movl	$_mindice, %esi
	pushl	%ebx
	call	_strlen
	addl	$24, %esp
	movw	$10844, (%eax,%ebx)
	movb	$0, 2(%eax,%ebx)
	pushl	%edi
	pushl	%ebx
	call	_FindFirstFileA@8
	movl	%eax, %ebx
	popl	%eax
	cmpl	$-1, %ebx
	popl	%edx
	je	L79
	.p2align 4,,7
L62:
	cmpb	$46, -300(%ebp)
	je	L80
L65:
	testb	$16, -344(%ebp)
	je	L68
	movl	_cntsubdirs, %eax
	movl	%esi, _subdirs(,%eax,4)
	incl	%eax
	movl	%eax, _cntsubdirs
L69:
	pushl	%eax
	pushl	%eax
	leal	-300(%ebp), %eax
	pushl	%eax
	pushl	%esi
	call	_strcpy
	addl	$16, %esp
	jmp	L77
	.p2align 4,,7
L81:
	incl	%esi
L77:
	cmpb	$0, (%esi)
	jne	L81
	incl	%esi
L64:
	pushl	%eax
	pushl	%eax
	pushl	%edi
	pushl	%ebx
	call	_FindNextFileA@8
	popl	%edx
	testl	%eax, %eax
	popl	%ecx
	jne	L62
	subl	$12, %esp
	pushl	%ebx
L78:
	call	_FindClose@4
	leal	-12(%ebp), %esp
	popl	%ebx
	popl	%esi
	popl	%edi
	popl	%ebp
	ret
L68:
	movb	$32, %cl
	movl	-316(%ebp), %eax
	movl	_cntindex, %edx
	sall	%cl, %eax
	movl	-312(%ebp), %ecx
	movl	%esi, _indexdir(,%edx,4)
	addl	%ecx, %eax
	movl	%eax, _sizedir(,%edx,4)
	incl	%edx
	movl	%edx, _cntindex
	jmp	L69
L80:
	movb	-299(%ebp), %al
	testb	%al, %al
	je	L64
	cmpb	$46, %al
	jne	L65
	cmpb	$0, -298(%ebp)
	je	L64
	jmp	L65
L79:
	subl	$12, %esp
	pushl	$-1
	jmp	L78
	.section .rdata,"dr"
LC156:
	.ascii "%s%s\0"
	.text
	.align 2
	.p2align 4,,15
.globl __Z10interpretePh
	.def	__Z10interpretePh;	.scl	2;	.type	32;	.endef
__Z10interpretePh:
	pushl	%ebp
	orl	$-1, %eax
	movl	%esp, %ebp
	pushl	%edi
	pushl	%esi
	pushl	%ebx
	subl	$12, %esp
	movl	8(%ebp), %edx
	testl	%edx, %edx
	je	L82
	movl	_gr_buffer, %eax
	movl	%edx, %ebx
	movl	$0, _SYSirqteclado
	movl	$0, _SYSirqsonido
	movl	$0, _SYSirqred
	movl	$0, _SYSEVENT
	movl	$1, _mcnt
	movl	%eax, -20(%ebp)
	movl	$_RSP, -16(%ebp)
	movl	$_ultimapalabra, _RSP
	movl	$_PSP, %esi
	xorl	%edi, %edi
	movl	$0, _PSP
	.p2align 4,,7
L323:
	xorl	%edx, %edx
	movb	(%ebx), %dl
	incl	%ebx
	cmpl	$149, %edx
	jbe	L325
L298:
	addl	$4, %esi
	movl	%edi, (%esi)
	leal	-150(%edx), %edi
	xorl	%edx, %edx
	movb	(%ebx), %dl
	incl	%ebx
	cmpl	$149, %edx
	ja	L298
L325:
	jmp	*L299(,%edx,4)
	.section .rdata,"dr"
	.align 4
L299:
	.long	L87
	.long	L88
	.long	L89
	.long	L90
	.long	L91
	.long	L92
	.long	L117
	.long	L93
	.long	L95
	.long	L97
	.long	L99
	.long	L101
	.long	L105
	.long	L107
	.long	L109
	.long	L111
	.long	L103
	.long	L113
	.long	L115
	.long	L119
	.long	L120
	.long	L121
	.long	L122
	.long	L123
	.long	L124
	.long	L125
	.long	L126
	.long	L127
	.long	L128
	.long	L129
	.long	L130
	.long	L131
	.long	L132
	.long	L133
	.long	L134
	.long	L135
	.long	L136
	.long	L137
	.long	L138
	.long	L139
	.long	L140
	.long	L141
	.long	L142
	.long	L143
	.long	L144
	.long	L145
	.long	L146
	.long	L147
	.long	L148
	.long	L149
	.long	L150
	.long	L151
	.long	L153
	.long	L154
	.long	L155
	.long	L156
	.long	L157
	.long	L158
	.long	L159
	.long	L160
	.long	L161
	.long	L162
	.long	L163
	.long	L164
	.long	L165
	.long	L166
	.long	L167
	.long	L168
	.long	L169
	.long	L170
	.long	L171
	.long	L172
	.long	L173
	.long	L174
	.long	L175
	.long	L176
	.long	L177
	.long	L263
	.long	L267
	.long	L271
	.long	L275
	.long	L240
	.long	L241
	.long	L243
	.long	L246
	.long	L249
	.long	L252
	.long	L259
	.long	L178
	.long	L183
	.long	L181
	.long	L182
	.long	L184
	.long	L185
	.long	L186
	.long	L187
	.long	L189
	.long	L191
	.long	L190
	.long	L192
	.long	L193
	.long	L198
	.long	L199
	.long	L200
	.long	L188
	.long	L201
	.long	L202
	.long	L203
	.long	L204
	.long	L205
	.long	L206
	.long	L207
	.long	L208
	.long	L209
	.long	L210
	.long	L211
	.long	L212
	.long	L215
	.long	L216
	.long	L217
	.long	L218
	.long	L219
	.long	L220
	.long	L221
	.long	L222
	.long	L224
	.long	L226
	.long	L228
	.long	L229
	.long	L230
	.long	L231
	.long	L232
	.long	L233
	.long	L236
	.long	L237
	.long	L279
	.long	L281
	.long	L284
	.long	L285
	.long	L286
	.long	L287
	.long	L288
	.long	L289
	.long	L290
	.long	L291
	.long	L293
	.long	L294
	.long	L295
	.long	L292
	.long	L296
	.text
L193:
	movl	$LC3, _exestr
	testl	%edi, %edi
	jne	L326
	movl	$1, _rebotea
L192:
	xorl	%eax, %eax
L82:
	leal	-12(%ebp), %esp
	popl	%ebx
	popl	%esi
	popl	%edi
	popl	%ebp
	ret
L190:
	subl	$12, %esp
	addl	$4, %esi
	pushl	$_sit
	call	_time
	movl	$_sit, (%esp)
	call	_localtime
	movl	%edi, (%esi)
	addl	$4, %esi
	addl	$16, %esp
	movl	20(%eax), %edi
	movl	%eax, _sitime
	addl	$1900, %edi
	movl	%edi, (%esi)
	addl	$4, %esi
	movl	16(%eax), %edi
	incl	%edi
	movl	%edi, (%esi)
	movl	12(%eax), %edi
	jmp	L323
L191:
	subl	$12, %esp
	addl	$4, %esi
	pushl	$_sit
	call	_time
	movl	$_sit, (%esp)
	call	_localtime
	movl	%edi, (%esi)
	addl	$4, %esi
	addl	$16, %esp
	movl	(%eax), %edi
	movl	%eax, _sitime
	movl	%edi, (%esi)
	addl	$4, %esi
	movl	4(%eax), %edi
	movl	%edi, (%esi)
	movl	8(%eax), %edi
	jmp	L323
L189:
	addl	$4, %esi
	movl	%edi, (%esi)
	call	_timeGetTime@0
	movl	%eax, %edi
	jmp	L323
L187:
	subl	$12, %esp
	pushl	%edi
	call	__Z6getjoyi
	addl	$16, %esp
	movl	%eax, %edi
	jmp	L323
L186:
	addl	$4, %esi
	movl	%edi, (%esi)
	movl	_cntJoy, %edi
	jmp	L323
L185:
	addl	$4, %esi
	movl	%edi, (%esi)
	movb	_SYSKEY, %cl
	andl	$255, %ecx
	movl	%ecx, %edi
	jmp	L323
L184:
	movl	%edi, _SYSirqteclado
	movl	(%esi), %edi
	subl	$4, %esi
	jmp	L323
L182:
	addl	$4, %esi
	movl	%edi, (%esi)
	movl	_SYSBM, %edi
	jmp	L323
L181:
	addl	$4, %esi
	movl	%edi, (%esi)
	addl	$4, %esi
	movl	_SYSXYM, %edx
	movl	%edx, %edi
	movzwl	%dx,%eax
	sarl	$16, %edi
	movl	%eax, (%esi)
	jmp	L323
L183:
	addl	$4, %esi
	movl	%edi, (%esi)
	movl	$_mbuff, %edi
	movl	_mcnt, %eax
	movl	$1, _mcnt
	decl	%eax
	movl	%eax, _mbuff
	jmp	L323
L178:
	subl	$12, %esp
	pushl	$1
	pushl	$0
	pushl	$0
	movl	_hWnd, %ecx
	pushl	%ecx
	pushl	$_msg
	call	_PeekMessageA@20
	addl	$12, %esp
	testl	%eax, %eax
	je	L323
	subl	$12, %esp
	pushl	$_msg
	call	_DispatchMessageA@4
	movl	_SYSEVENT, %eax
	addl	$12, %esp
	testl	%eax, %eax
	je	L323
	movl	-16(%ebp), %edx
	addl	$4, %edx
	movl	%edx, -16(%ebp)
	movl	-16(%ebp), %edx
	movl	%ebx, (%edx)
	movl	%eax, %ebx
	movl	$0, _SYSEVENT
	jmp	L323
L259:
	testl	%edi, %edi
	jne	L327
L261:
	subl	$8, %esi
	movl	(%esi), %edi
	subl	$4, %esi
	jmp	L323
L252:
	testl	%edi, %edi
	jne	L328
	movl	(%esi), %eax
L254:
	movl	%eax, %edi
	subl	$4, %esi
	jmp	L323
L249:
	movl	%edi, %eax
	cmpl	_cntsubdirs, %edi
	setge	%dl
	shrl	$31, %eax
	orb	%al, %dl
	je	L250
	xorl	%edi, %edi
	jmp	L323
L246:
	movl	%edi, %eax
	cmpl	_cntindex, %edi
	setge	%dl
	shrl	$31, %eax
	orb	%al, %dl
	je	L247
	xorl	%edi, %edi
	jmp	L323
L275:
	movl	-4(%esi), %edx
	movl	(%esi), %ecx
	addl	%edi, %edx
	addl	%edi, %ecx
	jmp	L322
L329:
	decl	%ecx
	decl	%edx
	movb	(%ecx), %al
	movb	%al, (%edx)
L322:
	decl	%edi
	cmpl	$-1, %edi
	jne	L329
	subl	$8, %esi
	movl	(%esi), %edi
	subl	$4, %esi
	jmp	L323
L241:
	testl	%edi, %edi
	jne	L330
	movl	(%esi), %edi
	subl	$4, %esi
	jmp	L323
L240:
	addl	$4, %esi
	movl	%edi, (%esi)
	movl	_memlibre, %edi
	jmp	L323
L267:
	leal	0(,%edi,4), %eax
	movl	-4(%esi), %edx
	movl	(%esi), %ecx
	addl	%eax, %edx
	addl	%eax, %ecx
	jmp	L320
L331:
	subl	$4, %ecx
	subl	$4, %edx
	movl	(%ecx), %eax
	movl	%eax, (%edx)
L320:
	decl	%edi
	cmpl	$-1, %edi
	jne	L331
	subl	$8, %esi
	movl	(%esi), %edi
	subl	$4, %esi
	jmp	L323
L263:
	movl	-4(%esi), %edx
	movl	(%esi), %ecx
	jmp	L319
L332:
	movl	(%ecx), %eax
	addl	$4, %ecx
	movl	%eax, (%edx)
	addl	$4, %edx
L319:
	decl	%edi
	cmpl	$-1, %edi
	jne	L332
	subl	$8, %esi
	movl	(%esi), %edi
	subl	$4, %esi
	jmp	L323
L271:
	movl	-4(%esi), %edx
	movl	(%esi), %ecx
	jmp	L321
L333:
	movb	(%ecx), %al
	incl	%ecx
	movb	%al, (%edx)
	incl	%edx
L321:
	decl	%edi
	cmpl	$-1, %edi
	jne	L333
	subl	$8, %esi
	movl	(%esi), %edi
	subl	$4, %esi
	jmp	L323
L243:
	movl	%edi, %eax
	cmpl	_cntindex, %edi
	setge	%dl
	shrl	$31, %eax
	orb	%al, %dl
	je	L244
	xorl	%edi, %edi
	jmp	L323
L177:
	movl	(%esi), %eax
	subl	$4, %esi
	movw	%ax, (%edi)
	addl	$2, %edi
	jmp	L323
L105:
	movl	(%esi), %eax
	movsbl	(%ebx),%edx
	incl	%ebx
	cmpl	%edi, %eax
	jl	L106
	addl	%edx, %ebx
L106:
	movl	%eax, %edi
	subl	$4, %esi
	jmp	L323
L101:
	movl	(%esi), %eax
	movsbl	(%ebx),%edx
	incl	%ebx
	cmpl	%edi, %eax
	je	L102
	addl	%edx, %ebx
L102:
	movl	%eax, %edi
	subl	$4, %esi
	jmp	L323
L144:
	xorl	$-1, %edi
	jmp	L323
L232:
	subl	$12, %esp
	pushl	$0
	pushl	$0
	pushl	$304
	pushl	%edi
	pushl	$-1
	call	_FSOUND_Sample_Load@20
	movl	%eax, %edi
	addl	$12, %esp
	jmp	L323
L231:
	movl	%edi, _mTex
	call	__Z7fillTexv
	movl	(%esi), %edi
	subl	$4, %esi
	jmp	L323
L230:
	call	__Z7fillRadv
	jmp	L323
L229:
	call	__Z7fillLinv
	jmp	L323
L228:
	call	__Z7fillSolv
	jmp	L323
L226:
	movl	(%esi), %eax
	subl	$4, %esi
	movl	%eax, _MA
	movl	%edi, _MB
	movl	(%esi), %edi
	subl	$4, %esi
	jmp	L323
L224:
	movl	(%esi), %eax
	subl	$4, %esi
	movl	%eax, _MTX
	movl	%edi, _MTY
	movl	(%esi), %edi
	subl	$4, %esi
	jmp	L323
L222:
	movl	(%esi), %eax
	subl	$4, %esi
	movl	%edi, _col2
	movl	%eax, _col1
	movl	(%esi), %edi
	subl	$4, %esi
	jmp	L323
L221:
	call	__Z11gr_drawPoliv
	jmp	L323
L220:
	movl	%edi, _gy2
	movl	(%esi), %eax
	subl	$4, %esi
	movl	%eax, _gx2
	movl	(%esi), %edi
	pushl	%ecx
	pushl	%ecx
	subl	$4, %esi
	movl	_gy2, %edx
	pushl	%edx
	pushl	%eax
	movl	_gyc, %eax
	pushl	%eax
	movl	_gxc, %eax
	pushl	%eax
	movl	_gy1, %eax
	pushl	%eax
	movl	_gx1, %eax
	pushl	%eax
	call	__Z10gr_psplineiiiiii
	movl	_gx2, %eax
	addl	$32, %esp
	movl	%eax, _gx1
	movl	_gy2, %eax
	movl	%eax, _gy1
	jmp	L323
L219:
	movl	%edi, _gy2
	movl	(%esi), %eax
	subl	$4, %esi
	movl	%eax, _gx2
	movl	_gy2, %edx
	movl	(%esi), %edi
	pushl	%edx
	pushl	%eax
	subl	$4, %esi
	movl	_gy1, %eax
	pushl	%eax
	movl	_gx1, %eax
	pushl	%eax
	call	__Z12gr_psegmentoiiii
	movl	_gx2, %eax
	addl	$16, %esp
	movl	%eax, _gx1
	movl	_gy2, %eax
	movl	%eax, _gy1
	jmp	L323
L218:
	movl	%edi, _gy2
	movl	(%esi), %eax
	subl	$4, %esi
	movl	%eax, _gx2
	movl	(%esi), %edi
	pushl	%ecx
	pushl	%ecx
	subl	$4, %esi
	movl	_gy2, %edx
	pushl	%edx
	pushl	%eax
	movl	_gyc, %eax
	pushl	%eax
	movl	_gxc, %eax
	pushl	%eax
	movl	_gy1, %eax
	pushl	%eax
	movl	_gx1, %ecx
	pushl	%ecx
	call	__Z9gr_splineiiiiii
	movl	_gx2, %eax
	addl	$32, %esp
	movl	%eax, _gx1
	movl	_gy2, %eax
	movl	%eax, _gy1
	jmp	L323
L217:
	movl	%edi, _gy2
	movl	(%esi), %eax
	subl	$4, %esi
	movl	%eax, _gx2
	movl	_gy2, %edx
	movl	(%esi), %edi
	pushl	%edx
	pushl	%eax
	subl	$4, %esi
	movl	_gy1, %eax
	pushl	%eax
	movl	_gx1, %eax
	pushl	%eax
	call	__Z7gr_lineiiii
	movl	_gx2, %eax
	addl	$16, %esp
	movl	%eax, _gx1
	movl	_gy2, %eax
	movl	%eax, _gy1
	jmp	L323
L216:
	movl	%edi, _gyc
	movl	(%esi), %eax
	subl	$4, %esi
	movl	%eax, _gxc
	movl	(%esi), %edi
	subl	$4, %esi
	jmp	L323
L215:
	movl	%edi, _gy1
	movl	(%esi), %eax
	subl	$4, %esi
	movl	%eax, _gx1
	movl	(%esi), %edi
	subl	$4, %esi
	jmp	L323
L212:
	cmpl	$254, %edi
	jle	L213
	call	__Z8gr_solidv
	movl	(%esi), %edi
	subl	$4, %esi
	jmp	L323
L211:
	addl	$4, %esi
	movl	%edi, (%esi)
	movl	_gr_color1, %edi
	jmp	L323
L210:
	movl	%edi, _gr_color1
	movl	(%esi), %edi
	subl	$4, %esi
	jmp	L323
L203:
	movl	-20(%ebp), %eax
	leal	(%eax,%edi,4), %eax
	movl	(%esi), %edi
	subl	$4, %esi
	movl	%eax, -20(%ebp)
	jmp	L323
L202:
	pushl	%eax
	pushl	%eax
	pushl	%edi
	movl	(%esi), %ecx
	subl	$4, %esi
	pushl	%ecx
	call	*_setxyf
	movl	(%esi), %edi
	addl	$16, %esp
	subl	$4, %esi
	movl	%eax, -20(%ebp)
	jmp	L323
L201:
	addl	$4, %esi
	movl	%edi, (%esi)
	movl	_gr_buffer, %edi
	jmp	L323
L188:
	call	__Z9gr_redrawv
	jmp	L323
L200:
	call	__Z9gr_clrscrv
	jmp	L323
L199:
	addl	$4, %esi
	movl	%edi, (%esi)
	movl	_gr_alto, %edi
	jmp	L323
L198:
	addl	$4, %esi
	movl	%edi, (%esi)
	movl	_gr_ancho, %edi
	jmp	L323
L207:
	call	__Z8gr_toxfbv
	jmp	L323
L209:
	movl	%edi, _gr_color2
	movl	(%esi), %edi
	subl	$4, %esi
	jmp	L323
L208:
	call	__Z8gr_xfbtov
	jmp	L323
L205:
	addl	$4, %esi
	movl	-20(%ebp), %ecx
	movl	%edi, (%esi)
	movl	(%ecx), %edi
	jmp	L323
L204:
	movl	-20(%ebp), %edx
	movl	%edi, (%edx)
	addl	$4, %edx
	movl	(%esi), %edi
	subl	$4, %esi
	movl	%edx, -20(%ebp)
	jmp	L323
L206:
	addl	$4, %esi
	movl	%edi, (%esi)
	movl	_XFB, %edi
	jmp	L323
L295:
	addl	$4, %esi
	movl	%edi, (%esi)
	addl	$4, %esi
	movl	_cWidthPels, %edi
	movl	%edi, (%esi)
	movl	_cHeightPels, %edi
	jmp	L323
L294:
	subl	$8, %esi
	movl	(%esi), %edi
	subl	$4, %esi
	jmp	L323
L293:
	pushl	%edx
	pushl	%edx
	movl	_hfntPrev, %eax
	pushl	%eax
	movl	_phDC, %eax
	pushl	%eax
	call	_SelectObject@8
	pushl	%eax
	movl	_hfnt, %eax
	pushl	%eax
	call	_DeleteObject@4
	movl	%edi, (%esp)
	pushl	$_plf+28
	call	_strcpy
	addl	$12, %esp
	movl	(%esi), %eax
	movl	$400, _plf+16
	movl	%eax, _plf+8
	pushl	$72
	pushl	$90
	movl	_phDC, %eax
	pushl	%eax
	call	_GetDeviceCaps@8
	pushl	%eax
	movl	-4(%esi), %eax
	subl	$8, %esi
	pushl	%eax
	call	_MulDiv@12
	negl	%eax
	movl	%eax, _plf
	pushl	%edi
	pushl	%edi
	pushl	$_plf
	call	_CreateFontIndirectA@4
	movl	%eax, _hfnt
	movl	%eax, (%esp)
	movl	_phDC, %ecx
	pushl	%ecx
	call	_SelectObject@8
	movl	%eax, _hfntPrev
	movl	(%esi), %edi
	popl	%eax
	subl	$4, %esi
	popl	%edx
	jmp	L323
L291:
	subl	$12, %esp
	pushl	%edi
	call	_strlen
	movl	%eax, (%esp)
	pushl	%edi
	pushl	$0
	pushl	$0
	movl	_phDC, %eax
	pushl	%eax
	call	_TextOutA@20
	movl	(%esi), %edi
	addl	$12, %esp
	subl	$4, %esi
	jmp	L323
L290:
	pushl	%eax
	pushl	%edi
	movl	(%esi), %eax
	subl	$4, %esi
	pushl	%eax
	movl	_phDC, %eax
	pushl	%eax
	call	_LineTo@12
	movl	(%esi), %edi
	popl	%eax
	subl	$4, %esi
	jmp	L323
L289:
	pushl	$0
	pushl	%edi
	movl	(%esi), %ecx
	subl	$4, %esi
	pushl	%ecx
	movl	_phDC, %edx
	pushl	%edx
	call	_MoveToEx@16
	movl	(%esi), %edi
	subl	$4, %esi
	jmp	L323
L288:
	subl	$12, %esp
	movl	_phDC, %eax
	pushl	%eax
	call	_EndPage@4
	movl	%eax, _lpError
	movl	_phDC, %eax
	pushl	%eax
	call	_EndDoc@4
	addl	$12, %esp
	movl	%eax, _lpError
	jmp	L323
L287:
	pushl	%eax
	pushl	%eax
	pushl	$_di
	movl	_phDC, %eax
	pushl	%eax
	call	_StartDocA@8
	movl	%eax, _lpError
	pushl	%eax
	movl	_phDC, %eax
	pushl	%eax
	call	_StartPage@4
	addl	$12, %esp
	movl	%eax, _lpError
	jmp	L323
L286:
	subl	$12, %esp
	movl	_soc, %edx
	pushl	%edx
	call	_closesocket@4
	addl	$12, %esp
	jmp	L323
L285:
	movl	(%esi), %eax
	subl	$4, %esi
	movl	%eax, _SYSirqred
	movl	%edi, _buffernet
	movl	(%esi), %edi
	subl	$4, %esi
	jmp	L323
L284:
	pushl	$0
	pushl	%edi
	movl	(%esi), %edi
	subl	$4, %esi
	pushl	%edi
	movl	_soc, %ecx
	pushl	%ecx
	call	_send@16
	movl	(%esi), %edi
	subl	$4, %esi
	jmp	L323
L281:
	subl	$12, %esp
	movl	%edi, %eax
	andl	$65535, %eax
	movw	$2, _naddr
	pushl	%eax
	call	_htons@4
	movl	(%esi), %edi
	movw	%ax, _naddr+2
	pushl	%edi
	call	_gethostbyname@4
	subl	$4, %esi
	addl	$12, %esp
	movl	%eax, _host
	testl	%eax, %eax
	jne	L282
	xorl	%edi, %edi
	jmp	L323
L279:
	subl	$12, %esp
	movl	%edi, %eax
	andl	$65535, %eax
	movw	$2, _naddr
	pushl	%eax
	call	_htons@4
	movw	%ax, _naddr+2
	pushl	$0
	call	_htonl@4
	movl	%eax, _naddr+4
	popl	%ecx
	popl	%eax
	pushl	$6
	pushl	$1
	pushl	$2
	call	_socket@12
	movl	%eax, _soc
	pushl	$16
	pushl	$_naddr
	pushl	%eax
	call	_bind@12
	popl	%edx
	incl	%eax
	jne	L280
	xorl	%edi, %edi
	jmp	L323
L236:
	subl	$12, %esp
	pushl	%edi
	call	_FMUSIC_LoadSong@4
	movl	%eax, %edi
	addl	$12, %esp
	jmp	L323
L237:
	testl	%edi, %edi
	je	L238
	subl	$12, %esp
	pushl	%edi
	call	_FMUSIC_PlaySong@4
	movl	(%esi), %edi
	addl	$12, %esp
	subl	$4, %esi
	jmp	L323
L233:
	testl	%edi, %edi
	je	L234
	pushl	%eax
	pushl	%eax
	pushl	%edi
	pushl	$-1
	call	_FSOUND_PlaySound@8
	popl	%edi
	movl	(%esi), %edi
	popl	%eax
	subl	$4, %esi
	jmp	L323
L91:
	movl	(%ebx), %ebx
	jmp	L323
L90:
	movl	-16(%ebp), %eax
	movl	(%ebx), %edx
	addl	$4, %eax
	addl	$4, %ebx
	movl	%eax, -16(%ebp)
	movl	-16(%ebp), %ecx
	movl	%ebx, (%ecx)
	movl	%edx, %ebx
	jmp	L323
L87:
	movl	-16(%ebp), %edx
	movl	(%edx), %ebx
	subl	$4, %edx
	movl	%edx, -16(%ebp)
	jmp	L323
L296:
	pushl	%ecx
	pushl	$68
	pushl	$0
	pushl	$_StartupInfo
	call	_memset
	movl	$68, _StartupInfo
	popl	%eax
	popl	%edx
	pushl	$_ProcessInfo
	pushl	$_StartupInfo
	pushl	$0
	pushl	$0
	pushl	$0
	pushl	$0
	pushl	$0
	pushl	$0
	pushl	%edi
	pushl	$0
	call	_CreateProcessA@40
	popl	%edx
	testl	%eax, %eax
	popl	%ecx
	jne	L334
	movl	(%esi), %edi
	subl	$4, %esi
	jmp	L323
L292:
	pushl	$_tsize
	pushl	%eax
	pushl	%eax
	pushl	%edi
	call	_strlen
	addl	$12, %esp
	addl	$4, %esi
	pushl	%eax
	pushl	%edi
	movl	_phDC, %ecx
	pushl	%ecx
	call	_GetTextExtentPointA@16
	movl	_tsize, %eax
	movl	_tsize+4, %edi
	movl	%eax, (%esi)
	jmp	L323
L89:
	movl	(%ebx), %edx
	addl	$4, %esi
	addl	$4, %ebx
	movl	%edi, (%esi)
	movl	(%edx), %edi
	jmp	L323
L88:
	addl	$4, %esi
	movl	%edi, (%esi)
	movl	(%ebx), %edi
	addl	$4, %ebx
	jmp	L323
L95:
	movsbl	(%ebx),%edx
	incl	%ebx
	testl	%edi, %edi
	jg	L323
	addl	%edx, %ebx
	jmp	L323
L93:
	movsbl	(%ebx),%edx
	incl	%ebx
	testl	%edi, %edi
	je	L323
	addl	%edx, %ebx
	jmp	L323
L117:
	movl	%edi, %edx
	movl	(%esi), %edi
	subl	$4, %esi
	testl	%edx, %edx
	je	L323
	movl	-16(%ebp), %eax
	addl	$4, %eax
	movl	%eax, -16(%ebp)
	movl	-16(%ebp), %eax
	movl	%ebx, (%eax)
	movl	%edx, %ebx
	jmp	L323
L92:
	movsbl	(%ebx),%edx
	leal	1(%edx,%ebx), %ebx
	jmp	L323
L99:
	movsbl	(%ebx),%edx
	incl	%ebx
	testl	%edi, %edi
	jne	L323
	addl	%edx, %ebx
	jmp	L323
L97:
	movsbl	(%ebx),%edx
	incl	%ebx
	testl	%edi, %edi
	js	L323
	addl	%edx, %ebx
	jmp	L323
L161:
	movl	(%esi), %eax
	movl	%edi, %ecx
	sall	%cl, %eax
	movl	%eax, %edi
	subl	$4, %esi
	jmp	L323
L160:
	addl	%edi, %edi
	jmp	L323
L159:
	sarl	%edi
	jmp	L323
L158:
	decl	%edi
	jmp	L323
L157:
	addl	$4, %edi
	jmp	L323
L156:
	incl	%edi
	jmp	L323
L155:
	negl	%edi
	jmp	L323
L154:
	movl	%edi, %edx
	sarl	$31, %edx
	addl	%edx, %edi
	xorl	%edx, %edi
	jmp	L323
L153:
	movl	(%esi), %eax
	subl	$4, %esi
	movl	%eax, %edx
	sarl	$31, %edx
	idivl	%edi
	movl	%edx, %edi
	jmp	L323
L151:
	testl	%edi, %edi
	jne	L152
	subl	$4, %esi
	movl	(%esi), %edi
	subl	$4, %esi
	jmp	L323
L150:
	movl	(%esi), %eax
	movl	%edi, %ecx
	imull	-4(%esi)
	shrdl	%cl,%edx, %eax
	sarl	%cl, %edx
	andl	$32, %ecx
	je	L318
	movl	%edx, %eax
L318:
	movl	%eax, %edi
	subl	$8, %esi
	jmp	L323
	.p2align 4,,7
L148:
	movl	(%esi), %edx
	subl	$4, %esi
	movl	%edx, %eax
	sarl	$31, %edx
	idivl	%edi
	movl	%eax, %edi
	jmp	L323
L147:
	movl	(%esi), %eax
	subl	$4, %esi
	imull	%eax, %edi
	jmp	L323
L146:
	movl	(%esi), %eax
	subl	$4, %esi
	subl	%edi, %eax
	movl	%eax, %edi
	jmp	L323
L145:
	movl	(%esi), %eax
	subl	$4, %esi
	addl	%eax, %edi
	jmp	L323
L149:
	movl	(%esi), %edx
	movl	-4(%esi), %ecx
	imull	%ecx, %edx
	movl	%edx, %eax
	subl	$8, %esi
	sarl	$31, %edx
	idivl	%edi
	movl	%eax, %edi
	jmp	L323
L169:
	movl	(%esi), %eax
	movl	(%edi), %edx
	subl	$4, %esi
	addl	%eax, %edx
	movl	%edx, (%edi)
	movl	(%esi), %edi
	subl	$4, %esi
	jmp	L323
L168:
	movl	(%esi), %eax
	subl	$4, %esi
	movw	%ax, (%edi)
	movl	(%esi), %edi
	subl	$4, %esi
	jmp	L323
L167:
	movl	(%esi), %eax
	subl	$4, %esi
	movb	%al, (%edi)
	movl	(%esi), %edi
	subl	$4, %esi
	jmp	L323
L166:
	movl	(%esi), %eax
	subl	$4, %esi
	movl	%eax, (%edi)
	movl	(%esi), %edi
	subl	$4, %esi
	jmp	L323
L165:
	movswl	(%edi),%edi
	jmp	L323
L164:
	movsbl	(%edi),%edi
	jmp	L323
L163:
	movl	(%edi), %edi
	jmp	L323
L162:
	movl	(%esi), %eax
	movl	%edi, %ecx
	sarl	%cl, %eax
	movl	%eax, %edi
	subl	$4, %esi
	jmp	L323
L173:
	movl	(%esi), %eax
	subl	$4, %esi
	movl	%eax, (%edi)
	addl	$4, %edi
	jmp	L323
L172:
	addl	$4, %esi
	leal	4(%edi), %eax
	movl	%eax, (%esi)
	movl	(%edi), %edi
	jmp	L323
L171:
	movw	(%edi), %ax
	addw	(%esi), %ax
	subl	$4, %esi
	movw	%ax, (%edi)
	movl	(%esi), %edi
	subl	$4, %esi
	jmp	L323
L170:
	movb	(%edi), %al
	addb	(%esi), %al
	subl	$4, %esi
	movb	%al, (%edi)
	movl	(%esi), %edi
	subl	$4, %esi
	jmp	L323
L175:
	movl	(%esi), %eax
	subl	$4, %esi
	movb	%al, (%edi)
	incl	%edi
	jmp	L323
L174:
	addl	$4, %esi
	leal	1(%edi), %eax
	movl	%eax, (%esi)
	movsbl	(%edi),%edi
	jmp	L323
L176:
	leal	2(%edi), %eax
	addl	$4, %esi
	movswl	(%edi),%edi
	movl	%eax, (%esi)
	jmp	L323
L128:
	movl	(%esi), %edx
	addl	$4, %esi
	movl	%edi, (%esi)
	addl	$4, %esi
	movl	%edx, (%esi)
	jmp	L323
L127:
	movl	%edi, %edx
	movl	(%esi), %eax
	movl	-4(%esi), %edi
	movl	%edx, (%esi)
	movl	%eax, -4(%esi)
	jmp	L323
L126:
	subl	$4, %esi
	jmp	L323
L125:
	movl	(%esi), %edx
	movl	%edi, (%esi)
	movl	%edx, %edi
	jmp	L323
L124:
	addl	$4, %esi
	movl	%edi, (%esi)
	movl	-16(%esi), %edi
	jmp	L323
L123:
	addl	$4, %esi
	movl	%edi, (%esi)
	movl	-12(%esi), %edi
	jmp	L323
L122:
	addl	$4, %esi
	movl	%edi, (%esi)
	movl	-8(%esi), %edi
	jmp	L323
L121:
	addl	$4, %esi
	movl	%edi, (%esi)
	movl	-4(%esi), %edi
	jmp	L323
L120:
	movl	(%esi), %edi
	subl	$4, %esi
	jmp	L323
L119:
	addl	$4, %esi
	movl	%edi, (%esi)
	jmp	L323
L115:
	movl	(%esi), %eax
	movsbl	(%ebx),%edx
	incl	%ebx
	testl	%edi, %eax
	je	L116
	addl	%edx, %ebx
L116:
	movl	%eax, %edi
	subl	$4, %esi
	jmp	L323
L113:
	movl	(%esi), %eax
	movsbl	(%ebx),%edx
	incl	%ebx
	testl	%edi, %eax
	jne	L114
	addl	%edx, %ebx
L114:
	movl	%eax, %edi
	subl	$4, %esi
	jmp	L323
L103:
	movl	(%esi), %eax
	movsbl	(%ebx),%edx
	incl	%ebx
	cmpl	%edi, %eax
	je	L335
	movl	%eax, %edi
	subl	$4, %esi
	jmp	L323
L109:
	movl	(%esi), %eax
	movsbl	(%ebx),%edx
	incl	%ebx
	cmpl	%edi, %eax
	jle	L110
	addl	%edx, %ebx
L110:
	movl	%eax, %edi
	subl	$4, %esi
	jmp	L323
L107:
	movl	(%esi), %eax
	movsbl	(%ebx),%edx
	incl	%ebx
	cmpl	%edi, %eax
	jg	L108
	addl	%edx, %ebx
L108:
	movl	%eax, %edi
	subl	$4, %esi
	jmp	L323
L111:
	movl	(%esi), %eax
	movsbl	(%ebx),%edx
	incl	%ebx
	cmpl	%edi, %eax
	jge	L112
	addl	%edx, %ebx
L112:
	movl	%eax, %edi
	subl	$4, %esi
	jmp	L323
L136:
	addl	$4, %esi
	movl	-16(%ebp), %eax
	movl	%edi, (%esi)
	movl	(%eax), %edi
	jmp	L323
L140:
	movl	-16(%ebp), %eax
	subl	$4, %eax
	movl	%eax, -16(%ebp)
	jmp	L323
L139:
	movl	-16(%ebp), %edx
	movl	(%edx), %eax
	movl	%edi, (%eax)
	addl	$4, %eax
	movl	(%esi), %edi
	subl	$4, %esi
	movl	%eax, (%edx)
	jmp	L323
L138:
	movl	-16(%ebp), %ecx
	addl	$4, %esi
	movl	(%ecx), %eax
	movl	%edi, (%esi)
	movl	(%eax), %edi
	addl	$4, %eax
	movl	%eax, (%ecx)
	jmp	L323
L137:
	movl	-16(%ebp), %edx
	movl	(%edx), %ecx
	addl	%edi, %ecx
	movl	%ecx, (%edx)
	movl	(%esi), %edi
	subl	$4, %esi
	jmp	L323
L142:
	movl	(%esi), %eax
	subl	$4, %esi
	orl	%eax, %edi
	jmp	L323
L141:
	movl	(%esi), %eax
	subl	$4, %esi
	andl	%eax, %edi
	jmp	L323
L143:
	movl	(%esi), %eax
	subl	$4, %esi
	xorl	%eax, %edi
	jmp	L323
L132:
	addl	$4, %esi
	movl	%edi, (%esi)
	movl	-12(%esi), %edi
	addl	$4, %esi
	movl	%edi, (%esi)
	movl	-12(%esi), %edi
	jmp	L323
L131:
	subl	$12, %esi
	movl	(%esi), %edi
	subl	$4, %esi
	jmp	L323
L130:
	subl	$8, %esi
	movl	(%esi), %edi
	subl	$4, %esi
	jmp	L323
L129:
	subl	$4, %esi
	movl	(%esi), %edi
	subl	$4, %esi
	jmp	L323
L134:
	movl	-16(%ebp), %eax
	addl	$4, %eax
	movl	%eax, -16(%ebp)
	movl	-16(%ebp), %edx
	movl	%edi, (%edx)
	movl	(%esi), %edi
	subl	$4, %esi
	jmp	L323
L133:
	movl	(%esi), %edx
	movl	-8(%esi), %eax
	movl	%edx, -8(%esi)
	movl	%edi, %edx
	movl	-4(%esi), %edi
	movl	%eax, (%esi)
	movl	%edx, -4(%esi)
	jmp	L323
L135:
	movl	-16(%ebp), %ecx
	addl	$4, %esi
	movl	%edi, (%esi)
	movl	(%ecx), %edi
	subl	$4, %ecx
	movl	%ecx, -16(%ebp)
	jmp	L323
L330:
	pushl	%ecx
	pushl	%ecx
	pushl	%edi
	pushl	$_pathdata
	call	_strcpy
	call	__Z7loaddirv
	movl	(%esi), %edi
	addl	$16, %esp
	subl	$4, %esi
	jmp	L323
L334:
	pushl	%eax
	pushl	%eax
	pushl	$-1
	movl	_ProcessInfo, %eax
	pushl	%eax
	call	_WaitForSingleObject@8
	pushl	%eax
	movl	_ProcessInfo+4, %edi
	pushl	%edi
	call	_CloseHandle@4
	movl	_ProcessInfo, %ecx
	pushl	%ecx
	call	_CloseHandle@4
	movl	(%esi), %edi
	addl	$12, %esp
	subl	$4, %esi
	jmp	L323
L335:
	addl	%edx, %ebx
	movl	%eax, %edi
	subl	$4, %esi
	jmp	L323
L238:
	call	_FMUSIC_StopAllSongs@0
	movl	(%esi), %edi
	subl	$4, %esi
	jmp	L323
L213:
	movl	%edi, %eax
	movb	%al, _gr_alphav
	call	__Z8gr_alphav
	movl	(%esi), %edi
	subl	$4, %esi
	jmp	L323
L234:
	subl	$12, %esp
	pushl	$-3
	call	_FSOUND_StopSound@4
	movl	(%esi), %edi
	addl	$12, %esp
	subl	$4, %esi
	jmp	L323
L247:
	movl	_sizedir(,%edi,4), %edi
	jmp	L323
L244:
	movl	_indexdir(,%edi,4), %edi
	jmp	L323
L250:
	movl	_subdirs(,%edi,4), %edi
	jmp	L323
L280:
	pushl	%eax
	pushl	%eax
	pushl	$10
	movl	_soc, %ecx
	pushl	%ecx
	call	_listen@8
	popl	%eax
	popl	%edx
	pushl	$41
	pushl	$1029
	movl	_hWnd, %eax
	pushl	%eax
	movl	_soc, %eax
	pushl	%eax
	call	_WSAAsyncSelect@16
	jmp	L323
L152:
	movl	(%esi), %edx
	movl	%edx, %eax
	sarl	$31, %edx
	idivl	%edi
	movl	%edx, %edi
	movl	%eax, (%esi)
	jmp	L323
L328:
	movl	(%esi), %eax
	testl	%eax, %eax
	je	L254
	pushl	%edi
	pushl	$_pathdata
	pushl	$LC156
	pushl	$_error
	call	_sprintf
	popl	%eax
	popl	%edx
	movl	(%esi), %edi
	pushl	$LC155
	pushl	$_error
	call	_fopen
	subl	$4, %esi
	addl	$16, %esp
	movl	%eax, _file
	testl	%eax, %eax
	je	L323
L256:
	movl	_file, %eax
	pushl	%eax
	pushl	$1024
	pushl	$1
	pushl	%edi
	call	_fread
	addl	$16, %esp
	addl	%eax, %edi
	cmpl	$1024, %eax
	je	L256
	subl	$12, %esp
	movl	_file, %eax
	pushl	%eax
	call	_fclose
	addl	$16, %esp
	jmp	L323
	.p2align 4,,7
L327:
	movl	(%esi), %ecx
	testl	%ecx, %ecx
	je	L261
	pushl	%edi
	pushl	$_pathdata
	pushl	$LC156
	pushl	$_error
	call	_sprintf
	popl	%eax
	popl	%edx
	movl	(%esi), %edi
	pushl	$LC154
	pushl	$_error
	call	_fopen
	subl	$4, %esi
	addl	$16, %esp
	movl	%eax, _file
	testl	%eax, %eax
	jne	L262
	subl	$4, %esi
	movl	(%esi), %edi
	subl	$4, %esi
	jmp	L323
L326:
	pushl	%eax
	pushl	%eax
	pushl	%edi
	movl	_pilaexecl, %eax
	pushl	%eax
	call	_strcpy
	movl	_pilaexecl, %eax
	addl	$16, %esp
	cmpb	$0, (%eax)
	je	L301
	leal	1(%eax), %edx
	movl	%edx, _pilaexecl
	cmpb	$0, 1(%eax)
	je	L336
L310:
	movl	%edx, %eax
	leal	1(%eax), %edx
	movl	%edx, _pilaexecl
	cmpb	$0, 1(%eax)
	jne	L310
L336:
	movl	%edx, %eax
L301:
	incl	%eax
	movl	%eax, _pilaexecl
	leal	-12(%ebp), %esp
	movl	$1, %eax
	popl	%ebx
	popl	%esi
	popl	%edi
	popl	%ebp
	ret
L282:
	movl	12(%eax), %eax
	movl	(%eax), %eax
	movl	(%eax), %eax
	movl	%eax, _naddr+4
	pushl	%ecx
	pushl	$6
	pushl	$1
	pushl	$2
	call	_socket@12
	movl	%eax, _soc
	pushl	$16
	pushl	$_naddr
	pushl	%eax
	call	_connect@12
	popl	%edx
	incl	%eax
	je	L337
	pushl	$33
	pushl	$1029
	movl	_hWnd, %eax
	pushl	%eax
	movl	_soc, %eax
	pushl	%eax
	call	_WSAAsyncSelect@16
	jmp	L323
L337:
	xorl	%edi, %edi
	jmp	L323
L262:
	pushl	%eax
	pushl	%edi
	pushl	$1
	movl	(%esi), %eax
	subl	$4, %esi
	pushl	%eax
	call	_fwrite
	popl	%eax
	movl	_file, %eax
	pushl	%eax
	call	_fclose
	movl	(%esi), %edi
	addl	$16, %esp
	subl	$4, %esi
	jmp	L323
	.align 2
	.p2align 4,,15
.globl __Z8esnumeroPc
	.def	__Z8esnumeroPc;	.scl	2;	.type	32;	.endef
__Z8esnumeroPc:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%edi
	pushl	%esi
	pushl	%ebx
	movl	8(%ebp), %ebx
	xorl	%edi, %edi
	movb	(%ebx), %al
	cmpb	$45, %al
	je	L362
	cmpb	$43, %al
	je	L363
L340:
	xorl	%edx, %edx
	testb	%al, %al
	je	L338
	cmpb	$36, %al
	je	L344
	cmpb	$37, %al
	je	L345
	movl	$10, %esi
L343:
	movl	$0, _numero
	xorl	%edx, %edx
	movb	(%ebx), %al
	testb	%al, %al
	je	L338
	jmp	L355
	.p2align 4,,7
L365:
	movsbl	%al,%eax
	leal	-48(%eax), %ecx
L351:
	movl	%ecx, %edx
	shrl	$31, %edx
	cmpl	%esi, %ecx
	setge	%al
	orb	%dl, %al
	jne	L352
	movl	_numero, %eax
	incl	%ebx
	imull	%esi, %eax
	leal	(%eax,%ecx), %edx
	movl	%edx, _numero
	movb	(%ebx), %al
	testb	%al, %al
	je	L364
L355:
	cmpb	$57, %al
	jle	L365
	cmpb	$64, %al
	jle	L352
	movsbl	%al,%eax
	leal	-55(%eax), %ecx
	jmp	L351
	.p2align 4,,7
L364:
	decl	%edi
	jne	L356
	negl	%edx
	movl	%edx, _numero
	.p2align 4,,7
L356:
	movl	$1, %edx
	.p2align 4,,7
L338:
	movl	%edx, %eax
	popl	%ebx
	popl	%esi
	popl	%edi
	popl	%ebp
	ret
	.p2align 4,,7
L362:
	incl	%ebx
	movw	$1, %di
	movb	(%ebx), %al
	jmp	L340
	.p2align 4,,7
L363:
	incl	%ebx
	movb	(%ebx), %al
	jmp	L340
L344:
	movl	$16, %esi
	incl	%ebx
	jmp	L343
L345:
	movl	$2, %esi
	incl	%ebx
	jmp	L343
L352:
	xorl	%edx, %edx
	jmp	L338
	.align 2
	.p2align 4,,15
.globl __Z9esnumerofPc
	.def	__Z9esnumerofPc;	.scl	2;	.type	32;	.endef
__Z9esnumerofPc:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%edi
	pushl	%esi
	pushl	%ebx
	pushl	%edi
	pushl	%edi
	movl	$0, -20(%ebp)
	movl	8(%ebp), %ecx
	movb	(%ecx), %al
	cmpb	$45, %al
	je	L393
	cmpb	$43, %al
	je	L394
L368:
	xorl	%edx, %edx
	testb	%al, %al
	je	L366
	movl	$0, _numero
	movb	(%ecx), %al
	testb	%al, %al
	je	L385
	.p2align 4,,7
L396:
	cmpb	$46, %al
	je	L395
	cmpb	$57, %al
	jg	L389
	movsbl	%al,%eax
	leal	-48(%eax), %edx
	cmpl	$9, %edx
	ja	L389
	movl	_numero, %eax
	incl	%ecx
	leal	(%eax,%eax,4), %eax
	leal	(%edx,%eax,2), %eax
	movl	%eax, _numero
L398:
	movb	(%ecx), %al
	testb	%al, %al
	jne	L396
L385:
	movl	_numero, %ecx
	movl	$1, %ebx
	movl	%ecx, %esi
	cmpl	$1, %ecx
	jle	L387
	movl	$1717986919, %edi
	.p2align 4,,7
L382:
	leal	(%ebx,%ebx,4), %eax
	leal	(%eax,%eax), %ebx
	movl	%ecx, %eax
	imull	%edi
	sarl	$2, %edx
	movl	%ecx, %eax
	sarl	$31, %eax
	movl	%edx, %ecx
	subl	%eax, %ecx
	cmpl	$1, %ecx
	jg	L382
L387:
	sall	$16, %esi
	movl	%esi, %edx
	movl	%esi, %eax
	sarl	$31, %edx
	movl	-16(%ebp), %esi
	sall	$16, %esi
	idivl	%ebx
	movl	%esi, -16(%ebp)
	andl	$65535, %eax
	movl	-16(%ebp), %ebx
	orl	%ebx, %eax
	cmpl	$1, -20(%ebp)
	je	L397
L388:
	movl	%eax, _numero
	movl	$1, %edx
L366:
	movl	%edx, %eax
	popl	%edx
	popl	%ecx
	popl	%ebx
	popl	%esi
	popl	%edi
	popl	%ebp
	ret
	.p2align 4,,7
L395:
	movl	_numero, %eax
	incl	%ecx
	movl	%eax, -16(%ebp)
	movl	$1, _numero
	jmp	L398
	.p2align 4,,7
L393:
	incl	%ecx
	movl	$1, -20(%ebp)
	movb	(%ecx), %al
	jmp	L368
L394:
	incl	%ecx
	movb	(%ecx), %al
	jmp	L368
L397:
	negl	%eax
	jmp	L388
L389:
	xorl	%edx, %edx
	jmp	L366
	.align 2
	.p2align 4,,15
.globl __Z5apilai
	.def	__Z5apilai;	.scl	2;	.type	32;	.endef
__Z5apilai:
	pushl	%ebp
	movl	_cntpila, %eax
	movl	%esp, %ebp
	movl	8(%ebp), %edx
	popl	%ebp
	movl	%edx, _pila(,%eax,4)
	incl	%eax
	movl	%eax, _cntpila
	ret
	.align 2
	.p2align 4,,15
.globl __Z8desapilav
	.def	__Z8desapilav;	.scl	2;	.type	32;	.endef
__Z8desapilav:
	movl	_cntpila, %eax
	pushl	%ebp
	decl	%eax
	movl	%esp, %ebp
	movl	%eax, _cntpila
	popl	%ebp
	movl	_pila(,%eax,4), %eax
	ret
	.align 2
	.p2align 4,,15
.globl __Z4iniAv
	.def	__Z4iniAv;	.scl	2;	.type	32;	.endef
__Z4iniAv:
	pushl	%ebp
	movl	$0, _cntpilaA
	movl	%esp, %ebp
	popl	%ebp
	ret
	.align 2
	.p2align 4,,15
.globl __Z5pushAi
	.def	__Z5pushAi;	.scl	2;	.type	32;	.endef
__Z5pushAi:
	pushl	%ebp
	movl	_cntpilaA, %eax
	movl	%esp, %ebp
	movl	8(%ebp), %edx
	popl	%ebp
	movl	%edx, _PSP(,%eax,4)
	incl	%eax
	movl	%eax, _cntpilaA
	ret
	.align 2
	.p2align 4,,15
.globl __Z4popAv
	.def	__Z4popAv;	.scl	2;	.type	32;	.endef
__Z4popAv:
	movl	_cntpilaA, %eax
	pushl	%ebp
	decl	%eax
	movl	%esp, %ebp
	movl	%eax, _cntpilaA
	popl	%ebp
	movl	_PSP(,%eax,4), %eax
	ret
	.align 2
	.p2align 4,,15
.globl __Z5adatoPKc
	.def	__Z5adatoPKc;	.scl	2;	.type	32;	.endef
__Z5adatoPKc:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%ebx
	subl	$12, %esp
	movl	_cntdato, %eax
	movl	8(%ebp), %ebx
	addl	$_data, %eax
	pushl	%ebx
	pushl	%eax
	call	_strcpy
	subl	$12, %esp
	pushl	%ebx
	call	_strlen
	movl	_cntdato, %edx
	addl	$16, %esp
	addl	%edx, %eax
	movl	-4(%ebp), %ebx
	incl	%eax
	movl	%eax, _cntdato
	leave
	ret
	.align 2
	.p2align 4,,15
.globl __Z8adatonroii
	.def	__Z8adatonroii;	.scl	2;	.type	32;	.endef
__Z8adatonroii:
	pushl	%ebp
	movl	_cntdato, %eax
	movl	%esp, %ebp
	movl	12(%ebp), %edx
	movl	8(%ebp), %ecx
	cmpl	$2, %edx
	je	L408
	jle	L411
	cmpl	$4, %edx
	je	L409
L406:
	addl	%edx, %eax
	popl	%ebp
	movl	%eax, _cntdato
	ret
	.p2align 4,,7
L411:
	cmpl	$1, %edx
	jne	L406
	movb	%cl, _data(%eax)
	addl	%edx, %eax
	movl	%eax, _cntdato
	popl	%ebp
	ret
	.p2align 4,,7
L408:
	movw	%cx, _data(%eax)
	addl	%edx, %eax
	movl	%eax, _cntdato
	popl	%ebp
	ret
	.p2align 4,,7
L409:
	movl	%ecx, _data(%eax)
	addl	%edx, %eax
	movl	%eax, _cntdato
	popl	%ebp
	ret
	.align 2
	.p2align 4,,15
.globl __Z8adatocnti
	.def	__Z8adatocnti;	.scl	2;	.type	32;	.endef
__Z8adatocnti:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%ebx
	movl	_cntdato, %ebx
	movl	8(%ebp), %eax
	leal	_data(%ebx), %ecx
	testl	%eax, %eax
	jle	L418
	movl	%eax, %edx
	.p2align 4,,7
L416:
	movb	$0, (%ecx)
	incl	%ecx
	decl	%edx
	jne	L416
L418:
	leal	(%ebx,%eax), %eax
	popl	%ebx
	movl	%eax, _cntdato
	popl	%ebp
	ret
	.align 2
	.p2align 4,,15
.globl __Z8aprognroi
	.def	__Z8aprognroi;	.scl	2;	.type	32;	.endef
__Z8aprognroi:
	pushl	%ebp
	movl	_cntprog, %edx
	movl	%esp, %ebp
	movl	$0, _lastcall
	leal	_prog(%edx), %ecx
	movl	8(%ebp), %eax
	cmpl	$104, %eax
	ja	L420
	subl	$106, %eax
	popl	%ebp
	movb	%al, _prog(%edx)
	leal	1(%edx), %eax
	movl	%eax, _cntprog
	ret
	.p2align 4,,7
L420:
	movb	$1, _prog(%edx)
	movl	%eax, 1(%ecx)
	leal	5(%edx), %eax
	popl	%ebp
	movl	%eax, _cntprog
	ret
	.align 2
	.p2align 4,,15
.globl __Z5aprogi
	.def	__Z5aprogi;	.scl	2;	.type	32;	.endef
__Z5aprogi:
	pushl	%ebp
	movl	_cntprog, %edx
	movl	%esp, %ebp
	leal	_prog(%edx), %ecx
	movl	8(%ebp), %eax
	movb	%al, _prog(%edx)
	cmpl	$3, %eax
	je	L426
	leal	1(%edx), %eax
	movl	$0, _lastcall
	movl	%eax, _cntprog
	popl	%ebp
	ret
	.p2align 4,,7
L426:
	leal	1(%edx), %eax
	movl	%ecx, _lastcall
	movl	%eax, _cntprog
	popl	%ebp
	ret
	.align 2
	.p2align 4,,15
.globl __Z8aproginti
	.def	__Z8aproginti;	.scl	2;	.type	32;	.endef
__Z8aproginti:
	pushl	%ebp
	movl	_cntprog, %eax
	movl	%esp, %ebp
	movl	8(%ebp), %edx
	popl	%ebp
	addl	$_prog, %edx
	movl	%edx, _prog(%eax)
	addl	$4, %eax
	movl	%eax, _cntprog
	ret
	.align 2
	.p2align 4,,15
.globl __Z9aprogaddri
	.def	__Z9aprogaddri;	.scl	2;	.type	32;	.endef
__Z9aprogaddri:
	pushl	%ebp
	movl	_cntprog, %edx
	movl	%esp, %ebp
	movl	8(%ebp), %eax
	popl	%ebp
	leal	(%eax,%eax,2), %eax
	movl	_indice+4(,%eax,4), %eax
	movl	%eax, _prog(%edx)
	addl	$4, %edx
	movl	%edx, _cntprog
	ret
	.align 2
	.p2align 4,,15
.globl __Z11aprogaddrexi
	.def	__Z11aprogaddrexi;	.scl	2;	.type	32;	.endef
__Z11aprogaddrexi:
	pushl	%ebp
	movl	_cntprog, %edx
	movl	%esp, %ebp
	movl	8(%ebp), %eax
	popl	%ebp
	leal	(%eax,%eax,2), %eax
	movl	_indiceex+4(,%eax,4), %eax
	movl	%eax, _prog(%edx)
	addl	$4, %edx
	movl	%edx, _cntprog
	ret
	.align 2
	.p2align 4,,15
.globl __Z6definePc
	.def	__Z6definePc;	.scl	2;	.type	32;	.endef
__Z6definePc:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%edi
	pushl	%esi
	pushl	%ebx
	subl	$12, %esp
	movl	_cntindice, %eax
	movl	8(%ebp), %esi
	leal	(%eax,%eax,2), %edx
	incl	%eax
	movl	%eax, _cntindice
	movsbl	(%esi),%eax
	leal	_indice(,%edx,4), %ebx
	incl	%esi
	movl	%eax, 8(%ebx)
	cmpb	$58, (%esi)
	je	L436
L431:
	movl	_cntnombre, %edi
	addl	$_nombre, %edi
	pushl	%eax
	pushl	%eax
	pushl	%esi
	pushl	%edi
	call	_strcpy
	subl	$12, %esp
	pushl	%esi
	call	_strlen
	movl	_cntnombre, %ecx
	addl	$32, %esp
	addl	%ecx, %eax
	movl	%edi, (%ebx)
	incl	%eax
	movl	%eax, _cntnombre
	cmpl	$58, 8(%ebx)
	je	L437
	movl	_cntdato, %eax
	addl	$_data, %eax
	movl	%eax, 4(%ebx)
	leal	-12(%ebp), %esp
	popl	%ebx
	popl	%esi
	popl	%edi
	popl	%ebp
	ret
	.p2align 4,,7
L437:
	movl	_cntprog, %eax
	addl	$_prog, %eax
	movl	%eax, 4(%ebx)
	leal	-12(%ebp), %esp
	popl	%ebx
	popl	%esi
	popl	%edi
	popl	%ebp
	ret
	.p2align 4,,7
L436:
	movl	_cntindiceex, %eax
	movl	_cntnombreex, %edi
	incl	%esi
	addl	$_nombreex, %edi
	leal	(%eax,%eax,2), %edx
	incl	%eax
	sall	$2, %edx
	movl	%eax, _cntindiceex
	movl	%edx, -20(%ebp)
	addl	$_indiceex, %edx
	movl	%edx, -16(%ebp)
	pushl	%ecx
	pushl	%ecx
	pushl	%esi
	pushl	%edi
	call	_strcpy
	subl	$12, %esp
	pushl	%esi
	call	_strlen
	movl	_cntnombreex, %edx
	addl	$32, %esp
	addl	%edx, %eax
	movl	-16(%ebp), %edx
	incl	%eax
	movl	%eax, _cntnombreex
	movl	8(%ebx), %eax
	movl	%eax, 8(%edx)
	movl	-20(%ebp), %edx
	cmpl	$58, %eax
	movl	%edi, _indiceex(%edx)
	je	L438
	movl	_cntdato, %eax
	addl	$_data, %eax
L433:
	movl	-16(%ebp), %edx
	movl	%eax, 4(%edx)
	jmp	L431
L438:
	movl	_cntprog, %eax
	addl	$_prog, %eax
	jmp	L433
	.align 2
	.p2align 4,,15
.globl __Z10compilofinv
	.def	__Z10compilofinv;	.scl	2;	.type	32;	.endef
__Z10compilofinv:
	pushl	%ebp
	movl	_lastcall, %eax
	movl	%esp, %ebp
	testl	%eax, %eax
	je	L440
	movb	$4, (%eax)
	movl	$0, _lastcall
	leave
	ret
	.p2align 4,,7
L440:
	pushl	$0
	call	__Z5aprogi
	popl	%eax
	leave
	ret
	.align 2
	.p2align 4,,15
.globl __Z8endefinev
	.def	__Z8endefinev;	.scl	2;	.type	32;	.endef
__Z8endefinev:
	pushl	%ebp
	movl	_cntindice, %eax
	movl	%esp, %ebp
	leal	(%eax,%eax,2), %eax
	leal	_indice-12(,%eax,4), %edx
	cmpl	$58, 8(%edx)
	je	L446
	movl	_cntdato, %eax
	addl	$_data, %eax
	cmpl	4(%edx), %eax
	je	L447
	leave
	ret
	.p2align 4,,7
L446:
	leave
	jmp	__Z10compilofinv
L447:
	pushl	$4
	pushl	$0
	call	__Z8adatonroii
	popl	%eax
	popl	%edx
	leave
	ret
	.align 2
	.p2align 4,,15
.globl __Z11endefinesinv
	.def	__Z11endefinesinv;	.scl	2;	.type	32;	.endef
__Z11endefinesinv:
	pushl	%ebp
	movl	_cntindice, %eax
	movl	%esp, %ebp
	leal	(%eax,%eax,2), %eax
	leal	_indice-12(,%eax,4), %edx
	cmpl	$58, 8(%edx)
	je	L448
	movl	_cntdato, %eax
	addl	$_data, %eax
	cmpl	4(%edx), %eax
	je	L450
L448:
	leave
	ret
L450:
	pushl	$4
	pushl	$0
	call	__Z8adatonroii
	popl	%ecx
	popl	%eax
	leave
	ret
	.align 2
	.p2align 4,,15
.globl __Z7esmacroPc
	.def	__Z7esmacroPc;	.scl	2;	.type	32;	.endef
__Z7esmacroPc:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%esi
	pushl	%ebx
	movl	$0, _numero
	movl	_macros, %eax
	movl	8(%ebp), %esi
	movl	$_macros, %ebx
	cmpb	$0, (%eax)
	je	L457
	.p2align 4,,7
L460:
	pushl	%eax
	pushl	%eax
	pushl	%esi
	movl	(%ebx), %eax
	pushl	%eax
	call	_strcmp
	addl	$16, %esp
	testl	%eax, %eax
	je	L459
	movl	_numero, %eax
	addl	$4, %ebx
	incl	%eax
	movl	%eax, _numero
	movl	(%ebx), %eax
	cmpb	$0, (%eax)
	jne	L460
L457:
	leal	-8(%ebp), %esp
	xorl	%eax, %eax
	popl	%ebx
	popl	%esi
	popl	%ebp
	ret
L459:
	leal	-8(%ebp), %esp
	movb	$1, %al
	popl	%ebx
	popl	%esi
	popl	%ebp
	ret
	.align 2
	.p2align 4,,15
.globl __Z9espalabraPc
	.def	__Z9espalabraPc;	.scl	2;	.type	32;	.endef
__Z9espalabraPc:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%edi
	pushl	%esi
	pushl	%ebx
	subl	$12, %esp
	movl	_cntindice, %esi
	movl	8(%ebp), %edi
	decl	%esi
	movl	%esi, _numero
	leal	(%esi,%esi,2), %eax
	leal	_indice(,%eax,4), %ebx
	cmpl	$_indice, %ebx
	jb	L467
	.p2align 4,,7
L470:
	pushl	%eax
	pushl	%eax
	pushl	%edi
	movl	(%ebx), %eax
	pushl	%eax
	call	_strcmp
	addl	$16, %esp
	testl	%eax, %eax
	je	L469
	leal	-1(%esi), %eax
	subl	$12, %ebx
	movl	%eax, %esi
	movl	%eax, _numero
	cmpl	$_indice, %ebx
	jae	L470
L467:
	leal	-12(%ebp), %esp
	xorl	%eax, %eax
	popl	%ebx
	popl	%esi
	popl	%edi
	popl	%ebp
	ret
L469:
	leal	-12(%ebp), %esp
	movb	$1, %al
	popl	%ebx
	popl	%esi
	popl	%edi
	popl	%ebp
	ret
	.align 2
	.p2align 4,,15
.globl __Z11espalabraexPc
	.def	__Z11espalabraexPc;	.scl	2;	.type	32;	.endef
__Z11espalabraexPc:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%edi
	pushl	%esi
	pushl	%ebx
	subl	$12, %esp
	movl	_cntindiceex, %esi
	movl	8(%ebp), %edi
	decl	%esi
	movl	%esi, _numero
	leal	(%esi,%esi,2), %eax
	leal	_indiceex(,%eax,4), %ebx
	cmpl	$_indiceex, %ebx
	jb	L477
	.p2align 4,,7
L480:
	pushl	%ecx
	pushl	%ecx
	pushl	%edi
	movl	(%ebx), %edx
	pushl	%edx
	call	_strcmp
	addl	$16, %esp
	testl	%eax, %eax
	je	L479
	leal	-1(%esi), %eax
	subl	$12, %ebx
	movl	%eax, %esi
	movl	%eax, _numero
	cmpl	$_indiceex, %ebx
	jae	L480
L477:
	leal	-12(%ebp), %esp
	xorl	%eax, %eax
	popl	%ebx
	popl	%esi
	popl	%edi
	popl	%ebp
	ret
L479:
	leal	-12(%ebp), %esp
	movb	$1, %al
	popl	%ebx
	popl	%esi
	popl	%edi
	popl	%ebp
	ret
	.align 2
	.p2align 4,,15
.globl __Z11estaincludePc
	.def	__Z11estaincludePc;	.scl	2;	.type	32;	.endef
__Z11estaincludePc:
	pushl	%ebp
	xorl	%eax, %eax
	movl	%esp, %ebp
	pushl	%esi
	pushl	%ebx
	movl	_cntincludes, %edx
	movl	8(%ebp), %esi
	testl	%edx, %edx
	je	L481
	leal	(%edx,%edx,2), %eax
	leal	_includes-12(,%eax,4), %ebx
	cmpl	$_includes, %ebx
	jb	L488
	.p2align 4,,7
L491:
	pushl	%eax
	pushl	%eax
	pushl	%esi
	movl	(%ebx), %eax
	pushl	%eax
	call	_strcmp
	addl	$16, %esp
	testl	%eax, %eax
	je	L489
	subl	$12, %ebx
	cmpl	$_includes, %ebx
	jae	L491
L488:
	xorl	%eax, %eax
L481:
	leal	-8(%ebp), %esp
	popl	%ebx
	popl	%esi
	popl	%ebp
	ret
L489:
	leal	-8(%ebp), %esp
	movl	$1, %eax
	popl	%ebx
	popl	%esi
	popl	%ebp
	ret
	.align 2
	.p2align 4,,15
.globl __Z13agregaincludePc
	.def	__Z13agregaincludePc;	.scl	2;	.type	32;	.endef
__Z13agregaincludePc:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%edi
	pushl	%esi
	pushl	%ebx
	subl	$20, %esp
	movl	_cntincludes, %eax
	movl	_cntnombreex, %edi
	movl	8(%ebp), %esi
	addl	$_nombreex, %edi
	pushl	%esi
	leal	(%eax,%eax,2), %ebx
	pushl	%edi
	incl	%eax
	sall	$2, %ebx
	movl	%eax, _cntincludes
	call	_strcpy
	subl	$12, %esp
	pushl	%esi
	call	_strlen
	movl	_cntnombreex, %edx
	movl	%edi, _includes(%ebx)
	addl	%edx, %eax
	addl	$16, %esp
	incl	%eax
	movl	%eax, _cntnombreex
	leal	-12(%ebp), %esp
	popl	%ebx
	popl	%esi
	popl	%edi
	popl	%ebp
	ret
	.align 2
	.p2align 4,,15
.globl __Z7tolowerc
	.def	__Z7tolowerc;	.scl	2;	.type	32;	.endef
__Z7tolowerc:
	pushl	%ebp
	movl	%esp, %ebp
	movb	8(%ebp), %dl
	leal	-65(%edx), %eax
	cmpb	$25, %al
	ja	L494
	addl	$32, %edx
L494:
	movsbl	%dl,%eax
	popl	%ebp
	ret
	.align 2
	.p2align 4,,15
.globl __Z7toupperc
	.def	__Z7toupperc;	.scl	2;	.type	32;	.endef
__Z7toupperc:
	pushl	%ebp
	movl	%esp, %ebp
	movb	8(%ebp), %dl
	leal	-97(%edx), %eax
	cmpb	$25, %al
	ja	L496
	subl	$32, %edx
L496:
	movsbl	%dl,%eax
	popl	%ebp
	ret
	.section .rdata,"dr"
LC160:
	.ascii "%s|%d|%d|%s\0"
LC157:
	.ascii "%s|0|0|no existe %s\0"
LC158:
	.ascii "no existe %s\0"
LC159:
	.ascii "palabra %s en dato ?\0"
	.text
	.align 2
	.p2align 4,,15
.globl __Z11compilafilePc
	.def	__Z11compilafilePc;	.scl	2;	.type	32;	.endef
__Z11compilafilePc:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%edi
	pushl	%esi
	pushl	%ebx
	subl	$556, %esp
	movl	8(%ebp), %ebx
	jmp	L641
L657:
	movsbl	%cl,%eax
	pushl	%eax
	call	__Z7tolowerc
	popl	%edx
	movb	%al, (%ebx)
	incl	%ebx
L641:
	movb	(%ebx), %cl
	cmpb	$32, %cl
	jg	L657
	movl	8(%ebp), %eax
	pushl	%eax
	leal	-536(%ebp), %eax
	pushl	$_pathdata
	pushl	$LC156
	pushl	%eax
	call	_sprintf
	popl	%esi
	leal	-536(%ebp), %edx
	popl	%edi
	pushl	$LC155
	pushl	%edx
	call	_fopen
	addl	$16, %esp
	testl	%eax, %eax
	movl	%eax, -540(%ebp)
	je	L658
	movl	-540(%ebp), %edx
	movl	$2, -544(%ebp)
	movl	$4, -548(%ebp)
	movl	$0, -552(%ebp)
	testb	$16, 12(%edx)
	movl	$1, -556(%ebp)
	movl	$0, _cntpila
L642:
	jne	L629
L505:
	movb	$0, -536(%ebp)
	pushl	%ebx
	leal	-536(%ebp), %ebx
	movl	-540(%ebp), %ecx
	leal	-536(%ebp), %eax
	pushl	%ecx
	pushl	$512
	pushl	%eax
	call	_fgets
	movb	(%ebx), %cl
	addl	$16, %esp
	testb	%cl, %cl
	setne	%dl
	cmpb	$32, %cl
	setle	%al
	testb	%al, %dl
	je	L659
	.p2align 4,,7
L524:
	incl	%ebx
L664:
	movb	(%ebx), %cl
	testb	%cl, %cl
	setne	%dl
	cmpb	$32, %cl
	setle	%al
	testb	%al, %dl
	jne	L524
L659:
	testb	%cl, %cl
	je	L510
	movl	%ebx, %esi
	cmpb	$34, %cl
	jne	L511
	jmp	L660
	.p2align 4,,7
L661:
	movsbl	%cl,%eax
	pushl	%eax
	call	__Z7toupperc
	popl	%edx
	movb	%al, (%ebx)
	incl	%ebx
	movb	(%ebx), %cl
L511:
	cmpb	$32, %cl
	jg	L661
L518:
	testb	%cl, %cl
	jne	L522
	movb	$0, 1(%ebx)
L522:
	movb	$0, (%ebx)
	movb	(%esi), %cl
	cmpb	$124, %cl
	je	L662
	cmpb	$34, %cl
	je	L663
	cmpb	$58, %cl
	sete	%dl
	cmpb	$35, %cl
	sete	%al
	orb	%al, %dl
	je	L530
	movl	_cntpila, %eax
	testl	%eax, %eax
	jg	L635
	call	__Z11endefinesinv
	call	__Z4iniAv
	cmpb	$0, 1(%esi)
	jne	L533
	movl	_cntprog, %eax
	addl	$_prog, %eax
	movl	%eax, _bootaddr
L534:
	cmpb	$58, (%esi)
	movl	$4, -548(%ebp)
	sete	%al
	andl	$255, %eax
	incl	%ebx
	movl	%eax, -544(%ebp)
	movl	-544(%ebp), %ecx
	incl	%ecx
	movl	%ecx, -544(%ebp)
	jmp	L664
L530:
	cmpb	$94, %cl
	je	L665
	pushl	%esi
	call	__Z8esnumeroPc
	popl	%edx
	decl	%eax
	je	L546
	pushl	%esi
	call	__Z9esnumerofPc
	popl	%edi
	decl	%eax
	jne	L545
L546:
	cmpl	$1, -544(%ebp)
	je	L548
	cmpl	$2, -544(%ebp)
	jne	L524
	movl	_numero, %eax
	pushl	%eax
	call	__Z8aprognroi
	popl	%eax
L669:
	incl	%ebx
	jmp	L664
L660:
	incl	%ebx
	movl	%ebx, %edx
	movb	(%ebx), %cl
	testb	%cl, %cl
	je	L513
	movb	%cl, %al
	jmp	L516
	.p2align 4,,7
L514:
	incl	%edx
	movb	%al, (%ebx)
	incl	%ebx
	movb	(%edx), %al
	testb	%al, %al
	je	L513
L516:
	cmpb	$34, %al
	jne	L514
	cmpb	$34, 1(%edx)
	jne	L513
	incl	%edx
	movb	(%edx), %al
	incl	%edx
	movb	%al, (%ebx)
	incl	%ebx
	movb	(%edx), %al
	testb	%al, %al
	jne	L516
L513:
	cmpl	%edx, %ebx
	je	L634
	movb	$0, (%ebx)
	movl	%edx, %ebx
L634:
	movb	(%ebx), %cl
	jmp	L518
L663:
	incl	%esi
	cmpl	$1, -544(%ebp)
	je	L527
	cmpl	$2, -544(%ebp)
	jne	L524
	subl	$12, %esp
	movl	_cntdato, %edi
	addl	$_data, %edi
	pushl	%esi
	call	__Z5adatoPKc
	pushl	%edi
	call	__Z8aprognroi
	addl	$20, %esp
L672:
	incl	%ebx
	jmp	L664
L533:
	pushl	%esi
	call	__Z8esnumeroPc
	popl	%edi
	decl	%eax
	je	L636
	subl	$12, %esp
	pushl	%esi
	call	__Z6definePc
	addl	$16, %esp
	jmp	L534
L665:
	subl	$12, %esp
	incl	%esi
	pushl	%esi
	call	__Z11estaincludePc
	addl	$16, %esp
	testl	%eax, %eax
	jne	L524
	subl	$12, %esp
	pushl	%esi
	call	__Z13agregaincludePc
	movl	%esi, (%esp)
	call	__Z11compilafilePc
	addl	$16, %esp
	cmpl	$1, %eax
	je	L637
	testl	%eax, %eax
	jne	L497
	incl	%ebx
	movl	$0, _cntnombre
	movl	$0, _cntindice
	jmp	L664
L545:
	subl	$12, %esp
	pushl	%esi
	call	__Z7esmacroPc
	addl	$16, %esp
	decl	%eax
	je	L666
	xorl	%edi, %edi
	cmpb	$39, (%esi)
	je	L667
L603:
	subl	$12, %esp
	pushl	%esi
	call	__Z9espalabraPc
	addl	$16, %esp
	decl	%eax
	jne	L605
	cmpl	$1, -544(%ebp)
	je	L607
	cmpl	$2, -544(%ebp)
	jne	L524
	testl	%edi, %edi
	jne	L609
	movl	_numero, %eax
	leal	(%eax,%eax,2), %eax
	cmpl	$35, _indice+8(,%eax,4)
	je	L668
	pushl	$3
L643:
	call	__Z5aprogi
	popl	%eax
	movl	_numero, %edi
	pushl	%edi
	call	__Z9aprogaddri
	popl	%eax
	jmp	L669
L548:
	movl	-548(%ebp), %ecx
	testl	%ecx, %ecx
	jne	L549
	movl	_numero, %edx
	pushl	%edx
	call	__Z8adatocnti
	popl	%eax
	jmp	L669
L549:
	movl	-548(%ebp), %eax
	pushl	%eax
	movl	_numero, %eax
	pushl	%eax
L646:
	call	__Z8adatonroii
L649:
	popl	%edx
	popl	%ecx
L677:
	incl	%ebx
	jmp	L664
L605:
	subl	$12, %esp
	pushl	%esi
	call	__Z11espalabraexPc
	addl	$16, %esp
	decl	%eax
	jne	L637
	cmpl	$1, -544(%ebp)
	je	L616
	cmpl	$2, -544(%ebp)
	jne	L524
	testl	%edi, %edi
	jne	L618
	movl	_numero, %eax
	leal	(%eax,%eax,2), %eax
	cmpl	$35, _indiceex+8(,%eax,4)
	je	L670
	pushl	$3
L644:
	call	__Z5aprogi
	popl	%eax
	movl	_numero, %eax
	pushl	%eax
	call	__Z11aprogaddrexi
	popl	%eax
	jmp	L669
L666:
	cmpl	$1, -544(%ebp)
	je	L555
	cmpl	$2, -544(%ebp)
	jne	L524
	movl	_numero, %eax
	cmpl	$5, %eax
	ja	L598
	jmp	*L601(,%eax,4)
	.section .rdata,"dr"
	.align 4
L601:
	.long	L567
	.long	L570
	.long	L573
	.long	L586
	.long	L595
	.long	L596
	.text
L667:
	incl	%esi
	movw	$1, %di
	pushl	%esi
	call	__Z8esnumeroPc
	popl	%edx
	decl	%eax
	jne	L603
	movl	$544174702, _error
	movw	$63, _error+4
	jmp	L532
	.p2align 4,,7
L629:
	movl	_cntprog, %eax
	cmpb	$0, _prog-1(%eax)
	jne	L671
L624:
	subl	$12, %esp
	movl	-540(%ebp), %eax
	pushl	%eax
	call	_fclose
	addl	$16, %esp
	cmpl	$1, %eax
	sbbl	%eax, %eax
	xorl	$-1, %eax
	andl	$2, %eax
L497:
	leal	-12(%ebp), %esp
	popl	%ebx
	popl	%esi
	popl	%edi
	popl	%ebp
	ret
L555:
	movl	_numero, %eax
	cmpl	$5, %eax
	ja	L563
	jmp	*L564(,%eax,4)
	.section .rdata,"dr"
	.align 4
L564:
	.long	L568
	.long	L558
	.long	L562
	.long	L560
	.long	L561
	.long	L562
	.text
L618:
	pushl	$1
	jmp	L644
L671:
	pushl	$0
	call	__Z5aprogi
	popl	%eax
	jmp	L624
L562:
	call	__Z8desapilav
	incl	%ebx
	movl	%eax, -548(%ebp)
	jmp	L664
L561:
	movl	-548(%ebp), %eax
	pushl	%eax
	call	__Z5apilai
	movl	$2, -548(%ebp)
	popl	%eax
	jmp	L669
L560:
	incl	%ebx
	movl	$0, -548(%ebp)
	jmp	L664
L558:
	movl	-548(%ebp), %eax
	pushl	%eax
	call	__Z5apilai
	movl	$1, -548(%ebp)
	popl	%eax
	jmp	L669
L568:
	call	__Z8endefinev
	incl	%ebx
	jmp	L664
L596:
	call	__Z8desapilav
	cmpl	$4, %eax
	jne	L639
	call	__Z8desapilav
	movl	%eax, %edi
L648:
	movl	%edi, %eax
	incl	%ebx
	xorl	$-1, %eax
	addb	_cntprog, %al
	movb	%al, _prog(%edi)
	jmp	L664
L595:
	pushl	$1
	call	__Z5aprogi
	movl	_cntprog, %eax
	addl	$6, %eax
	pushl	%eax
	call	__Z8aproginti
	pushl	$5
	call	__Z5aprogi
	movl	_cntprog, %edi
	pushl	%edi
	call	__Z5apilai
	pushl	$4
	call	__Z5apilai
	movl	_cntprog, %esi
	addl	$20, %esp
	incl	%esi
	movl	%esi, _cntprog
	jmp	L672
L586:
	call	__Z8desapilav
	cmpl	$1, %eax
	je	L673
	cmpl	$2, %eax
	jne	L591
	call	__Z8desapilav
	cmpl	$1, -552(%ebp)
	movl	%eax, %edi
	jne	L592
	movl	_cntprog, %eax
	pushl	%eax
	call	__Z5apilai
	movl	_cntprog, %eax
	incl	%eax
	movl	%eax, _cntprog
	pushl	%edi
	call	__Z5apilai
	pushl	$3
	call	__Z5apilai
	movl	$0, -552(%ebp)
	addl	$12, %esp
L678:
	incl	%ebx
	jmp	L664
L573:
	call	__Z8desapilav
	movl	$0, _lastcall
	cmpl	$1, %eax
	je	L674
	cmpl	$2, %eax
	je	L675
	cmpl	$3, %eax
	jne	L582
	call	__Z8desapilav
	movl	%eax, %edi
	movl	-552(%ebp), %eax
	testl	%eax, %eax
	jne	L582
	pushl	$5
	call	__Z5aprogi
	movl	_cntprog, %eax
	movl	%edi, %edx
	subb	%al, %dl
	decl	%edx
	movb	%dl, _prog(%eax)
	incl	%eax
	movl	%eax, _cntprog
	call	__Z8desapilav
	movl	%eax, %edi
	xorl	$-1, %eax
	addb	_cntprog, %al
	movb	%al, _prog(%edi)
	popl	%eax
	jmp	L669
	.p2align 4,,7
L570:
	cmpl	$1, -552(%ebp)
	je	L676
	movl	_cntprog, %edx
	pushl	%edx
	call	__Z5apilai
	pushl	$2
	call	__Z5apilai
	popl	%edx
	popl	%ecx
	jmp	L677
	.p2align 4,,7
L567:
	movl	_cntpila, %edi
	testl	%edi, %edi
	jle	L568
	call	__Z10compilofinv
	incl	%ebx
	jmp	L664
	.p2align 4,,7
L662:
	movb	$0, 1(%ebx)
	incl	%ebx
	jmp	L664
L527:
	subl	$12, %esp
	incl	%ebx
	pushl	%esi
	call	__Z5adatoPKc
	addl	$16, %esp
	jmp	L664
L510:
	movl	-556(%ebp), %eax
	incl	%eax
	movl	%eax, -556(%ebp)
	movl	-540(%ebp), %eax
	testb	$16, 12(%eax)
	jmp	L642
L616:
	pushl	$4
	movl	_numero, %eax
	leal	(%eax,%eax,2), %eax
	movl	_indiceex+4(,%eax,4), %esi
	pushl	%esi
	call	__Z8adatonroii
	jmp	L649
L607:
	pushl	$4
	movl	_numero, %eax
	leal	(%eax,%eax,2), %eax
	movl	_indice+4(,%eax,4), %eax
	pushl	%eax
	jmp	L646
L635:
	movl	$1903127650, _error
	movl	$1830839669, _error+4
	movl	$1663069281, _error+8
	movl	$1634890341, _error+12
	movw	$28516, _error+16
L652:
	movb	$0, _error+18
L532:
	leal	-536(%ebp), %edx
	subl	%edx, %ebx
	pushl	%esi
	pushl	%esi
	pushl	$_error
	pushl	%ebx
	movl	-556(%ebp), %ebx
	pushl	%ebx
	movl	8(%ebp), %ecx
	pushl	%ecx
	pushl	$LC160
	pushl	%edx
	call	_sprintf
	addl	$24, %esp
	leal	-536(%ebp), %edx
	pushl	%edx
	pushl	$_error
	call	_strcpy
	leal	-12(%ebp), %esp
	movl	$3, %eax
	popl	%ebx
	popl	%esi
	popl	%edi
	popl	%ebp
	ret
L598:
	pushl	%eax
	call	__Z5aprogi
	movl	_numero, %eax
	popl	%ecx
	subl	$7, %eax
	cmpl	$11, %eax
	setbe	%al
	andl	$255, %eax
	incl	%ebx
	movl	%eax, -552(%ebp)
	jmp	L664
L670:
	pushl	$2
	jmp	L644
L668:
	pushl	$2
	jmp	L643
L609:
	pushl	$1
	jmp	L643
L658:
	leal	-536(%ebp), %eax
	pushl	%eax
	pushl	$_linea
	pushl	$LC157
	pushl	$_error
	call	_sprintf
	leal	-12(%ebp), %esp
	movl	$1, %eax
	popl	%ebx
	popl	%esi
	popl	%edi
	popl	%ebp
	ret
L636:
	movl	$544174702, _error
	movl	$1635151465, _error+4
	movl	$1868851564, _error+8
	movb	$0, _error+12
	jmp	L532
L637:
	pushl	%edi
	pushl	%esi
	pushl	$LC158
L655:
	pushl	$_error
	call	_sprintf
	addl	$16, %esp
	jmp	L532
L676:
	movl	_cntprog, %esi
	pushl	%esi
	call	__Z5apilai
	pushl	$1
	call	__Z5apilai
	movl	_cntprog, %ecx
	movl	$0, -552(%ebp)
	incl	%ecx
	movl	%ecx, _cntprog
	popl	%edx
	popl	%ecx
	jmp	L677
L675:
	call	__Z8desapilav
	cmpl	$1, -552(%ebp)
	movl	%eax, %edi
	jne	L579
	movl	_cntprog, %edx
	incl	%ebx
	subb	%dl, %al
	movl	$0, -552(%ebp)
	decl	%eax
	movb	%al, _prog(%edx)
	incl	%edx
	movl	%edx, _cntprog
	jmp	L664
L674:
	call	__Z8desapilav
	movl	%eax, %edi
	movl	-552(%ebp), %eax
	testl	%eax, %eax
	je	L648
	movl	$539566143, _error
	movl	$1981837166, _error+4
	movl	$1684630625, _error+8
	movw	$8303, _error+12
	jmp	L654
L579:
	pushl	$5
	call	__Z5aprogi
	movl	_cntprog, %edx
	movl	%edi, %eax
	subb	%dl, %al
	decl	%eax
	movb	%al, _prog(%edx)
	incl	%edx
	movl	%edx, _cntprog
	popl	%eax
	jmp	L669
L673:
	call	__Z8desapilav
	movl	%eax, %edi
	movl	-552(%ebp), %eax
	testl	%eax, %eax
	jne	L588
	pushl	$5
	call	__Z5aprogi
	movl	_cntprog, %eax
	pushl	%eax
	call	__Z5apilai
	pushl	$1
	call	__Z5apilai
	movl	_cntprog, %eax
	movl	%edi, %edx
	incl	%eax
	addl	$12, %esp
	movl	%eax, _cntprog
	subb	%dl, %al
	decl	%eax
	movb	%al, _prog(%edi)
	jmp	L678
L563:
	pushl	%eax
	pushl	%esi
	pushl	$LC159
	jmp	L655
L639:
	movl	$1830837595, _error
L651:
	movl	$1663069281, _error+4
	movl	$1634890341, _error+8
L653:
	movw	$28516, _error+12
L654:
	movb	$0, _error+14
	jmp	L532
L588:
	movl	$673783871, _error
	movl	$544173600, _error+4
	movl	$1768710518, _error+8
	jmp	L653
L582:
	movl	$1634541609, _error
	movl	$1700995180, _error+4
	movl	$1684107890, _error+8
	movw	$111, _error+12
	jmp	L532
L592:
	movl	$1713383465, _error
	movl	$1635019873, _error+4
	movl	$1852793632, _error+8
	movl	$1768122724, _error+12
	movw	$28271, _error+16
	jmp	L652
L591:
	movl	$1830823977, _error
	jmp	L651
	.section .rdata,"dr"
LC161:
	.ascii "w+\0"
LC162:
	.ascii "debug.err\0"
	.text
	.align 2
	.p2align 4,,15
.globl __Z10grabalineav
	.def	__Z10grabalineav;	.scl	2;	.type	32;	.endef
__Z10grabalineav:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%ebx
	subl	$12, %esp
	pushl	$LC161
	pushl	$LC162
	call	_fopen
	addl	$16, %esp
	movl	%eax, %ebx
	testl	%eax, %eax
	je	L679
	pushl	%ecx
	pushl	%ecx
	pushl	%eax
	pushl	$_error
	call	_fputs
	movl	%ebx, (%esp)
	call	_fclose
	addl	$16, %esp
L679:
	movl	-4(%ebp), %ebx
	leave
	ret
	.section .rdata,"dr"
LC163:
	.ascii "runtime.err\0"
LC164:
	.ascii "%s\15\0"
LC165:
	.ascii "IP: %d %d\15\0"
LC166:
	.ascii "D: \0"
LC168:
	.ascii "%d )\15\0"
LC169:
	.ascii "R: \0"
LC167:
	.ascii "%d \0"
LC170:
	.ascii ")\15\0"
LC171:
	.ascii "code:%d cnt:%d\15\0"
LC172:
	.ascii "data:%d cnt:%d\15\0"
LC173:
	.ascii "%d %d %d %d %d \15\0"
	.text
	.align 2
	.p2align 4,,15
.globl __Z26MyUnhandledExceptionFilterP19_EXCEPTION_POINTERS@4
	.def	__Z26MyUnhandledExceptionFilterP19_EXCEPTION_POINTERS@4;	.scl	2;	.type	32;	.endef
__Z26MyUnhandledExceptionFilterP19_EXCEPTION_POINTERS@4:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%edi
	pushl	%esi
	pushl	%ebx
	subl	$20, %esp
	pushl	$LC161
	pushl	$LC163
	call	_fopen
	addl	$12, %esp
	movl	%eax, %edi
	pushl	$_linea
	pushl	$LC164
	pushl	%eax
	call	_fprintf
	movl	8(%ebp), %edx
	movl	4(%edx), %eax
	movl	$_prog, %edx
	xorl	$-1, %edx
	movl	168(%eax), %ebx
	pushl	%ebx
	movl	$_PSP, %ebx
	movl	164(%eax), %ecx
	addl	%ecx, %edx
	pushl	%edx
	pushl	$LC165
	pushl	%edi
	call	_fprintf
	addl	$24, %esp
	pushl	$LC166
	pushl	%edi
	call	_fprintf
	movl	8(%ebp), %eax
	movl	4(%eax), %edx
	addl	$16, %esp
	movl	160(%edx), %esi
	movl	%esi, %eax
	subl	%ebx, %eax
	cmpl	$32, %eax
	jle	L683
	leal	-32(%esi), %ebx
L683:
	cmpl	%esi, %ebx
	jl	L687
L694:
	pushl	%eax
	movl	156(%edx), %eax
	pushl	%eax
	pushl	$LC168
	pushl	%edi
	call	_fprintf
	popl	%ebx
	popl	%esi
	pushl	$LC169
	pushl	%edi
	call	_fprintf
	movl	8(%ebp), %edx
	movl	4(%edx), %eax
	movl	$_RSP, %ebx
	addl	$16, %esp
	movl	180(%eax), %eax
	movl	-16(%eax), %esi
	movl	%esi, %eax
	subl	%ebx, %eax
	cmpl	$32, %eax
	jle	L688
	leal	-32(%esi), %ebx
L688:
	cmpl	%esi, %ebx
	jg	L696
	.p2align 4,,7
L697:
	pushl	%ecx
	movl	(%ebx), %edx
	addl	$4, %ebx
	pushl	%edx
	pushl	$LC167
	pushl	%edi
	call	_fprintf
	addl	$16, %esp
	cmpl	%esi, %ebx
	jle	L697
L696:
	pushl	%eax
	pushl	%eax
	pushl	$LC170
	pushl	%edi
	call	_fprintf
	movl	_cntprog, %eax
	pushl	%eax
	pushl	$_prog
	pushl	$LC171
	pushl	%edi
	call	_fprintf
	addl	$32, %esp
	movl	_cntdato, %eax
	pushl	%eax
	pushl	$_data
	pushl	$LC172
	pushl	%edi
	call	_fprintf
	addl	$12, %esp
	movl	_cntincludes, %eax
	movl	_cntnombre, %esi
	pushl	%eax
	movl	_cntnombreex, %eax
	pushl	%eax
	movl	_cntindice, %ebx
	movl	_cntindiceex, %eax
	pushl	%eax
	pushl	%esi
	pushl	%ebx
	pushl	$LC173
	pushl	%edi
	call	_fprintf
	addl	$20, %esp
	pushl	%edi
	call	_fclose
	leal	-12(%ebp), %esp
	movl	$1, %eax
	popl	%ebx
	popl	%esi
	popl	%edi
	popl	%ebp
	ret	$4
	.p2align 4,,7
L687:
	pushl	%eax
	movl	(%ebx), %eax
	addl	$4, %ebx
	pushl	%eax
	pushl	$LC167
	pushl	%edi
	call	_fprintf
	addl	$16, %esp
	cmpl	%esi, %ebx
	jl	L687
	movl	8(%ebp), %eax
	movl	4(%eax), %edx
	jmp	L694
	.section .rdata,"dr"
LC177:
	.ascii "winspool\0"
LC178:
	.ascii "r4doc\0"
LC175:
	.ascii "r4\0"
	.align 4
LC176:
	.ascii ":R4 console\12  c<CODIGO> compile\12  i<IMAGEN> build\12  x<IMAGEN> exec\12  w<SCRW>\12  h<SCRH>\12  f fullscreen \12  s without screen\12  ? help\12\0"
LC174:
	.ascii "r4.ini\0"
LC179:
	.ascii "%s|0|0|NO BOOT\0"
	.text
	.align 2
	.p2align 4,,15
.globl _WinMain@16
	.def	_WinMain@16;	.scl	2;	.type	32;	.endef
_WinMain@16:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%edi
	pushl	%esi
	pushl	%ebx
	subl	$72, %esp
	movl	$640, %edi
	pushl	$__Z26MyUnhandledExceptionFilterP19_EXCEPTION_POINTERS@4
	call	_SetUnhandledExceptionFilter@4
	movl	$480, -60(%ebp)
	movl	$0, -64(%ebp)
	movl	$0, -68(%ebp)
	movl	16(%ebp), %esi
	movl	$3092270, _pathdata
	pushl	$40
	pushl	$0
	pushl	$_wc
	call	__Z8mimemsetPcci
	addl	$12, %esp
	movl	$0, _wc
	movl	$__Z7WndProcP6HWND__jjl@16, _wc+4
	pushl	$0
	call	_GetModuleHandleA@4
	movl	$_wndclass, _wc+36
	movl	%eax, _wc+16
	pushl	$_wc
	call	_RegisterClassA@4
	orl	$-1, %edx
	addl	$12, %esp
	testw	%ax, %ax
	je	L698
	movl	$_pilaexec, %ebx
	movl	$1852399981, _pilaexec
	movl	%ebx, _pilaexecl
	movl	$1954051118, _pilaexec+4
	movb	$0, _pilaexec+8
	cmpb	$0, _pilaexec
	je	L762
	.p2align 4,,7
L702:
	movl	%ebx, %eax
	incl	%ebx
	movl	%ebx, _pilaexecl
	cmpb	$0, 1(%eax)
	jne	L702
L753:
	incl	%ebx
	movl	%ebx, _pilaexecl
L703:
	movl	$0, _rebotea
	movb	(%esi), %cl
	testb	%cl, %cl
	je	L782
	.p2align 4,,7
L725:
	cmpb	$105, %cl
	je	L783
	cmpb	$99, %cl
	je	L784
L709:
	cmpb	$120, %cl
	je	L785
	cmpb	$119, %cl
	je	L786
L714:
	cmpb	$104, %cl
	je	L787
L715:
	cmpb	$102, %cl
	je	L788
	cmpb	$115, %cl
	je	L789
	cmpb	$112, %cl
	je	L790
L718:
	cmpb	$63, %cl
	jne	L769
	jmp	L768
	.p2align 4,,7
L791:
	incl	%esi
	movb	(%esi), %cl
L769:
	cmpb	$32, %cl
	setne	%dl
	testb	%cl, %cl
	setne	%al
	testb	%al, %dl
	jne	L791
	cmpb	$32, %cl
	je	L792
	incl	%esi
L763:
	movb	(%esi), %cl
L704:
	testb	%cl, %cl
	jne	L725
	cmpl	$1, -64(%ebp)
	je	L793
	movl	$262144, _dwExStyle
	movl	$382205952, _dwStyle
L727:
	subl	$12, %esp
	pushl	$0
	call	_ShowCursor@4
	movl	-60(%ebp), %eax
	movl	$0, _rec+4
	movl	$0, _rec
	movl	%edi, _rec+8
	movl	%eax, _rec+12
	popl	%eax
	popl	%edx
	pushl	$0
	movl	_dwStyle, %ebx
	pushl	%ebx
	pushl	$_rec
	call	_AdjustWindowRect@12
	movl	$0, (%esp)
	movl	_wc+16, %ecx
	pushl	%ecx
	pushl	$0
	pushl	$0
	movl	_rec+4, %edx
	movl	_rec+12, %eax
	subl	%edx, %eax
	pushl	%eax
	movl	_rec, %ebx
	movl	_rec+8, %eax
	subl	%ebx, %eax
	pushl	%eax
	pushl	%ecx
	pushl	$1
	call	_GetSystemMetrics@4
	movl	_rec+12, %edx
	movl	_rec+4, %ebx
	subl	%edx, %eax
	addl	%ebx, %eax
	sarl	%eax
	movl	%eax, (%esp)
	pushl	$0
	call	_GetSystemMetrics@4
	movl	_rec+8, %ecx
	movl	_rec, %edx
	subl	%ecx, %eax
	addl	%edx, %eax
	sarl	%eax
	pushl	%eax
	movl	_dwStyle, %eax
	pushl	%eax
	movl	_wc+36, %eax
	pushl	%eax
	movl	_wc+36, %eax
	pushl	%eax
	movl	_dwExStyle, %eax
	pushl	%eax
	call	_CreateWindowExA@48
	movl	%eax, _hWnd
	testl	%eax, %eax
	je	L794
	subl	$12, %esp
	pushl	%eax
	call	_GetDC@4
	addl	$12, %esp
	movl	%eax, _hDC
	testl	%eax, %eax
	je	L795
	pushl	%eax
	pushl	%eax
	movl	-60(%ebp), %eax
	pushl	%eax
	pushl	%edi
	call	__Z7gr_initii
	addl	$16, %esp
	testl	%eax, %eax
	js	L796
	leal	-56(%ebp), %eax
	pushl	$0
	pushl	$0
	pushl	%eax
	pushl	$LC177
	call	_CreateDCA@16
	movl	%eax, _phDC
	pushl	$20
	pushl	$0
	pushl	$_di
	call	__Z8mimemsetPcci
	movl	$20, _di
	movl	$LC178, _di+4
	movl	$8, (%esp)
	movl	_phDC, %ebx
	pushl	%ebx
	call	_GetDeviceCaps@8
	movl	%eax, _cWidthPels
	pushl	$10
	movl	_phDC, %ecx
	pushl	%ecx
	call	_GetDeviceCaps@8
	movl	%eax, _cHeightPels
	pushl	$1
	movl	_phDC, %edx
	pushl	%edx
	call	_SetBkMode@8
	movl	$1634300481, _plf+28
	movw	$108, _plf+32
	movl	$400, _plf+16
	movl	$0, _plf+8
	pushl	%eax
	pushl	$_plf
	call	_CreateFontIndirectA@4
	movl	%eax, _hfnt
	movl	%eax, (%esp)
	movl	_phDC, %eax
	pushl	%eax
	call	_SelectObject@8
	movl	%eax, _hfntPrev
	pushl	$1
	movl	_phDC, %eax
	pushl	%eax
	call	_SetTextAlign@8
	pushl	%eax
	movl	_hWnd, %eax
	pushl	%eax
	call	__Z12InitJoystickP6HWND__
	call	__Z7loaddirv
	popl	%ebx
	popl	%eax
	pushl	$_wsaData
	pushl	$2
	call	_WSAStartup@8
	movl	$0, (%esp)
	pushl	$32
	pushl	$44100
	call	_FSOUND_Init@12
	popl	%ecx
	testb	%al, %al
	je	L797
L767:
	movl	_pilaexecl, %ebx
L776:
	movl	_exestr, %ecx
L732:
L775:
	leal	-2(%ebx), %edx
	movl	%edx, _bootstr
	cmpb	$0, -2(%ebx)
	je	L734
	.p2align 4,,7
L798:
	cmpl	$_pilaexec, %edx
	jbe	L737
	movl	%edx, %eax
	decl	%edx
	movl	%edx, _bootstr
	cmpb	$0, -1(%eax)
	jne	L798
L734:
	cmpl	$_pilaexec, %edx
	jbe	L737
	leal	1(%edx), %eax
	movl	$0, _bootaddr
	movl	%eax, _bootstr
	cmpb	$0, (%ecx)
	jne	L799
	.p2align 4,,7
L738:
	movl	_bootaddr, %edx
	testl	%edx, %edx
	jne	L743
L800:
	movl	_bootstr, %eax
	cmpb	$0, (%eax)
	je	L770
	pushl	%edx
	pushl	%edx
	pushl	%eax
	pushl	$_linea
	call	_strcpy
	movl	$0, _cntincludes
	movl	$0, _cntnombreex
	movl	$0, _cntindiceex
	movl	$0, _cntprog
	movl	$0, _cntdato
	movl	$0, _cntnombre
	movl	$0, _cntindice
	movl	$_linea, (%esp)
	call	__Z11compilafilePc
	addl	$16, %esp
	testl	%eax, %eax
	je	L740
	call	__Z10grabalineav
	movl	_DEBUGR4X, %eax
	cmpl	%eax, _exestr
	je	L779
	movl	%eax, %ecx
	movl	%eax, _exestr
L737:
	movl	$0, _bootaddr
	cmpb	$0, (%ecx)
	je	L738
L799:
	subl	$12, %esp
	pushl	%ecx
	call	__Z10loadimagenPc
	movl	_bootaddr, %edx
	addl	$16, %esp
	movl	$LC3, _exestr
	testl	%edx, %edx
	je	L800
L743:
	movl	_cntdato, %eax
	addl	$_data, %eax
	movl	%eax, _memlibre
	cmpl	$1, -68(%ebp)
	je	L745
	subl	$12, %esp
	pushl	%edx
	call	__Z10interpretePh
	addl	$16, %esp
	decl	%eax
	je	L767
L745:
	movl	_rebotea, %eax
	testl	%eax, %eax
	jne	L746
	movl	_pilaexecl, %eax
	leal	-2(%eax), %ebx
	movl	%ebx, _pilaexecl
	cmpb	$0, -2(%eax)
	je	L774
L801:
	cmpl	$_pilaexec, %ebx
	jbe	L748
	movl	%ebx, %eax
	decl	%ebx
	movl	%ebx, _pilaexecl
	cmpb	$0, -1(%eax)
	jne	L801
L774:
	leal	1(%ebx), %eax
	movl	%eax, %ebx
	movl	%eax, _pilaexecl
	jmp	L776
L792:
	movb	$0, (%esi)
	incl	%esi
	jmp	L763
L788:
	movl	$1, -64(%ebp)
	jmp	L769
L785:
	leal	1(%esi), %ecx
	movl	%ecx, _exestr
	movb	(%esi), %cl
	cmpb	$119, %cl
	jne	L714
L786:
	leal	1(%esi), %eax
	pushl	%eax
	call	__Z8esnumeroPc
	movb	(%esi), %cl
	movl	_numero, %edi
	popl	%eax
	cmpb	$104, %cl
	jne	L715
L787:
	leal	1(%esi), %eax
	pushl	%eax
	call	__Z8esnumeroPc
	movl	_numero, %eax
	movl	%eax, -60(%ebp)
	popl	%ebx
	movb	(%esi), %cl
	jmp	L715
L783:
	leal	1(%esi), %eax
	movl	%eax, _compilastr
	movb	(%esi), %cl
	cmpb	$99, %cl
	jne	L709
L784:
	movl	$LC3, _exestr
	pushl	%eax
	pushl	%eax
	leal	1(%esi), %eax
	movl	$_pilaexec, %ebx
	pushl	%eax
	pushl	$_pilaexec
	call	_strcpy
	addl	$16, %esp
	movl	%ebx, _pilaexecl
	cmpb	$32, _pilaexec
	jle	L764
	.p2align 4,,7
L712:
	movl	%ebx, %eax
	incl	%ebx
	movl	%ebx, _pilaexecl
	cmpb	$32, 1(%eax)
	jg	L712
	movb	$0, (%ebx)
	movl	_pilaexecl, %eax
	incl	%eax
	movl	%eax, _pilaexecl
	movb	(%esi), %cl
	jmp	L709
L789:
	movl	$1, -68(%ebp)
	jmp	L769
L768:
	pushl	%esi
	pushl	%esi
	pushl	$LC175
	pushl	$LC176
	call	_printf
	addl	$16, %esp
	xorl	%edx, %edx
L698:
	leal	-12(%ebp), %esp
	movl	%edx, %eax
	popl	%ebx
	popl	%esi
	popl	%edi
	popl	%ebp
	ret	$16
L762:
	movl	_pilaexecl, %ebx
	jmp	L753
L782:
	pushl	%eax
	pushl	%eax
	pushl	$LC155
	pushl	$LC174
	call	_fopen
	addl	$16, %esp
	movl	%eax, _file
	testl	%eax, %eax
	je	L763
	pushl	%eax
	pushl	$1024
	pushl	$1
	pushl	$_setings
	call	_fread
	popl	%eax
	movl	_file, %eax
	movl	$_setings, %esi
	pushl	%eax
	call	_fclose
	addl	$16, %esp
	movb	_setings, %cl
	jmp	L704
L793:
	movl	$512, _dwExStyle
	movl	$13565952, _dwStyle
	jmp	L727
L740:
	movl	_compilastr, %eax
	cmpb	$0, (%eax)
	jne	L802
L766:
	movl	_bootaddr, %edx
	testl	%edx, %edx
	jne	L743
L770:
	pushl	%eax
	pushl	$_linea
	pushl	$LC179
	pushl	$_error
	call	_sprintf
	call	__Z10grabalineav
	movl	_DEBUGR4X, %eax
	addl	$16, %esp
	cmpl	%eax, _exestr
	je	L779
	movl	%eax, %ecx
	movl	_pilaexecl, %ebx
	movl	%eax, _exestr
	jmp	L775
L779:
	movl	$1, %edx
	leal	-12(%ebp), %esp
	movl	%edx, %eax
	popl	%ebx
	popl	%esi
	popl	%edi
	popl	%ebp
	ret	$16
L748:
	cmpb	$0, (%ebx)
	je	L774
L746:
	call	_FSOUND_Close@0
	pushl	%eax
	pushl	%eax
	movl	_hfntPrev, %eax
	pushl	%eax
	movl	_phDC, %eax
	pushl	%eax
	call	_SelectObject@8
	pushl	%ebx
	movl	_hfnt, %ecx
	pushl	%ecx
	call	_DeleteObject@4
	movl	_phDC, %edx
	pushl	%edx
	call	_DeleteDC@4
	addl	$12, %esp
	call	__Z15ReleaseJoystickv
	subl	$12, %esp
	movl	_soc, %eax
	pushl	%eax
	call	_closesocket@4
	addl	$12, %esp
	call	_WSACleanup@0
	call	__Z6gr_finv
	pushl	%eax
	pushl	%eax
	movl	_hDC, %eax
	pushl	%eax
	movl	_hWnd, %eax
	pushl	%eax
	call	_ReleaseDC@8
	pushl	%eax
	movl	_hWnd, %eax
	pushl	%eax
	call	_DestroyWindow@4
	pushl	$1
	call	_ShowCursor@4
	addl	$12, %esp
	cmpl	$1, _rebotea
	je	L703
	subl	$12, %esp
	pushl	$0
	call	_ExitProcess@4
	.p2align 4,,7
L790:
	leal	1(%esi), %eax
	pushl	%ecx
	pushl	%ecx
	pushl	%eax
	leal	-56(%ebp), %eax
	pushl	%eax
	call	_strcpy
	addl	$16, %esp
	movb	(%esi), %cl
	jmp	L718
L764:
	movl	_pilaexecl, %ebx
	movb	$0, (%ebx)
	movl	_pilaexecl, %eax
	incl	%eax
	movl	%eax, _pilaexecl
	movb	(%esi), %cl
	jmp	L709
L802:
	subl	$12, %esp
	pushl	%eax
	call	__Z10saveimagenPc
	addl	$16, %esp
	jmp	L766
L795:
	movl	$-3, %edx
	jmp	L698
L796:
	orl	$-1, %edx
	jmp	L698
L794:
	movl	$-2, %edx
	jmp	L698
L797:
	movl	$-4, %edx
	jmp	L698
	.def	_memset;	.scl	2;	.type	32;	.endef
	.def	_strlen;	.scl	2;	.type	32;	.endef
	.def	__Z6gr_finv;	.scl	3;	.type	32;	.endef
	.def	__Z15ReleaseJoystickv;	.scl	3;	.type	32;	.endef
	.def	__Z12InitJoystickP6HWND__;	.scl	3;	.type	32;	.endef
	.def	__Z7gr_initii;	.scl	3;	.type	32;	.endef
	.def	_printf;	.scl	2;	.type	32;	.endef
	.def	_fprintf;	.scl	2;	.type	32;	.endef
	.def	_fputs;	.scl	2;	.type	32;	.endef
	.def	_fgets;	.scl	3;	.type	32;	.endef
	.def	_strcmp;	.scl	2;	.type	32;	.endef
	.def	_sprintf;	.scl	2;	.type	32;	.endef
	.def	__Z7fillTexv;	.scl	3;	.type	32;	.endef
	.def	__Z7fillRadv;	.scl	3;	.type	32;	.endef
	.def	__Z7fillLinv;	.scl	3;	.type	32;	.endef
	.def	__Z7fillSolv;	.scl	3;	.type	32;	.endef
	.def	__Z11gr_drawPoliv;	.scl	3;	.type	32;	.endef
	.def	__Z10gr_psplineiiiiii;	.scl	3;	.type	32;	.endef
	.def	__Z12gr_psegmentoiiii;	.scl	3;	.type	32;	.endef
	.def	__Z9gr_splineiiiiii;	.scl	3;	.type	32;	.endef
	.def	__Z7gr_lineiiii;	.scl	3;	.type	32;	.endef
	.def	__Z8gr_alphav;	.scl	3;	.type	32;	.endef
	.def	__Z8gr_solidv;	.scl	3;	.type	32;	.endef
	.def	__Z8gr_xfbtov;	.scl	3;	.type	32;	.endef
	.def	__Z8gr_toxfbv;	.scl	3;	.type	32;	.endef
	.def	__Z9gr_clrscrv;	.scl	3;	.type	32;	.endef
	.def	_localtime;	.scl	3;	.type	32;	.endef
	.def	_time;	.scl	3;	.type	32;	.endef
	.def	__Z9gr_redrawv;	.scl	3;	.type	32;	.endef
	.def	__Z6getjoyi;	.scl	3;	.type	32;	.endef
	.def	_strcpy;	.scl	2;	.type	32;	.endef
	.def	_strncpy;	.scl	2;	.type	32;	.endef
	.def	_fread;	.scl	3;	.type	32;	.endef
	.def	_fclose;	.scl	3;	.type	32;	.endef
	.def	_fwrite;	.scl	2;	.type	32;	.endef
	.def	_fopen;	.scl	3;	.type	32;	.endef
