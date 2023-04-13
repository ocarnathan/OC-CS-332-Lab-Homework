# LAB11: Create threads using POSIX threads library 

## Name: Obie Carnathan

## Honor Code:

I, Obie Carnathan, declare that I have completed this assignment completely and entirely on my own, without any unathorized consultation from others or unathorized access to online websites. I have read the UAB Academic Honor Code and understand that any breach of the UAB Academic Honor Code may result in severe penalties.

Student Signature/Initials: OC

Date: 20230412

## Assignment:
Objectives 
• Create threads using POSIX threads library
• Thread synchronization using Mutexes
 
Homework
Modify the pthread_sum.c program to create a structure and pass the structure as argument to the thread creation function instead of using global variables a, sum, N, and size. You have to create a structure that contains the variables a and sum with type double, variables N and size with type int, and variable tid with type long or int. You have to create an instance of this structure specific to each thread and pass the structure as an argument to the corresponding thread creation function. Test the program for different values of N and number of threads and make sure that the result is correct.
