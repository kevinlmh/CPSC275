#!/bin/bash
    for i in 32 64 128 256 512 1024; do
		time ./matmul_block 2048 $i
	done
