.LC0:
		.string		"x = %d y = %d\n"

		.global main
main:
		pushl 	%ebp		# save frame pointer
		movl	%esp, %ebp	# adjust stack pointer

		movl	$10, %eax	# store 10 in %eax
		movl	$20, %ebx	# store 20 in %ebx
		pushl	%ebx		# push %ebx onto stack
		pushl	%eax		# push %eax onto stack
		pushl	$.LC0		# push string LC0 onto stack
		call	printf		# call function printf()

		leave				# restore the current activation
		ret					# return to caller
