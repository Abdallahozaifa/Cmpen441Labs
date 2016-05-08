/*Academic Integrity Statement: I certify that, while others may have assisted me in brain storming, debugging and validating this program, the program itself is my own work. I understand that submitting code which is the work of other individuals is a violation of the course Academic Integrity Policy and may result in a zero credit for the assignment, or course failure and a report to the Academic Dishonesty Board. I also understand that if I knowingly give my original work to another individual that it could also result in a zero credit for the assignment, or course failure and a report to the Academic Dishonesty Board.

See Academic Integrity Procedural Guidelines at:  https://psbehrend.psu.edu/intranet/faculty-resources/academic-integrity/academic-integrity-procedural-guidelines

 Assisted by and Assisted line numbers:

 Your name: Hozaifa Abdalla
 */
 
#include <stdio.h>
#include <stdlib.h>
#include <alloca.h>
#include <unistd.h>

extern char etext, edata, end;
int a = 0xaaaa, b;
void printBreakPoints(int argc);

int main(int argc, char * argv[]) {   
    printBreakPoints(argc);
    return 0;
}

/*
 * Prints all the break points
 */
void printBreakPoints(int argc){
    int i, c = 0xcccc;
    int *d_ptr = (int*) malloc(sizeof(int)); // allocates space for the pointer
    int *e_ptr = (int*) alloca(sizeof(int)); // allocates space for the pointer and frees the spaces immediately after returning to caller
    b = 0xbbbb;
    *d_ptr = 0xdddd;
    *e_ptr = 0xeeee;
    
    printf("%p:etext\n\n", &etext);
    printf("%p:a=%0x\n", &a, a);
    printf("%p:edata\n\n", &edata);
    printf("%p:b=%0x\n", &b, b);
    printf("%p:end\n\n", &end);
    printf("%p:d=%0x\n", d_ptr, *d_ptr);
    printf("%p:brk\n\n", sbrk(0));
    for(i = 1; i <= 8192; i++) {
        d_ptr = (int*) malloc(sizeof(int));
        *d_ptr = 0xdddd;
    }
    
    printf("%p:d=%0x\n", d_ptr, *d_ptr);
    printf("%p:brk\n\n", sbrk(0));
    printf("%p:e=%0x\n", e_ptr, *e_ptr);
    printf("%p:argc=%0x\n", &argc, argc);
    printf("%p:c=%0x\n", &c, c);
    
    /*
     * Prints all the breakpoints of all the regions
     */
    printf("|------------------------------|<--- %p:main\n", &main); // starting point
    printf("|        Kernel Space          |\n");
    printf("|------------------------------|<--- %p:argc\n",&argc); // break point between stack and the kernel virtual memory
    printf("|        argv, environ         |\n"); 
    printf("|------------------------------|<--- %p:stack\n", &i); // break point betwee the stack and argv
    printf("|            Stack             |\n");
    printf("|------------------------------|\n"); 
    printf("|        unallocated memory    |\n");
    printf("|------------------------------|<--- %p:brk\n", sbrk(0)); 
    printf("|            Heap              |\n");
    printf("|------------------------------|<--- %p:end\n", &end); // edata break point between initialized data and uninitialized data
    printf("|        UnInitialized Data    |\n");
    printf("|------------------------------|<--- %p:edata\n", &edata); // edata break point between initialized data and uninitialized data
    printf("|        Initialized Data      |\n");
    printf("|------------------------------|<--- %p:etext\n", &etext); // edata break point between initialized data and uninitialized data
    printf("|            Text              |\n");
    printf("|------------------------------|\n");
    printf("|------------------------------|\n");
    printf("|                              |\n");
    printf("|------------------------------|\n");     
}

/* Output Below 
hozaifa@hozaifa-UX31A:~/Desktop/Cmpen441/lab9/part2$ gcc -o proj9 proj9.c
hozaifa@hozaifa-UX31A:~/Desktop/Cmpen441/lab9/part2$ ./proj9
0x4009ad:etext

0x602058:a=aaaa
0x60205c:edata

0x602060:b=bbbb
0x602068:end

0x1799010:d=dddd
0x17ba000:brk

0x17d9010:d=dddd
0x17db000:brk

0x7fffce3d9120:e=eeee
0x7fffce3d914c:argc=1
0x7fffce3d915c:c=cccc
|------------------------------|<--- 0x40060d:main
|        Kernel Space          |
|------------------------------|<--- 0x7fffce3d914c:argc
|        argv, environ         |
|------------------------------|<--- 0x7fffce3d9158:stack
|            Stack             |
|------------------------------|
|        unallocated memory    |
|------------------------------|<--- 0x17db000:brk
|            Heap              |
|------------------------------|<--- 0x602068:end
|        UnInitialized Data    |
|------------------------------|<--- 0x60205c:edata
|        Initialized Data      |
|------------------------------|<--- 0x4009ad:etext
|            Text              |
|------------------------------|
|------------------------------|
|                              |
|------------------------------|
*/