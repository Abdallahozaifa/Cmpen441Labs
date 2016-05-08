/*Academic Integrity Statement: I certify that, while others may have assisted me in brain storming, debugging and validating this program, the program itself is my own work. I understand that submitting code which is the work of other individuals is a violation of the course Academic Integrity Policy and may result in a zero credit for the assignment, or course failure and a report to the Academic Dishonesty Board. I also understand that if I knowingly give my original work to another individual that it could also result in a zero credit for the assignment, or course failure and a report to the Academic Dishonesty Board.

See Academic Integrity Procedural Guidelines at:  https://psbehrend.psu.edu/intranet/faculty-resources/academic-integrity/academic-integrity-procedural-guidelines

 Assisted by and Assisted line numbers:

 Your name: Hozaifa Abdalla
 */
 
#include <stdio.h>
#include <stdlib.h>
#include <alloca.h>
#include <unistd.h>
#include <limits.h>
#include <string.h>
#include <sys/cdefs.h>

void fifo();
int main(int argc, char * argv[]) {
    int MAX_FRAMESIZE = 20, ; 
    /* Exits program if not enough parameters are supplied */  
    if(argc < 3 || argc > 4){
        printf("Not enough parameters supplied!\n");
        exit(0);
    }else{
        if(strtonum(argv[3],0,1000) > 20){
            printf("Max Frame size exceeded!\n");
            exit(0);
        }
    }
    
    
    return 0;
}