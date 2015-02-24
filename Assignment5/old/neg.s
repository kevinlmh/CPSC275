	.file	"number.c"
.globl digits
	.data
	.type	digits, @object
	.size	digits, 10
digits:
	.byte	48
	.byte	49
	.byte	50
	.byte	51
	.byte	52
	.byte	53
	.byte	54
	.byte	55
	.byte	56
	.byte	57
	.section	.rodata
.LC0:
	.string	"Enter an integer: "
.LC1:
	.string	"%d"
	.align 4
.LC2:
	.string	"The numeric string equivalent to %d is "
.LC3:
	.string	"."
	.text
.globl main
	.type	main, @function
main:
	pushl	%ebp
	movl	%esp, %ebp
	andl	$-16, %esp
	subl	$48, %esp
	movl	%gs:20, %eax
	movl	%eax, 44(%esp)
	xorl	%eax, %eax
	movl	$.LC0, %eax
	movl	%eax, (%esp)
	call	printf
	movl	$.LC1, %eax
	leal	28(%esp), %edx
	movl	%edx, 4(%esp)
	movl	%eax, (%esp)
	call	__isoc99_scanf
	movl	28(%esp), %edx
	movl	$.LC2, %eax
	movl	%edx, 4(%esp)
	movl	%eax, (%esp)
	call	printf
	/*********************/
	movl	28(%esp), %eax
	testl	%eax, %eax
	jne	.L2
	movl	$48, (%esp)
	call	putchar
.L2:
	movl	28(%esp), %eax
	testl	%eax, %eax
	jns	.L3
	movl	$45, (%esp)
	call	putchar
	movl	28(%esp), %eax
	negl	%eax
	movl	%eax, 28(%esp)
.L3:
	movl	28(%esp), %eax
	leal	34(%esp), %edx
	movl	%edx, 4(%esp)
	movl	%eax, (%esp)
	call	int2str
	/**********************/
	movl	$0, 20(%esp)
	movl	$0, 24(%esp)
	jmp	.L4
.L9:
	cmpl	$0, 20(%esp)
	jne	.L5
	movl	24(%esp), %edx
	leal	34(%esp), %eax
	addl	%edx, %eax
	movzbl	(%eax), %eax
	cmpb	$48, %al
	je	.L12
	movl	24(%esp), %edx
	leal	34(%esp), %eax
	addl	%edx, %eax
	movzbl	(%eax), %eax
	movsbl	%al,%eax
	movl	%eax, (%esp)
	call	putchar
	movl	24(%esp), %ecx
	movl	$1431655766, %edx
	movl	%ecx, %eax
	imull	%edx
	movl	%ecx, %eax
	sarl	$31, %eax
	subl	%eax, %edx
	movl	%edx, %eax
	addl	%eax, %eax
	addl	%edx, %eax
	movl	%ecx, %edx
	subl	%eax, %edx
	testl	%edx, %edx
	jne	.L7
	cmpl	$9, 24(%esp)
	je	.L7
	movl	$44, (%esp)
	call	putchar
.L7:
	movl	$1, 20(%esp)
	jmp	.L8
.L5:
	movl	24(%esp), %edx
	leal	34(%esp), %eax
	addl	%edx, %eax
	movzbl	(%eax), %eax
	movsbl	%al,%eax
	movl	%eax, (%esp)
	call	putchar
	movl	24(%esp), %ecx
	movl	$1431655766, %edx
	movl	%ecx, %eax
	imull	%edx
	movl	%ecx, %eax
	sarl	$31, %eax
	subl	%eax, %edx
	movl	%edx, %eax
	addl	%eax, %eax
	addl	%edx, %eax
	movl	%ecx, %edx
	subl	%eax, %edx
	testl	%edx, %edx
	jne	.L8
	cmpl	$9, 24(%esp)
	je	.L8
	movl	$44, (%esp)
	call	putchar
	jmp	.L8
.L12:
	nop
.L8:
	addl	$1, 24(%esp)
.L4:
	cmpl	$9, 24(%esp)
	jle	.L9
	movl	$.LC3, (%esp)
	call	puts
	movl	44(%esp), %edx
	xorl	%gs:20, %edx
	je	.L11
	call	__stack_chk_fail
.L11:
	leave
	ret
	.size	main, .-main
.globl tentopower
	.type	tentopower, @function
tentopower:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$16, %esp
	movl	$1, -4(%ebp)
	jmp	.L14
.L15:
	movl	-4(%ebp), %edx
	movl	%edx, %eax
	sall	$2, %eax
	addl	%edx, %eax
	addl	%eax, %eax
	movl	%eax, -4(%ebp)
	subl	$1, 8(%ebp)
.L14:
	cmpl	$0, 8(%ebp)
	jg	.L15
	movl	-4(%ebp), %eax
	leave
	ret
	.size	tentopower, .-tentopower
.globl int2str
	.type	int2str, @function
int2str:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%ebx
	subl	$24, %esp
	movl	$0, -8(%ebp)
	jmp	.L18
.L19:
	movl	-8(%ebp), %eax
	movl	%eax, (%esp)
	call	tentopower
	movl	%eax, -24(%ebp)
	movl	8(%ebp), %edx
	movl	%edx, %eax
	sarl	$31, %edx
	idivl	-24(%ebp)
	movl	%eax, %ecx
	movl	$1717986919, %edx
	movl	%ecx, %eax
	imull	%edx
	sarl	$2, %edx
	movl	%ecx, %eax
	sarl	$31, %eax
	movl	%edx, %ebx
	subl	%eax, %ebx
	movl	%ebx, %eax
	movl	%eax, -12(%ebp)
	movl	-12(%ebp), %edx
	movl	%edx, %eax
	sall	$2, %eax
	addl	%edx, %eax
	addl	%eax, %eax
	movl	%ecx, %edx
	subl	%eax, %edx
	movl	%edx, %eax
	movl	%eax, -12(%ebp)
	movl	-8(%ebp), %eax
	movl	$9, %edx
	movl	%edx, %ecx
	subl	%eax, %ecx
	movl	%ecx, %eax
	addl	12(%ebp), %eax
	movl	-12(%ebp), %edx
	movzbl	digits(%edx), %edx
	movb	%dl, (%eax)
	addl	$1, -8(%ebp)
.L18:
	cmpl	$9, -8(%ebp)
	jle	.L19
	addl	$24, %esp
	popl	%ebx
	popl	%ebp
	ret
	.size	int2str, .-int2str
	.ident	"GCC: (Ubuntu 4.4.3-4ubuntu5.1) 4.4.3"
	.section	.note.GNU-stack,"",@progbits
