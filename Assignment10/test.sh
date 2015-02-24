#!/bin/bash
for i in 1 2 57 128 256 511 513 1024; do
	time ./myfilecopy2 infile.txt outfile.txt $i 
done
