#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <stdbool.h>
#include <unistd.h>
#include <sys/stat.h>/*is a system call in Unix-like operating systems that
 is used to retrieve information about a file, such as its size, permissions, 
 timestamps, and other attributes. The stat system call takes a filename as input, 
 and returns a struct stat object that contains the file's attributes.*/
#include <time.h>

#define MAX_PATH_SIZE 2000
static long enteredFileSize = 0;
static long fileInfoSize = 0;
static int enteredDepth = 0;
char *substring = "";

char *filetype(unsigned char type) {//

  char *str;
  switch(type) {
  case DT_BLK: str = "block device"; break;
  case DT_CHR: str = "character device"; break;
  case DT_DIR: str = "directory"; break;
  case DT_FIFO: str = "named pipe (FIFO)"; break;
  case DT_LNK: str = "symbolic link"; break;
  case DT_REG: str = "regular file"; break;
  case DT_SOCK: str = "UNIX domain socket"; break;
  case DT_UNKNOWN: str = "unknown file type"; break;
  default: str = "UNKNOWN";
  }
  return str;
}

//Variables below for getOpt to verify what options were chosen.
typedef void traverseFunctionPointer(char *path, int tabSpaces);//Points to traverseDirectory
static bool S_opt = false;
static bool s_low_opt = false;
static bool f_opt = false;




long getFileSize(char *path){
    struct stat fileSize;
    int size;
    if(stat(path, &fileSize) == -1){
        printf("stat error %s\n", path);
    }
    else{
        size = fileSize.st_size;
    }
    return size;
}
//https://www.ibm.com/docs/en/zos/2.1.0?topic=functions-access-determine-whether-file-can-be-accessed
char *fileInfo(char *path){
    char *lastAccessed;
    //int size;
    char filePermissions[10];
    char *fileSizePermissionsLastAccess = malloc(sizeof(char) * 100);
    struct stat file;
    if(stat(path, &file) == -1){
        exit(-1);
    }
    else{

        //sprintf(fileSizePermissionsLastAccessed, "Size: %d bytes, Last accessed: %s",size,lastAccessed);  
        if(access(path, R_OK) == 0){
            strcat(filePermissions,"-r");
        }
        else{
            strcat(filePermissions,"-");
        }
        if(access(path, W_OK) == 0){
            strcat(filePermissions,"w");
        }
        else{
            strcat(filePermissions,"-");
        }
        if(access(path, X_OK) == 0){
            strcat(filePermissions,"x");
        }
        else{
            strcat(filePermissions,"-");
        }
        //sprintf(fileSizePermissionsLastAccessed, "Size: %ld bytes, Permissions: %s , Last accessed: %s",fileInfoSize,filePermissions,lastAccessed);
    }
    lastAccessed = ctime(&file.st_atime);
    fileInfoSize = file.st_size;
    sprintf(fileSizePermissionsLastAccess, "Size: %ld bytes, Permissions: %s , Last accessed: %s",fileInfoSize,filePermissions,lastAccessed);
    fileSizePermissionsLastAccess[strlen(fileSizePermissionsLastAccess) - 1] = '\0';
    
    return fileSizePermissionsLastAccess;
}

//https://www.geeksforgeeks.org/getopt-function-in-c-to-parse-command-line-arguments/
void getOpt(int argc, char **argv, char *path, int tabSpaces, traverseFunctionPointer *TD){
    int opt;

    while((opt = getopt(argc, argv, "Ss:f:")) != -1){//The program accepts three options, -S,-s, or -f.
        switch(opt){
            case 'S':
                //printf("You entered S");
                S_opt = true;
                break;
            case 's':
                //printf("You entered s\n");
                s_low_opt = true;
                break;
            case 'f':
                //printf("You entered f\n");
                substring = (optarg);//working
                //printf("f arg %s\n", substring);
                enteredDepth = atoi(argv[optind]);
                f_opt = true;
                break;
            default:
                printf("Error\n");
        }
    }
    return TD(path, tabSpaces);
}


