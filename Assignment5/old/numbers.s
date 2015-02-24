	.file	"numbers.c"
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
	movl	28(%esp), %eax
	leal	34(%esp), %edx
	movl	%edx, 4(%esp)
	movl	%eax, (%esp)
	call	int2str
	movl	28(%esp), %edx
	movl	$.LC2, %eax
	movl	%edx, 4(%esp)
	movl	%eax, (%esp)
	call	printf
	movl	$0, 20(%esp)
	movl	$0, 24(%esp)
	jmp	.L2
.L7:
	cmpl	$0, 20(%esp)
	jne	.L3
	movl	24(%esp), %edx
	leal	34(%esp), %eax
	addl	%edx, %eax
	movzbl	(%eax), %eax
	cmpb	$48, %al
	je	.L10
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
	jne	.L5
	cmpl	$9, 24(%esp)
	je	.L5
	movl	$44, (%esp)
	call	putchar
.L5:
	movl	$1, 20(%esp)
	jmp	.L6
.L3:
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
	jne	.L6
	cmpl	$9, 24(%esp)
	je	.L6
	movl	$44, (%esp)
	call	putchar
	jmp	.L6
.L10:
	nop
.L6:
	addl	$1, 24(%esp)
.L2:
	cmpl	$9, 24(%esp)
	jle	.L7
	movl	$.LC3, (%esp)
	call	puts
	movl	44(%esp), %edx
	xorl	%gs:20, %edx
	je	.L9
	call	__stack_chk_fail
.L9:
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
	jmp	.L12
.L13:
	movl	-4(%ebp), %edx
	movl	%edx, %eax
	sall	$2, %eax
	addl	%edx, %eax
	addl	%eax, %eax
	movl	%eax, -4(%ebp)
	subl	$1, 8(%ebp)
.L12:
	cmpl	$0, 8(%ebp)
	jg	.L13
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
	subl	$84, %esp
	movl	12(%ebp), %eax
	movl	%eax, -44(%ebp)
	movl	%gs:20, %eax
	movl	%eax, -12(%ebp)
	xorl	%eax, %eax
	movb	$48, -22(%ebp)
	movb	$49, -21(%ebp)
	movb	$50, -20(%ebp)
	movb	$51, -19(%ebp)
	movb	$52, -18(%ebp)
	movb	$53, -17(%ebp)
	movb	$54, -16(%ebp)
	movb	$55, -15(%ebp)
	movb	$56, -14(%ebp)
	movb	$57, -13(%ebp)
	movl	$0, -28(%ebp)
	jmp	.L16
.L17:
	movl	-28(%ebp), %eax
	movl	%eax, (%esp)
	call	tentopower
	movl	%eax, -60(%ebp)
	movl	8(%ebp), %edx
	movl	%edx, %eax
	sarl	$31, %edx
	idivl	-60(%ebp)
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
	movl	%eax, -32(%ebp)
	movl	-32(%ebp), %edx
	movl	%edx, %eax
	sall	$2, %eax
	addl	%edx, %eax
	addl	%eax, %eax
	movl	%ecx, %edx
	subl	%eax, %edx
	movl	%edx, %eax
	movl	%eax, -32(%ebp)
	movl	-28(%ebp), %eax
	movl	$9, %edx
	movl	%edx, %ecx
	subl	%eax, %ecx
	movl	%ecx, %eax
	addl	-44(%ebp), %eax
	movl	-32(%ebp), %edx
	movzbl	-22(%ebp,%edx), %edx
	movb	%dl, (%eax)
	addl	$1, -28(%ebp)
.L16:
	cmpl	$9, -28(%ebp)
	jle	.L17
	movl	-12(%ebp), %ebx
	xorl	%gs:20, %ebx
	je	.L19
	call	__stack_chk_fail
.L19:
	addl	$84, %esp
	popl	%ebx
	popl	%ebp
	ret
	.size	int2str, .-int2str
	.ident	"GCC: (Ubuntu 4.4.3-4ubuntu5.1) 4.4.3"
	.section	.note.GNU-stack,"",@progbits
