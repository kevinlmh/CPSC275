/*
 * File: numstr.s
 * CPSC-275 Assignment 5 Problem 4
 * Author: Kevin Liu
 * Date: Oct 12 2014
 */

.LC0:
	.string	"Enter an integer: "
.LC1:
	.string	"%d"
.LC2:
	.string	"The numeric string equivalent to %d is "
.LC3:
	.string	".\n"
.LC4: 
	.string "%c"
	
	.text
.globl main
main:
	pushl	%ebp					# save frame pointer
	movl	%esp, %ebp				# adjust stack pointer
	subl	$48, %esp				# allocate space on stack
	movl	$.LC0, %eax				# load address of string LC0
	movl	%eax, (%esp)			# use address LC0 as argument
	call	printf					# print string LC0
	movl	$.LC1, %eax				# load address of string LC1
	leal	28(%esp), %edx			# load address of variable num
	movl	%edx, 4(%esp)			# use address of num as argument
	movl	%eax, (%esp)			# use address of LC1 as argument
	call	scanf					# scan a number and store in num
	movl	28(%esp), %edx			# load num
	movl	$.LC2, %eax				# load address of string LC2
	movl	%edx, 4(%esp)			# use num as argument
	movl	%eax, (%esp)			# use address of string LC2 as argument
	call	printf					# print string LC2 and num
	movl	28(%esp), %eax			# load variable num
	testl	%eax, %eax				# test num (zero test)
	jne	.L1							# if num != 0 test negativity
	movl	$.LC4, %edx				# load address of string LC4
	movl	$48, 4(%esp)			# use char '0' as argument
	movl	%edx, (%esp)			# use address of LC4 as argument
	call	printf					# num == 0 so print '0'
.L1:
	movl	28(%esp), %eax			# load variable num
	testl	%eax, %eax				# test num (negativity test)
	jns	.L4							# num > 0 do nothing
	movl	$.LC4, %edx				# load address of string LC4
	movl	$45, 4(%esp)			# use char '-' as argument
	movl	%edx, (%esp)			# use address of LC4 as argument
	call	printf					# num < 0 so print '-'
	movl	28(%esp), %eax			# load variable num
	negl	%eax					# num = -num
	movl	%eax, 28(%esp)			# store num
.L4:
	movl	28(%esp), %eax			# load variable num
	leal	34(%esp), %edx			# load address of array buffer
	movl	%edx, 4(%esp)			# use address of buffer as argument
	movl	%eax, (%esp)			# use num as argument
	call	int2str					# convert num to string and store in buffer
	movl	$0, 20(%esp)			# assign 0 to variable significant
	movl	$0, 24(%esp)			# assign 0 to loop counter i
	jmp	.L2							# jump to loop condition check
.L7:
	cmpl	$0, 20(%esp)			# compare variable significant to 0
	jne	.L3							# significant != 0 then print a siginificant digit
	movl	24(%esp), %edx			# load loop counter i
	leal	34(%esp), %eax			# load address of buffer
	addl	%edx, %eax				# buffer + i
	movzbl	(%eax), %eax			# load *(buffer + i)
	cmpb	$48, %al				# compare *(buffer + i) to '0'
	je	.L10						# '0' means not a significant digit, do not print
	movl	24(%esp), %edx			# load i
	leal	34(%esp), %eax			# load address of buffer
	addl	%edx, %eax				# buffer + i
	movzbl	(%eax), %eax			# load *(buffer + i)
	movsbl	%al,%eax				# load L.S.Byte and sign extend
	movl	$.LC4, %edx				# load address of string LC4
	movl	%eax, 4(%esp)			# use LSB as argument
	movl	%edx, (%esp)			# use address of LC4 as argument
	call	printf					# print out char at *(buffer + i)
	movl	24(%esp), %eax			# load loop counter i
	cltd							# extend to [%edx:%eax]
	movl	$3, %ecx				# load literal value 3
	idivl	%ecx					# divide i by 3
	testl	%edx, %edx				# test the remainder
	jne	.L5							# i % 3 != 0 then do not print comma
	cmpl	$9, 24(%esp)			# compare i to 9
	je	.L5							# last digit in buffer, do no print comma
	movl	$.LC4, %edx				# load adress of string LC4
	movl	$44, 4(%esp)			# use ascii value 44 as argument (44 is ',')
	movl	%edx, (%esp)			# use address of LC4 as argument
	call	printf					# print a comma
.L5:
	movl	$1, 20(%esp)			# found the first significant digit 
	jmp	.L6							# set significant to 1 and increment loop counter
