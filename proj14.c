/*
Note: Please copy the following paragraph of reminding the academic integerity policy in your source file header part, then fill your name and assisted by if you have :

Academic Integrity Statement: I certify that, while others may have assisted me in brain storming, debugging and validating this program, the program itself is my own work. I understand that submitting code which is the work of other individuals is a violation of the course Academic Integrity Policy and may result in a zero credit for the assignment, or course failure and a report to the Academic Dishonesty Board. I also understand that if I knowingly give my original work to another individual that it could also result in a zero credit for the assignment, or course failure and a report to the Academic Dishonesty Board.

See Academic Integrity Procedural Guidelines at:  https://psbehrend.psu.edu/intranet/faculty-resources/academic-integrity/academic-integrity-procedural-guidelines

 Assisted by and Assisted line numbers:

 Your name: Hozaifa Abdalla
 */
 
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <stdbool.h>
#include <pthread.h>
#include <semaphore.h>

/* Thread function that executes once the thread is created */
void * Count(void * a){
    printf("Thread started!");
}

sem_t semaphore;

int main(){
    pthread_t thread1, thread2;
    char fileName;
    //sem_init(&mutex, 1, 1);
    
    printf("Please enter the name of your data file:");
    scanf("%s", &fileName);
    printf("FileName inputed: %s\n", &fileName);
    // if(pthread_create(&thread1, NULL, Count, NULL))
    // {
    //     printf("\n ERROR creating thread 1");
    //     exit(1);
    // }

    // if(pthread_create(&thread2, NULL, Count, NULL))
    // {
    //     printf("\n ERROR creating thread 2");
    //     exit(1);
    // }
    
}