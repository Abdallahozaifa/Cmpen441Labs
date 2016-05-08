/** CMPSC 474 /CMPEN 441
 * Lab 8
 * File Name: proj8.c
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
 
#include <unistd.h>
#include <stdlib.h>
#include <curses.h>
#include <string.h>
#include <ncurses.h>

#define NAME_LEN 256 // Maximum User Length
#define PW_LEN 256 // Maximum Password Length

void createBar(int y, int x, char direction[], int endPos, WINDOW *window);
void createChatScreen();
void displayUserName(WINDOW *window, char name[], int yPos);
void outlineTopWindow(WINDOW *window);
void outlineBottomWindow(WINDOW *window);
void renderInput(WINDOW *bottomWindow, WINDOW *topWindow, char name[]);
int main() {
    char name[NAME_LEN];
    char password[PW_LEN];
    char *real_password = "xyz";
    int i = 0;

    initscr(); // Initializes the Curses Screen

    // // /* Displays the Header */
    move(5, 10);
    printw("%s", "Please login:");
    
    move(7, 10);
    printw("%s", "User name: ");
    getstr(name);

    move(9, 10);  
    printw("%s", "Password: ");
    refresh();

    /*  When the user enters their password, we need to stop the password from being echoed to the screen.
        Then we check the password against xyz.  */

    cbreak(); // Allows the input to be read immediately
    noecho(); // Does not echo the characters that are typed

    memset(password, '\0', sizeof(password));  
    while (i < PW_LEN) {
        password[i] = getch();
        move(9, 20 + i); 
        addch('*');
        refresh();
        if (password[i] == '\n') break;
        if (strcmp(password, real_password) == 0) break;
        i++;
    }

    /*  Finally, we re-enable the keyboard echo and print out success or failure.  */

    echo();
    nocbreak();

    move(11, 10);
    if (strcmp(password, real_password) == 0){ 
        printw("%s", "Correct");
    }else {
        printw("%s", "Wrong");
    }
    
    refresh();
    sleep(2);
    
    clear();
    refresh();
    
    WINDOW *topWindow;
    WINDOW *bottomWindow;
    int x_loop=0;
    int y_loop=0;
    
    topWindow = newwin(12,80,0,0);
    bottomWindow = newwin(12,80,12,0);
    outlineTopWindow(topWindow);
    outlineBottomWindow(bottomWindow);
    renderInput(bottomWindow, topWindow, name);
  
    endwin();
    exit(EXIT_SUCCESS);
}

 
/*-----------------------------------------*\
 | Creates a bar in the specified direction |
 | @param y                                 |
 | @param x                                 |
 | @param direction                         |
 | @param endpos                            |
\*-----------------------------------------*/
void createBar(int y, int x, char direction[], int endPos, WINDOW *window){
    int startPos;
    
    if(strcmp(direction, "x") == 0){
        startPos = x;
        // printw("%s", "x direction triggered!");
    }else if(strcmp(direction, "y") == 0){
        startPos = y;
        // printw("%s", "y direction triggered!");
    }
    
    /* moves from the start position till the end position */
    while(startPos <= endPos){
        
        /* Detects the different directions */
        if(strcmp(direction, "x") == 0){
            
            // printw("%s", "X incremented!");
            x++;
            mvwprintw(window,y,x, "%c", '-');
            
        }else if(strcmp(direction, "y") == 0){
            
            // printw("%s", "y incremented!")
            mvwprintw(window,y,x,"%c", '|');
            y++;
        }      
        startPos++;
    }   
    wrefresh(window);
}


/*--------------------------------*\
 | Creates the top window outline  |
\*--------------------------------*/
void outlineTopWindow(WINDOW *window){
    createBar(0,0,"x",79,window); // top bar
    createBar(0,0,"y",11, window); // left side bar
    createBar(11,0,"x",79, window); // middle seperator
    createBar(0,79,"y",11, window); // right side bar
}

/*-----------------------------------*\
 | Creates the bottom screen outline |
\*-----------------------------------*/
void outlineBottomWindow(WINDOW *window){   
    createBar(0,0,"y",11, window); // left bottom side bar
    createBar(11,0,"x",79, window); // bottom bar
    createBar(0,79,"y",11, window); // bottom right side bar
}

/*-----------------------------------*\
 | Displays the username              |
\*-----------------------------------*/
void displayUserName(WINDOW *window, char name[], int yPos){
    int startPos = 1, nameCount=0,nameLen=strlen(name);
    while(startPos <= nameLen){
        mvwprintw(window,yPos,startPos, "%c", name[startPos-1]);
        startPos++;
    }
    mvwprintw(window,yPos,startPos, "%c", ':');
    wrefresh(window);
};

/*-----------------------------------*\
 | Reads the input of the user        |
\*-----------------------------------*/
void renderInput(WINDOW *bottomWindow, WINDOW *topWindow, char name[]){
    char usrInput[255], userInputCount=0;
    int bottomY=0, bottomX=0, topY=1,topX, unusedY; 
    bzero(usrInput,255);
    
    while(1){
        mvwprintw(bottomWindow,bottomY,bottomX, "%s", "|");
        bottomY++;
         
        echo();
        scrollok(bottomWindow,TRUE);
        scrollok(topWindow,TRUE);
        idlok(bottomWindow,TRUE);
        idlok(topWindow,TRUE);
        userInputCount=0;
        bzero(usrInput,255);
        
        while(1){
            if(strcmp(usrInput,"quit") == 0){
                return;
            }
            usrInput[userInputCount] = wgetch(bottomWindow);
            if(usrInput[userInputCount] == '\n'){
                break;
            }        
            userInputCount++;      
        }
             
        displayUserName(topWindow, name, topY);
        getyx(topWindow, unusedY, topX);
        if(bottomY > 11){
            wscrl(bottomWindow,1);
            bottomY = 9;
        }
        
        if(unusedY == 11){
            wscrl(topWindow,1);
            topY = 9;
            
        } 
        mvwprintw(topWindow,topY,topX+1, "%s", usrInput);
        mvwprintw(topWindow,topY,79, "%c", '|');
        // wborder(topWindow, '|', '|', '-', '-' , 0, 0, 0, 0);
        if(unusedY == 12){
            clearok(topWindow, TRUE);
        }
        
        // wborder(bottomWindow, '|', '|', '-', '-' , 0, 0, 0, 0);
        wrefresh(bottomWindow);
        wrefresh(topWindow);
        topY++;
    }
}

