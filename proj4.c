/** CMPSC 474 /CMPEN 441
 * Lab 4
 * File Name: proj4.c
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

/* function declaration of the function that prints the users information*/
void umtpPrintUserInfo(struct utmp *log);

int main(){
    int logsize = 10,file,i; // variable declaration for the logsize to read the file, file, and loop counter           
    struct utmp log[logsize]; // declares the struct for utmp
    
    // opens the file to be read only
    file = open("/var/run/utmp", O_RDONLY);  
    
    // checks to see if the file opens correctly and if not exits the program
    if( file < 0 ) {  
        printf("Failed to open");
        return(0);
    }

    // if the file opened correctly
    if (file >=0) {
        
            // read the file into the log struct       
            read(file, &log, logsize * sizeof (struct utmp));
                        
            // iterates and prints each user                
            for(i = 0; i < logsize; i++) {
                
                /* obtains the users that are logged, however user process only finds the ones that are connected locally
                so it checks to see if the last username matches another entry and connected through a different host*/
                if(log[i].ut_type == USER_PROCESS || strstr(log[i].ut_user,log[logsize-1].ut_user) !=NULL){
                    umtpPrintUserInfo(&log[i]);
                }
                
            }              
            close(file); // closes the file

    } else {
            return(0);
    }
    return (0);
}

// prints the users information
void umtpPrintUserInfo(struct utmp *log){
    time_t currentTime = time(NULL); // gets the current time
    time_t sec =(time_t)log->ut_tv.tv_sec; // gets the time of the login 
    struct tm *currentDate = localtime(&currentTime); // gets the current date
    static char date[] = "YYYY-MM-DD\n"; // formatter for the date 
    int year=1900 + currentDate->tm_year,month = currentDate->tm_mon+1,day = currentDate->tm_mday; // contains the variables for the dates                
    char timeBuffer[20], *userName = log->ut_user, *hostName = log->ut_line; // contains the user name
    strftime(timeBuffer, 20, "%H:%M", localtime(&sec)); // formats the hours and minutes 
    sprintf(date, "%s  %s        %d-0%d-%d %s\n",userName, hostName, year,month,day,timeBuffer); //formats the string into the date array
    printf("%s", date); // prints the date
}

/**  Your sample output is posted below:

hozaifa@hozaifa-UX31A:~/Desktop/Cmpen441/lab4/part2$ ./lab4
hozaifa  tty1        2016-02-12 11:48
hozaifa  :0        2016-02-12 11:48
hozaifa  pts/0        2016-02-12 18:06
*/
