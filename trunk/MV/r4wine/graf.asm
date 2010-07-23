	.file	"graf.cpp"
.globl _fillpoly
	.bss
	.align 4
_fillpoly:
	.space 4
.globl _gr_pixela
	.align 4
_gr_pixela:
	.space 4
.globl _gr_pixel
	.align 4
_gr_pixel:
	.space 4
.globl _setxyf
	.align 4
_setxyf:
	.space 4
.globl _bmi
	.data
	.align 32
_bmi:
	.long	40
	.long	800
	.long	-600
	.word	1
	.word	32
	.long	0
	.long	0
	.long	0
	.long	0
	.long	0
	.long	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
.globl _gr_alphav
	.bss
_gr_alphav:
	.space 1
.globl _yMax
	.align 4
_yMax:
	.space 4
.globl _yMin
	.align 4
_yMin:
	.space 4
.globl _cntSegm
	.align 4
_cntSegm:
	.space 4
.globl _xquis
	.align 32
_xquis:
	.space 1024
.globl _xquisc
	.align 4
_xquisc:
	.space 4
.globl _actual
	.align 32
_actual:
	.space 1024
.globl _pact
	.align 4
_pact:
	.space 4
.globl _segmentos
	.align 32
_segmentos:
	.space 16384
.globl _mTex
	.align 4
_mTex:
	.space 4
.globl _MTY
	.align 4
_MTY:
	.space 4
.globl _MTX
	.align 4
_MTX:
	.space 4
.globl _MB
	.align 4
_MB:
	.space 4
.globl _MA
	.align 4
_MA:
	.space 4
.globl _gr_ypitch
	.align 4
_gr_ypitch:
	.space 4
.globl _col2
	.align 4
_col2:
	.space 4
.globl _col1
	.align 4
_col1:
	.space 4
.globl _gr_color2
	.align 4
_gr_color2:
	.space 4
.globl _gr_color1
	.align 4
_gr_color1:
	.space 4
.globl _gr_alto
	.align 4
_gr_alto:
	.space 4
.globl _gr_ancho
	.align 4
_gr_ancho:
	.space 4
.globl _XFB
	.align 4
_XFB:
	.space 4
.globl _gr_buffer
	.align 4
_gr_buffer:
	.space 4
.globl _hRC
	.align 4
_hRC:
	.space 4
.globl _hDC
	.align 4
_hDC:
	.space 4
.lcomm _gr_sizescreen,16
	.text
	.align 2
	.p2align 4,,15
.globl __Z5setxyii
	.def	__Z5setxyii;	.scl	2;	.type	32;	.endef
__Z5setxyii:
	pushl	%ebp
	movl	_gr_ancho, %eax
	movl	%esp, %ebp
	movl	12(%ebp), %ecx
	movl	8(%ebp), %edx
	imull	%ecx, %eax
	addl	%edx, %eax
	movl	_gr_buffer, %edx
	popl	%ebp
	leal	(%edx,%eax,4), %eax
	ret
	.align 2
	.p2align 4,,15
.globl __Z8setxy640ii
	.def	__Z8setxy640ii;	.scl	2;	.type	32;	.endef
__Z8setxy640ii:
	pushl	%ebp
	movl	%esp, %ebp
	movl	12(%ebp), %edx
	movl	%edx, %eax
	sall	$7, %eax
	sall	$9, %edx
	addl	%edx, %eax
	movl	8(%ebp), %edx
	addl	%edx, %eax
	movl	_gr_buffer, %edx
	popl	%ebp
	leal	(%edx,%eax,4), %eax
	ret
	.align 2
	.p2align 4,,15
.globl __Z8setxy800ii
	.def	__Z8setxy800ii;	.scl	2;	.type	32;	.endef
__Z8setxy800ii:
	pushl	%ebp
	movl	%esp, %ebp
	movl	12(%ebp), %edx
	movl	8(%ebp), %ecx
	movl	%edx, %eax
	popl	%ebp
	sall	$8, %edx
	sall	$5, %eax
	addl	%edx, %eax
	addl	%edx, %edx
	addl	%edx, %eax
	movl	_gr_buffer, %edx
	addl	%ecx, %eax
	leal	(%edx,%eax,4), %eax
	ret
	.align 2
	.p2align 4,,15
.globl __Z9setxy1024ii
	.def	__Z9setxy1024ii;	.scl	2;	.type	32;	.endef
__Z9setxy1024ii:
	pushl	%ebp
	movl	_gr_buffer, %edx
	movl	%esp, %ebp
	movl	12(%ebp), %eax
	movl	8(%ebp), %ecx
	sall	$10, %eax
	popl	%ebp
	addl	%ecx, %eax
	addl	%edx, %eax
	sall	$2, %eax
	ret
	.align 2
	.p2align 4,,15
.globl __Z9setxy1280ii
	.def	__Z9setxy1280ii;	.scl	2;	.type	32;	.endef
__Z9setxy1280ii:
	pushl	%ebp
	movl	%esp, %ebp
	movl	12(%ebp), %edx
	movl	8(%ebp), %ecx
	movl	%edx, %eax
	popl	%ebp
	sall	$8, %edx
	sall	$10, %eax
	addl	%edx, %eax
	movl	_gr_buffer, %edx
	addl	%ecx, %eax
	addl	%edx, %eax
	sall	$2, %eax
	ret
	.align 2
	.p2align 4,,15
.globl __Z7fillSolv
	.def	__Z7fillSolv;	.scl	2;	.type	32;	.endef
__Z7fillSolv:
	pushl	%ebp
	movl	$__Z13_FlineaSolidoiP4SegmS0_, _fillpoly
	movl	%esp, %ebp
	popl	%ebp
	ret
	.align 2
	.p2align 4,,15
.globl __Z8gr_solidv
	.def	__Z8gr_solidv;	.scl	2;	.type	32;	.endef
__Z8gr_solidv:
	pushl	%ebp
	movl	$__Z10_gr_pixelsPm, _gr_pixel
	movl	%esp, %ebp
	movl	$__Z10_gr_pixelaPmh, _gr_pixela
	movb	$-1, _gr_alphav
	popl	%ebp
	ret
	.align 2
	.p2align 4,,15
.globl __Z7gr_initii
	.def	__Z7gr_initii;	.scl	2;	.type	32;	.endef
__Z7gr_initii:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%esi
	pushl	%ebx
	pushl	$4
	movl	8(%ebp), %esi
	movl	12(%ebp), %ebx
	movl	%esi, %eax
	pushl	$4096
	imull	%ebx, %eax
	movl	%eax, _gr_sizescreen
	sall	$2, %eax
	pushl	%eax
	pushl	$0
	call	_VirtualAlloc@16
	movl	%eax, _gr_buffer
	movl	_gr_sizescreen, %eax
	sall	$2, %eax
	pushl	$4
	pushl	$4096
	pushl	%eax
	pushl	$0
	call	_VirtualAlloc@16
	movl	%esi, _gr_ancho
	movl	%eax, _XFB
	movl	%esi, _gr_ypitch
	movl	%ebx, _gr_alto
	cmpl	$800, %esi
	je	L11
	jg	L15
	cmpl	$640, %esi
	je	L10
L14:
	movl	$__Z5setxyii, _setxyf
L9:
	leal	1(%ebx), %eax
	movl	$0, _cntSegm
	movl	%eax, _yMin
	movl	$-1, _yMax
	call	__Z7fillSolv
	movl	$0, _gr_color2
	movl	$16777215, _gr_color1
	movl	$0, _col1
	movl	$16777215, _col2
	call	__Z8gr_solidv
	negl	%ebx
	movl	%esi, _bmi+4
	movl	%ebx, _bmi+8
	xorl	%eax, %eax
	leal	-8(%ebp), %esp
	popl	%ebx
	popl	%esi
	popl	%ebp
	ret
	.p2align 4,,7
L15:
	cmpl	$1024, %esi
	je	L12
	cmpl	$1280, %esi
	jne	L14
	movl	$__Z9setxy1280ii, _setxyf
	jmp	L9
	.p2align 4,,7
L11:
	movl	$__Z8setxy800ii, _setxyf
	jmp	L9
	.p2align 4,,7
L12:
	movl	$__Z9setxy1024ii, _setxyf
	jmp	L9
	.p2align 4,,7
L10:
	movl	$__Z8setxy640ii, _setxyf
	jmp	L9
	.align 2
	.p2align 4,,15
.globl __Z9gr_redrawv
	.def	__Z9gr_redrawv;	.scl	2;	.type	32;	.endef
__Z9gr_redrawv:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$20, %esp
	movl	_gr_buffer, %eax
	pushl	$13369376
	pushl	$0
	pushl	$_bmi
	pushl	%eax
	movl	_gr_alto, %eax
	pushl	%eax
	movl	_gr_ancho, %eax
	pushl	%eax
	movl	_gr_alto, %eax
	pushl	$0
	pushl	$0
	pushl	%eax
	movl	_gr_ancho, %eax
	pushl	%eax
	movl	_hDC, %eax
	pushl	$0
	pushl	$0
	pushl	%eax
	call	_StretchDIBits@52
	leave
	ret
	.align 2
	.p2align 4,,15
.globl __Z6gr_finv
	.def	__Z6gr_finv;	.scl	2;	.type	32;	.endef
__Z6gr_finv:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$12, %esp
	movl	_XFB, %ecx
	pushl	$32768
	pushl	$0
	pushl	%ecx
	call	_VirtualFree@12
	movl	_gr_buffer, %edx
	pushl	$32768
	pushl	$0
	pushl	%edx
	call	_VirtualFree@12
	leave
	ret
	.align 2
	.p2align 4,,15
.globl __Z9gr_clrscrv
	.def	__Z9gr_clrscrv;	.scl	2;	.type	32;	.endef
__Z9gr_clrscrv:
	pushl	%ebp
	movl	_gr_buffer, %ecx
	movl	%esp, %ebp
	movl	_gr_sizescreen, %edx
	jmp	L26
	.p2align 4,,7
L27:
	movl	_gr_color2, %eax
	decl	%edx
	movl	%eax, (%ecx)
	addl	$4, %ecx
L26:
	testl	%edx, %edx
	jg	L27
	popl	%ebp
	ret
	.align 2
	.p2align 4,,15
.globl __Z8gr_toxfbv
	.def	__Z8gr_toxfbv;	.scl	2;	.type	32;	.endef
__Z8gr_toxfbv:
	pushl	%ebp
	movl	_XFB, %ecx
	movl	%esp, %ebp
	movl	_gr_sizescreen, %edx
	pushl	%ebx
	movl	_gr_buffer, %ebx
	jmp	L34
	.p2align 4,,7
L35:
	movl	(%ebx), %eax
	decl	%edx
	movl	%eax, (%ecx)
	addl	$4, %ebx
	addl	$4, %ecx
L34:
	testl	%edx, %edx
	jg	L35
	popl	%ebx
	popl	%ebp
	ret
	.align 2
	.p2align 4,,15
.globl __Z8gr_xfbtov
	.def	__Z8gr_xfbtov;	.scl	2;	.type	32;	.endef
__Z8gr_xfbtov:
	pushl	%ebp
	movl	_XFB, %ecx
	movl	%esp, %ebp
	movl	_gr_sizescreen, %edx
	pushl	%ebx
	movl	_gr_buffer, %ebx
	jmp	L42
	.p2align 4,,7
L43:
	movl	(%ecx), %eax
	decl	%edx
	movl	%eax, (%ebx)
	addl	$4, %ecx
	addl	$4, %ebx
L42:
	testl	%edx, %edx
	jg	L43
	popl	%ebx
	popl	%ebp
	ret
	.align 2
	.p2align 4,,15
.globl __Z10_gr_pixelsPm
	.def	__Z10_gr_pixelsPm;	.scl	2;	.type	32;	.endef
