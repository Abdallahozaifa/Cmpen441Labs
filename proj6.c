/** CMPSC 474 /CMPEN 441
 * Lab 6
 * File Name: proj6.c
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
/* CMPSC/CMPEN441 Sp16 (M. Su)  Lab5.2 reference solution proj5.c */

#include <unistd.h>
#include <sys/stat.h>
#include <stdio.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>
#include <dirent.h>
#include <stdlib.h> 

void printLsInfo(char file[]);
int main(int argc, char *argv[])
{
    DIR *directory; // pointer to a directory
    struct dirent *dir; // pointer to the dirent struct
    
    if(argc == 1){
        directory = opendir(".");
    }else if(argc == 2){
        char *ptr;
        char actualpath [PATH_MAX+1];
        //ptr = realpath(argv[1], actualpath);
        //printf(" %s", ptr);
        directory = opendir(ptr); // opens the  directory that the user wants
    }else if(argc > 2){
        printf("Invalid number of arguments!\n");
        return 0;
    }

    /* If there is a current directory */
    if (directory)
    {
        /* Reads everyfile in the current directory */
        while ((dir = readdir(directory)) != NULL)
        {
            /* Compares the file name for the current directory */
            if((strcmp(dir->d_name, ".") != 0) &&(strcmp(dir->d_name, "..") != 0)){
                printLsInfo(dir->d_name);
            }
        }
        /* Closes the Current Directory */
        closedir(directory);
    }
    
	return(0);
}

/* Function that prints all the files information */
void printLsInfo(char file[]){
    struct stat data; // structure for stat
    struct group *grp; // pointer to structure for grp
    struct passwd *pwd; // pointer to structure for pwd
    struct tm *tm; // pointer to structure for tm
    char buf[256]; // buffer that holds the string for time
    
    /* gets the files information */
	if(lstat(file, &data) == -1 ) // get stat data
	{
		printf("Could not read \'%s\'.\n", file);
		return;
	}
	
    /* Determines the file type */
	switch( data.st_mode & S_IFMT )	
	{
		case S_IFDIR: putchar( 'd' ); break;
		case S_IFREG: putchar( '-' ); break;
		case S_IFCHR: putchar( 'c' ); break;
		case S_IFBLK: putchar( 'b' ); break;
		case S_IFLNK: putchar( 'l' ); break;
		case S_IFIFO: putchar( 'p' ); break;
		case S_IFSOCK: putchar('s' ); break;
		default: putchar('?');
	}

	/* user permissions */
	if( data.st_mode & S_IRUSR ) putchar( 'r' ); else putchar('-');
	if( data.st_mode & S_IWUSR ) putchar( 'w' ); else putchar('-');
	if( data.st_mode & S_ISUID ) putchar( 's' );
	else if( data.st_mode & S_IXUSR ) putchar( 'x' ); else putchar('-');

	/* // group permissions */
	if( data.st_mode & S_IRGRP ) putchar( 'r' ); else putchar('-');
	if( data.st_mode & S_IWGRP ) putchar( 'w' ); else putchar('-');
	if( data.st_mode & S_ISGID ) putchar( 's' );
	else if( data.st_mode & S_IXGRP ) putchar( 'x' ); else putchar('-');

	/* // other permissions */
	if( data.st_mode & S_IROTH ) putchar( 'r' ); else putchar('-');
	if( data.st_mode & S_IWOTH ) putchar( 'w' ); else putchar('-');
	if( data.st_mode & S_ISVTX ) putchar( 't' );
	else if( data.st_mode & S_IXOTH ) putchar( 'x' ); else putchar('-');
    
    /* This field specifies the number of links or directories inside this directory. */
    printf(" %ld", (long) data.st_nlink);

    grp = getgrgid(data.st_gid);
    pwd = getpwuid(data.st_uid);
    
    /* The user that owns the file, or directory */
    printf(" %s", pwd->pw_name);
    
    /* The group that file belongs to, and any user in that group will have the permissions given in the third field over that file. */
    printf(" %s", grp->gr_name);
    
    /* The size in bytes */ 
    printf(" %ld", (long) data.st_size);
    
    tm = localtime(&(data.st_ctime));
    
    /* The date of last modification */
    strftime(buf,256,"%m %d %H:%M", tm);
    printf(" %s",buf);
    
    /* The file name */
    printf(" %s", file);
	putchar('\n');   
}
/* OUTPUT BELOW!

hozaifa@hozaifa-UX31A:~/Desktop/Cmpen441/lab6/part2$ ./lab6
-rwxrwxr-x 1 hozaifa hozaifa 13343 02 25 19:22 lab6
-rw-rw-r-- 1 hozaifa hozaifa 4501 02 25 19:22 proj6.c

*/