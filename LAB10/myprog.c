/* 
 * Sample program to illustrate I/O streams and I/O redirection 
 * To Compile: gcc -Wall -o myprog myprog.c 
 */
#include <stdio.h>

int main(int argc, char **argv) {
	char name[BUFSIZ];

	printf("Please enter your name: ");
	scanf("%s", name);//When using < filename.txt as a terminal entry. This scanf function will take input from the given txt file
	printf("[stdout]: Hello %s!\n", name);
	fprintf(stderr, "[stderr]: Hello %s!\n", name);

	return 0;
}