__Z10_gr_pixelsPm:
	pushl	%ebp
	movl	_gr_color1, %edx
	movl	%esp, %ebp
	movl	8(%ebp), %eax
	movl	%edx, (%eax)
	popl	%ebp
	ret
	.align 2
	.p2align 4,,15
.globl __Z10_gr_pixelaPmh
	.def	__Z10_gr_pixelaPmh;	.scl	2;	.type	32;	.endef
__Z10_gr_pixelaPmh:
	pushl	%ebp
	movl	_gr_color1, %eax
	movl	%esp, %ebp
	pushl	%edi
	pushl	%esi
	pushl	%ebx
	movl	8(%ebp), %esi
	movl	%eax, %edx
	andl	$16711935, %edx
	xorl	%ecx, %ecx
	movl	(%esi), %ebx
	movb	12(%ebp), %cl
	movl	%ebx, %edi
	andl	$65280, %eax
	andl	$16711935, %edi
	subl	%edi, %edx
	imull	%ecx, %edx
	shrl	$8, %edx
	addl	%edi, %edx
	movl	%ebx, %edi
	andl	$65280, %edi
	andl	$16711935, %edx
	subl	%edi, %eax
	imull	%ecx, %eax
	shrl	$8, %eax
	addl	%edi, %eax
	andl	$65280, %eax
	orl	%edx, %eax
	movl	%eax, (%esi)
	popl	%ebx
	popl	%esi
	popl	%edi
	popl	%ebp
	ret
	.align 2
	.p2align 4,,15
.globl __Z11_gr_pixelsaPm
	.def	__Z11_gr_pixelsaPm;	.scl	2;	.type	32;	.endef
__Z11_gr_pixelsaPm:
	pushl	%ebp
	movl	_gr_color1, %eax
	movl	%esp, %ebp
	pushl	%edi
	pushl	%esi
	pushl	%ebx
	movl	8(%ebp), %esi
	movl	%eax, %edx
	andl	$16711935, %edx
	xorl	%ecx, %ecx
	movl	(%esi), %ebx
	movb	_gr_alphav, %cl
	movl	%ebx, %edi
	andl	$65280, %eax
	andl	$16711935, %edi
	subl	%edi, %edx
	imull	%ecx, %edx
	shrl	$8, %edx
	addl	%edi, %edx
	movl	%ebx, %edi
	andl	$65280, %edi
	andl	$16711935, %edx
	subl	%edi, %eax
	imull	%ecx, %eax
	shrl	$8, %eax
	addl	%edi, %eax
	andl	$65280, %eax
	orl	%edx, %eax
	movl	%eax, (%esi)
	popl	%ebx
	popl	%esi
	popl	%edi
	popl	%ebp
	ret
	.align 2
	.p2align 4,,15
.globl __Z11_gr_pixelaaPmh
	.def	__Z11_gr_pixelaaPmh;	.scl	2;	.type	32;	.endef
__Z11_gr_pixelaaPmh:
	pushl	%ebp
	xorl	%ecx, %ecx
	movl	%esp, %ebp
	xorl	%eax, %eax
	movb	_gr_alphav, %al
	pushl	%edi
	movb	12(%ebp), %cl
	pushl	%esi
	imull	%eax, %ecx
	movl	8(%ebp), %esi
	pushl	%ebx
	shrl	$8, %ecx
	movl	_gr_color1, %eax
	movl	(%esi), %ebx
	movl	%eax, %edx
	movl	%ebx, %edi
	andl	$16711935, %edx
	andl	$16711935, %edi
	andl	$65280, %eax
	subl	%edi, %edx
	imull	%ecx, %edx
	shrl	$8, %edx
	addl	%edi, %edx
	movl	%ebx, %edi
	andl	$65280, %edi
	andl	$16711935, %edx
	subl	%edi, %eax
	imull	%ecx, %eax
	shrl	$8, %eax
	addl	%edi, %eax
	andl	$65280, %eax
	orl	%edx, %eax
	movl	%eax, (%esi)
	popl	%ebx
	popl	%esi
	popl	%edi
	popl	%ebp
	ret
	.align 2
	.p2align 4,,15
.globl __Z8gr_alphav
	.def	__Z8gr_alphav;	.scl	2;	.type	32;	.endef
__Z8gr_alphav:
	pushl	%ebp
	movl	$__Z11_gr_pixelsaPm, _gr_pixel
	movl	%esp, %ebp
	movl	$__Z11_gr_pixelaaPmh, _gr_pixela
	popl	%ebp
	ret
	.align 2
	.p2align 4,,15
.globl __Z7fillLinv
	.def	__Z7fillLinv;	.scl	2;	.type	32;	.endef
__Z7fillLinv:
	pushl	%ebp
	movl	$__Z9_FlineaDLiP4SegmS0_, _fillpoly
	movl	%esp, %ebp
	popl	%ebp
	ret
	.align 2
	.p2align 4,,15
.globl __Z7fillRadv
	.def	__Z7fillRadv;	.scl	2;	.type	32;	.endef
__Z7fillRadv:
	pushl	%ebp
	movl	$__Z9_FlineaDRiP4SegmS0_, _fillpoly
	movl	%esp, %ebp
	popl	%ebp
	ret
	.align 2
	.p2align 4,,15
.globl __Z7fillTexv
	.def	__Z7fillTexv;	.scl	2;	.type	32;	.endef
__Z7fillTexv:
	pushl	%ebp
	movl	$__Z9_FlineaTXiP4SegmS0_, _fillpoly
	movl	%esp, %ebp
	popl	%ebp
	ret
	.align 2
	.p2align 4,,15
.globl __Z8gr_hlineiii
	.def	__Z8gr_hlineiii;	.scl	2;	.type	32;	.endef
__Z8gr_hlineiii:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%esi
	pushl	%ebx
	movl	8(%ebp), %ecx
	movl	16(%ebp), %esi
	movl	%ecx, %eax
	movl	12(%ebp), %edx
	xorl	$-1, %eax
	sarl	$31, %eax
	andl	%eax, %ecx
	movl	_gr_ancho, %eax
	cmpl	%eax, %esi
	jl	L57
	leal	-1(%eax), %esi
	cmpl	%eax, %ecx
	jge	L55
L57:
	movl	_gr_ypitch, %ebx
	movl	_gr_buffer, %eax
	imull	%ebx, %edx
	addl	%ecx, %edx
	leal	(%eax,%edx,4), %ebx
	leal	0(,%ecx,4), %edx
	leal	(%ebx,%esi,4), %eax
	subl	%edx, %eax
	leal	4(%eax), %esi
	.p2align 4,,7
L59:
	subl	$12, %esp
	pushl	%ebx
	addl	$4, %ebx
	call	*_gr_pixel
	addl	$16, %esp
	cmpl	%esi, %ebx
	jb	L59
L55:
	leal	-8(%ebp), %esp
	popl	%ebx
	popl	%esi
	popl	%ebp
	ret
	.align 2
	.p2align 4,,15
.globl __Z8gr_vlineiii
	.def	__Z8gr_vlineiii;	.scl	2;	.type	32;	.endef
__Z8gr_vlineiii:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%esi
	pushl	%ebx
	movl	12(%ebp), %ecx
	movl	16(%ebp), %esi
	movl	%ecx, %eax
	xorl	$-1, %eax
	sarl	$31, %eax
	andl	%eax, %ecx
	movl	_gr_alto, %eax
	cmpl	%eax, %esi
	jl	L64
	leal	-1(%eax), %esi
	cmpl	%eax, %ecx
	jge	L62
L64:
	movl	_gr_ypitch, %ebx
	movl	%ecx, %eax
	imull	%ebx, %eax
	movl	8(%ebp), %edx
	subl	%ecx, %esi
	addl	%edx, %eax
	movl	_gr_buffer, %edx
	leal	(%edx,%eax,4), %ebx
	leal	4(,%esi,4), %eax
	movl	_gr_ancho, %esi
	imull	%esi, %eax
	leal	(%eax,%ebx), %esi
	.p2align 4,,7
L66:
	subl	$12, %esp
	pushl	%ebx
	call	*_gr_pixel
	movl	_gr_ypitch, %eax
	addl	$16, %esp
	leal	(%ebx,%eax,4), %ebx
	cmpl	%esi, %ebx
	jb	L66
L62:
	leal	-8(%ebp), %esp
	popl	%ebx
	popl	%esi
	popl	%ebp
	ret
	.align 2
	.p2align 4,,15
.globl __Z11gr_cliplinePiS_S_S_
	.def	__Z11gr_cliplinePiS_S_S_;	.scl	2;	.type	32;	.endef
__Z11gr_cliplinePiS_S_S_:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%edi
	pushl	%esi
	pushl	%ebx
	subl	$20, %esp
	movl	8(%ebp), %eax
	movl	_gr_ancho, %ebx
	movl	(%eax), %eax
	movl	%eax, %edi
	movl	%eax, -24(%ebp)
	shrl	$31, %edi
	cmpl	%ebx, %eax
	jl	L72
	orl	$2, %edi
L72:
	movl	12(%ebp), %edx
	movl	(%edx), %edx
	movl	%edx, -28(%ebp)
	testl	%edx, %edx
	js	L100
L73:
	movl	_gr_alto, %ecx
	movl	%ecx, -20(%ebp)
	decl	%ecx
	movl	%ecx, -32(%ebp)
	cmpl	%ecx, -28(%ebp)
	jl	L74
	orl	$8, %edi
L74:
	movl	16(%ebp), %esi
	movl	(%esi), %eax
	movl	%eax, %esi
	shrl	$31, %esi
	cmpl	%ebx, %eax
	jl	L77
	orl	$2, %esi
L77:
	movl	20(%ebp), %edx
	movl	(%edx), %ecx
	testl	%ecx, %ecx
	js	L101
L78:
	cmpl	-32(%ebp), %ecx
	jl	L79
	orl	$8, %esi
L79:
	testl	%esi, %edi
	jne	L80
	movl	%edi, %edx
	orl	%esi, %edx
	je	L80
	testl	$12, %edi
	jne	L102
L81:
	testl	$12, %esi
	je	L87
	movl	$0, -16(%ebp)
	cmpl	$7, %esi
	jle	L89
	movl	_gr_alto, %esi
	subl	$2, %esi
	movl	%esi, -16(%ebp)
L89:
	movl	16(%ebp), %ecx
	movl	20(%ebp), %edx
	movl	-24(%ebp), %esi
	movl	(%ecx), %ebx
	movl	(%edx), %eax
	movl	%ebx, %ecx
	movl	-16(%ebp), %edx
	subl	%esi, %ecx
	subl	%eax, %edx
	imull	%ecx, %edx
	movl	-28(%ebp), %ecx
	subl	%ecx, %eax
	movl	20(%ebp), %ecx
	movl	%eax, %esi
	movl	%edx, %eax
	sarl	$31, %edx
	idivl	%esi
	movl	16(%ebp), %edx
	leal	(%ebx,%eax), %eax
	movl	-16(%ebp), %ebx
	movl	%eax, (%edx)
	movl	%ebx, (%ecx)
	movl	(%edx), %eax
	movl	_gr_ancho, %ebx
	movl	%eax, %esi
	shrl	$31, %esi
	cmpl	%ebx, %eax
	jl	L87
	orl	$2, %esi
	.p2align 4,,7
L87:
	testl	%esi, %edi
	jne	L80
	movl	%edi, %eax
	orl	%esi, %eax
	je	L80
	testl	%edi, %edi
	jne	L103
L94:
	testl	%esi, %esi
	je	L80
	movl	$0, -16(%ebp)
	decl	%esi
	je	L99
	movl	_gr_ancho, %ecx
	decl	%ecx
	movl	%ecx, -16(%ebp)
