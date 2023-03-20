# HW3: Add -e flag

## Name: Obie Carnathan

## Honor Code:

I, Obie Carnathan, declare that I have completed this assignment completely and entirely on my own, without any unathorized consultation from others or unathorized access to online websites. I have read the UAB Academic Honor Code and understand that any breach of the UAB Academic Honor Code may result in severe penalties.

Student Signature/Initials: OC

Date: 20230319

## Assignment:
Objectives 
To add additional features to the search program implemented in Project #2.
 
Description
The goal of this project is to add additional functionality to the search program
implemented in Project #2. In addition to the functionality described in Project #2, the
program must support the following command-line options:
1. -e "<unix-command with arguments>"
For each file that matches the search criteria the UNIX command specified with
arguments must be executed.
2. -E "<unix-command with arguments>" [Graduate Students Only]
The list of files that matches the search criteria must be provided as an argument to
the UNIX command specified.
Note that with the -e option the UNIX command is executed for each file whereas with
the -E option the UNIX command is executed only once but uses all the file names as
the argument. You must use fork/exec/wait to create a new process to execute the
UNIX command.
The UNIX command and any optional arguments are enclosed within double quotes.
The program should support -e or -E options in combination with -s and -f options. You
can assume that the -e or -E options appear after the -s and -f options.

## Compilation instructions:
    make file is set to compile the program. Once the program has been compiled you must enter ./HW3 to run the program. By default the program will list all files in the current directory.

    A directory does not need to be specified to run program.

## Testing:
    Program was tested with all favorable commands and command combinations.

    Program may error out or exit with a segmentation fault if a command is not valid.