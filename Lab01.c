#include <stdio.h>
#include <math.h>

// I, Obie Carnathan, declare that I have completed this assignment completely and entirely on my own, without any unathorized consultation from others or unathorized access to online websites. I have read the UAB Academic Honor Code and understand that any breach of the UAB Academic Honor Code may result in severe penalties.

// Student Signature/Initials: OC

// Date: January 13, 2023


void checkifPrime(int n){
    int j = 0;
    double root = sqrt(n);
    int factors = 0;
    for(j = 2;j <= root;j++)
    {
        if(n % j == 0) //if n is evenly divisible by j
        {
            factors++;
        }
    }
         
    if(factors < 1 && n > 1)//If the current i value only has two factors.
    {
        printf("The given number %d, is a prime number. ",n);
    }
    else {
        printf("The given number %d, is not a prime number. ",n);
    }
}
int main() { 
    int givenNumber = 0;
    printf("\nEnter an integer.\n");
    scanf("%d",&givenNumber);
    checkifPrime(givenNumber);
    // double number = givenNumber;
    // double sq;
    // sq = sqrt(number);
    // printf("%lf",sq);
return 0;
}
//gcc Lab01.c -lm