L99:
	movl	16(%ebp), %ebx
	movl	20(%ebp), %esi
	movl	-16(%ebp), %edx
	movl	(%ebx), %eax
	movl	(%esi), %ebx
	movl	12(%ebp), %esi
	movl	%ebx, %ecx
	subl	%eax, %edx
	subl	(%esi), %ecx
	imull	%ecx, %edx
	movl	8(%ebp), %ecx
	movl	(%ecx), %esi
	movl	-16(%ebp), %ecx
	subl	%esi, %eax
	movl	%eax, %esi
	movl	%edx, %eax
	sarl	$31, %edx
	idivl	%esi
	addl	%eax, %ebx
	movl	16(%ebp), %edx
	movl	20(%ebp), %eax
	xorl	%esi, %esi
	movl	%ebx, (%eax)
	movl	%ecx, (%edx)
	.p2align 4,,7
L80:
	orl	%esi, %edi
	sete	%al
	andl	$255, %eax
	addl	$20, %esp
	popl	%ebx
	popl	%esi
	popl	%edi
	popl	%ebp
	ret
	.p2align 4,,7
L101:
	orl	$4, %esi
	jmp	L78
	.p2align 4,,7
L100:
	orl	$4, %edi
	jmp	L73
	.p2align 4,,7
L102:
	movl	$0, -16(%ebp)
	cmpl	$7, %edi
	jle	L83
	movl	-20(%ebp), %ebx
	subl	$2, %ebx
	movl	%ebx, -16(%ebp)
L83:
	movl	-24(%ebp), %ebx
	movl	-28(%ebp), %edi
	movl	-16(%ebp), %edx
	subl	%ebx, %eax
	subl	%edi, %edx
	movl	-24(%ebp), %edi
	imull	%eax, %edx
	movl	-28(%ebp), %eax
	subl	%eax, %ecx
	movl	%edx, %eax
	sarl	$31, %edx
	idivl	%ecx
	addl	%eax, %edi
	movl	12(%ebp), %ecx
	movl	%edi, -24(%ebp)
	movl	8(%ebp), %edi
	movl	-24(%ebp), %eax
	movl	-16(%ebp), %edx
	movl	%eax, (%edi)
	movl	%edx, (%ecx)
	movl	(%edi), %ebx
	movl	%edx, -28(%ebp)
	movl	%ebx, -24(%ebp)
	movl	%ebx, %edi
	shrl	$31, %edi
	movl	_gr_ancho, %ebx
	cmpl	%ebx, -24(%ebp)
	jl	L81
	orl	$2, %edi
	jmp	L81
L103:
	movl	$0, -16(%ebp)
	decl	%edi
	je	L96
	decl	%ebx
	movl	%ebx, -16(%ebp)
L96:
	movl	8(%ebp), %edx
	movl	20(%ebp), %ecx
	movl	12(%ebp), %edi
	movl	(%edx), %ebx
	movl	(%ecx), %eax
	movl	-16(%ebp), %edx
	movl	(%edi), %ecx
	subl	%ecx, %eax
	subl	%ebx, %edx
	imull	%eax, %edx
	movl	16(%ebp), %edi
	movl	(%edi), %eax
	movl	12(%ebp), %edi
	subl	%ebx, %eax
	movl	%eax, %ebx
	movl	%edx, %eax
	sarl	$31, %edx
	idivl	%ebx
	addl	%eax, %ecx
	movl	8(%ebp), %eax
	movl	%ecx, (%edi)
	movl	-16(%ebp), %edx
	xorl	%edi, %edi
	movl	%edx, (%eax)
	jmp	L94
	.align 2
	.p2align 4,,15
.globl __Z7gr_lineiiii
	.def	__Z7gr_lineiiii;	.scl	2;	.type	32;	.endef
__Z7gr_lineiiii:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%edi
	pushl	%esi
	pushl	%ebx
	subl	$12, %esp
	leal	20(%ebp), %eax
	pushl	%eax
	leal	16(%ebp), %eax
	pushl	%eax
	leal	12(%ebp), %eax
	pushl	%eax
	leal	8(%ebp), %eax
	pushl	%eax
	call	__Z11gr_cliplinePiS_S_S_
	addl	$16, %esp
	testb	%al, %al
	je	L104
	movl	8(%ebp), %ecx
	movl	16(%ebp), %ebx
	cmpl	%ebx, %ecx
	je	L133
	movl	12(%ebp), %esi
	movl	20(%ebp), %edx
	cmpl	%edx, %esi
	je	L134
	jg	L135
L112:
	subl	%ecx, %ebx
	movl	%edx, %edi
	subl	%esi, %edi
	movl	%ebx, -16(%ebp)
	movl	$1, -20(%ebp)
	testl	%ebx, %ebx
	jle	L136
L116:
	movl	_gr_ypitch, %eax
	subl	$12, %esp
	imull	%eax, %esi
	movl	_gr_buffer, %eax
	movw	$0, -24(%ebp)
	leal	(%esi,%ecx), %edx
	leal	(%eax,%edx,4), %ebx
	pushl	%ebx
	call	*_gr_pixel
	addl	$16, %esp
	cmpl	-16(%ebp), %edi
	jle	L117
	movl	-16(%ebp), %ebx
	sall	$16, %ebx
	movl	%ebx, -16(%ebp)
	movl	-16(%ebp), %edx
	movl	%edx, %eax
	sarl	$31, %edx
	idivl	%edi
	movw	%ax, -22(%ebp)
	jmp	L130
	.p2align 4,,7
L137:
	movw	-22(%ebp), %ax
	movl	-24(%ebp), %edx
	addw	%ax, -24(%ebp)
	andl	$65535, %edx
	movl	-24(%ebp), %eax
	decl	%edi
	andl	$65535, %eax
	cmpl	%edx, %eax
	jg	L120
	movl	8(%ebp), %ecx
	movl	-20(%ebp), %eax
	addl	%eax, %ecx
	movl	%ecx, 8(%ebp)
L120:
	movl	12(%ebp), %eax
	movl	8(%ebp), %ebx
	incl	%eax
	movl	-24(%ebp), %esi
	shrw	$8, %si
	movl	%eax, 12(%ebp)
	movl	_gr_ypitch, %edx
	imull	%edx, %eax
	movl	_gr_buffer, %edx
	addl	%ebx, %eax
	pushl	%ecx
	pushl	%ecx
	leal	(%edx,%eax,4), %ebx
	movl	%esi, %eax
	xorl	$-1, %eax
	andl	$255, %eax
	pushl	%eax
	pushl	%ebx
	call	*_gr_pixela
	movl	-20(%ebp), %eax
	leal	(%ebx,%eax,4), %ebx
	popl	%eax
	movl	%esi, %eax
	popl	%edx
	andl	$255, %eax
	pushl	%eax
	pushl	%ebx
	call	*_gr_pixela
	addl	$16, %esp
L130:
	testl	%edi, %edi
	jg	L137
	.p2align 4,,7
L104:
	leal	-12(%ebp), %esp
	popl	%ebx
	popl	%esi
	popl	%edi
	popl	%ebp
	ret
	.p2align 4,,7
L133:
	movl	12(%ebp), %eax
	movl	20(%ebp), %edx
	cmpl	%edx, %eax
	jle	L107
	xorl	%edx, %eax
	xorl	%eax, %edx
	xorl	%edx, %eax
	movl	%edx, 20(%ebp)
	movl	%eax, 12(%ebp)
L107:
	pushl	%edx
	movl	20(%ebp), %eax
	pushl	%eax
	movl	12(%ebp), %eax
	pushl	%eax
	pushl	%ecx
	call	__Z8gr_vlineiii
	leal	-12(%ebp), %esp
	popl	%ebx
	popl	%esi
	popl	%edi
	popl	%ebp
	ret
	.p2align 4,,7
L135:
	xorl	%ebx, %ecx
	movl	%ebx, %eax
	xorl	%ecx, %eax
	xorl	%eax, %ecx
	movl	%eax, 16(%ebp)
	movl	%eax, %ebx
	movl	%esi, %eax
	xorl	%edx, %eax
	movl	%ecx, 8(%ebp)
	xorl	%eax, %edx
	xorl	%edx, %eax
	movl	%edx, 20(%ebp)
	movl	%eax, %esi
	movl	%eax, 12(%ebp)
	jmp	L112
	.p2align 4,,7
L117:
	sall	$16, %edi
	movl	%edi, %edx
	movl	%edi, %eax
	sarl	$31, %edx
	idivl	-16(%ebp)
	movw	%ax, -22(%ebp)
	jmp	L131
	.p2align 4,,7
L138:
	movl	-16(%ebp), %eax
	movl	-24(%ebp), %edx
	decl	%eax
	andl	$65535, %edx
	movl	%eax, -16(%ebp)
	movw	-22(%ebp), %ax
	addw	%ax, -24(%ebp)
	movl	8(%ebp), %esi
	movl	-24(%ebp), %eax
	movl	12(%ebp), %edi
	andl	$65535, %eax
	cmpl	%edx, %eax
	movl	-20(%ebp), %edx
	setle	%al
	andl	$255, %eax
	addl	%esi, %edx
	addl	%edi, %eax
	movl	%edx, 8(%ebp)
	movl	%eax, 12(%ebp)
	movl	-24(%ebp), %esi
	movl	12(%ebp), %ebx
	movl	_gr_ypitch, %eax
	imull	%ebx, %eax
	shrw	$8, %si
	addl	%edx, %eax
	movl	_gr_buffer, %edx
	pushl	%ecx
	pushl	%ecx
	leal	(%edx,%eax,4), %ebx
	movl	%esi, %eax
	xorl	$-1, %eax
	andl	$255, %eax
	pushl	%eax
	pushl	%ebx
	call	*_gr_pixela
	movl	_gr_ypitch, %eax
	leal	(%ebx,%eax,4), %ebx
	popl	%eax
	movl	%esi, %eax
	popl	%edx
	andl	$255, %eax
	pushl	%eax
	pushl	%ebx
	call	*_gr_pixela
	addl	$16, %esp
L131:
	movl	-16(%ebp), %eax
	testl	%eax, %eax
	jg	L138
	leal	-12(%ebp), %esp
	popl	%ebx
	popl	%esi
	popl	%edi
	popl	%ebp
	ret
	.p2align 4,,7
L134:
	cmpl	%ebx, %ecx
	jle	L110
	movl	%ecx, %eax
	movl	%ebx, %edx
	xorl	%ebx, %eax
	xorl	%eax, %edx
	xorl	%edx, %eax
	movl	%edx, 16(%ebp)
	movl	%eax, 8(%ebp)
L110:
	pushl	%eax
	movl	16(%ebp), %eax
	pushl	%eax
	pushl	%esi
	movl	8(%ebp), %eax
	pushl	%eax
	call	__Z8gr_hlineiii
	leal	-12(%ebp), %esp
	popl	%ebx
	popl	%esi
	popl	%edi
	popl	%ebp
	ret
L136:
	negl	-16(%ebp)
	movl	$-1, -20(%ebp)
	jmp	L116
	.align 2
	.p2align 4,,15
.globl __Z13gr_splineiteriiiiii
	.def	__Z13gr_splineiteriiiiii;	.scl	2;	.type	32;	.endef
__Z13gr_splineiteriiiiii:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%edi
	pushl	%esi
	pushl	%ebx
	subl	$28, %esp
	movl	8(%ebp), %eax
	movl	12(%ebp), %ecx
	movl	%eax, -16(%ebp)
	movl	%ecx, -20(%ebp)
	movl	24(%ebp), %eax
	movl	28(%ebp), %ecx
	movl	16(%ebp), %esi
	movl	20(%ebp), %edi
	movl	%eax, -24(%ebp)
	movl	%ecx, -28(%ebp)
	jmp	L143
	.p2align 4,,7
