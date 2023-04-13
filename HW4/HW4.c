#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/wait.h>




int main(int argc, char **argv){
    if (argc == 2){
        printf("%s", argv[1]);
    }
    if (argc < 2){
        printf("Less than Two %s", argv[0]);
    }
    if (argc > 2){
        printf("More than Two %s", argv[0]);
    }

    while(fget)
    return 0;
}