#include<stdio.h>
#include "header.h"
#include<unistd.h>

void sort(int array[],int order)
{
int i,j,a;
int size=7;
int n=7;
	if(order)
	{
		for (i = 0; i < n; ++i){
   for (j = i + 1; j < n; ++j){
      if (array[i] > array[j]){
         a = array[i];
         array[i] = array[j];
         array[j] = a;
      }
   }
}
}
	else{
		for (i = 0; i < n; ++i){
   			for (j = i + 1; j < n; ++j){
      				if (array[i] < array[j]){
         				a = array[i];
         				array[i] = array[j];
         				array[j] = a;
      				}
   			}
		}
	}
}
int findHighest(int array[],int nth)
{
sort(array,0);
return array[nth-1];
}
void print(int array[])
{
int i;
int size=7;
for(i=0;i<size;i++)
{
	printf("%d",array[i]);
}}
