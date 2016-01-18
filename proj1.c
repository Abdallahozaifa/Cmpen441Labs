/** CMPSC 474 /CMPEN 441
 * Lab 1
 * File Name: proj1.c
 *
 *Your Name: Hozaifa Abdalla
 *
 *Your PSU user ID:  hea113
 *
 *CMPSC474 Spring 2016 
 *
 *Due Time: Time, Thursday, January, 2016
 *
 *Time of Last Modification: Time, Sunday, January 17, 2016

 *Academic Integrity Statement: I certify that, while others may have assisted me in brain storming, debugging and validating this program, the program itself is my own work. I understand that submitting code which is the work of other individuals is a violation of the course Academic Integrity Policy and may result in a zero credit for the assignment, or course failure and a report to the Academic Dishonesty Board. I also understand that if I knowingly give my original work to another individual that it could also result in a zero credit for the assignment, or course failure and a report to the Academic Dishonesty Board. See Academic Integrity Procedural Guidelines at:  
https://psbehrend.psu.edu/intranet/faculty-resources/academic-integrity/academic-integrity-procedural-guidelines
 
 *Assisted by and Assisted line numbers:
 */


#include <stdio.h>
#include <assert.h>

struct numlist {
	float *list;   /* points to list of numbers in an array */
	int   len;     /* number of items in list   */
	float min,     /* the minimal value in list */
	max,     /* the maximal value in list */
	avg;     /* the mean of the numbers   */
};

// calculates the minimum, average, and maxium of the numbers in the list
void compute_stats(struct numlist *lp)
{
    int i;
    double min = lp->list[0], max = lp->list[lp->len-1], total = 0;
    
    // checks each element in the array to compute the min, max, and avg
	for(i=0;i<lp->len;i++){
        // checks for min val 
        if(lp->list[i] < min){
            min = lp->list[i];
        }
        // checks for max val
        if(lp->list[i] > max){
            max = lp->list[i];
        }
        // computes total
        total += lp->list[i];
    }
    // sets the values for what lp points to
    lp-> min = min;
    lp-> max = max;
    lp-> avg = total/lp->len;
}

/**
 * Outputs all of the data from the numlist
 */
void print_nums(struct numlist *lp)
{   
    printf("The elements in the list are\n");
    int i;
    // outputs each element in the array
    for(i=0;i<lp->len;i++){
        printf("%f ", lp->list[i]);
    }
    printf("\n");
    printf("length of list: %d\n", lp->len); //outputs length of list
    printf("Minimum: %f\n", lp->min); // outputs min val
    printf("Maximum: %f\n", lp->max); // outputs max val
    printf("Average: %f\n", lp->avg); // outputs avg val
}

int main(int argc, char **argv)
{

	/* Build a simple numlist to test */
	float data[10] = { 0.1, 1.1, 2.1, 3.1, 4.1, 5.1, 6.1, 7.1, 8.1, 9.1 };
	struct numlist l;
    // assigns the l's list to the data array and len to 10
	l.list = data;
	l.len = 10;
    // computes the min, max, and avg
	compute_stats(&l);
    // prints all the data from the struct
	print_nums(&l);
	return 0;
}

/**  Your sample output is posted below:

    The elements in the list are
    0.100000 1.100000 2.100000 3.100000 4.100000 5.100000 6.100000 7.100000 8.100000 9.100000 
    length of list: 10
    Minimum: 0.100000
    Maximum: 9.100000
    Average: 4.600000
*/
