#include <stdio.h>
#include <math.h>
#include <stdlib.h>

// I, Obie Carnathan, declare that I have completed this assignment completely and entirely on my own, without any unathorized consultation from others or unathorized access to online websites. I have read the UAB Academic Honor Code and understand that any breach of the UAB Academic Honor Code may result in severe penalties.

// Student Signature/Initials: OC

// Date: January 21, 2023

int insertionSort(int array[], int size){
    

    return 0;
}
int main() {

    int arraySize = 0;
    printf("\nPlease enter number of elements in array:\n");
    scanf("%d",&arraySize);
    int i = 0;
    int inputArray[arraySize];
    //printf("\nPlease enter each of the %d elements of the array (You must click enter after each entry)\n",arraySize);
    for(i = 0; i < arraySize; i++){
        printf("\nPlease enter element %d of the array followed by enter\n",i + 1);
        scanf("%d",&inputArray[i]);
    }
    printf("\nThe given array is: ");
    printf("[");
    for(i = 0; i < arraySize; i++){
        //printf("%d, ",inputArray[i]);
        if(i == arraySize-1){
            printf("%d",inputArray[i]);
        }
        else{
            printf("%d, ",inputArray[i]); 
        }
    }
    printf("]\n");
return 0;
}