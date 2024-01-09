/* THIS FILE INCLUDES ALL THE PROMPTS TO USER AND ALL THE PRINT FUNCTIONS */
#include <stdio.h>
#include <string.h>
#include "mainmat.c"
#include "errorHandler.c"
#include "mymat.c"
#include "mymat.h"


/**********************************************
**********      print_mat command       *******
**********************************************/
void print_mat(mat *matrix) {
    int i,j;
    printf("Printing %s:\n", matrix->name); /* NEED TO REMOVE THIS LINE !!*/
    for (i = 0; i < MAT_SIZE; i++) {
        for (j = 0; j < MAT_SIZE; j++) {
            printf("%.2f\t", matrix->matrix[i][j]);
        }
        printf("\n");
    }
}
/**********************************************
**********          ERRORS              *******
**********************************************/
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
/* Missing argument */
void err_miss_argument(){
    printf("Missing argument!\n");
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
    printf("There is no stop command at the end of the file...\nTerminating the program!");
    stop();
}

/**********************************************
**********     COMMAND MESSAGES         *******
**********************************************/
/* A message when stop() is received */
void msg_stop(){
    printf("Stopping the program...");
    stop();
}
/* A message when read_mat() is received */
void msg_read_mat(mat *matrix){
    printf("Initiating variables into %s ...\n",matrix->name);
}
/* A message when add_mat() is received */
void msg_add_mat(mat *matrixA,mat *matrixB,mat *matrixC){
    printf("Calculating %s = %s + %s : \n",matrixC->name,matrixA->name,matrixB->name);
}
/* A message when sub_mat() is received */
void msg_sub_mat(mat *matrixA,mat *matrixB,mat *matrixC){
    printf("Calculating %s = %s - %s : \n",matrixC->name,matrixA->name,matrixB->name);
}
/* A message when mul_mat() is received */
void msg_mul_mat(mat *matrixA,mat *matrixB,mat *matrixC){
    printf("Calculating %s = %s x %s : \n",matrixC->name,matrixA->name,matrixB->name);
}
/* A message when mul_scalar() is received */
void msg_mul_scalar(mat *matrixA,mat *matrixB,float num){
    printf("Calculating %s = %s * %d : \n",matrixB->name,matrixA->name,num);
}
/* A message when trans_mat() is received */
void msg_trans_mat(mat *matrixA,mat *matrixB){
    printf("Calculating %s = %s%c : \n",matrixB->name,matrixA->name,39);
}

