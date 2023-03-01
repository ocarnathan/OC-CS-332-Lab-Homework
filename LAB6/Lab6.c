#include <stdio.h>//This library provides functions for performing input and output operations on files and streams. Functions such as printf(), scanf(), fopen(), fclose(), fread(), and fwrite() are part of this library.
#include <sys/stat.h>
#include <stdlib.h>
#include <string.h>

#define LINESIZE 1024

//1. Declare a struct called 'Listing' with contains all the attributes found in 'Listings.csv'.
//Listing contains all the attributes found in Listing.csv
struct listing {
	int id, host_id, minimum_nights, number_of_reviews, calculated_host_listings_count,availability_365;
	char *host_name, *neighbourhood_group, *neighbourhood, *room_type;
	float latitude, longitude, price;
};
//2. Define a function that will take one line of the CSV file and return a 'Listing' struct with corresponding attribute values.
struct listing getfields(char* line){
	struct listing item;

	/* Note: you have to pass the string to strtok on the first 
	   invocation and then pass NULL on subsequent invocations */
	item.id = atoi(strtok(line, ","));
	item.host_id = atoi(strtok(NULL, ","));
	item.host_name = strdup(strtok(NULL, ","));
	item.neighbourhood_group = strdup(strtok(NULL, ","));
	item.neighbourhood = strdup(strtok(NULL, ","));
	item.latitude = atof(strtok(NULL, ","));
	item.longitude = atof(strtok(NULL, ","));
	item.room_type = strdup(strtok(NULL, ","));
	item.price = atof(strtok(NULL, ","));
	item.minimum_nights = atoi(strtok(NULL, ","));
	item.number_of_reviews = atoi(strtok(NULL, ","));
	item.calculated_host_listings_count = atoi(strtok(NULL, ","));
	item.availability_365 = atoi(strtok(NULL, ","));
	/*The strdup function takes a single argument, which is a pointer
	 to a null-terminated string of characters (const char *str). 
	 The function returns a pointer to a newly allocated memory block 
	 containing a duplicate copy of the input string. If the memory 
	 allocation fails, the function returns NULL.*/

	return item;
}

// FILE *fptr;
// fptr = fopen("listings.csv", "rw+");
int getLine(FILE *fp, char *line);

int getLine(FILE *fp, char *line){
    int c, i = 0;
    while((c = getc(fp)) != '\n' && c != EOF)
    /*getc() gets next character from the specified stream and
    advances the position indicator for the stream*/

        line[i++] = c;
    line[i] = '\0';
    return i;
}

int sortByPrice (const void *ptr1, const void *ptr2){
	//Cast the argument back to the the type we passed in.
	const struct listing *arg1 = (struct listing *)ptr1;
	const struct listing *arg2 = (struct listing *)ptr2;

    if (arg1->price < arg2->price){
        return -1;
    } 
    else if (arg1->price == arg2->price) {
        return 0;
    }
    else if (arg1->price > arg2->price) {
        return 1;
    }
}

int sortByHostName (const void *ptr1, const void *ptr2){
	//Cast the argument back to the the type we passed in.
	const struct listing *arg1 = (struct listing *)ptr1;
	const struct listing *arg2 = (struct listing *)ptr2;

    if (strcmp(arg1->host_name, arg2->host_name) < 0) {
        return -1;
    } 
    else if (strcmp(arg1->host_name, arg2->host_name) == 0) {
        return 0;
    }
    else if (strcmp(arg1->host_name, arg2->host_name) > 0) {
        return 1;
    }
}

// void sortByHostName(struct listing arr[], int size){
//     qsort(arr,size,LINESIZE,cmpfunc);
//     //return arr;
// }
/*DESCRIPTION
       The qsort() function sorts an array with nmemb elements of size size.  The base argument points to the start of the array.

       The  contents  of the array are sorted in ascending order according to a comparison function pointed to by compar, which is called
       with two arguments that point to the objects being compared.

       The comparison function must return an integer less than, equal to, or greater than zero if the first argument is considered to be
       respectively less than, equal to, or greater than the second.  If two members compare as equal, their order in the sorted array is
       undefined.*/
