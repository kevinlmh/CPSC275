/*
 * Program: spell.c
 * Purpose: Spell out a list of numbers in english (numbers will be sorted)
 * Author:  Kevin Liu
 * Date:    9/14/2014
 */

#include <stdio.h>

char *ones[] = { "zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine" };
char *teens[] = { "ten", "eleven", "twelve", "thirteen", "fourteen", "fifteen", "sixteen", "seventeen", "eighteen", "nineteen" };
char *tens[] = { "", "ten", "twenty", "thirty", "forty", "fifty", "sixty", "seventy", "eighty", "ninety" };
char hundred[] = " hundred";
char thousand[] = " thousand";
char string[100] = "";

/*
 * Function: mystrcp
 * Purpose:  Copy a char array to another
 *
 * Parameters:
 *    des: the destination array
 *    src: the source array
 *
 * Returns: not return value
 */
void mystrcp(char *des, char *src) {
	while (*src != '\0') {
		*des = *src;
		src++;
		des++;
	}
	*des = *src;
}

/*
 * Function: mystrcat
 * Purpose:  Concatenate two arrays
 *
 * Parameters:
 *    des: the destination array
 *    src: the source array
 *
 * Returns: pointer to desination array
 */
char *mystrcat(char *des, char *src) {
	char temp_array[100];
	char *temp = temp_array;
	mystrcp(temp, src);
	char *des1 = des;
	while (*des1 != '\0')
		des1++;
	while (*temp != '\0') {
		*des1 = *temp;
		temp++;
		des1++;
	}
	*des1 = '\0';
	return des;
}

/*
 * Function: spellout
 * Purpose:  spellout a number less than a million in English
 *
 * Parameters:
 *    x: an integer to be spelled
 *    string: the pointer to an array in which you want to store
 *            the English words
 *
 * Returns: English words for the number
 */
char *spellout(int x, char *string) {
   if (x < 10)
      return ones[x];
   else if (x < 20)
      return teens[x - 10];
   else if (x < 100) {
      if (x % 10 == 0)
         return tens[x / 10];
      else {
		mystrcat(string, tens[x / 10]);
		mystrcat(string, " ");
		mystrcat(string, ones[x % 10]);
		return string;
	  }
   }
   else if (x < 1000) {
      if (x % 100 == 0) {
      	mystrcat(string, ones[x / 100]);
      	mystrcat(string, hundred);
      	return string;
      }
      else {
      	mystrcat(string, ones[x / 100]);
      	mystrcat(string, hundred);
      	mystrcat(string, " ");
      	char temp[100] = "";
      	mystrcat(string, spellout(x % 100, temp));
      	return string;
      }
   }
   else if (x < 1000000) {
      if (x % 1000 == 0) {
        char temp[100] = "";
     	mystrcat(string, spellout(x / 1000, temp));
     	mystrcat(string, thousand);
     	return string;
      }
      else {
        char temp[100] = "";
      	mystrcat(string, spellout(x / 1000, temp));
      	mystrcat(string, thousand);
      	mystrcat(string, " ");
      	char temp2[100] = "";
      	mystrcat(string, spellout(x % 1000, temp2));
      	return string;
      }
   }
   else {
   		mystrcat(string, "Invalid input: integer must be smaller than a million!");
   		return string;
   }		
}

/*
 * Function: clearString
 * Purpose:  Clear out a char array so it can be reused
 *
 * Parameters:
 *    string: the char array to be cleared otu
 *    n: size of string
 *
 * Returns: not return value
 */
void clearString(char *string, int n) {
	int i;
	for (i=0; i<n; i++)
		string[i] = '\0';
}

/*
 * Function: bubbleSort
 * Purpose:  Sort an array of integers using bubble sort algorithm
 *
 * Parameters:
 *    array: an array of integers to be sorted
 *    size: size of array
 *
 * Returns: not return value
 */
void bubbleSort(int array[], int size) {
	int i,j;
	for (i=0; i<size; i++) {
		for (j=0; j<size-1; j++) {
			if (array[j]>array[j+1]) {
				int temp = array[j+1];
				array[j+1] = array[j];
				array[j] = temp;
			}
		}
	}
}

int main(void) {
	int input[100];
	int input_count = 0;
	int i;
	while (scanf("%d", &input[input_count]) != EOF) {
		input_count++;				
	}
	bubbleSort(input, input_count);
	for (i=0; i<input_count; i++) {
		clearString(string, 500);
		printf("%d: %s\n", input[i], spellout(input[i], string));
	}
}