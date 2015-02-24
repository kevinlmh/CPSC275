/* File: primes.s
 * CPSC-275 Lab5
 * Author: Kevin Liu & Ian Weist
 * Date: Oct 7 2014
 */

.LC0:
		.string		"Enter a positive integer: "
.LC1:
		.string		"%d"
.LC2:
		.string		"Primes less than %d: "	
.LC3:
		.string		", %d"
.LC4:
		.string		"\n"

		.global main
main:
		pushl 	%ebp				# save frame pointer
		movl	%esp, %ebp			# adjust stack pointer

		subl	$40, %esp			# move esp down
		movl	$.LC0, (%esp)		# store address of LC0 in (esp) (arg of printf)
		call	printf	

		leal	-4(%ebp), %eax		# store the address of ebp-4 in eax
		movl	%eax, 4(%esp)		# store the address of ebp-4 in 4(esp) (arg 2 of scanf)
		movl	$.LC1, (%esp)		# store the address of LC1 in (esp) (arg 1 of scanf)
		call	scanf
		
		movl	-4(%ebp), %eax		# load N in eax
		movl	%eax, 4(%esp)		# store N in (esp+4) (arg 2 of printf)
		movl	$.LC2, (%esp)		# store LC2 in (esp) (arg 1 of printf)
		call	printf
		

		movl	-4(%ebp), %eax		# load N in eax
		cmpl	$1, %eax			# compare n to 1
		je		newline				# if n = 1 just quit
		movl	$2, %ecx			# m = 2
		movl	%ecx, -8(%ebp)		# store m in mem


printprimes:
		movl	%ecx, (%esp)		# store m in (esp)
		call	isprime				# isprime(m)
		movl	-8(%ebp), %ecx		# restore m from mem
		cmpl	$0, %eax			# compare eax to 0
		je		continue			# if return value is 0 jump to continue
		cmpl	$2, %ecx			# compare m to 2
		je		two					# if m = 2 do not print comma
		movl	%ecx, 4(%esp)		# store m in (esp+4) (arg 2 of printf)
		movl	$.LC3, (%esp)		# store LC3 in (esp) (arg 1 of printf)
		call	printf				
		movl	-8(%ebp), %ecx		# restore m from mem
		jmp		continue			# jump to continue
two:	movl	%ecx, 4(%esp)		# store ecx in (%esp+4) (arg 2 of printf)
		movl	$.LC1, (%esp)		# store LC1	in (esp) (arg 1 of printf)
		call	printf				
		movl	-8(%ebp), %ecx		# restore m from mem
continue:
		incl	%ecx				# m++
		movl	%ecx, -8(%ebp)		# store m in mem
		cmpl	-4(%ebp), %ecx		# compare m with n
		jl		printprimes			# if m < n loop again	
newline:
		movl	$.LC4, (%esp)		# print a new line character
		call	printf

		leave						# restore the current activation
		ret							# return to caller

isprime:
		pushl 	%ebp				# save frame pointer
		movl	%esp, %ebp			# adjust stack pointer

		movl	8(%ebp), %eax		# store n in eax
		cmpl	$1, %eax			# compare n to 1
		je		notprime			# return 0 if n == 1
		
		cltd						# sign extend
		movl	$2, %ebx			# store 2 in ebx
		idivl	%ebx				# divide n by two
		movl	%eax, %ebx			# store the quotient in ebx (ebx = n/2)
		cmpl	$2, %ebx			# compare the quotient to 2
		jl		prime				# if quotient < 2 n is prime
		movl	$2, %ecx			# store 2 in ecx (ecx is the divider and will go from 2 to n/2)

loop:	movl	8(%ebp), %eax		# store n in eax
		cltd						# sign extend
		idivl	%ecx				# divide n by m
		cmpl	$0, %edx			# compare remainder to 0
		je		notprime			# if remainder is 0 jump to notprime
		incl	%ecx				# m++
		cmpl	%ebx, %ecx			# compare m to n/2
		jl		loop				# if m < n/2 jump to loop
prime:
		movl	$1, %eax			# set return value to 1
		leave
		ret
notprime:
		movl	$0, %eax			# set return value to 0
		leave						# restore the current activation
		ret							# return to caller










