/*
Simple Pthread Program to find the sum of a vector.
Uses mutex locks to update the global sum.
Author: Purushotham Bangalore
Date: Jan 25, 2009

To Compile: gcc -O -Wall lab11.c -lpthread
To Run: ./a.out 1000 4
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
/*
int pthread_create(pthread_t *thread, const pthread_attr_t *attr, void *(*start_routine) (void *), void *arg);


The new thread that will be created by the pthread_create function will invoke the function start_routine. Note that the function start_routine takes one argument of type void * and has the return type as void *. In other words, the
function start_routine has the following function definition:
void *start_routine(void *arg)
*/

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

// double *a = NULL, sum = 0.0;
// int N, size;


struct Variables{
    double a;
    double sum;
    int N;
    int size;
    long tid;
};

void *compute(void *arg) {
    int myStart, myEnd, myN, i;

    struct Variables *values = ( struct Variables *) arg;
    long tid = (*values).tid;//cast struct back to it's original data type here.
    // determine start and end of computation for the current thread
    //When accessing data types in a struct, if it's a pointer then you use an arrow "->", else use "."
    char size = (*values).size;
    int N = (*values).N + 1;
    
    myN = N / size;
    myStart = tid*myN;
    myEnd = myStart + myN;

    if(tid == (size-1)) myEnd = N;

    //compute partial sum
    double mysum = 0.0;

    for (i=myStart; i<myEnd; i++)
        mysum += i;

    //grab the lock, update global sum, and release lock
    pthread_mutex_lock(&mutex);//Will lock the chuck of code below until it sees unlock.
    (*values).sum += mysum;
    pthread_mutex_unlock(&mutex);

    return (NULL);
}

int main(int argc, char **argv) {
    long i;
    pthread_t *tid;
    double sum = 0;
    //Variables *values;

    if (argc != 3) {
        printf("Usage: %s <# of elements> of threads>\n" ,argv[0]);
        exit(-1);
    }

    int N = atoi(argv[1]); // no. of elements
    int size = atoi(argv[2]); // no. of threads
    struct Variables values[N];
    // allocate cvector and initialize
    tid = (pthread_t *)malloc(sizeof(pthread_t)*size);
    double *a = (double *)malloc(sizeof(double)*N);
    //values = (Variables *)malloc(sizeof(Variables)*size);

    for (i=0; i<N; i++){
        a[i] = (double)(i + 1);
        values[i].a = a[i];
        values[i].N = N;
        values[i].size = size;
    }
    // create threads
    for ( i=0; i<size; i++){

        values[i].tid = i;

        pthread_create(&tid[i], NULL, compute, (void *)&values[i]);//pass in struct here in the last parameter position. U won't need the mutex lock to avoid race conditions.

    }
/*       The pthread_create() function starts a new thread in the calling process.  The new thread starts execution by invoking start_routine(); arg is passed as the sole argument of start_routine().

       The new thread terminates in one of the following ways:

       * It calls pthread_exit(3), specifying an exit status value that is available to another thread in the same process that calls pthread_join(3).

       * It returns from start_routine().  This is equivalent to calling pthread_exit(3) with the value supplied in the return statement.

       * It is canceled (see pthread_cancel(3)).

       * Any of the threads in the process calls exit(3), or the main thread performs a return from main().  This causes the termination of all threads in the process.

       The  attr argument points to a pthread_attr_t structure whose contents are used at thread creation time to determine attributes for the new thread; this structure is initialized using pthread_attr_init(3) and re‐
       lated functions.  If attr is NULL, then the thread is created with default attributes.

       Before returning, a successful call to pthread_create() stores the ID of the new thread in the buffer pointed to by thread; this identifier is used to refer to the thread in subsequent  calls  to  other  pthreads
       functions.

       The  new  thread  inherits  a copy of the creating thread's signal mask (pthread_sigmask(3)).  The set of pending signals for the new thread is empty (sigpending(2)).  The new thread does not inherit the creating
       thread's alternate signal stack (sigaltstack(2)).

       The new thread inherits the calling thread's floating-point environment (fenv(3)).

       The initial value of the new thread's CPU-time clock is 0 (see pthread_getcpuclockid(3)).
*/        

    // wait for them to complete
    for (i = 0; i < size; i++)
        pthread_join(tid[i], NULL);
/*       The  pthread_join()  function  waits for the thread specified by thread to terminate.  If that thread has already terminated, then pthread_join() returns immediately.  The thread specified by thread must be join‐
       able.

       If retval is not NULL, then pthread_join() copies the exit status of the target thread (i.e., the value that the target thread supplied to pthread_exit(3)) into the location pointed to by retval.  If  the  target
       thread was canceled, then PTHREAD_CANCELED is placed in the location pointed to by retval.

       If multiple threads simultaneously try to join with the same thread, the results are undefined.  If the thread calling pthread_join() is canceled, then the target thread will remain joinable (i.e., it will not be
       detached).
*/ 
    for (int j = 0; j < N; j++){
        sum += values[j].sum;
    }
    printf("The total is %g, it should be equal to %g\n", sum, ((double)N*(N+1))/2);
   
    return 0;
}