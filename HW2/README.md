# HW2: implement a search program in C 

## Name: Obie Carnathan

## Honor Code:

I, Obie Carnathan, declare that I have completed this assignment completely and entirely on my own, without any unathorized consultation from others or unathorized access to online websites. I have read the UAB Academic Honor Code and understand that any breach of the UAB Academic Honor Code may result in severe penalties.

Student Signature/Initials: OC

Date: 20230219

## Assignment:
Objectives 
To implement a search program in C program using system calls for files and 
directories. 
 
Description 
Find is a popular UNIX command that traverses a file hierarchy and performs various 
functions on each file in the hierarchy. The goal of this project is to implement a 
program similar called search that supports the following functionality: 
1. The program should take the directory name from where to start the file traversal as a 
command-line argument and print the file hierarchy starting with the directory that is 
provided by the command-line argument. 
2. If the program is executed without any arguments, the program should print the file 
hierarchy starting with the current directory where the program is executed. If there are no 
directories in the current directory only files are listed one per line. 
3. If there are other directories in the current directory then the directory name is first 
displayed on a separate line and then the files in that directory are listed one-per-line with 
one-tab indentation. 
4. If a file is a symbolic link then the program should display the symbolic link name and in 
parentheses the file name the link points to. 
5. The program should also support three command-line options: 
1. -S 
This should list all files in the hierarchy and print the size, permissions, and last access 
time next to the filename in parenthesis. Print 0 for the size of a directory. 
2. -s <file size in bytes> 
This should list all files in the hierarchy with file size less than or equal to the value 
specified. 
3. -f <string pattern> <depth> 
This should list all files in the hierarchy that satisfy the following conditions: 1) the file 
name contains the substring in the string pattern option, AND 2) the depth of the file 
relative to the starting directory of the traversal is less than or equal to the depth option. 
The starting directory itself has a depth of 0. 
6. The program should support not only each of these options separately but also any 
combination of these options. For example: -S, -s 1024, -f jpg 1, -S -s 1024, -S -f jpg 2, -s 
1024 -f jpg 2, -S -s 1024 -f jpg 1, -S -f jpg 2 -s 1024. 

## Compilation instructions:
    make file is set to compile the program. Once the program has been compiled you must enter ./HW2 to run the program. By default the program will list all files in the current directory.

    You must enter a directory or specific commands to modify the output.

## Testing:
    Program was tested with all favorable commands and command combinations.

    Program may error out or exit with a segmentation fault if a command it not valid.