L140:
	movl	-24(%ebp), %ecx
	movl	-16(%ebp), %edx
	addl	%esi, %edx
	addl	%ecx, %esi
	movl	%esi, -32(%ebp)
	movl	-28(%ebp), %ebx
	movl	-32(%ebp), %esi
	movl	-20(%ebp), %eax
	sarl	%esi
	addl	%edi, %eax
	movl	%esi, -32(%ebp)
	addl	%ebx, %edi
	sarl	%edx
	movl	-32(%ebp), %ecx
	sarl	%eax
	sarl	%edi
	leal	(%edx,%ecx), %esi
	sarl	%esi
	leal	(%eax,%edi), %ebx
	pushl	%ecx
	sarl	%ebx
	pushl	%ecx
	pushl	%ebx
	pushl	%esi
	pushl	%eax
	pushl	%edx
	movl	-20(%ebp), %eax
	pushl	%eax
	movl	-16(%ebp), %ecx
	pushl	%ecx
	call	__Z13gr_splineiteriiiiii
	movl	%esi, -16(%ebp)
	movl	%ebx, -20(%ebp)
	movl	-32(%ebp), %esi
	addl	$32, %esp
L143:
	movl	-16(%ebp), %ecx
	movl	-20(%ebp), %edx
	movl	%esi, %eax
	movl	-28(%ebp), %ebx
	subl	%ecx, %eax
	subl	%edx, %ebx
	movl	-16(%ebp), %ecx
	movl	-24(%ebp), %edx
	subl	%ecx, %edx
	movl	%edi, %ecx
	subl	-20(%ebp), %ecx
	imull	%ebx, %eax
	imull	%ecx, %edx
	subl	%edx, %eax
	movl	%eax, %edx
	sarl	$31, %edx
	leal	(%edx,%eax), %eax
	xorl	%edx, %eax
	cmpl	$999, %eax
	jg	L140
	movl	-28(%ebp), %eax
	movl	-24(%ebp), %edi
	movl	-20(%ebp), %esi
	movl	-16(%ebp), %ebx
	sarl	$4, %eax
	sarl	$4, %edi
	movl	%eax, -28(%ebp)
	movl	%edi, -24(%ebp)
	movl	-28(%ebp), %eax
	sarl	$4, %esi
	movl	-24(%ebp), %ecx
	sarl	$4, %ebx
	movl	%esi, -20(%ebp)
	movl	%ebx, -16(%ebp)
	movl	%eax, 20(%ebp)
	movl	%ecx, 16(%ebp)
	movl	-20(%ebp), %eax
	movl	-16(%ebp), %ecx
	movl	%eax, 12(%ebp)
	movl	%ecx, 8(%ebp)
	leal	-12(%ebp), %esp
	popl	%ebx
	popl	%esi
	popl	%edi
	popl	%ebp
	jmp	__Z7gr_lineiiii
	.align 2
	.p2align 4,,15
.globl __Z9gr_splineiiiiii
	.def	__Z9gr_splineiiiiii;	.scl	2;	.type	32;	.endef
__Z9gr_splineiiiiii:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%esi
	pushl	%ebx
	movl	8(%ebp), %esi
	movl	12(%ebp), %ebx
	movl	16(%ebp), %ecx
	movl	20(%ebp), %edx
	movl	24(%ebp), %eax
	sall	$4, 28(%ebp)
	sall	$4, %ebx
	sall	$4, %esi
	movl	%ebx, 12(%ebp)
	sall	$4, %eax
	movl	%esi, 8(%ebp)
	sall	$4, %edx
	movl	%eax, 24(%ebp)
	sall	$4, %ecx
	movl	%edx, 20(%ebp)
	movl	%ecx, 16(%ebp)
	popl	%ebx
	popl	%esi
	popl	%ebp
	jmp	__Z13gr_splineiteriiiiii
	.align 2
	.p2align 4,,15
.globl __Z12gr_psegmentoiiii
	.def	__Z12gr_psegmentoiiii;	.scl	2;	.type	32;	.endef
__Z12gr_psegmentoiiii:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%edi
	pushl	%esi
	pushl	%ebx
	pushl	%ecx
	pushl	%ecx
	movl	12(%ebp), %ebx
	movl	20(%ebp), %esi
	movl	8(%ebp), %edi
	movl	16(%ebp), %ecx
	cmpl	%esi, %ebx
	je	L145
	jg	L157
L147:
	cmpl	_gr_alto, %ebx
	setge	%dl
	testl	%esi, %esi
	setle	%al
	orb	%al, %dl
	jne	L145
	sall	$8, %edi
	movl	%esi, %eax
	sall	$8, %ecx
	subl	%ebx, %eax
	subl	%edi, %ecx
	movl	%eax, -20(%ebp)
	movl	%ecx, %edx
	movl	%ecx, %eax
	sarl	$31, %edx
	idivl	-20(%ebp)
	movl	%eax, -16(%ebp)
	testl	%ebx, %ebx
	js	L158
L149:
	cmpl	%ebx, _yMin
	jg	L159
L150:
	cmpl	%esi, _yMax
	jge	L151
	movl	%esi, _yMax
L151:
	movl	_cntSegm, %ecx
	movl	%ecx, %eax
	sall	$4, %eax
	leal	_segmentos-16(%eax), %edx
	cmpl	$_segmentos, %edx
	jb	L153
	cmpl	%ebx, _segmentos-16(%eax)
	jle	L153
	.p2align 4,,7
L160:
	movl	(%edx), %eax
	movl	%eax, 16(%edx)
	movl	4(%edx), %eax
	movl	%eax, 20(%edx)
	movl	8(%edx), %eax
	movl	%eax, 24(%edx)
	movl	12(%edx), %eax
	movl	%eax, 28(%edx)
	subl	$16, %edx
	cmpl	$_segmentos, %edx
	jb	L153
	cmpl	%ebx, (%edx)
	jg	L160
L153:
	addl	$16, %edx
	leal	128(%edi), %eax
	movl	%eax, 4(%edx)
	movl	-16(%ebp), %eax
	movl	%eax, 12(%edx)
	leal	1(%ecx), %eax
	movl	%ebx, (%edx)
	movl	%esi, 8(%edx)
	movl	%eax, _cntSegm
L145:
	popl	%eax
	popl	%edx
	popl	%ebx
	popl	%esi
	popl	%edi
	popl	%ebp
	ret
	.p2align 4,,7
L157:
	movl	%edi, %edx
	movl	%ecx, %edi
	movl	%edx, %ecx
	movl	%ebx, %edx
	movl	%esi, %ebx
	movl	%edx, %esi
	jmp	L147
	.p2align 4,,7
L159:
	movl	%ebx, _yMin
	jmp	L150
L158:
	imull	%eax, %ebx
	subl	%ebx, %edi
	xorl	%ebx, %ebx
	jmp	L149
	.align 2
	.p2align 4,,15
.globl __Z14gr_iteracionSPllllll
	.def	__Z14gr_iteracionSPllllll;	.scl	2;	.type	32;	.endef
__Z14gr_iteracionSPllllll:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%edi
	pushl	%esi
	pushl	%ebx
	subl	$20, %esp
	movl	8(%ebp), %eax
	movl	12(%ebp), %ecx
	movl	%eax, -16(%ebp)
	movl	%ecx, -20(%ebp)
	movl	24(%ebp), %eax
	movl	28(%ebp), %ecx
	movl	16(%ebp), %esi
	movl	20(%ebp), %edi
	movl	%eax, -24(%ebp)
	movl	%ecx, -28(%ebp)
	jmp	L165
	.p2align 4,,7
L162:
	movl	-24(%ebp), %ecx
	movl	-16(%ebp), %edx
	addl	%esi, %edx
	addl	%ecx, %esi
	movl	%esi, -32(%ebp)
	movl	-28(%ebp), %ebx
	movl	-32(%ebp), %esi
	movl	-20(%ebp), %eax
	sarl	%esi
	addl	%edi, %eax
	movl	%esi, -32(%ebp)
	addl	%ebx, %edi
	sarl	%edx
	movl	-32(%ebp), %ecx
	sarl	%eax
	sarl	%edi
	leal	(%edx,%ecx), %esi
	sarl	%esi
	leal	(%eax,%edi), %ebx
	pushl	%ecx
	sarl	%ebx
	pushl	%ecx
	pushl	%ebx
	pushl	%esi
	pushl	%eax
	pushl	%edx
	movl	-20(%ebp), %eax
	pushl	%eax
	movl	-16(%ebp), %eax
	pushl	%eax
	call	__Z14gr_iteracionSPllllll
	movl	%esi, -16(%ebp)
	movl	%ebx, -20(%ebp)
	movl	-32(%ebp), %esi
	addl	$32, %esp
L165:
	movl	-16(%ebp), %ecx
	movl	-20(%ebp), %edx
	movl	%esi, %eax
	movl	-28(%ebp), %ebx
	subl	%ecx, %eax
	subl	%edx, %ebx
	movl	-16(%ebp), %ecx
	movl	-24(%ebp), %edx
	subl	%ecx, %edx
	movl	%edi, %ecx
	subl	-20(%ebp), %ecx
	imull	%ebx, %eax
	imull	%ecx, %edx
	subl	%edx, %eax
	movl	%eax, %edx
	sarl	$31, %edx
	leal	(%edx,%eax), %eax
	xorl	%edx, %eax
	cmpl	$999, %eax
	jg	L162
	movl	-28(%ebp), %eax
	movl	-24(%ebp), %edi
	movl	-20(%ebp), %esi
	movl	-16(%ebp), %ebx
	sarl	$4, %eax
	sarl	$4, %edi
	movl	%eax, -28(%ebp)
	movl	%edi, -24(%ebp)
	movl	-28(%ebp), %eax
	sarl	$4, %esi
	movl	-24(%ebp), %ecx
	sarl	$4, %ebx
	movl	%esi, -20(%ebp)
	movl	%ebx, -16(%ebp)
	movl	%eax, 20(%ebp)
	movl	%ecx, 16(%ebp)
	movl	-20(%ebp), %eax
	movl	-16(%ebp), %ecx
	movl	%eax, 12(%ebp)
	movl	%ecx, 8(%ebp)
	leal	-12(%ebp), %esp
	popl	%ebx
	popl	%esi
	popl	%edi
	popl	%ebp
	jmp	__Z12gr_psegmentoiiii
	.align 2
	.p2align 4,,15
.globl __Z10gr_psplineiiiiii
	.def	__Z10gr_psplineiiiiii;	.scl	2;	.type	32;	.endef
__Z10gr_psplineiiiiii:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%esi
	pushl	%ebx
	movl	8(%ebp), %esi
	movl	12(%ebp), %ebx
	movl	16(%ebp), %ecx
	movl	20(%ebp), %edx
	movl	24(%ebp), %eax
	sall	$4, 28(%ebp)
	sall	$4, %ebx
	sall	$4, %esi
	movl	%ebx, 12(%ebp)
	sall	$4, %eax
	movl	%esi, 8(%ebp)
	sall	$4, %edx
	movl	%eax, 24(%ebp)
	sall	$4, %ecx
	movl	%edx, 20(%ebp)
	movl	%ecx, 16(%ebp)
	popl	%ebx
	popl	%esi
	popl	%ebp
	jmp	__Z14gr_iteracionSPllllll
	.align 2
	.p2align 4,,15
.globl __Z13_FlineaSolidoiP4SegmS0_
	.def	__Z13_FlineaSolidoiP4SegmS0_;	.scl	2;	.type	32;	.endef
__Z13_FlineaSolidoiP4SegmS0_:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%edi
	pushl	%esi
	pushl	%ebx
	subl	$44, %esp
	movl	12(%ebp), %ecx
	movl	16(%ebp), %ebx
	movl	8(%ebp), %eax
	movl	4(%ecx), %esi
	movl	4(%ebx), %edi
	movl	%eax, -16(%ebp)
	cmpl	%edi, %esi
	je	L208
	movl	12(%ecx), %eax
L203:
	movl	12(%ebx), %edx
L168:
	testl	%eax, %eax
	js	L209
	leal	(%esi,%eax), %eax
	movl	%esi, %ebx
	movl	%eax, -20(%ebp)
