/* 
 * price.c - computes the best buy from a list of paper goods.
 *
 * Author: Peter Yoon
 *
 * Date: October 1, 2013
 */

#include <stdio.h>

int main(void)
{
   char *brandName[] = {"", "Kleenex", "Charmin", "Delsey", "Generic"};
   char *productName[] = {"", "Tissue", "TP"};
   char *storeName[] = {"", "Shaw's", "Walmart", "BJ's", "Mom's"};
   
   // for reading input
   int nLines, brand, product, store, nSheets;
   float length, width, price;

   // for computing the best product
   float unitPrice, bestPrice;
   int bestBrand, bestProduct, bestStore, i;

   // read the number of products
   scanf("%d", &nLines);

   // read the first product - It's the best product so far.
   scanf("%d %d %f %f %d %d %f", &bestBrand, &bestProduct, &length, &width, &nSheets, &bestStore, &price);
   bestPrice = price / (length * width * nSheets); 

   // process the remaining input data
   for (i = 0; i < nLines - 1; i++) {
      scanf("%d %d %f %f %d %d %f", &brand, &product, &length, &width, &nSheets, &store, &price);
      unitPrice = price / (length * width * nSheets); 
      if (unitPrice < bestPrice) {   // if better product is found, switch.
         bestBrand = brand;
         bestProduct = product;
         bestStore = store;
      }
   }
   
   // print the result
   printf("Get %s %s at %s.\n", brandName[bestBrand], productName[bestProduct], storeName[bestStore]);
      
   return 0;
}
