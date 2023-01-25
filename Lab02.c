#include <stdio.h>
#include <math.h>
#include <stdlib.h>

// I, Obie Carnathan, declare that I have completed this assignment completely and entirely on my own, without any unathorized consultation from others or unathorized access to online websites. I have read the UAB Academic Honor Code and understand that any breach of the UAB Academic Honor Code may result in severe penalties.

// Student Signature/Initials: OC

// Date: January 21, 2023

int insertionSort(int array[], int size){
    int temp, current;
    int i = 0;
    for(int i = 0; i < size; i++){
        current = i;
        while(current > 0 && array[current-1] > array[current]){
            temp = array[current];
            array[current] = array[current-1];
            array[current-1] = temp;
            current-=1;
        }
    }
    printf("\nThe sorted array is: ");
    printf("[");
    for(i = 0; i < size; i++){
        if(i == size-1){
            printf("%d",array[i]);
        }
        else{
            printf("%d, ",array[i]); 
        }
    }
    printf("]\n");
    return 0;
}
int main() {

    int arraySize = 0;
    printf("\nPlease enter number of elements in array:\n");
    scanf("%d",&arraySize);
    int i = 0;
    int inputArray[arraySize];

    for(i = 0; i < arraySize; i++){
        printf("\nPlease enter element %d of the array followed by enter\n",i + 1);
        scanf("%d",&inputArray[i]);
    }
    printf("\nThe given array is: ");
    printf("[");
    for(i = 0; i < arraySize; i++){
        if(i == arraySize-1){
            printf("%d",inputArray[i]);
        }
        else{
            printf("%d, ",inputArray[i]); 
        }
    }
    printf("]\n");
    insertionSort(inputArray,arraySize);
return 0;
}