L170:
	testl	%edx, %edx
	js	L210
	addl	%edi, %edx
	movl	%edi, -24(%ebp)
	movl	%edx, -28(%ebp)
L172:
	movl	-20(%ebp), %edx
	movl	-24(%ebp), %eax
	sarl	$8, %edx
	movl	%ebx, %ecx
	sarl	$8, %eax
	movl	%edx, -32(%ebp)
	movl	-28(%ebp), %edx
	movl	%eax, -36(%ebp)
	sarl	$8, %edx
	sarl	$8, %ecx
	movl	%edx, -40(%ebp)
	testl	%edx, %edx
	jle	L167
	movl	_gr_ancho, %eax
	movl	%eax, -52(%ebp)
	cmpl	%eax, %ecx
	jge	L167
	testl	%ecx, %ecx
	jle	L175
	movl	-16(%ebp), %edx
	movl	_gr_ypitch, %esi
	imull	%esi, %edx
	movl	_gr_buffer, %eax
	movl	%edx, -16(%ebp)
	addl	%ecx, %edx
L204:
	leal	(%eax,%edx,4), %esi
	movl	-32(%ebp), %eax
	testl	%eax, %eax
	jle	L177
	cmpl	-32(%ebp), %ecx
	je	L211
	movl	$65280, %edx
	movl	-32(%ebp), %ebx
	subl	%ecx, %ebx
	movl	%edx, %eax
	sarl	$31, %edx
	xorl	%edi, %edi
	idivl	%ebx
	movl	%eax, -44(%ebp)
	testl	%ecx, %ecx
	js	L212
L180:
	movl	-52(%ebp), %edx
	cmpl	%edx, -32(%ebp)
	jge	L213
L181:
	movl	-32(%ebp), %ebx
	subl	%ecx, %ebx
	jmp	L205
	.p2align 4,,7
L214:
	movl	%edi, %edx
	pushl	%eax
	pushl	%eax
	movzbl	%dh, %eax
	pushl	%eax
	pushl	%esi
	call	*_gr_pixela
	movl	-44(%ebp), %eax
	addl	$4, %esi
	addl	%eax, %edi
	addl	$16, %esp
	decl	%ebx
L205:
	cmpl	$-1, %ebx
	jne	L214
L177:
	movl	-32(%ebp), %eax
	cmpl	%eax, -36(%ebp)
	jle	L167
	movl	-36(%ebp), %edi
	testl	%edi, %edi
	jle	L186
	xorl	$-1, %eax
	movl	-32(%ebp), %ebx
	sarl	$31, %eax
	andl	%eax, %ebx
	movl	_gr_ancho, %eax
	movl	%ebx, -32(%ebp)
	cmpl	%eax, -36(%ebp)
	jle	L188
	movl	%eax, -36(%ebp)
L188:
	movl	-36(%ebp), %eax
	movl	-32(%ebp), %ecx
	subl	%ecx, %eax
	leal	-2(%eax), %ebx
	jmp	L206
	.p2align 4,,7
L215:
	subl	$12, %esp
	decl	%ebx
	pushl	%esi
	addl	$4, %esi
	call	*_gr_pixel
	addl	$16, %esp
L206:
	cmpl	$-1, %ebx
	jne	L215
L186:
	movl	-36(%ebp), %edx
	cmpl	%edx, -40(%ebp)
	je	L216
	movl	-36(%ebp), %eax
	movl	$-65280, %edx
	movl	-40(%ebp), %ecx
	movl	-36(%ebp), %ebx
	subl	%eax, %ecx
	movl	%edx, %eax
	sarl	$31, %edx
	movl	$65280, %edi
	idivl	%ecx
	movl	%eax, -48(%ebp)
	testl	%ebx, %ebx
	js	L217
L194:
	movl	_gr_ancho, %eax
	cmpl	%eax, -40(%ebp)
	jle	L195
	movl	%eax, -40(%ebp)
L195:
	movl	-40(%ebp), %ebx
	movl	-36(%ebp), %ecx
	subl	%ecx, %ebx
	jmp	L207
	.p2align 4,,7
L218:
	pushl	%edx
	pushl	%edx
	movl	%edi, %edx
	movzbl	%dh, %eax
	pushl	%eax
	pushl	%esi
	call	*_gr_pixela
	movl	-48(%ebp), %eax
	addl	$4, %esi
	addl	%eax, %edi
	addl	$16, %esp
L207:
	decl	%ebx
	cmpl	$-1, %ebx
	jne	L218
	.p2align 4,,7
L167:
	leal	-12(%ebp), %esp
	popl	%ebx
	popl	%esi
	popl	%edi
	popl	%ebp
	ret
	.p2align 4,,7
L208:
	movl	12(%ecx), %eax
	movl	12(%ebx), %edx
	cmpl	%edx, %eax
	jle	L168
	movl	%edi, %esi
	movl	%ecx, %ebx
	movl	4(%ecx), %edi
	movl	%edx, %eax
	jmp	L203
	.p2align 4,,7
L210:
	leal	(%edi,%edx), %edx
	movl	%edi, -28(%ebp)
	movl	%edx, -24(%ebp)
	jmp	L172
	.p2align 4,,7
L209:
	leal	(%esi,%eax), %ebx
	movl	%esi, -20(%ebp)
	jmp	L170
L213:
	decl	%edx
	movl	%edx, -32(%ebp)
	jmp	L181
L175:
	movl	-16(%ebp), %eax
	movl	_gr_ypitch, %edx
	imull	%edx, %eax
	movl	%eax, -16(%ebp)
	movl	_gr_buffer, %eax
	movl	-16(%ebp), %edx
	jmp	L204
L212:
	movl	%ecx, %edi
	xorl	%ecx, %ecx
	negl	%edi
	imull	%eax, %edi
	jmp	L180
L216:
	movl	-24(%ebp), %eax
	movl	-28(%ebp), %edx
	addl	%edx, %eax
	movl	%esi, 8(%ebp)
	sarl	%eax
	andl	$255, %eax
	movl	%eax, 12(%ebp)
	movl	_gr_pixela, %ecx
	leal	-12(%ebp), %esp
	popl	%ebx
	popl	%esi
	popl	%edi
	popl	%ebp
	jmp	*%ecx
L211:
	pushl	%eax
	pushl	%eax
	movl	-20(%ebp), %edx
	leal	(%ebx,%edx), %eax
	sarl	%eax
	xorl	$-1, %eax
	andl	$255, %eax
	pushl	%eax
	pushl	%esi
	call	*_gr_pixela
	addl	$4, %esi
	addl	$16, %esp
	jmp	L177
L217:
	negl	-36(%ebp)
	movl	-36(%ebp), %edx
	movl	$0, -36(%ebp)
	imull	%eax, %edx
	leal	65280(%edx), %edi
	jmp	L194
	.align 2
	.p2align 4,,15
.globl __Z9_FlineaDLiP4SegmS0_
	.def	__Z9_FlineaDLiP4SegmS0_;	.scl	2;	.type	32;	.endef
__Z9_FlineaDLiP4SegmS0_:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%edi
	pushl	%esi
	pushl	%ebx
	subl	$60, %esp
	movl	12(%ebp), %edx
	movl	16(%ebp), %ecx
	movl	8(%ebp), %eax
	movl	4(%edx), %esi
	movl	4(%ecx), %edi
	movl	%eax, -16(%ebp)
	cmpl	%edi, %esi
	je	L269
	movl	12(%edx), %eax
L265:
	movl	12(%ecx), %ebx
L220:
	testl	%eax, %eax
	js	L270
	leal	(%esi,%eax), %eax
	movl	%esi, -24(%ebp)
	movl	%eax, -28(%ebp)
L222:
	testl	%ebx, %ebx
	js	L271
	leal	(%edi,%ebx), %ebx
	movl	%edi, -32(%ebp)
	movl	%ebx, -36(%ebp)
L224:
	movl	-32(%ebp), %edx
	movl	-36(%ebp), %eax
	sarl	$8, %edx
	movl	-24(%ebp), %ebx
	sarl	$8, %eax
	movl	-28(%ebp), %edi
	sarl	$8, %ebx
	movl	%edx, -40(%ebp)
	sarl	$8, %edi
	movl	%eax, -44(%ebp)
	testl	%eax, %eax
	jle	L219
	movl	_gr_ancho, %edx
	movl	%edx, -60(%ebp)
	cmpl	%edx, %ebx
	jge	L219
	movl	_MTX, %edx
	movl	%edi, %eax
	subl	%edx, %eax
	movl	_MA, %esi
	imull	%esi, %eax
	movl	_MTY, %ecx
	movl	%eax, -48(%ebp)
	movl	-16(%ebp), %eax
	movl	_MB, %edx
	subl	%ecx, %eax
	movl	-48(%ebp), %esi
	imull	%edx, %eax
	subl	%eax, %esi
	movl	_col2, %edx
	movl	%esi, -48(%ebp)
	movl	%edx, -52(%ebp)
	movl	-48(%ebp), %edx
	movl	_col1, %ecx
	sarl	$8, %edx
	testl	%edx, %edx
	jle	L272
	cmpl	$254, %edx
	jle	L273
	movl	%ecx, _gr_color1
L228:
	testl	%ebx, %ebx
	jle	L231
	movl	-16(%ebp), %edx
	movl	_gr_ypitch, %ecx
	imull	%ecx, %edx
	movl	_gr_buffer, %eax
	movl	%edx, -16(%ebp)
	addl	%ebx, %edx
	leal	(%eax,%edx,4), %edx
	movl	%edx, -20(%ebp)
L232:
	testl	%edi, %edi
	jle	L233
	cmpl	%edi, %ebx
	je	L274
	movl	$65280, %edx
	movl	%edi, %ecx
	subl	%ebx, %ecx
	movl	%edx, %eax
	sarl	$31, %edx
	xorl	%esi, %esi
	idivl	%ecx
	movl	%eax, -56(%ebp)
	testl	%ebx, %ebx
	js	L275
L236:
	cmpl	-60(%ebp), %edi
	jl	L237
	movl	-60(%ebp), %edi
	decl	%edi
L237:
	movl	%edi, %edx
	subl	%ebx, %edx
	movl	%edx, %ebx
	jmp	L266
	.p2align 4,,7
L276:
	pushl	%edx
	pushl	%edx
	movl	%esi, %edx
	movzbl	%dh, %eax
	pushl	%eax
	decl	%ebx
	movl	-20(%ebp), %eax
	pushl	%eax
	call	*_gr_pixela
	movl	-20(%ebp), %eax
	addl	$16, %esp
	addl	$4, %eax
	movl	%eax, -20(%ebp)
	movl	-56(%ebp), %eax
	addl	%eax, %esi
L266:
	cmpl	$-1, %ebx
	jne	L276
L233:
	cmpl	%edi, -40(%ebp)
	jle	L219
	movl	-40(%ebp), %eax
	testl	%eax, %eax
	jle	L242
	testl	%edi, %edi
	js	L277
L243:
	movl	_gr_ancho, %eax
	cmpl	%eax, -40(%ebp)
	jle	L244
	movl	%eax, -40(%ebp)
L244:
	movl	-40(%ebp), %eax
	subl	%edi, %eax
	leal	-2(%eax), %ebx
	jmp	L267
	.p2align 4,,7
L279:
	movl	%ecx, %eax
	movl	%edi, %esi
	andl	$16711935, %esi
	andl	$16711935, %eax
	andl	$255, %edx
	subl	%esi, %eax
	imull	%edx, %eax
	shrl	$8, %eax
	andl	$65280, %ecx
	addl	%esi, %eax
	movl	%edi, %esi
	andl	$65280, %esi
	andl	$16711935, %eax
	subl	%esi, %ecx
	imull	%edx, %ecx
	shrl	$8, %ecx
	leal	(%ecx,%esi), %edx
	andl	$65280, %edx
	orl	%eax, %edx
	movl	%edx, _gr_color1
