#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <sys/types.h>  
#include <stdlib.h>
//The objective of this lab is to introduce you to create processes and manage them. 


int main(int argc, char **argv) {
    pid_t pid;
    int status;

    pid = fork(); /*creates a new process by calling the fork() system call. 
    The return value of fork() indicates whether the current process is the parent or child process.*/
    if (pid == 0) {//If fork() returns 0, then the current process is the child process
        printf("This is the child process, my PID is %ld and my parent PID is %ld\n",
        (long)getpid(),(long)getppid());
    /* ^If the current process is the child process, it prints a message indicating that it is the child
     process and displays its process ID (PID) and its parent process ID (PPID).*/
    } else if (pid > 0) {// if fork() returns a positive integer, then the current process is the parent process.
        printf("This is the parent process, my PID is %ld and the child PID is %ld\n",
        (long)getpid(),(long)pid);
    /*If the current process is the parent process, it prints a message indicating that it is the parent
     process and displays its process ID (PID) and the child process ID (pid) returned by the fork()
     system call. The parent process then waits for the child process to terminate by calling the wait()
     system call. The wait() system call suspends the execution of the parent process until the child
     process terminates.*/

    printf("Wait for the child process to terminate\n");
    wait(&status);//Wait for the child process to terminate
    if(WIFEXITED(status)) {//child process terminated normally
        printf("Child process exited with status = %d\n", WEXITSTATUS(status));
    } else {//child process did not terminate normally!\n
        printf("ERROR: Child process did not terminate normally!\n");
        //loot at the man page for wait(man 2 wait) to determine how the child process was terminated
    }
    } else {//we have an error in the process creation
        perror("fork");
        exit(EXIT_FAILURE);    
    }
    /*After the child process terminates, the parent process checks the status of the child process
     by calling the WIFEXITED and WEXITSTATUS macros defined in sys/wait.h. If the child process 
     terminated normally, WIFEXITED returns a non-zero value, and WEXITSTATUS returns the exit status 
     of the child process. If the child process did not terminate normally, the parent process prints an error message.*/
    printf("[%ld]: Existing program .....\n", (long)getpid());
    return 0;

}
/*
int execl(const char *pathname, const char *arg, ...); 
int execlp(const char *filename, const char *arg, ...); 
int execle(const char *pathname, const char *arg, ..., char * const envp[]); 
int execv(const char *pathname, char *const argv[]); 
int execvp(const char *filename, char *const argv[]); 
int execvpe(const char *filename, char *const argv[], char *const envp[]); 
*/
/*The execl() function takes as arguments the full pathname of the executable 
along with a pointer to an array of characters for each argument. Since we can 
have a variable number of arguments, the last argument is a null pointer. */