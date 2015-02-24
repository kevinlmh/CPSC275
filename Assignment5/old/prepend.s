
.global str
	.data
	.type	str, @object
	.size	str, 20
str:
	.string	""
	.zero	19

	.text

/*
.global prepend
	.TYPE	prepend, @function
prepend:
		pushl	%ebp				# save frame pointer
		movl	%esp, %ebp			# adjust stack pointer

		movl	$0, %ecx			# int i = 0
		leal	str, %edx			# get address of str
length:
		movb	(%edx,%ecx), %al			# get str[i]
		cmpb	0, %al				# compare str[i] with 0
		je		move				# if str[i] = null break
		incl	%ecx				# i++
		jmp		length				# loop again
move:	
		movb	(%edx,%ecx), %al	# eax = str[i]
		movb	%al, 1(%edx,%ecx)	# str[i+1] = eax
		decl	%ecx				# i--
		cmpl	0, %ecx				# compare i with 0
		jns		move				# if i >= 0 keep lopping

		movl	$0, %ecx			# i = 0
		movb	1(%ebp), %al		# eax = c
		movb	%al, (%edx,%ecx)	# str[0] = c
		leal	str, %eax			# eax = address of str

		leave						# restore the current activation
		ret							# return to caller
*/


.global prepend
	.type	prepend, @function
prepend:
		pushl	%ebp				# save frame pointer
		movl	%esp, %ebp			# adjust stack pointer
		
		movzb	4(%ebp), %eax		# al = arg char c

		leave
		ret


	
