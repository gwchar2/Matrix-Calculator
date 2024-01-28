/* THIS FILE INCLUDES ALL THE PROMPTS TO USER AND ALL THE PRINT FUNCTIONS */
#include <stdio.h>
#include <string.h>
#include "mainmat.c"
#include "errorHandler.c"
#include "mymat.c"
#include "mymat.h"


/**********************************************
**********      Print Commands       **********
**********************************************/

/* 
*   This function prints a specific matrix 
*/
void print_mat(mat *matrix) {
    int i,j;
    printf("Printing %s:\n", matrix->name); 
    for (i = 0; i < MAT_SIZE; i++) {
        for (j = 0; j < MAT_SIZE; j++) {
            printf("%.2f\t", matrix->matrix[i][j]);
        }
        printf("\n");
    }
}

/* This function prompts the user for input */
void prompt_message(){ 
    printf("\nEnter the desired command and matrices with the correct syntax!:  (e.g., mul_mat mat_a, mat_b, mat_c):\n");
}

/* This function send the user a very nice welcome message on his first time to the app */
void welcome(){
    printf("*************************************************************************************************\n");
    printf("*\t\t\t\t\t\t\t\t\t\t\t\t*\n*");
    printf("\t\t\tWelcome to the Matrix Calculator App!\t\t\t\t\t*\n");
    printf("*\t\t\t\t\t\t\t\t\t\t\t\t*\n");
    printf("*************************************************************************************************\n");
    printf("*\tThis application allows you to perform various matrix operations.\t\t\t*\n*\tHere is a list of commands at your disposal:\t\t\t\t\t\t*\n");
    printf("*\tprint_mat MAT_A              |  Prints the matrix in a nice 4x4. .2lf\t\t\t*\n"
            "*\tadd_mat MAT_A,MAT_B,MAT_C    |   MAT_C = MAT_A+MAT_B\t\t\t\t\t*\n"
            "*\tsub_mat MAT_A,MAT_B,MAT_C    |   MAT_C = MAT_A-MAT_B\t\t\t\t\t*\n"
            "*\tmul_mat MAT_A,MAT_B,MAT_C    |   MAT_C = MAT_A*MAT_B\t\t\t\t\t*\n"
            "*\tmul_scalar MAT_A,#R,MAT_B    |   MAT_B = MAT_A*#R\t\t\t\t\t*\n"
            "*\ttrans_mat MAT_A, MAT_B       |   MAT_B = Transpose(MAT_A)\t\t\t\t*\n"
            "*\tstop                         |   stops the program\t\t\t\t\t*\n");
    printf("*************************************************************************************************\n\n");
}

/**********************************************
*******         ERROR MESSAGES          *******
**********************************************/

/* Missing argument */
void err_miss_argument(){
    printf("Missing argument!\n");
}
/* Undefined matrix name */
void err_mat_name(){
    printf("Undefined matrix name!\n");
}
/* Undefined command name */
void err_com_name(){
    printf("Undefined command name!\n");
}
/* Argument is not a real number */
void err_num(){
    printf("Argument is not a real number!\n");
}
/* Extraneous text after end of command */
void err_text(){
    printf("Extraneous text after end of command!\n");
}
/* Missing comma */
void err_miss_comma(){
    printf("Missing comma!\n");
}
/* Illegal comma */
void err_illegal_comma(){
    printf("Illegal comma!\n");
}
/* Multiple consecutive commas */
void err_consec_comma(){
    printf("Multiple consecutive commas!\n");
}
/* Argument is not a scalar */
void err_not_scalar(){
    printf("Argument is not a scalar!\n");
}
/* No stop() command from file */
void err_no_stop(){
    printf("There is no stop command at the end of the file...\nTerminating the program!\n");
    stop();
}

/**********************************************
**********     COMMAND MESSAGES         *******
**********************************************/

/* A message when stop() is received */
void msg_stop(){
    printf("Stopping the program...\n");
    stop();
}
/* A message when read_mat() is received */
void msg_read_mat(mat *matrix){
    printf("Initiating variables into %s ...\n",matrix->name);
}
/* A message when add_mat() is received */
void msg_add_mat(mat *matrixA,mat *matrixB,mat *matrixC){
    printf("Calculating %s = %s + %s ...\n",matrixC->name,matrixA->name,matrixB->name);
}
/* A message when sub_mat() is received */
void msg_sub_mat(mat *matrixA,mat *matrixB,mat *matrixC){
    printf("Calculating %s = %s - %s ...\n",matrixC->name,matrixA->name,matrixB->name);
}
/* A message when mul_mat() is received */
void msg_mul_mat(mat *matrixA,mat *matrixB,mat *matrixC){
    printf("Calculating %s = %s x %s ...\n",matrixC->name,matrixA->name,matrixB->name);
}
/* A message when mul_scalar() is received */
void msg_mul_scalar(mat *matrixA,mat *matrixB,double num){
    printf("Calculating %s = %s * %f ...\n",matrixB->name,matrixA->name,num);
}
/* A message when trans_mat() is received */
void msg_trans_mat(mat *matrixA,mat *matrixB){
    printf("Calculating %s = [%s]%c ...\n",matrixB->name,matrixA->name,39);
}

