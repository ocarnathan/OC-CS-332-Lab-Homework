#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>


// I, Obie Carnathan, declare that I have completed this assignment completely and entirely on my own, without any unathorized consultation from others or unathorized access to online websites. I have read the UAB Academic Honor Code and understand that any breach of the UAB Academic Honor Code may result in severe penalties.

// Student Signature/Initials: OC

// Date: January 22, 2023



int checkifPrime(int n){//Takes a positive integer n and tells if it is a prime number or not
    int j = 0;//initializes and declares int j. To be used later as iterative variable in for loop
    double root = sqrt(n);//Computes the square root of the input number. if you test all the numbers up to the square root, you can rest assured that the number is prime. 
    int factors = 0;//Keeps count of the amount of factors tha the input number has
    for(j = 2;j <= root;j++)//Beginning at 2, this for loop divides J into the input number.
    {
        if(n % j == 0) //if n is evenly divisible by j the factor counter will increase.
        {
            factors++;
        }
    }
         
    if(factors < 1 && n > 1)//If the current i value only has two factors.
    {
        //printf("The given number %d, is a prime number. ",n);
        return 1;
    }
    else {
        //printf("The given number %d, is not a prime number. ",n);
        return 0;
    }
}
// Write the function intro332532 that takes a positive integer n and prints a string according
// to the following conditions
// - if n is divisible by 5, it should print “UAB”
// - if n is divisible by 3, it should print “CS”
// - if n is divisible by both 3 and 5, it should print “UAB CS 332&532”
// - if n is a prime number other than 3 or 5 it should print “Go Blazers”
// - otherwise, it should print the cube of n
void intro332532(int n){//takes a positive integer as input
    if (n % 5 == 0 && n % 3 == 0){//if the input number is evenly divisible by 5 and evenly divisible by 3
        printf("UAB CS 332&532\n");//print "UAB CS 332&532"
    }
    else if (n % 5 == 0){//If the input number is evenly divisible by 5
        printf("UAB\n");//print "UAB"
    }
    else if (n % 3 == 0){//If the input number is evenly divisible by 3
        printf("CS\n");//print "CS"
    }
    else if (checkifPrime(n) && n != 3 && n != 5){
        printf("Go Blazers\n");
    }
}

// Write the function UABNumber that will ask user to enter an integer and assign this value to a
// an integer variable n2. Your function will return a Boolean value (True or False). You will
// consider a number is a UABNumber if the value of the number is equal to the sum of its
// positive divisors. Your function will consider the input value and return True if the input
// parameter is a UABNumber, it will return False otherwise. While finding the positive divisors, do
// not include the number itself and assume n is equal or greater than 0.
int UABNumber(int n2){
    int i = 1;
    int total = 0;
    for(i = 1; i < n2; i++){
        if(n2 % i == 0){
            total+=i;
        }
    }
    if ( n2 == total){
        printf("True\n");
        return 1;
    }
    else{
        printf("False\n");
        return 0;
    }
    // return(n2 == total);
}

// Write the function “reverseNum” that takes an integer n3 and returns another integer. The
// function will reverse the order of the digits and return the new value. Assume the input will
// contain the positive integers only
// REFERENCE: https://www.tutorialspoint.com/c_standard_library/c_function_sprintf.htm
// REFERENCE: https://stackoverflow.com/questions/10204471/convert-char-array-to-a-int-number-in-c
int reverseNum(int n3){
  char input[50] = {0};
    // result[50];
  //int num = 1234;
  sprintf(input, "%d", n3);
  printf("\n You entered: %s", input);
  char result[50];
  int i = 0;
  int j = 49;
  int k = 0;
  int o;
    for(i = 49; i >= 0; i--){    
      if(input[i] != 0){
        result[k] = input[i];
        k+=1;
      }
    }
  o = atoi(result);
  printf(" The number in reverse is: %d\n",o);
}

