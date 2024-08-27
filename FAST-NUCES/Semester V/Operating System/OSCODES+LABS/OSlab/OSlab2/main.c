#include<stdio.h>
#include<unistd.h>
#include "header.h"
int main()
{
    int arr1[7]={3,2,1,6,5,4,2};
    printf("\nOn passing 0 in order: sort()=>");
    sort(arr1,0);
    print(arr1);
    int arr2[7]={3,2,1,6,5,4,2};
    printf("\nOn passing 1 in order: sort()=>");
    sort(arr2,1);
    print(arr2);
    printf("\nPrinting the 3rd highest index: ");
    int arr3[7]={3,2,1,6,5,4,2};
    int x = findHighest(arr3,2);
    printf("%d",x );
    printf("\n");
    return 0;
}