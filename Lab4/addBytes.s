# File: addBytes.s
# CPSC-275 Lab4
# Courtney Driscoll & Kevin Liu
# Sep 29 2014
.LC0:
		.string		"Byte 3 = 0x%x\nByte 2 = ox%x\nByte 1 = 0x%x\nByte 0 = 0x%x\nSum = 0x%x\n"

		.global main
main:
		pushl 	%ebp				# save frame pointer
		movl	%esp, %ebp			# adjust stack pointer

		movl	$0, %eax			# store o in %eax
		movl	$0x12345678, %ebx	# store 0x1234678 in %ebx
		shrl	$24, %ebx			# logical right shift %ebx 24 bits
		addl	%ebx, %eax			# add %ebx to %eax
		movl	%ebx, %ecx			# store the first byte in %ecx

		movl	$0x12345678, %ebx	# store 0x12345678 in %ebx
		sall	$8, %ebx			# left shift %ebx 8 bits
		shrl	$24, %ebx			# logical right shift %ebx 24 bits
		addl	%ebx, %eax			# add %ebx to %eax
		movl	%ebx, %edx			# store the second byte in %edx

		movl	$0x12345678, %ebx	# store 0x12345678 in %ebx
		sall	$16, %ebx			# left shift %ebx 16 bits
		shrl	$24, %ebx			# logical right shift %ebx 24 bits
		addl	%ebx, %eax			# add %ebx to %eax
		movl	%ebx, %esi			# store the third byte in %esi

		movl	$0x12345678, %ebx	# store 0x12345678 in %ebx
		sall	$24, %ebx			# left shift %ebx 24 bits
		shrl	$24, %ebx			# logical right shift %ebx 24 bits
		addl	%ebx, %eax			# add %ebx to %eax
		movl	%ebx, %edi			# store the fourth byte in %edi

		pushl	%eax				# push %eax onto stack
		pushl	%edi				# push %edi onto stack
		pushl	%esi				# push %esi onto stack
		pushl	%edx				# push %edx onto stack
		pushl	%ecx				# push %ecx onto stack
		pushl	$.LC0				# push string LC0 onto stack
		call	printf				# call function printf()

		leave						# restore the current activation
		ret							# return to caller
