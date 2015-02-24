#!/bin/bash
    for i in 32 64 128 256 512 1024 2048 4096; do
		time ./matmul $i
	done
