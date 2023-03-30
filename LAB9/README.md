# Lab-09: Signal Handling

## **Outcomes:**

- Understand what a signal is (in relationship to Unix).

- Understand the roles signals play in a Unix environment.

- Understand what might cause a signal to be sent.

- Understand what the signals SIGINT, SIGQUIT, SIGTSTP, SIGUSR1, SIGUSR2 do.

- Understand the three responses a process might have to a signal.

- Understand what signal catching is.

- Be able to use the signal()/sigaction() function to modify the default response (disposition) of a process to a signal.

## **Objective:** 

Modify the program *forkexecvp.c* (found on GitHub and Canvas) such that when you type Control-C the child process is interrupted and when you type Control-Z the child process is suspended. In both cases,the parent process should continues to wait until it receives a quit signal (Control-\). 

## **Submission:**

- Your submission to Canvas should include a README file (including basic information about your program) and your source code as a .c file) 

- Be sure to submit your README and your source code in a ZIP file.

- Be sure to include the independent completition code snippet at the top of your source code.

I, Obie Carnathan, declare that I have completed this assignment completely and entirely on my own, without any unathorized consultation from others or unathorized access to online websites. I have read the UAB Academic Honor Code and understand that any breach of the UAB Academic Honor Code may result in severe penalties.

Student Signature/Initials: OC

Date: 20230328