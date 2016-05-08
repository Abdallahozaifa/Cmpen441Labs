/** CMPSC 474 /CMPEN 441
 * Lab 5
 * File Name: proj5.c
 *
 *Your Name: Hozaifa Abdalla
 *
 *Your PSU user ID:  hea113
 *
 *CMPSC474 Spring 2016 
 *
 *Due Time: 12:00, Thursday, January, 2016
 *
 *Time of Last Modification: 12:00 a.m., Thursday, February 12, 2016
 *Academic Integrity Statement: I certify that, while others may have assisted me in brain storming, debugging and validating this program, the program itself is my own work. I understand that submitting code which is the work of other individuals is a violation of the course Academic Integrity Policy and may result in a zero credit for the assignment, or course failure and a report to the Academic Dishonesty Board. I also understand that if I knowingly give my original work to another individual that it could also result in a zero credit for the assignment, or course failure and a report to the Academic Dishonesty Board. See Academic Integrity Procedural Guidelines at:  
https://psbehrend.psu.edu/intranet/faculty-resources/academic-integrity/academic-integrity-procedural-guidelines
 
 *Assisted by and Assisted line numbers:
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <stdbool.h>
#include <utmp.h>
#include <fcntl.h>
#include <time.h>
#include <sys/stat.h>
#include <sys/types.h>

void getOwnerPerm(char *argv[], struct stat fileInfo, char *fileName);
void getGroupPerm(struct stat fileInfo);
void getAllPerm(struct stat fileInfo);

int main(int argc, char *argv[]){
    struct stat fileInfo;
    char *fileName = argv[1];
    if(argc != 2){
        printf("Only 1 parameter required!\n");
        return;
    }else{
        getOwnerPerm(argv, fileInfo, fileName);
        getGroupPerm(fileInfo);
        getAllPerm(fileInfo);
        printf("\n");
    }
}
void getOwnerPerm(char *argv[], struct stat fileInfo, char *fileName){
    
    /* If file does not exist  or error retrieving file type info */
    if (lstat(fileName, &fileInfo) == -1) {
        perror("stat");
        exit(EXIT_FAILURE);
    }
    
    /* determines the file type of the file name listed above unless it doesn't exist */
    switch (fileInfo.st_mode & S_IFMT) {
        /* block device file */
        case S_IFBLK:  
            printf("b");            
            break;
        /* character device file */
        case S_IFCHR:  
            printf("c");        
            break;
        /* directory file */
        case S_IFDIR:  
            printf("d");               
            break;
        /* first-in first-out special file */
        case S_IFIFO:  
            printf("p");               
            break;
        /* symbolic link file */
        case S_IFLNK:  
            printf("l");                 
            break;
        /* regular file */
        case S_IFREG:  
            printf("-");            
            break;
        /* socket file */
        case S_IFSOCK: 
            printf("s");                  
            break;
        default:       
            printf("unknown File Type!\n");                
            break;
    }
    
    printf((fileInfo.st_mode & S_IRUSR) ? "r" : "-"); // column 2
    printf((fileInfo.st_mode & S_IWUSR) ? "w" : "-"); // column 3
    // column 4
    if(fileInfo.st_mode & S_ISUID){
        printf("s");
    }else if(fileInfo.st_mode & S_IXUSR){
        printf("x");
    }else{
        printf("-");
    }
}

void getGroupPerm(struct stat fileInfo){
    printf((fileInfo.st_mode & S_IRGRP) ? "r" : "-"); // column 5
    printf((fileInfo.st_mode & S_IWGRP) ? "w" : "-"); // column 6
    // column 7
    if(fileInfo.st_mode & S_ISGID){
        printf("s");    
    }else if(fileInfo.st_mode & S_IXGRP){
        printf("x");
    }else{
        printf("-");
    }
}

void getAllPerm(struct stat fileInfo){
    printf((fileInfo.st_mode & S_IROTH)==0 ? "r" : "-"); // column 8
    printf((fileInfo.st_mode & S_IWOTH)==0 ? "w" : "-"); // column 9
    //printf((fileInfo.st_mode & S_IXOTH) ? "x" : "-"); // column 10
    
    if((fileInfo.st_mode & S_ISVTX)==0){
        printf("t");
    }else if((fileInfo.st_mode & S_IXOTH)==0){
        printf("x");
    }else{
        printf("-");
    }
    
     
}

/* Output Below!

-rw-rw-r--


*/
