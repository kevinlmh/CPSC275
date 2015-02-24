#include <stdio.h>

char *ones[] = { "zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine" };
char *teens[] = { "ten", "eleven", "twelve", "thirteen", "fourteen", "fifteen", "sixteen", "seventeen", "eighteen", "nineteen" };
char *tens[] = { "", "ten", "twenty", "thirty", "forty", "fifty", "sixty", "seventy", "eighty", "ninety" };
char hundred[] = " hundred";
char thousand[] = " thousand";
char string[100] = "";

void mystrcp(char *des, char *src) {
	while (*src != '\0') {
		*des = *src;
		src++;
		des++;
	}
	*des = *src;
}

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

char *spellout(int x, char *string) {
   if (x < 10)
      return ones[x];
   else if (x < 20)
      return teens[x - 10];
   else if (x < 100) {
      if (x % 10 == 0)
         return tens[x / 10];
      else {
    	//return tens[x / 10] + "-" + ones[x % 10];
		mystrcat(string, tens[x / 10]);
		mystrcat(string, " ");
		mystrcat(string, ones[x % 10]);
		return string;
	  }
   }
   else if (x < 1000) {
      if (x % 100 == 0) {
         //return ones[x / 100] + hundred;
      	mystrcat(string, ones[x / 100]);
      	mystrcat(string, hundred);
      	return string;
      }
      else {
         //return ones[x / 100] + hundred + " " + spellout(x % 100);
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
        //return spellout(x / 1000) + thousand[0];
        char temp[100] = "";
     	mystrcat(string, spellout(x / 1000, temp));
     	mystrcat(string, thousand);
     	return string;
      }
      else {
         //return spellout(x / 1000) + thousand[0] + " " + spellout(x % 1000);
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

void clearString(char *string, int n) {
	int i;
	for (i=0; i<n; i++)
		string[i] = '\0';
}

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
	char *output[100];
	int input_count = 0;
	int i;
	while(scanf("%d", &input[input_count]) != EOF) {
		input_count++;				
	}
	bubbleSort(input, input_count);
	for(i=0; i<input_count; i++) {
		clearString(string, 500);
		printf("%d: %s\n", input[i], spellout(input[i], string));
	}
}

