#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <sys/types.h>  
#include <stdlib.h>
#include <time.h>
#include <string.h>


int main(int argc, char **argv) {

    pid_t pid;
    int status;

    if (argc < 2) {//require at least one argument givenSS
        printf("Usage: %s <command> [args]\n", argv[0]);
        exit(-1);
    }

    FILE *fptr = fopen(argv[1], "r");//1. Open the file provided as a command-line argument.
    FILE *fptr2 = fopen("output.log", "w");//New file for writing
    if(fptr == NULL || fptr2 == NULL){
        exit(-1);
    }
    char *line = malloc(BUFSIZ * sizeof(char));

    while(fgets(line, BUFSIZ,fptr) != NULL){//2. Read the contents of the file one-line at a time (use fgets or getline).
        int i = 0;
        
        char **commands = malloc(sizeof(char*)* BUFSIZ);//array for tokens
        char* token = strtok(line, " \n");

        while(token != NULL){
            commands[i] = malloc(sizeof(char) * BUFSIZ);
            strcpy(commands[i],token);
            token = strtok(NULL," \n");
            i++;
        }
        commands[i] = NULL;//setting last index equal to NULL
        time_t startTime = time(NULL);/*4. The parent process will make note of the time the program was 
        started (you can use a timer such as the time function defined in <time.h> to capture the time 
        before the fork method is invoked, you can find out more about time function by typing man time).*/
        pid = fork();

        if (pid == 0) { /* this is child process */
            execvp(commands[0],commands);
            printf("If you see this statement then exec failed ;-(\n");
            perror("execvp");
            exit(-1);
        } else if (pid > 0) { /* this is the parent process */
            printf("Wait for the child process to terminate\n");/*Then the parent process will wait for the child 
            process to complete and when the child process terminates successfully, the parent process will 
            capture the time the child process completed (you can again use a timer function to capture the time 
            when the wait function returns).*/
            wait(&status); /* wait for the child process to terminate */
            if (WIFEXITED(status)) { /* child process terminated normally */
                printf("Child process exited with status = %d\n", WEXITSTATUS(status));
                time_t endTime = time(NULL);
                fprintf(fptr2, "%s\t%s\t%s\n", line,ctime(&startTime), ctime(&endTime));//No idea why this won't format.
                /*Open a log file (say, output.log) and write the command executed along with arguments, 
                start time of the process, and the end time of the process separated by tabs. Use ctime 
                function to write the time in a human readable form.*/
            } else { /* child process did not terminate normally */
                printf("Child process did not terminate normally!\n");
                /* look at the man page for wait (man 2 wait) to determine
                how the child process was terminated */
            }
        } else { /* we have an error */
            perror("fork"); /* use perror to print the system error message */
            exit(EXIT_FAILURE);
        }
    }
        fclose(fptr);
        fclose(fptr2);
        printf("[%ld]: Exiting program .....\n", (long)getpid());
    return 0;
}
