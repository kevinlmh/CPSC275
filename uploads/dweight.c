/*
   dweight.c - computes the dimensional weight of a 12" x 10" x 8" box

   Key Ideas: 
     - Division is represented by / in C, so the obvious way to compute the 
       dimensional weight would be

	     dweight = volume / 166;

     - In C, however, when one integer is divided by another, the answer is truncated
       i.e., all digits after the decimal point are lost.  The volume of a 12" x 10" x 8"  
       box will be 960 cubic inches.  Dividing by 166 gives 5 instead of 5.783.

     - One solution is to add 165 to the volume before dividing by 166:

	     weight = (volume + 165) / 166;

       A volume of 166 would give a weight of 331/166, or 1, while a volume of 167 would 
       yield 332/166, or 2.
*/


#include <stdio.h>

int main()
{
  int height, length, width, volume, weight;

  height = 8;
  length = 12;
  width = 10;
  volume = height * length * width;
  weight = (volume + 165) / 166;

  printf("Dimensions: %dx%dx%d\n", length, width, height);
  printf("Volume (cubic inches): %d\n", volume);
  printf("Dimensional weight (pounds): %d\n", weight);

  return 0;
}