.L3:
	movl	24(%esp), %edx			# load loop counter i
	leal	34(%esp), %eax			# load address of buffer
	addl	%edx, %eax				# buffer + i
	movzbl	(%eax), %eax			# load *(buffer + i)
	movsbl	%al,%eax				# load L.S.Byte and sign extend
	movl	$.LC4, %edx				# load address of string LC4
	movl	%eax, 4(%esp)			# use LSB as argument
	movl	%edx, (%esp)			# use address of LC4 as argument
	call	printf					# print out char at *(buffer + i)
	movl	24(%esp), %eax			# load loop counter i
	cltd							# extend to [%edx:%eax]
	movl	$3, %ecx				# load literal value 3
	idivl	%ecx					# divide i by 3
	testl	%edx, %edx				# test the remainder
	jne	.L6							# i % 3 !=0 then do not print comma 
	cmpl	$9, 24(%esp)			# compare i to 9
	je	.L6							# last digit in buffer, do not print comma
	movl	$.LC4, %edx				# load address of string LC4
	movl	$44, 4(%esp)			# use ascii value 44 as argument (44 is ',')
	movl	%edx, (%esp)			# use address of LC4 as argument
	call	printf					# print a comma
	jmp	.L6							# increment loop counter
.L10:
	nop
.L6:
	incl	24(%esp)				# increment loop counter i
.L2:
	cmpl	$9, 24(%esp)			# compare i to 9
	jle	.L7							# i<9 then enter loop
	movl	$.LC3, (%esp)			# load address of string LC3
	call	printf					# print string LC3
.L9:
	leave							# restore the current activation
	ret								# return to caller

.globl tentopower
tentopower:
	pushl	%ebp					# save frame pointer
	movl	%esp, %ebp				# adjust stack pointer
	subl	$16, %esp				# allocate space on stack
	movl	$1, -4(%ebp)			# assign one to variable t
	jmp	.L12						# jump to loop condition check
.L13:
	movl	-4(%ebp), %edx			# load variable t
	movl	%edx, %eax				# keep a copy of t in edx
	leal	(%eax,%eax,8),%eax		# eax *= 9
	addl	%edx, %eax				# eax += t (eax now = 10t)
	movl	%eax, -4(%ebp)			# store t
	subl	$1, 8(%ebp)				# argument/counter p--
.L12:
	cmpl	$0, 8(%ebp)				# compare p to 0 
	jg	.L13						# p > 0 enter loop
	movl	-4(%ebp), %eax			# set variable t as return value
	leave							# restore the current activation
	ret								# return to caller

.globl int2str
int2str:
	pushl	%ebp					# save frame pointer
	movl	%esp, %ebp				# adjust stack pointer
	pushl	%ebx					# save %ebx
	subl	$24, %esp				# allocate space on stack
	movl	$0, -8(%ebp)			# assign 0 to loop counter i
	jmp	.L16						# jump to loop condition check
.L17:
	movl	-8(%ebp), %eax			# load loop counter i
	movl	%eax, (%esp)			# use i as argument
	call	tentopower				# compute 10ei
	movl	%eax, -24(%ebp)			# store 10ei
	movl	8(%ebp), %eax			# load argument num
	cltd							# extend to [%edx:%eax]
	idivl	-24(%ebp)				# num / 10ei
	cltd							# extend quotient to [%edx:%eax]
	movl	$10, %ecx				# load literal value 10
	idivl	%ecx					# (num / 10ei) / 10
	movl	%edx, -12(%ebp)			# assign remainder to variable d
	movl	-8(%ebp), %eax			# load loop counter i
	movl	$9, %edx				# load literal value 9
	movl	%edx, %ecx				# make a copy of 9 in ecx
	subl	%eax, %ecx				# 9-i
	movl	%ecx, %eax				# load 9-i
	addl	12(%ebp), %eax			# buffer + 9-i
	movl	-12(%ebp), %edx			# load variable d
	addl	$48, %edx				# load '0' + d
	movb	%dl, (%eax)				# assign character digit[d] to buffer[9-i]
	incl	-8(%ebp)				# loop counter i++
.L16:
	cmpl	$9, -8(%ebp)			# compare loop counter i to 9
	jle	.L17						# i < 9 then enter loop
	movl	12(%ebp), %eax			# load address of buffer
	addl	$24, %esp				# move stack pointer back
	popl	%ebx					# restore %ebx
	popl	%ebp					# restore old ebp
	ret								# return address of buffer to caller
