# File number.s
# CPSC-275 Assignment 5 Problem 4
# Author: Kevin Liu
# Date: Oct 4 2014

.LC0:
	.string		"Enter an integer: "
.LC1:
	.string		"The numeric string equvilant to %d is %s."
.LC2:
	.string		"%d"

	.text
	.global main
main:
	push	%ebp			# save fram pointer
	movl	%esp, %ebp		# adjust stack pointer

	

	leave					# restore the current activation
	ret						# return to caller

int2str:
	push	%ebp			# save frame pointer
	movl	%esp, %ebp		# adjust stack pointer

	

	leave					# restore the current activation
	ret						# return to caller

prepend_char:
	


	.data
digit:	.ascii	"0123456789"
str:	.byte	20