// Write the function smallerThanIndex() that takes an array of integers (numbers) and return an
// integer. The function will check every number’s value and their indices. Count the number of integers in
// the array whose value is smaller than index and return the total.
// +10 Bonus points: Use pointers to manipulate the array
// REFERENCE: https://flaviocopes.com/c-array-length/
int smallerThanIndex(int nums[], int size){
    int element;//iteration variable
    int counter = 0;//Counts the number of integers whose value is smaller than index
    for(int element = 0; element < size; element++){//loops through the input array
        if(nums[element] < element){//if the value at index is smaller than the index
            counter+=1;//Counts the number of integers whose value is smaller than index
        }
    }
    return counter;//returns the number of integers with a value smaller than their perspective index
}

// Write a function arrayDetails that takes in an integer array arr and returns another array
// containing (in the following order) the number of elements in the array, the minimum value, the
// minimum value’s index, the mean (rounded to the nearest hundredth), the maximum value and the
// maximum value’s index (total of six elements). Assume that the input will always be an array of
// integers. Built-in-methods and functions are permitted.
int arrayDetails(int array[], int size){
    double arrayDetails[6];
    arrayDetails[0] = size;//First element equals size of the input array
    int minIndex = 0;
    int minValue = 0;
    int i = 0;
    double meanOfArray = 0;
    for(i = 0; i < size; i++){
        if(array[i] < array[minIndex]){
            minIndex = i;
            arrayDetails[1] = array[minIndex];//Second element equals the minimun value of the input array.
            arrayDetails[2] = minIndex;//Third element equals the index of the minimun value of the input array.
        }
        meanOfArray+=array[i];
    }
    meanOfArray = meanOfArray/size;
    arrayDetails[3] = meanOfArray;//Fourth element equals the mean of the elements in the input array.
     for(i = 0; i < size; i++){
        if(array[i] > array[minIndex]){
            minIndex = i;
            arrayDetails[4] = array[minIndex];//Fifth element equals the maximum value of the input array.
            arrayDetails[5] = minIndex;//Sixth element equals the index of the maximum value of the input array.
        }
    }
    printf("[");
    for(i = 0; i < 6; i++){
        //printf("%d, ",(int)arrayDetails[i]);
        if(i == 6-1){
            printf("%d",(int)arrayDetails[i]);
        }
        else if(i == 6-3){
            printf("%.2f, ",arrayDetails[i]);             
        }
        else{
            printf("%d, ",(int)arrayDetails[i]); 
        }
    }
    printf("]\n");
    return 0;
}
int main()
{
    printf("\nHere are the results from the Intro332532 Function\n");
    intro332532(15);
    intro332532(10);
    intro332532(9);
    intro332532(89);

    printf("\nHere are the results from the UABNumber Function\n");
    UABNumber(28);
    UABNumber(12);
    UABNumber(6);
    UABNumber(27);

    reverseNum(1234);

    printf("\nHere are the results from the smallerThanIndex Function\n");    
    int numbers[5] = {10,20,1,2,30};
    int size = sizeof(numbers)/sizeof(numbers[0]);
    printf("%d\n",smallerThanIndex(numbers,size));

    int numbers2[6] = {1,2,0,44,29,309};
    size = sizeof(numbers2)/sizeof(numbers2[0]);
    printf("%d\n",smallerThanIndex(numbers2,size));

    int numbers3[5] = {-4,-3,2,1,0};
    size = sizeof(numbers3)/sizeof(numbers3[0]);
    printf("%d\n",smallerThanIndex(numbers3,size));
// REFERENCE: https://www.youtube.com/watch?v=tdJz1JzqN4A
    int arraySize = 0;
    printf("\nPlease enter number of elements in array:\n");
    scanf("%d",&arraySize);
    int *array = (int*) malloc(arraySize * sizeof(int));
    if(array == NULL){
        puts("failed to allocate memory");
    }
    else{
        int i = 0;
        for(i = 0; i < arraySize; i++){
            printf("\nPlease enter element %d of the array followed by enter\n",i + 1);
            scanf("%d",&array[i]);
    }
    printf("\nThe given array is: ");
    printf("[");
    for(i = 0; i < arraySize; i++){
        if(i == arraySize-1){
            printf("%d",array[i]);
        }
        else{
            printf("%d, ",array[i]); 
        }
    }
    printf("]\n");
    arrayDetails(array,arraySize);
    free(array);
}
}