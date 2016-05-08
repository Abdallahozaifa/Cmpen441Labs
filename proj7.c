/** CMPSC 474 /CMPEN 441
 * Lab 7
 * File Name: proj7.c
 *
 *Your Name: Hozaifa Abdalla
 *
 *Your PSU user ID:  hea113
 *
 *CMPSC474 Spring 2016 
 *
 *Due Time: 12:00, Thursday, March, 2016
 *
 *Time of Last Modification: 12:00 a.m., Thursday, March 3, 2016
 *Academic Integrity Statement: I certify that, while others may have assisted me in brain storming, debugging and validating this program, the program itself is my own work. I understand that submitting code which is the work of other individuals is a violation of the course Academic Integrity Policy and may result in a zero credit for the assignment, or course failure and a report to the Academic Dishonesty Board. I also understand that if I knowingly give my original work to another individual that it could also result in a zero credit for the assignment, or course failure and a report to the Academic Dishonesty Board. See Academic Integrity Procedural Guidelines at:  
https://psbehrend.psu.edu/intranet/faculty-resources/academic-integrity/academic-integrity-procedural-guidelines
 
 *Assisted by and Assisted line numbers:
 */
#include <stdio.h>
#include <ctype.h>
#include <termios.h>
#include <signal.h>
#include <unistd.h>
#include <fcntl.h> 

int main() {
  int c;
  struct termios original_mode;
  struct termios ttystate;
  
  
  // record initial terminal settings for later use
  tcgetattr(0, &original_mode);

    // change settings
  tcgetattr( 0, &ttystate);         /* read curr. setting   */
  
  ttystate.c_lflag  &= ~ICANON;     /* no buffering         */
  ttystate.c_lflag &= ~ECHO;        /* Disables echoing the input characters */
  ttystate.c_cc[VQUIT] =  'Q';     /* quits the program */
  ttystate.c_cc[VMIN] = 0;      /* No minimum number of characters */
  ttystate.c_cc[VTIME] = 10;    /* waits until 1 second */
  tcsetattr( 0 , TCSANOW, &ttystate);     /* install settings     */

  /* Obtains users input one character at a time */
  while (1) {
    c=getchar();
    
    /* Detects the ctrl-d character with its ascii value */
    if(c == 4){
        putchar('.');
        
    }else{
        
        /* Detects if the character entered is Q */
        if(c== 'Q'){
            break;
        }
        
        /* Detects if the character entered is Z */
        else if(c=='z'){
            c = 'a';
        }
        
        /* Detects if lowercase */
        else if (islower(c)){
            c++;
        }
        putchar(c);
    }
  }

  /* VERY IMPORTANT or terminal settings change!
   * restore initial terminal settings 
   */
  tcsetattr(0, TCSANOW, &original_mode); 
  return 0;
} 