L248:
	subl	$12, %esp
	movl	-20(%ebp), %edi
	decl	%ebx
	pushl	%edi
	call	*_gr_pixel
	movl	-20(%ebp), %esi
	movl	-48(%ebp), %ecx
	movl	_MA, %eax
	addl	$4, %esi
	addl	%eax, %ecx
	movl	%esi, -20(%ebp)
	movl	%ecx, -48(%ebp)
	addl	$16, %esp
L267:
	cmpl	$-1, %ebx
	je	L242
	movl	-48(%ebp), %edx
	movl	_col1, %ecx
	sarl	$8, %edx
	movl	_col2, %edi
	testl	%edx, %edx
	jle	L278
	cmpl	$254, %edx
	jle	L279
	movl	%ecx, _gr_color1
	jmp	L248
	.p2align 4,,7
L242:
	movl	-40(%ebp), %edx
	cmpl	%edx, -44(%ebp)
	je	L280
	movl	-40(%ebp), %eax
	movl	$-65280, %edx
	movl	-44(%ebp), %ecx
	movl	$65280, %esi
	subl	%eax, %ecx
	movl	%edx, %eax
	sarl	$31, %edx
	idivl	%ecx
	movl	%eax, %edi
	movl	-40(%ebp), %eax
	testl	%eax, %eax
	js	L281
L254:
	movl	_gr_ancho, %eax
	cmpl	%eax, -44(%ebp)
	jle	L255
	movl	%eax, -44(%ebp)
L255:
	movl	-44(%ebp), %ebx
	movl	-40(%ebp), %eax
	subl	%eax, %ebx
	jmp	L268
	.p2align 4,,7
L282:
	movl	%esi, %edx
	pushl	%eax
	pushl	%eax
	movzbl	%dh, %eax
	pushl	%eax
	addl	%edi, %esi
	movl	-20(%ebp), %eax
	pushl	%eax
	call	*_gr_pixela
	movl	-20(%ebp), %eax
	addl	$16, %esp
	addl	$4, %eax
	movl	%eax, -20(%ebp)
L268:
	decl	%ebx
	cmpl	$-1, %ebx
	jne	L282
	.p2align 4,,7
L219:
	leal	-12(%ebp), %esp
	popl	%ebx
	popl	%esi
	popl	%edi
	popl	%ebp
	ret
	.p2align 4,,7
L269:
	movl	12(%edx), %eax
	movl	12(%ecx), %ebx
	cmpl	%ebx, %eax
	jle	L220
	movl	%edi, %esi
	movl	%edx, %ecx
	movl	4(%edx), %edi
	movl	%ebx, %eax
	jmp	L265
	.p2align 4,,7
L271:
	leal	(%edi,%ebx), %ebx
	movl	%edi, -36(%ebp)
	movl	%ebx, -32(%ebp)
	jmp	L224
	.p2align 4,,7
L270:
	leal	(%esi,%eax), %eax
	movl	%esi, -28(%ebp)
	movl	%eax, -24(%ebp)
	jmp	L222
L273:
	movl	%ecx, %eax
	movl	-52(%ebp), %esi
	andl	$16711935, %esi
	andl	$16711935, %eax
	andl	$255, %edx
	subl	%esi, %eax
	imull	%edx, %eax
	shrl	$8, %eax
	andl	$65280, %ecx
	addl	%esi, %eax
	movl	-52(%ebp), %esi
	andl	$65280, %esi
	andl	$16711935, %eax
	subl	%esi, %ecx
	imull	%edx, %ecx
	shrl	$8, %ecx
	leal	(%ecx,%esi), %edx
	andl	$65280, %edx
	orl	%eax, %edx
	movl	%edx, _gr_color1
	jmp	L228
	.p2align 4,,7
L278:
	movl	%edi, _gr_color1
	jmp	L248
L231:
	movl	-16(%ebp), %eax
	movl	_gr_ypitch, %edx
	imull	%edx, %eax
	movl	%eax, -16(%ebp)
	movl	_gr_buffer, %eax
	movl	-16(%ebp), %edx
	leal	(%eax,%edx,4), %eax
	movl	%eax, -20(%ebp)
	jmp	L232
L272:
	movl	-52(%ebp), %eax
	movl	%eax, _gr_color1
	jmp	L228
L275:
	movl	%ebx, %esi
	xorl	%ebx, %ebx
	negl	%esi
	imull	%eax, %esi
	jmp	L236
L280:
	movl	-32(%ebp), %eax
	movl	-36(%ebp), %edx
	addl	%edx, %eax
	sarl	%eax
	andl	$255, %eax
	movl	%eax, 12(%ebp)
	movl	-20(%ebp), %eax
	movl	%eax, 8(%ebp)
	movl	_gr_pixela, %ecx
	leal	-12(%ebp), %esp
	popl	%ebx
	popl	%esi
	popl	%edi
	popl	%ebp
	jmp	*%ecx
L274:
	pushl	%eax
	pushl	%eax
	movl	-24(%ebp), %eax
	movl	-28(%ebp), %esi
	addl	%esi, %eax
	sarl	%eax
	xorl	$-1, %eax
	andl	$255, %eax
	pushl	%eax
	movl	-20(%ebp), %ebx
	pushl	%ebx
	call	*_gr_pixela
	movl	-20(%ebp), %ecx
	addl	$16, %esp
	addl	$4, %ecx
	movl	%ecx, -20(%ebp)
	jmp	L233
L277:
	movl	_MA, %eax
	imull	%eax, %edi
	movl	-48(%ebp), %eax
	subl	%edi, %eax
	xorl	%edi, %edi
	movl	%eax, -48(%ebp)
	jmp	L243
L281:
	negl	-40(%ebp)
	movl	-40(%ebp), %edx
	movl	$0, -40(%ebp)
	imull	%edi, %edx
	leal	65280(%edx), %esi
	jmp	L254
	.align 2
	.p2align 4,,15
.globl __Z9_FlineaDRiP4SegmS0_
	.def	__Z9_FlineaDRiP4SegmS0_;	.scl	2;	.type	32;	.endef
__Z9_FlineaDRiP4SegmS0_:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%edi
	pushl	%esi
	pushl	%ebx
	subl	$76, %esp
	movl	12(%ebp), %edx
	movl	16(%ebp), %ecx
	movl	8(%ebp), %eax
	movl	4(%edx), %esi
	movl	4(%ecx), %edi
	movl	%eax, -16(%ebp)
	cmpl	%edi, %esi
	je	L344
	movl	12(%edx), %eax
L339:
	movl	12(%ecx), %ebx
L284:
	testl	%eax, %eax
	js	L345
	leal	(%esi,%eax), %eax
	movl	%esi, -24(%ebp)
	movl	%eax, -28(%ebp)
L286:
	testl	%ebx, %ebx
	js	L346
	leal	(%edi,%ebx), %ebx
	movl	%edi, -32(%ebp)
	movl	%ebx, -36(%ebp)
L288:
	movl	-24(%ebp), %edx
	movl	-28(%ebp), %ecx
	sarl	$8, %edx
	movl	-32(%ebp), %eax
	sarl	$8, %ecx
	movl	%edx, -40(%ebp)
	movl	-36(%ebp), %edx
	movl	%ecx, -44(%ebp)
	sarl	$8, %eax
	sarl	$8, %edx
	movl	%eax, -48(%ebp)
	movl	%edx, -52(%ebp)
	testl	%edx, %edx
	jle	L283
	movl	_gr_ancho, %ecx
	movl	%ecx, -76(%ebp)
	cmpl	%ecx, -40(%ebp)
	jge	L283
	movl	_MTX, %eax
	movl	-44(%ebp), %ecx
	subl	%eax, %ecx
	movl	_MA, %esi
	movl	%ecx, %eax
	movl	-16(%ebp), %edx
	imull	%esi, %eax
	movl	%eax, -56(%ebp)
	movl	_MTY, %eax
	subl	%eax, %edx
	movl	_MB, %ebx
	movl	%edx, %eax
	movl	-56(%ebp), %edi
	imull	%ebx, %eax
	imull	%ebx, %ecx
	imull	%esi, %edx
	subl	%eax, %edi
	movl	%edi, -56(%ebp)
	leal	(%ecx,%edx), %edx
	movl	-56(%ebp), %eax
	movl	-56(%ebp), %ecx
	sarl	$31, %eax
	movl	%edx, -60(%ebp)
	movl	_col2, %edx
	movl	_col1, %edi
	leal	(%eax,%ecx), %ebx
	movl	-60(%ebp), %ecx
	xorl	%eax, %ebx
	movl	-60(%ebp), %eax
	sarl	$31, %eax
	movl	%edx, -64(%ebp)
	movl	%ebx, %esi
	leal	(%eax,%ecx), %edx
	xorl	%eax, %edx
	movl	%edx, %ecx
	cmpl	%edx, %ebx
	jge	L347
L294:
	movl	%ecx, %eax
	movl	%ecx, %edx
	sall	$8, %eax
	sall	$4, %edx
	leal	(%eax,%ecx,8), %eax
	subl	%edx, %eax
	leal	(%ecx,%ecx), %edx
	subl	%edx, %eax
	movl	%esi, %edx
	sall	$7, %edx
	addl	%edx, %eax
	movl	%esi, %edx
	sall	$5, %edx
	subl	%edx, %eax
	leal	(%eax,%esi,8), %edx
	leal	(%esi,%esi), %eax
	subl	%eax, %edx
	sarl	$16, %edx
	testl	%edx, %edx
	jle	L348
	cmpl	$254, %edx
	jg	L337
	movl	%edi, %eax
	movl	-64(%ebp), %ecx
	andl	$16711935, %ecx
	andl	$16711935, %eax
	andl	$255, %edx
	subl	%ecx, %eax
	imull	%edx, %eax
	shrl	$8, %eax
	andl	$65280, %edi
	addl	%ecx, %eax
	movl	-64(%ebp), %ecx
	andl	$65280, %ecx
	andl	$16711935, %eax
	subl	%ecx, %edi
	imull	%edx, %edi
	shrl	$8, %edi
	leal	(%edi,%ecx), %edx
	andl	$65280, %edx
	orl	%eax, %edx
	movl	%edx, _gr_color1
L297:
	movl	-40(%ebp), %eax
	testl	%eax, %eax
	jle	L300
	movl	-16(%ebp), %edx
	movl	_gr_ypitch, %eax
	imull	%eax, %edx
	movl	-40(%ebp), %eax
	movl	%edx, -16(%ebp)
	addl	%eax, %edx
	movl	_gr_buffer, %eax
	leal	(%eax,%edx,4), %edx
	movl	%edx, -20(%ebp)
L301:
	movl	-44(%ebp), %edi
	testl	%edi, %edi
	jle	L302
	movl	-44(%ebp), %eax
	cmpl	%eax, -40(%ebp)
	je	L349
	movl	-40(%ebp), %eax
	movl	$65280, %edx
	movl	-44(%ebp), %ecx
	xorl	%ebx, %ebx
	subl	%eax, %ecx
	movl	%edx, %eax
	sarl	$31, %edx
	idivl	%ecx
	movl	%eax, %esi
	movl	-40(%ebp), %eax
	testl	%eax, %eax
	js	L350
L305:
	movl	-76(%ebp), %edx
	cmpl	%edx, -44(%ebp)
	jl	L306
	decl	%edx
	movl	%edx, -44(%ebp)
L306:
	movl	-44(%ebp), %edi
	movl	-40(%ebp), %eax
	subl	%eax, %edi
	jmp	L340
	.p2align 4,,7
L351:
	pushl	%eax
	pushl	%eax
	decl	%edi
	movzbl	%bh, %eax
	pushl	%eax
	addl	%esi, %ebx
	movl	-20(%ebp), %eax
	pushl	%eax
	call	*_gr_pixela
	movl	-20(%ebp), %eax
	addl	$16, %esp
	addl	$4, %eax
	movl	%eax, -20(%ebp)
