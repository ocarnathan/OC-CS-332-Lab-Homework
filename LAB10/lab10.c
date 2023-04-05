/* 
 * To Compile: gcc -Wall -o lab10 lab10.c
 * To Run: ./lab10 commands.txt
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>
#include <string.h>
#include <fcntl.h>

void createarray(char *buf, char **array) {
	int i, count, len;
	len = strlen(buf);
	buf[len-1] = '\0'; /* replace last character (\n) with \0 */
	for (i = 0, array[0] = &buf[0], count = 1; i < len; i++) {
		if (buf[i] == ' ') {
		   buf[i] = '\0';
		   array[count++] = &buf[i+1];
		}
	}
	array[count] = (char *)NULL;
}

int main(int argc, char **argv) {
    pid_t pid = getpid();
    int status;
    char line[BUFSIZ], buf[BUFSIZ], *args[BUFSIZ];
    time_t t1, t2;
    int fdin, fdout;
    
    char pid_str_out[10];//pid.out
    char pid_str_err[10];//pid.err
    sprintf(pid_str_out, "%d.out", pid);
    sprintf(pid_str_err, "%d.err", pid);
    /* display program usage if arguments are missing */
    if (argc < 2) {
        printf("Usage: %s <commands file>\n", argv[0]);
        exit(-1);
    }
    // 1. Open the file specified as the command-line argument.
    FILE *fp1 = fopen(argv[1],"r");
    if (fp1 == NULL) {
	printf("Error opening file %s for reading\n", argv[1]);
	exit(-1);
    }

    FILE *fp2 = fopen("output.log","w");
    if (fp2 == NULL) {
	printf("Error opening file output.log for writing\n");
	exit(-1);
    }

    if ((fdin = open(pid_str_out, O_CREAT | O_APPEND | O_WRONLY, 0755)) == -1) {
       printf("Error opening file %s for input\n", pid_str_out);
       exit(-1);
    }

    if ((fdout = open(pid_str_err, O_CREAT | O_APPEND | O_WRONLY, 0755)) == -1) {
       printf("Error opening file %s for output\n", pid_str_err);
       exit(-1);
    }
    // 2. Read contents of the file one-line at a time.
    while (fgets(line, BUFSIZ, fp1) != NULL) {
      strcpy(buf, line); /* save line read */
      createarray(line, args);
#ifdef DEBUG
      int i;
      printf("%s", buf);
      for (i = 0; args[i] != NULL; i++)
          printf("[%s] ", args[i]);
      printf("\n");
#endif
      time(&t1);
      /* 3. Use fork-exec to create a new process that executes the program 
      specified in the input file along with the arguments provided.*/
      pid = fork();
      if (pid == 0) { /* this is child process */
      /* 4. The child process will redirect the standard output stream (stdout) to a
        file <pid>.out. The child process will redirect the standard output stream (stdout) to a
       file <pid>.out */
        dup2(fdin, 1);
        dup2(fdout, 2);
        execvp(args[0], args);
	      perror("exec");
	      exit(-1);
      } else if (pid > 0) { /* this is the parent process */
        //printf("Child started at %s", ctime(&t1));
        //printf("Wait for the child process to terminate\n");
        wait(&status); /* wait for the child process to terminate */
        time(&t2);
        //printf("Child ended at %s", ctime(&t2));
        if (WIFEXITED(status)) { /* child process terminated normally */
	  //printf("Child process exited with status = %d\n", WEXITSTATUS(status));
        } else { /* child process did not terminate normally */
	  /* look at the man page for wait (man 2 wait) to determine
	     how the child process was terminated */
        }
	buf[strlen(buf) - 1] = '\t'; /* replace \n included by fgets with \t */
	strcat(buf, ctime(&t1)); /* append start time to command with arguments */
	buf[strlen(buf) - 1] = '\t'; /* replace \n added by ctime at the end with \t */
	strcat(buf, ctime(&t2)); /* append end time */
	fprintf(fp2, "%s", buf);
	fflush(fp2);
      } else { /* we have an error */
        perror("fork"); /* use perror to print the system error message */
        exit(EXIT_FAILURE);
      }
    }

    fclose(fp1);
    fclose(fp2);
    printf("[%ld]: Exiting main program .....\n", (long)getpid());

    return 0;
}
