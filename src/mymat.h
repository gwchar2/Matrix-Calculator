/* HEADER FILE INCLUDES THE FOLLOWING: 
declarations of functions, data structures, constants, 
and other constructs that can be shared across multiple source files. 
The purpose of header files is to declare the interface of a module, 
allowing other modules to use its functionality without having access to the implementation details.
*/
#ifndef MYMAT_H
#define MYMAT_H
#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
/**********************************************
****************      Macros      *************
**********************************************/
#define MAT_SIZE 4
#define MAT_NAME_SIZE 6
#define COMMANDS_COUNT 9
#define WHITESPACE(c) ((c == ' ' || c == '\t' || c == '\n' || c == '\r' || c == '\f' || c == '\v'))     /* Checks if a character is a whitespace */
#define DELIMETER_1 (" ,\t\n\r\f\v") /* A delimeter for strtok function with a comma */
#define DELIMITER_2 (" \t\n\r\f\v") /* A delimeter for strtok function without a comma */
#define MY_FREE()  free_data(myCommand->user_input, inputCopy)
#define CHECK_AND_FREE(c) \
        if (c == 1) { \
            MY_FREE(); /* resets the data if needed to */ \
            return 1; \
        } \
        if (c == 2){ \
            return 0; \
        } \
/**********************************************
**************     Structures      ***********
**********************************************/
/* A matrix structure with a name and default size of 4x4. */
typedef struct{
    const char name[MAT_NAME_SIZE];
    double matrix[MAT_SIZE][MAT_SIZE];
} mat; 

/* An enum of command values */
enum Commands{
    READ_MAT,
    PRINT_MAT,
    ADD_MAT,
    SUB_MAT,
    MUL_MAT,
    MUL_SCALAR,
    TRANS_MAT,
    STOP,
    INVALID
};


/* A command structure with a respective name & variables. */
typedef struct{
    char *user_input;
    enum Commands user_cmd;
    mat *user_mat_a;
    mat *user_mat_b;
    mat *user_mat_c;
    double user_scalar;
    double read_scalars[16];
} cmd;

/**********************************************
**********      Prompts and Prints      *******
**********************************************/
void print_mat(mat *matrix); /* Print matrix values for the specified matrix */

void prompt_message(); /* This function prompts the user for input */

void welcome(); /* This function send the user a very nice welcome message on his first time to the app */

void err_miss_argument(); /* Print error message for missing argument */

void err_mat_name(); /* Print error message for undefined matrix name */

void err_com_name(); /* Print error message for undefined command name */

void err_num(); /* Print error message for argument not being a real number */

void err_text(); /* Print error message for extraneous text after the end of the command */

void err_miss_comma(); /* Print error message for missing comma */

void err_illegal_comma(); /* Print error message for illegal comma */

void err_consec_comma(); /* Print error message for multiple consecutive commas */

void err_not_scalar(); /* Print error message for argument not being a scalar */

void err_no_stop(); /* Print error message when no stop() command is found at the end of the file */

void msg_stop(); /* Print message when stop() is received */

void msg_read_mat(mat *matrix); /* Print message when read_mat() is received */

void msg_add_mat(mat *matrixA, mat *matrixB, mat *matrixC); /* Print message when add_mat() is received */

void msg_sub_mat(mat *matrixA, mat *matrixB, mat *matrixC); /* Print message when sub_mat() is received */

void msg_mul_mat(mat *matrixA, mat *matrixB, mat *matrixC); /* Print message when mul_mat() is received */

void msg_mul_scalar(mat *matrixA, mat *matrixB, double num); /* Print message when mul_scalar() is received */

void msg_trans_mat(mat *matrixA, mat *matrixB); /* Print message when trans_mat() is received */


/**********************************************
**********      mymat.c commands       *******
**********************************************/

void add_mat(mat *MAT_A, mat *MAT_B, mat *MAT_C); /* Add MAT_A and MAT_B, store the result in MAT_C */

void sub_mat(mat *MAT_A, mat *MAT_B, mat *MAT_C); /* Subtract MAT_B from MAT_A, store the result in MAT_C */

void mul_mat(mat *MAT_A, mat *MAT_B, mat *MAT_C); /* Multiply MAT_A and MAT_B, store the result in MAT_C */

void mul_scalar(mat *MAT_A, double num, mat *MAT_B); /* Multiply MAT_A by a scalar (num), store the result in MAT_B */

void trans_mat(mat *MAT_A, mat *MAT_B); /* Transpose MAT_A, store the result in MAT_B */



/**********************************************
*******      errorHandler commands       ******
**********************************************/

int check_cmd_name(char *cmd); /* This method checks if a user-inputted command name is correct - but with a comma after it */

int check_scalar(char *mat_b); /* This function checks to see if the input in mat_b is a double (R) */

double turn_to_scalar(char *mat_b);  /* This function turns the input in mat_b to a double (R) */

enum Commands process_command(char *input); /* This command processes the user input for desired command. */

int comma_handler(cmd *myCommand,size_t read); /* This Function handles the amount of commas in the user input. */

int get_mat_C(char *pointer, cmd *myCommand, mat **matrices,int comma_error_handler); /* This function analyzes the third variable. */

int get_mat_B(char *pointer, cmd *myCommand, mat **matrices,int comma_error_handler); /* This function analyzes the second variable. */

int get_mat_A(char *pointer, cmd *myCommand, mat **matrices,int comma_error_handler); /* This function analyzes the first variable. */

int get_Command(char *pointer,cmd *myCommand); /* This function analyzes the command. */

int handle_comma_error(int comma_error_handler); /* Calls for the correct print command according to the received error */

void free_data(char *input,char *inputCopy); /* Frees the allocated memory if it was previously allocated */

void stop(); /* Stops the program execution */


#endif