L340:
	cmpl	$-1, %edi
	jne	L351
L302:
	movl	-44(%ebp), %ecx
	cmpl	%ecx, -48(%ebp)
	jle	L283
	movl	-48(%ebp), %esi
	testl	%esi, %esi
	jle	L311
	testl	%ecx, %ecx
	js	L352
L312:
	movl	_gr_ancho, %eax
	cmpl	%eax, -48(%ebp)
	jle	L313
	movl	%eax, -48(%ebp)
L313:
	movl	-48(%ebp), %eax
	movl	-44(%ebp), %esi
	subl	%esi, %eax
	leal	-2(%eax), %edi
	jmp	L341
	.p2align 4,,7
L354:
	movl	-68(%ebp), %eax
	movl	-72(%ebp), %ecx
	andl	$16711935, %ecx
	andl	$16711935, %eax
	subl	%ecx, %eax
	andl	$255, %edx
	imull	%edx, %eax
	shrl	$8, %eax
	movl	-68(%ebp), %ebx
	andl	$65280, %ebx
	addl	%ecx, %eax
	movl	%ebx, -68(%ebp)
	movl	-72(%ebp), %ecx
	movl	-68(%ebp), %esi
	andl	$65280, %ecx
	subl	%ecx, %esi
	andl	$16711935, %eax
	movl	%esi, -68(%ebp)
	movl	-68(%ebp), %ebx
	imull	%ebx, %edx
	shrl	$8, %edx
	movl	%edx, -68(%ebp)
	addl	%ecx, %edx
	andl	$65280, %edx
	orl	%eax, %edx
L342:
	movl	%edx, _gr_color1
L322:
	subl	$12, %esp
	movl	-20(%ebp), %eax
	decl	%edi
	pushl	%eax
	call	*_gr_pixel
	movl	_MA, %ecx
	movl	-56(%ebp), %ebx
	movl	-20(%ebp), %esi
	addl	%ecx, %ebx
	movl	_MB, %eax
	movl	-60(%ebp), %ecx
	addl	$4, %esi
	addl	%eax, %ecx
	movl	%esi, -20(%ebp)
	movl	%ebx, -56(%ebp)
	movl	%ecx, -60(%ebp)
	addl	$16, %esp
L341:
	cmpl	$-1, %edi
	je	L311
	movl	_col1, %eax
	movl	-56(%ebp), %ecx
	movl	%eax, -68(%ebp)
	movl	-56(%ebp), %eax
	sarl	$31, %eax
	movl	_col2, %edx
	movl	%edx, -72(%ebp)
	leal	(%eax,%ecx), %ebx
	movl	-60(%ebp), %ecx
	xorl	%eax, %ebx
	movl	-60(%ebp), %eax
	sarl	$31, %eax
	movl	%ebx, %esi
	leal	(%eax,%ecx), %edx
	xorl	%eax, %edx
	movl	%edx, %ecx
	cmpl	%edx, %ebx
	jl	L319
	movl	%edx, %esi
	movl	%ebx, %ecx
L319:
	movl	%ecx, %eax
	movl	%ecx, %edx
	sall	$8, %eax
	sall	$4, %edx
	leal	(%eax,%ecx,8), %eax
	subl	%edx, %eax
	leal	(%ecx,%ecx), %edx
	subl	%edx, %eax
	movl	%esi, %edx
	sall	$7, %edx
	addl	%edx, %eax
	movl	%esi, %edx
	sall	$5, %edx
	subl	%edx, %eax
	leal	(%eax,%esi,8), %edx
	leal	(%esi,%esi), %eax
	subl	%eax, %edx
	sarl	$16, %edx
	testl	%edx, %edx
	jle	L353
	cmpl	$254, %edx
	jle	L354
	movl	-68(%ebp), %edx
	jmp	L342
	.p2align 4,,7
L311:
	movl	-48(%ebp), %edx
	cmpl	%edx, -52(%ebp)
	je	L355
	movl	-48(%ebp), %eax
	movl	$-65280, %edx
	movl	-52(%ebp), %ecx
	movl	$65280, %ebx
	subl	%eax, %ecx
	movl	%edx, %eax
	sarl	$31, %edx
	idivl	%ecx
	movl	%eax, %esi
	movl	-48(%ebp), %eax
	testl	%eax, %eax
	js	L356
L328:
	movl	_gr_ancho, %eax
	cmpl	%eax, -52(%ebp)
	jle	L329
	movl	%eax, -52(%ebp)
L329:
	movl	-52(%ebp), %edi
	movl	-48(%ebp), %eax
	subl	%eax, %edi
	jmp	L343
	.p2align 4,,7
L357:
	pushl	%eax
	pushl	%eax
	movzbl	%bh, %eax
	pushl	%eax
	addl	%esi, %ebx
	movl	-20(%ebp), %eax
	pushl	%eax
	call	*_gr_pixela
	movl	-20(%ebp), %ecx
	addl	$16, %esp
	addl	$4, %ecx
	movl	%ecx, -20(%ebp)
L343:
	decl	%edi
	cmpl	$-1, %edi
	jne	L357
	.p2align 4,,7
L283:
	leal	-12(%ebp), %esp
	popl	%ebx
	popl	%esi
	popl	%edi
	popl	%ebp
	ret
	.p2align 4,,7
L344:
	movl	12(%edx), %eax
	movl	12(%ecx), %ebx
	cmpl	%ebx, %eax
	jle	L284
	movl	%edi, %esi
	movl	%edx, %ecx
	movl	4(%edx), %edi
	movl	%ebx, %eax
	jmp	L339
	.p2align 4,,7
L346:
	leal	(%edi,%ebx), %ebx
	movl	%edi, -36(%ebp)
	movl	%ebx, -32(%ebp)
	jmp	L288
	.p2align 4,,7
L345:
	leal	(%esi,%eax), %eax
	movl	%esi, -28(%ebp)
	movl	%eax, -24(%ebp)
	jmp	L286
	.p2align 4,,7
L347:
	movl	%edx, %esi
	movl	%ebx, %ecx
	jmp	L294
	.p2align 4,,7
L353:
	movl	-72(%ebp), %eax
	movl	%eax, _gr_color1
	jmp	L322
L337:
	movl	%edi, _gr_color1
	jmp	L297
L348:
	movl	-64(%ebp), %eax
	movl	%eax, _gr_color1
	jmp	L297
L300:
	movl	_gr_ypitch, %eax
	movl	-16(%ebp), %ecx
	imull	%eax, %ecx
	movl	_gr_buffer, %eax
	leal	(%eax,%ecx,4), %eax
	movl	%eax, -20(%ebp)
	jmp	L301
L350:
	movl	-40(%ebp), %ebx
	movl	$0, -40(%ebp)
	negl	%ebx
	imull	%esi, %ebx
	jmp	L305
L355:
	movl	-32(%ebp), %eax
	movl	-36(%ebp), %edx
	addl	%edx, %eax
	movl	-20(%ebp), %ecx
	sarl	%eax
	movl	%ecx, 8(%ebp)
	andl	$255, %eax
	movl	%eax, 12(%ebp)
	movl	_gr_pixela, %ecx
	leal	-12(%ebp), %esp
	popl	%ebx
	popl	%esi
	popl	%edi
	popl	%ebp
	jmp	*%ecx
L349:
	pushl	%esi
	pushl	%esi
	movl	-24(%ebp), %eax
	movl	-28(%ebp), %ebx
	addl	%ebx, %eax
	sarl	%eax
	xorl	$-1, %eax
	andl	$255, %eax
	pushl	%eax
	movl	-20(%ebp), %ecx
	pushl	%ecx
	call	*_gr_pixela
	movl	-20(%ebp), %edx
	addl	$16, %esp
	addl	$4, %edx
	movl	%edx, -20(%ebp)
	jmp	L302
L352:
	movl	%ecx, %eax
	movl	_MA, %ebx
	negl	%eax
	movl	%eax, %edx
	movl	-56(%ebp), %ecx
	imull	%ebx, %edx
	addl	%edx, %ecx
	movl	_MB, %edx
	imull	%edx, %eax
	movl	-60(%ebp), %edi
	movl	%ecx, -56(%ebp)
	addl	%eax, %edi
	movl	$0, -44(%ebp)
	movl	%edi, -60(%ebp)
	jmp	L312
L356:
	negl	-48(%ebp)
	movl	-48(%ebp), %edx
	movl	$0, -48(%ebp)
	imull	%esi, %edx
	leal	65280(%edx), %ebx
	jmp	L328
	.align 2
	.p2align 4,,15
.globl __Z9_FlineaTXiP4SegmS0_
	.def	__Z9_FlineaTXiP4SegmS0_;	.scl	2;	.type	32;	.endef
__Z9_FlineaTXiP4SegmS0_:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%edi
	pushl	%esi
	pushl	%ebx
	subl	$60, %esp
	movl	12(%ebp), %edx
	movl	16(%ebp), %ecx
	movl	8(%ebp), %eax
	movl	4(%edx), %esi
	movl	4(%ecx), %edi
	movl	%eax, -16(%ebp)
	cmpl	%edi, %esi
	je	L401
	movl	12(%edx), %eax
L396:
	movl	12(%ecx), %ebx
L359:
	testl	%eax, %eax
	js	L402
	leal	(%esi,%eax), %eax
	movl	%esi, -24(%ebp)
	movl	%eax, -28(%ebp)
L361:
	testl	%ebx, %ebx
	js	L403
	leal	(%edi,%ebx), %ebx
	movl	%edi, -32(%ebp)
	movl	%ebx, -36(%ebp)
L363:
	movl	-28(%ebp), %edx
	movl	-32(%ebp), %eax
	sarl	$8, %edx
	movl	-24(%ebp), %edi
	sarl	$8, %eax
	movl	%edx, -40(%ebp)
	movl	-36(%ebp), %edx
	movl	%eax, -44(%ebp)
	sarl	$8, %edx
	sarl	$8, %edi
	movl	%edx, -48(%ebp)
	testl	%edx, %edx
	jle	L358
	movl	_gr_ancho, %eax
	movl	%eax, -64(%ebp)
	cmpl	%eax, %edi
	jge	L358
	movl	_MTX, %edx
	movl	-40(%ebp), %ecx
	subl	%edx, %ecx
	movl	_MA, %esi
	movl	%ecx, %edx
	movl	_MTY, %eax
	imull	%esi, %edx
	movl	%edx, -52(%ebp)
	movl	-16(%ebp), %edx
	subl	%eax, %edx
	movl	_MB, %ebx
	movl	%edx, %eax
	imull	%ebx, %eax
	imull	%ebx, %ecx
	imull	%esi, %edx
	subl	%eax, -52(%ebp)
	leal	(%ecx,%edx), %edx
	movl	%edx, -56(%ebp)
	movl	-52(%ebp), %edx
	movzbl	%dh, %eax
	movl	-56(%ebp), %edx
	andl	$65280, %edx
	orl	%edx, %eax
	movl	_mTex, %edx
	testl	%edi, %edi
	movl	(%edx,%eax,4), %eax
	movl	%eax, _gr_color1
	jle	L367
	movl	_gr_ypitch, %edx
	movl	-16(%ebp), %eax
	imull	%edx, %eax
	movl	%eax, %edx
	addl	%edi, %edx
L397:
	movl	_gr_buffer, %eax
	leal	(%eax,%edx,4), %esi
	movl	-40(%ebp), %eax
	testl	%eax, %eax
	jle	L369
	cmpl	-40(%ebp), %edi
	je	L404
	movl	$65280, %edx
	movl	-40(%ebp), %ecx
	subl	%edi, %ecx
	movl	%edx, %eax
	sarl	$31, %edx
	movl	$0, -20(%ebp)
	idivl	%ecx
	movl	%eax, -60(%ebp)
	testl	%edi, %edi
	js	L405
