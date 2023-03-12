# LAB7: Fork and Exec

## Name: Obie Carnathan

## Honor Code:

I, Obie Carnathan, declare that I have completed this assignment completely and entirely on my own, without any unathorized consultation from others or unathorized access to online websites. I have read the UAB Academic Honor Code and understand that any breach of the UAB Academic Honor Code may result in severe penalties.

Student Signature/Initials: OC

Date: 20230311

## Assignment:
Objective: Write a program that takes a filename as a command-line argument and performs the following steps:

Open the file provided as a command-line argument.

Read the contents of the file one-line at a time (use fgets or getline).

Use fork-exec to create a new process that executes the program specified in the input file along with the arguments provided.

The parent process will make note of the time the program was started (you can use a timer such as the time function defined in <time.h> to capture the time before the fork method is invoked, you can find out more about time function by typing man time).

Then the parent process will wait for the child process to complete and when the child process terminates successfully, the parent process will capture the time the child process completed (you can again use a timer function to capture the time when the wait function returns).

Open a log file (say, output.log) and write the command executed along with arguments, start time of the process, and the end time of the process separated by tabs. Use ctime function to write the time in a human readable form.

Go to step 2 and repeat the above process for very command in the input file. Please use standard I/O library function calls for all I/O operations in this assignment. Make sure you open the file in the appropriate modes for reading and writing and also make sure to close the file, especially when you are writing the file.