int main(int argc, char* args[]) {
	struct listing list_items[22555];//Array of listing structs
	char line[LINESIZE];

	int i, count;

	FILE *fptr = fopen("listings.csv", "r");//Opening the listings.csv in read-mode.
	if(fptr == NULL){
		printf("Error reading input file listings.csv\n");
		exit (-1);
	}

	count = 0;
    //5. Loop through each line of the 'Listings.csv' file. Feel free to use either the fgets() function or the getline() function.
    //6. For each line, call the function you previously defined.
	while (fgets(line, LINESIZE, fptr) != NULL){//Looping through each line of the listings.csv file
    //7. Store the result in array of 'Listing' structs.
		list_items[count++] = getfields(line);//storing the results in array
	}
	fclose(fptr);
	
	FILE *fptr2 = fopen("sortedByHostName.csv", "w");
	if(fptr == NULL){
		printf("Error opening file sorted.csv\n");
		exit (-1);
	}
	
	fprintf(fptr2,
		"id,host_id,host_name,neighbourhood_group,neighbourhood,latitude,longitude,room_type,price,minimum_nights,number_of_reviews,calculated_host_listings_count,availability_365\n");
	
	//qsort(list_items, count,sizeof(list_items[0]), sortByHostName);
	//qsort(list_items, count,sizeof(list_items[0]), sortByPrice);

	qsort(list_items, count,sizeof(list_items[0]), sortByHostName);

	for (i = 0; i < count; i++){

		if(!strcmp(list_items[i].host_name,"host_name")){
			continue;
		}
		fprintf(fptr2,
				"%d,%d,%s,%s,%s,%.13f,%.13f,%s,%.0f,%d,%d,%d,%d\n",
				list_items[i].id, list_items[i].host_id,list_items[i].host_name,list_items[i].neighbourhood_group,list_items[i].neighbourhood,
				list_items[i].latitude,list_items[i].longitude,list_items[i].room_type,list_items[i].price,list_items[i].minimum_nights,
				list_items[i].number_of_reviews,list_items[i].calculated_host_listings_count,list_items[i].availability_365);
	}
	fclose(fptr2);
	
	FILE *fptr3 = fopen("sortedByPrice.csv", "w");
	if(fptr3 == NULL){
		printf("Error opening file sorted.csv\n");
		exit (-1);
	}

	fprintf(fptr3,
		"id,host_id,host_name,neighbourhood_group,neighbourhood,latitude,longitude,room_type,price,minimum_nights,number_of_reviews,calculated_host_listings_count,availability_365\n");

	// fprintf(fptr3,
	// 	"%d, %d, %s, %s, %s, %.8f, %.6f, %s, %.0f, %d, %d, %d, %d\n",
	// 	list_items[0].id, list_items[0].host_id,list_items[0].host_name,list_items[0].neighbourhood_group,list_items[0].neighbourhood,
	// 	list_items[0].latitude,list_items[0].longitude,list_items[0].room_type,list_items[0].price,list_items[0].minimum_nights,
	// 	list_items[0].number_of_reviews,list_items[0].calculated_host_listings_count,list_items[0].availability_365);
	
	//qsort(list_items, count,sizeof(list_items[0]), sortByHostName);
	//qsort(list_items, count,sizeof(list_items[0]), sortByPrice);

	qsort(list_items, count,sizeof(list_items[0]), sortByPrice);

	for (i = 0; i < count; i++){

		if(!strcmp(list_items[i].host_name,"host_name")){
			continue;
		}
		fprintf(fptr3,
				"%d,%d,%s,%s,%s,%.13f,%.13f,%s,%.0f,%d,%d,%d,%d\n",
				list_items[i].id, list_items[i].host_id,list_items[i].host_name,list_items[i].neighbourhood_group,list_items[i].neighbourhood,
				list_items[i].latitude,list_items[i].longitude,list_items[i].room_type,list_items[i].price,list_items[i].minimum_nights,
				list_items[i].number_of_reviews,list_items[i].calculated_host_listings_count,list_items[i].availability_365);
	}
	fclose(fptr3);

	return 0;
}

/*
Standard I/O libraries in programming provide functions for input and output operations on files and other streams, such as standard input and output. The most commonly used standard I/O libraries are:

<stdio.h> - This library provides functions for performing input and output operations on files and streams. Functions such as printf(), scanf(), fopen(), fclose(), fread(), and fwrite() are part of this library.

<iostream> - This library is part of the C++ standard library and provides the same functionality as <stdio.h> but using a different syntax. It includes the classes cin, cout, cerr, and clog for handling input and output.

<cstdio> - This is a C++ implementation of <stdio.h> and provides the same set of functions.

<fstream> - This library is also part of the C++ standard library and provides classes for handling input and output files. It includes ifstream and ofstream classes for reading and writing files, respectively.

<unistd.h> - This library is used for performing I/O operations on Unix-like systems. It includes functions such as read(), write(), open(), and close().

These libraries provide a wide range of functions and classes for performing input and output operations, and are commonly used in programming for tasks such as reading and writing files, handling user input, and displaying output to the console or terminal.
*/