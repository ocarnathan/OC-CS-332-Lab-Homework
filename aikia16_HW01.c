#include <stdio.h>
#include <math.h>



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


int main()
{
    intro332532(15);
    intro332532(10);
    intro332532(9);
    intro332532(89);      
}