void traverseDirectory(char *path, int tabSpaces) {/*path is the name of the directory to be opened. Tab spaces will increase at every recursive call*/
   struct dirent *dirent;/*Initializes a struct dirent object pointer. 
   Will represent the next directory entry in the stream.*/

    DIR *parentDir;//Initializes a DIR pointer.
    // First, we need to open the directory.

    parentDir = opendir(path);/*path is the name of the directory to be opened*/
    /*opendir() is used to open a directory stream for reading. 
    Takes the name of the directory to be opened, as an argument. 
    It returns a pointer to a DIR structure that represents the directory stream.*/
    if (parentDir == NULL) { //If the directory was not valid(found) then return error message and exit.
        printf ("Error opening directory '%s'\n", path); 
        exit (-1);
    }
    int depthCount = 0;
    int count = 1; //Count equals 1 if directory was successfully found.
    // After we open the directory, we can read the contents of the directory, file by file.

    while((dirent = readdir(parentDir)) != NULL){ 
        /*readdir() is used to read the contents of a directory stream that was opened with opendir().
        Takes a pointer to the directory stream returned by opendir(), as an argument. It returns a 
        pointer to a struct dirent object that represents the next directory entry in the stream.*/

        // If the file's name is "." or "..", ignore them. We do not want to infinitely recurse.
        if (strcmp(dirent->d_name, ".") == 0 || strcmp(dirent->d_name, "..") == 0) {
        /*strcmp checks to see if the string arguments are equal.
        If they are, strcmp will return 0.
        If the name of the directory equals either "." or ".." the program will ignore them.*/
            continue;
        }    

        //Modifications start here

        char *filePath = (char *) malloc(MAX_PATH_SIZE);
        strcpy(filePath, path);/*strcpy() is used to copy a string from one location to another.
        Here path will be copied to subDirPath*/
        strcat(filePath, "/");//Adds a "/" to the end of the subDirPath name
        strcat(filePath, dirent->d_name);//Adds the dirent file name to the end of subDirPath name

        if(S_opt && !s_low_opt && !f_opt){//if S was entered as an option and nothing else
            printf("%*s[%d] %s (%s)\n", 4 * tabSpaces, " ", count, dirent->d_name,fileInfo(filePath)); 
        }

        else if(S_opt && s_low_opt && !f_opt){//if -S and -s was entered as an option
        //printf("working");
            fileInfoSize = getFileSize(filePath);
            // char *str = NULL;
            // char *type = filetype(dirent->d_type);
            // str = fileInfo(filePath);
            //printf("current file size:%d Desired file size:%d\n",fileInfoSize, enteredFileSize);
            if(fileInfoSize <= enteredFileSize){
                if(dirent->d_type == DT_DIR){
                    fileInfoSize = 0;
                }
                //printf("(%s) %ld is less than %ld\n",filetype(dirent->d_type),fileInfoSize,enteredFileSize);
                printf("%*s[%d] %s (%s)\n", 4 * tabSpaces, " ", count, dirent->d_name,fileInfo(filePath));
                //continue;
            }
            //printf("%*s[%d] %s (%s)\n", 4 * tabSpaces, " ", count, dirent->d_name,str);

        }
        else if(s_low_opt && !S_opt && !f_opt){//if only -s was entered
            //printf("lowercase s");
        //static int enteredFileSize = 0;
        //static int fileInfoSize = 0;
        //printf("working");
            fileInfoSize = getFileSize(filePath);
            // char *str = NULL;
            // char *type = filetype(dirent->d_type);
            // str = fileInfo(filePath);
            //printf("current file size:%ld Desired file size:%ld\n",fileInfoSize, enteredFileSize);
            if(fileInfoSize <= enteredFileSize){
                if(dirent->d_type == DT_DIR){
                    fileInfoSize = 0;
                }
                //printf("(%s) %ld is less than %ld\n",filetype(dirent->d_type),fileInfoSize,enteredFileSize);
                printf("%*s[%d] %s %ld bytes\n", 4 * tabSpaces, " ", count, dirent->d_name,fileInfoSize);
                //continue;
            }
            //printf("%*s[%d] %s (%s)\n", 4 * tabSpaces, " ", count, dirent->d_name,str);
            
        }
        else if(f_opt && !S_opt && !s_low_opt){//if only -f was entered 
            //fileInfoSize = getFileSize(filePath);
            if(strstr(dirent->d_name,substring)){
                fileInfo(filePath);
                if(depthCount <= enteredDepth && tabSpaces <= enteredDepth){
                    printf("%*s[%d] %s %ld bytes\n", 4 * tabSpaces, " ", count, dirent->d_name,fileInfoSize);
                }
            }
        }
        else if(f_opt && s_low_opt && !S_opt){//if -s and -f entered
            fileInfoSize = getFileSize(filePath);
            if(strstr(dirent->d_name,substring) && fileInfoSize <= enteredFileSize){
                fileInfo(filePath);
                if(depthCount <= enteredDepth){
                    printf("%*s[%d] %s %ld bytes\n", 4 * tabSpaces, " ", count, dirent->d_name,fileInfoSize);
                }
            }
        }
        else if(f_opt && S_opt && !s_low_opt){//if -S and -f was entered 
            //fileInfoSize = getFileSize(filePath);
            if(strstr(dirent->d_name,substring)){
                fileInfo(filePath);
                if(depthCount <= enteredDepth && tabSpaces <= enteredDepth){
                    printf("%*s[%d] %s (%s)\n", 4 * tabSpaces, " ", count, dirent->d_name,fileInfo(filePath)); 
                }
            }
        }
        else if(f_opt && S_opt && s_low_opt){//if -S and -f  and -s were entered 
            fileInfoSize = getFileSize(filePath);
            if(strstr(dirent->d_name,substring) && fileInfoSize <= enteredFileSize){
                fileInfo(filePath);
                if(depthCount <= enteredDepth && tabSpaces <= enteredDepth){
                    printf("%*s[%d] %s (%s)\n", 4 * tabSpaces, " ", count, dirent->d_name,fileInfo(filePath)); 
                }
            }
        }

        // Print the formated file.
        else{
            printf("%*s[%d] %s (%s)\n", 4 * tabSpaces, " ", count, dirent->d_name, filetype(dirent->d_type));
        }
        count++; 

        // Check to see if the file type is a directory. If it is, recursively call traverseDirectory on it.
        if (dirent->d_type == DT_DIR) { 
            /* Check to see if the file type is a directory. 
            If it is, recursively call traverseDirectory on it.*/
            // Build the new file path.
            char *subDirPath = (char *) malloc(MAX_PATH_SIZE);
            strcpy(subDirPath, path);/*strcpy() is used to copy a string from one location to another.
            Here path will be copied to subDirPath*/
            strcat(subDirPath, "/");//Adds a "/" to the end of the subDirPath name
            strcat(subDirPath, dirent->d_name);//Adds the dirent file name to the end of subDirPath name
            traverseDirectory(subDirPath, tabSpaces + 1);//Calls traverseDirectory with subDirPath and + 1 tabSpaces
            depthCount++;
        }
    } 

    closedir(parentDir);
}


int main(int argc, char **argv) {
    int tabSpaces = 0;//Tab spaces begin at 0.
    // Check to see if the user provides at least 2 command-line-arguments.

    if (argc == 1) { 
        char *root = "../";
        getOpt(argc, argv, root, tabSpaces, traverseDirectory);
    //     //exit(-1);
    }

    if (argc == 2) { 
        getOpt(argc, argv, argv[1], tabSpaces, traverseDirectory);
        //exit(-1);
    }
    // if (argc < 2) { 
    //     printf ("Usage: %s <dirname>\n", argv[0]); 
    //     exit(-1);
    // }
    // if(argc == 2){
    // traverseDirectory(argv[1], tabSpaces);
    // }
    if(argc > 2){
        char *search = "-s";
        int i = 0;
        for (i = 1; i < argc; i++){
            if(strstr(argv[i], search) != NULL){
                 enteredFileSize = atoi(argv[i + 1]);
            }
        }
        getOpt(argc, argv, argv[1], tabSpaces, traverseDirectory);
    }

    return 0;
}
//Compile line gcc HW2.c -o test
//Standard input ./test ../
//Sample input ./test /workspaces/OC-CS-332-Lab-Homework/HW2