L372:
	movl	-64(%ebp), %eax
	cmpl	%eax, -40(%ebp)
	jge	L406
L373:
	movl	-40(%ebp), %ebx
	subl	%edi, %ebx
	jmp	L398
	.p2align 4,,7
L407:
	pushl	%ecx
	pushl	%ecx
	decl	%ebx
	movl	-20(%ebp), %edx
	movzbl	%dh, %eax
	pushl	%eax
	pushl	%esi
	call	*_gr_pixela
	movl	-20(%ebp), %edx
	movl	-60(%ebp), %eax
	addl	$4, %esi
	addl	%eax, %edx
	addl	$16, %esp
	movl	%edx, -20(%ebp)
L398:
	cmpl	$-1, %ebx
	jne	L407
L369:
	movl	-40(%ebp), %edx
	cmpl	%edx, -44(%ebp)
	jle	L358
	movl	-44(%ebp), %edi
	testl	%edi, %edi
	jle	L378
	testl	%edx, %edx
	js	L408
L379:
	movl	_gr_ancho, %eax
	cmpl	%eax, -44(%ebp)
	jle	L380
	movl	%eax, -44(%ebp)
L380:
	movl	-44(%ebp), %eax
	movl	-40(%ebp), %ecx
	subl	%ecx, %eax
	leal	-2(%eax), %ebx
	jmp	L399
	.p2align 4,,7
L409:
	movl	-52(%ebp), %edx
	subl	$12, %esp
	movzbl	%dh, %eax
	movl	-56(%ebp), %edx
	decl	%ebx
	andl	$65280, %edx
	orl	%edx, %eax
	movl	_mTex, %edx
	movl	(%edx,%eax,4), %eax
	movl	%eax, _gr_color1
	pushl	%esi
	call	*_gr_pixel
	movl	-52(%ebp), %edx
	movl	_MA, %eax
	movl	-56(%ebp), %edi
	addl	%eax, %edx
	addl	$4, %esi
	movl	%edx, -52(%ebp)
	movl	_MB, %edx
	addl	%edx, %edi
	addl	$16, %esp
	movl	%edi, -56(%ebp)
L399:
	cmpl	$-1, %ebx
	jne	L409
L378:
	movl	-44(%ebp), %eax
	cmpl	%eax, -48(%ebp)
	je	L410
	movl	-44(%ebp), %edx
	movl	-48(%ebp), %ecx
	subl	%edx, %ecx
	movl	$-65280, %edx
	movl	%edx, %eax
	movl	$65280, -20(%ebp)
	sarl	$31, %edx
	idivl	%ecx
	movl	%eax, %edi
	movl	-44(%ebp), %eax
	testl	%eax, %eax
	js	L411
L387:
	movl	_gr_ancho, %eax
	cmpl	%eax, -48(%ebp)
	jle	L388
	movl	%eax, -48(%ebp)
L388:
	movl	-48(%ebp), %ebx
	movl	-44(%ebp), %eax
	subl	%eax, %ebx
	jmp	L400
	.p2align 4,,7
L412:
	pushl	%eax
	pushl	%eax
	movl	-20(%ebp), %edx
	movzbl	%dh, %eax
	pushl	%eax
	pushl	%esi
	call	*_gr_pixela
	movl	-20(%ebp), %eax
	addl	%edi, %eax
	addl	$4, %esi
	movl	%eax, -20(%ebp)
	addl	$16, %esp
L400:
	decl	%ebx
	cmpl	$-1, %ebx
	jne	L412
	.p2align 4,,7
L358:
	leal	-12(%ebp), %esp
	popl	%ebx
	popl	%esi
	popl	%edi
	popl	%ebp
	ret
	.p2align 4,,7
L401:
	movl	12(%edx), %eax
	movl	12(%ecx), %ebx
	cmpl	%ebx, %eax
	jle	L359
	movl	%edi, %esi
	movl	%edx, %ecx
	movl	4(%edx), %edi
	movl	%ebx, %eax
	jmp	L396
	.p2align 4,,7
L403:
	leal	(%edi,%ebx), %ebx
	movl	%edi, -36(%ebp)
	movl	%ebx, -32(%ebp)
	jmp	L363
	.p2align 4,,7
L402:
	leal	(%esi,%eax), %eax
	movl	%esi, -28(%ebp)
	movl	%eax, -24(%ebp)
	jmp	L361
L406:
	decl	%eax
	movl	%eax, -40(%ebp)
	jmp	L373
L367:
	movl	-16(%ebp), %edx
	movl	_gr_ypitch, %eax
	imull	%eax, %edx
	jmp	L397
L405:
	negl	%edi
	movl	%edi, %edx
	xorl	%edi, %edi
	imull	%eax, %edx
	movl	%edx, -20(%ebp)
	jmp	L372
L410:
	movl	-36(%ebp), %ecx
	movl	-32(%ebp), %eax
	addl	%ecx, %eax
	movl	%esi, 8(%ebp)
	sarl	%eax
	andl	$255, %eax
	movl	%eax, 12(%ebp)
	movl	_gr_pixela, %ecx
	leal	-12(%ebp), %esp
	popl	%ebx
	popl	%esi
	popl	%edi
	popl	%ebp
	jmp	*%ecx
L404:
	pushl	%edi
	pushl	%edi
	movl	-24(%ebp), %eax
	movl	-28(%ebp), %ebx
	addl	%ebx, %eax
	sarl	%eax
	xorl	$-1, %eax
	andl	$255, %eax
	pushl	%eax
	pushl	%esi
	call	*_gr_pixela
	addl	$4, %esi
	addl	$16, %esp
	jmp	L369
L408:
	movl	%edx, %eax
	movl	_MA, %ebx
	negl	%eax
	movl	%eax, %edx
	movl	_MB, %edi
	imull	%ebx, %edx
	imull	%edi, %eax
	movl	-52(%ebp), %ecx
	movl	-56(%ebp), %ebx
	addl	%edx, %ecx
	addl	%eax, %ebx
	movl	%ecx, -52(%ebp)
	movl	%ebx, -56(%ebp)
	movl	$0, -40(%ebp)
	jmp	L379
L411:
	negl	-44(%ebp)
	movl	-44(%ebp), %edx
	movl	$0, -44(%ebp)
	imull	%edi, %edx
	leal	65280(%edx), %eax
	movl	%eax, -20(%ebp)
	jmp	L387
	.align 2
	.p2align 4,,15
.globl __Z6addlinP4Segm
	.def	__Z6addlinP4Segm;	.scl	2;	.type	32;	.endef
__Z6addlinP4Segm:
	pushl	%ebp
	movl	_xquisc, %eax
	movl	%esp, %ebp
	pushl	%esi
	leal	-4(%eax), %ecx
	pushl	%ebx
	movl	8(%ebp), %esi
	cmpl	$_xquis, %ecx
	movl	4(%esi), %ebx
	jb	L415
	movl	-4(%eax), %edx
	cmpl	%ebx, 4(%edx)
	jle	L415
	.p2align 4,,7
L419:
	movl	%edx, 4(%ecx)
	subl	$4, %ecx
	cmpl	$_xquis, %ecx
	jb	L415
	movl	(%ecx), %edx
	cmpl	%ebx, 4(%edx)
	jg	L419
L415:
	movl	%esi, 4(%ecx)
	addl	$4, %eax
	popl	%ebx
	movl	%eax, _xquisc
	popl	%esi
	popl	%ebp
	ret
	.align 2
	.p2align 4,,15
.globl __Z11gr_drawPoliv
	.def	__Z11gr_drawPoliv;	.scl	2;	.type	32;	.endef
__Z11gr_drawPoliv:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%edi
	pushl	%esi
	pushl	%ebx
	subl	$12, %esp
	movl	$_actual, %esi
	movl	_cntSegm, %eax
	movl	_yMax, %ecx
	sall	$4, %eax
	movl	$_segmentos, -16(%ebp)
	movl	%esi, _pact
	movl	$-1, _segmentos(%eax)
	movl	_gr_alto, %eax
	cmpl	%eax, %ecx
	jle	L421
	movl	%eax, _yMax
	movl	%eax, %ecx
L421:
	movl	_yMin, %edx
	cmpl	%ecx, %edx
	jge	L441
	.p2align 4,,7
L439:
	movl	-16(%ebp), %eax
	cmpl	%edx, (%eax)
	je	L426
L443:
	movl	$_actual, %ebx
	movl	$_xquis, _xquisc
	cmpl	%esi, %ebx
	jae	L445
	.p2align 4,,7
L452:
	movl	(%ebx), %eax
	addl	$4, %ebx
	pushl	%eax
	call	__Z6addlinP4Segm
	popl	%eax
	movl	_pact, %esi
	cmpl	%esi, %ebx
	jb	L452
L445:
	movl	$_xquis+4, %edx
	movl	$_xquis, %ebx
	cmpl	_xquisc, %edx
	jb	L433
	movl	_yMin, %eax
	movl	$_actual, %ebx
	incl	%eax
	cmpl	%esi, %ebx
	movl	%eax, _yMin
	jae	L450
L454:
	movl	%eax, %ecx
	movl	%eax, %edi
	jmp	L438
	.p2align 4,,7
L453:
	movl	4(%edx), %ecx
	movl	12(%edx), %eax
	addl	%eax, %ecx
	addl	$4, %ebx
	movl	%ecx, 4(%edx)
	movl	%edi, %ecx
L434:
	cmpl	%esi, %ebx
	jae	L449
L438:
	movl	(%ebx), %edx
	cmpl	%ecx, 8(%edx)
	jg	L453
	movl	-4(%esi), %eax
	subl	$4, %esi
	movl	%eax, (%ebx)
	movl	%esi, _pact
	jmp	L434
	.p2align 4,,7
L426:
	movl	-16(%ebp), %eax
	movl	%eax, (%esi)
	addl	$16, %eax
	addl	$4, %esi
	movl	%eax, -16(%ebp)
	cmpl	%edx, (%eax)
	je	L426
	movl	%esi, _pact
	jmp	L443
	.p2align 4,,7
L433:
	pushl	%eax
	movl	4(%ebx), %eax
	movl	_yMin, %esi
	pushl	%eax
	movl	(%ebx), %edi
	addl	$8, %ebx
	pushl	%edi
	pushl	%esi
	call	*_fillpoly
	leal	4(%ebx), %eax
	addl	$16, %esp
	cmpl	_xquisc, %eax
	jb	L433
	movl	_yMin, %eax
	movl	_pact, %esi
	incl	%eax
	movl	$_actual, %ebx
	movl	%eax, _yMin
	cmpl	%esi, %ebx
	jb	L454
L450:
	movl	_yMin, %ecx
L449:
	movl	%ecx, %edx
	cmpl	_yMax, %ecx
	jl	L439
	movl	_gr_alto, %eax
L441:
	incl	%eax
	movl	$-1, _yMax
	movl	%eax, _yMin
	movl	$0, _cntSegm
	leal	-12(%ebp), %esp
	popl	%ebx
	popl	%esi
	popl	%edi
	popl	%ebp
	ret
	.def	__Z12gr_psegmentoiiii;	.scl	3;	.type	32;	.endef
	.def	__Z9_FlineaTXiP4SegmS0_;	.scl	3;	.type	32;	.endef
	.def	__Z9_FlineaDRiP4SegmS0_;	.scl	3;	.type	32;	.endef
	.def	__Z9_FlineaDLiP4SegmS0_;	.scl	3;	.type	32;	.endef
	.def	__Z13_FlineaSolidoiP4SegmS0_;	.scl	3;	.type	32;	.endef
	.def	__Z8gr_solidv;	.scl	3;	.type	32;	.endef
	.def	__Z7fillSolv;	.scl	3;	.type	32;	.endef
