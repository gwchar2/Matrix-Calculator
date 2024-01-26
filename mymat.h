/* HEADER FILE INCLUDES THE FOLLOWING: 
declarations of functions, data structures, constants, 
and other constructs that can be shared across multiple source files. 
The purpose of header files is to declare the interface of a module, 
allowing other modules to use its functionality without having access to the implementation details.
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stddef.h>
#include <unistd.h>


#include "promptsAndPrints.c"
#include "errorHandler.c"
#include "mymat.c"
#include "mainmat.c"

#define COMMANDS_COUNT 9

/* A matrix structure with a name and default size of 4x4. */
typedef struct{
    const char name[6];
    float matrix[MAT_SIZE][MAT_SIZE];
} mat; 

/**********************************************
**********      Prompts and Prints      *******
**********************************************/
void print_mat(mat *matrix) /* Print matrix values for the specified matrix */

void desired_command() /* This function prompts the user for input */

void welcome() /* This function send the user a very nice welcome message on his first time to the app */

void err_mat_name(); /* Print error message for undefined matrix name */

void err_com_name(); /* Print error message for undefined command name */

void err_num(); /* Print error message for argument not being a real number */

void err_text(); /* Print error message for extraneous text after the end of the command */

void err_miss_argument(); /* Print error message for missing argument */

void err_miss_comma(); /* Print error message for missing comma */

void err_illegal_comma(); /* Print error message for illegal comma */

void err_consec_comma(); /* Print error message for multiple consecutive commas */

void err_not_scalar(); /* Print error message for argument not being a scalar */

void err_no_stop(); /* Print error message when no stop() command is found at the end of the file */

void msg_stop() /* Print message when stop() is received */

void msg_read_mat(mat *matrix); /* Print message when read_mat() is received */

void msg_add_mat(mat *matrixA, mat *matrixB, mat *matrixC); /* Print message when add_mat() is received */

void msg_sub_mat(mat *matrixA, mat *matrixB, mat *matrixC); /* Print message when sub_mat() is received */

void msg_mul_mat(mat *matrixA, mat *matrixB, mat *matrixC); /* Print message when mul_mat() is received */

void msg_mul_scalar(mat *matrixA, mat *matrixB, float num); /* Print message when mul_scalar() is received */

void msg_trans_mat(mat *matrixA, mat *matrixB); /* Print message when trans_mat() is received */


/**********************************************
**********      mymat.c commands       *******
**********************************************/
void read_mat(mat *MAT_A); /* Assign matrix values for MAT_A */

void add_mat(mat *MAT_A, mat *MAT_B, mat *MAT_C); /* Add MAT_A and MAT_B, store the result in MAT_C */

void sub_mat(mat *MAT_A, mat *MAT_B, mat *MAT_C); /* Subtract MAT_B from MAT_A, store the result in MAT_C */

void mul_mat(mat *MAT_A, mat *MAT_B, mat *MAT_C); /* Multiply MAT_A and MAT_B, store the result in MAT_C */

void mul_scalar(mat *MAT_A, float num, mat *MAT_B); /* Multiply MAT_A by a scalar (num), store the result in MAT_B */

void trans_mat(mat *MAT_A, mat *MAT_B); /* Transpose MAT_A, store the result in MAT_B */



/**********************************************
*******      errorHandler commands       ******
**********************************************/

void stop(); /* Stops the program execution */

int check_mat_name(char *variables) /* This method checks if a user-inputted matrix name is correct. */

int check_cmd_name(char *cmd) /* This method checks if a user-inputted command name is correct - but with a comma after it */

int check_R(char *mat_b)  /* This function checks to see if the input in mat_b is a double (R) */

double turn_to_R(char *mat_b) /* This function turns the input in mat_b to a double (R) */

enum Commands process_command(char *input) /* This command processes the user input for desired command. */

void my_free(char **operation,char **mat_a_name,char **mat_b_name,char **mat_c_name); /* Frees the allocated memory if it was previously allocated */