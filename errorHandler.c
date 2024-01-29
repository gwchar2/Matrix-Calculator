/* HANDLES ALL THE ERRORS POSSIBLE. CHECKS THE DATA AND INPUT FROM USER !! ??*/
#include <stdio.h>
#include <string.h>
#include "promptsAndPrints.c"
#include "mainmat.c"
#include "mymat.c"
#include "mymat.h"



/*
* This method checks if a user-inputted command name is correct - but with a comma after it !
* Returns 1 if the command is correct but has a comma at the end, 0 else.
*/
int check_cmd_name(char *cmd){
    enum Commands com;
    size_t length_cmd = strlen(cmd);    			/* Gets the size of the user-input command */
    char temp[length_cmd];              		    /* Makes a new char array with the same size */
    char lc_cmd = cmd[length_cmd-1];    			/* Stores the last character from cmd */
    strcpy(temp,cmd);
    if (length_cmd > 0) {           				/* If the size is greater than 0*/
        temp[length_cmd - 1] = '\0';    			/* Reduce the size by one */
    }
	com = process_command(temp);  					/* Send the new array reduced by 1 to be checked for a viable command */
    if (com != INVALID && lc_cmd == ','){       	/* If the new command is a real one, and also the last character is a comma , return 1, else 0. */
        return 1;
    }
    return 0;
}


/* 
*This function checks to see if the input in mat_b is a double (R)
*/
int check_scalar(char *mat_b){
    char *end_pointer;
    double numericValue = strtod(mat_b, &end_pointer);

    if (mat_b == end_pointer) {
        return 0;
    } else {
        return 1;
    }
}


/* 
*This function turns the input in mat_b to a double (R)
*/
double turn_to_scalar(char *mat_b){
    char *end_pointer;
    double numericValue = strtod(mat_b, &end_pointer);
    return numericValue;
}


/*
* This command processes the user input for desired command.
*/
enum Commands process_command(char *input) {
    if (strcmp(input, "print_mat") == 0) {
        return PRINT_MAT;
    } else if (strcmp(input, "add_mat") == 0) {
        return ADD_MAT;
    } else if (strcmp(input, "sub_mat") == 0) {
        return SUB_MAT;
    }else if (strcmp(input, "mul_mat") == 0) {
        return MUL_MAT;
    }    else if (strcmp(input, "mul_scalar") == 0) {
        return MUL_SCALAR;
    }else if (strcmp(input, "trans_mat") == 0) {
        return TRANS_MAT;
    }else if (strcmp(input, "stop") == 0) {
        return STOP;
    }
    else if (strcmp(input, "read_mat") == 0){
        return READ_MAT;
    }
    else {
        return INVALID; 
    } 
}


/*
*   This Function handles the amount of commas in the user input.
*   Returns 1 if there is a missing comma.
*   Returns 2 if there are extra commas.
*   Returns 3 if there is more than 2 consecutive commas.
*   Otherwise, it returns 0.
*/
int comma_handler(cmd *myCommand,size_t read){
    size_t i = 0;
    size_t newSize = 0; /* Holds the size of the array without whitespaces */
    int j = 0;
    int total_comma = 0, total_comma_in_a_row = 0; /* Total amount of commas in the input, and total amount of them in a row. */
    char *noSpace = NULL; /* An array of the input without whitespaces. */
    for (i = 0; i < read; i++){
        if (!WHITESPACE(myCommand->user_input[i])){
            newSize++;
            noSpace = realloc(noSpace, newSize);
            noSpace[newSize - 1] = myCommand->user_input[i];
        }
        if (noSpace[newSize - 1] == ',' && !WHITESPACE(myCommand->user_input[i])){
            total_comma++;
            total_comma_in_a_row++;
            if (total_comma_in_a_row == 2){
                return 3;
            }
        }
        else if (noSpace[newSize - 1] != ',' && !WHITESPACE(myCommand->user_input[i])){
            total_comma_in_a_row = 0;
        }
    }
    if (total_comma > 2 && (myCommand->user_cmd == ADD_MAT || myCommand->user_cmd == SUB_MAT ||
        myCommand->user_cmd == MUL_MAT || myCommand->user_cmd == MUL_SCALAR)){
            return 1;
    }
    else if (total_comma < 2 && (myCommand->user_cmd == ADD_MAT || myCommand->user_cmd == SUB_MAT ||
        myCommand->user_cmd == MUL_MAT || myCommand->user_cmd == MUL_SCALAR)){
            return 2;
    }
    else if (total_comma > 1 && (myCommand->user_cmd == TRANS_MAT)){
            return 1;
    }  
    else if (total_comma < 1 && (myCommand->user_cmd == TRANS_MAT)){
            return 2;
    }  
    else if (total_comma >= 1 && (myCommand->user_cmd == STOP || myCommand->user_cmd == PRINT_MAT)){
        return 1;
    }
    return 0;
}


/*
*   This function analyzes the third variable. 
*   Returns 1 if it is invalid, 0 if it is a good input.
*/
int get_mat_C(char *pointer, cmd *myCommand, mat **matrices,int comma_error_handler){
    /* ---- MAT_C ---- */
    int i = 0;
    int numcheck = 0;
    if (pointer == NULL && (myCommand->user_cmd == ADD_MAT || myCommand->user_cmd == MUL_SCALAR || myCommand->user_cmd == SUB_MAT || myCommand->user_cmd == MUL_MAT)) {
        err_miss_argument();         
        return 1;
    }
    else if (pointer != NULL){
        if (myCommand->user_cmd == TRANS_MAT || myCommand->user_cmd == PRINT_MAT ){     
            err_text();
            return 1;                                            /* If the command is trans_mat or print_mat return extra text error */
        }
        for (i = 0; i < 6  ; i++){
            if (strcmp(matrices[i]-> name , pointer) == 0){
                myCommand->user_mat_c = matrices[i];
                numcheck = 1;
                break;
            }
        }
        if (numcheck != 1){
            if (handle_comma_error(comma_error_handler) != 0)
                return 1;
            else
                err_mat_name();
            return 1;
        }                       
    } 
    return 0;
}


/*
*   This function analyzes the second variable. 
*   Returns 1 if it is invalid, 0 if it is a good input.
*/
int get_mat_B(char *pointer, cmd *myCommand, mat **matrices,int comma_error_handler){
    /* ---- MAT_B ---- */
    int i=0;
    int numcheck = 0;
    if (pointer == NULL && myCommand->user_cmd != PRINT_MAT && myCommand->user_cmd != READ_MAT){
        err_miss_argument();
        return 1;
    }
    if (pointer != NULL) {
        switch (myCommand->user_cmd){                     
            case MUL_SCALAR:                                            /* If the command is mul_scalar, checks to see if MAT_B = (R) Number */
                if (!check_scalar(pointer)){
                    if (handle_comma_error(comma_error_handler) != 0)
                        return 1;
                    else
                        err_not_scalar();
                    return 1;
                }
                else{
                    myCommand->user_scalar = turn_to_scalar(pointer);
                    return 0;
                }
            case PRINT_MAT:                                             /* If the command is a print_mat command, return extra txt error */
                if (handle_comma_error(comma_error_handler) != 0)
                    return 1;
                else
                    err_text();
                return 1;
            case READ_MAT:
                printf("// FOR TEST DELETE THIS LATER // READ_MAT get_mat_b\n");
                return 0;
			default:
                for (i = 0; i < 6 ; i++){
                    if (strcmp(matrices[i]->name , pointer) == 0){
                        myCommand->user_mat_b = matrices[i];
                        numcheck = 1;
                        break;
                    }
                }
                if (numcheck != 1){
                    if (handle_comma_error(comma_error_handler) != 0)
                        return 1;
                else
                    err_mat_name();
                return 1;
                }                                                         
            break;
        }
   }
   return 0;
}


/*
*   This function analyzes the first variable. 
*   Returns 1 if it is invalid, 0 if it is a good input.
*/
int get_mat_A(char *pointer, cmd *myCommand, mat **matrices,int comma_error_handler){
    /*  ---- MAT_A ---- */
    int i=0;
    int numcheck = 0;
    if (pointer == NULL && myCommand->user_cmd != STOP){
        err_miss_argument();
        return 1;
    }
    else if (pointer == NULL && myCommand->user_cmd == STOP){
        msg_stop();
        stop();
    }
    else { 
        switch (myCommand->user_cmd){
            case STOP:
                err_text();
                return 1;
            default:
                for (i = 0; i < 6  ; i++){
                    if (strcmp(matrices[i]-> name , pointer) == 0){
                        myCommand->user_mat_a = matrices[i];
                        numcheck = 1;
                        break;
                    }
                }
                if (numcheck != 1){
                    if (handle_comma_error(comma_error_handler) != 0)
                        return 1;
                    else
                        err_mat_name(); 
                    return 1;
                }                                                         
                break;
         }
    }
    return 0;
}


/*
*   This function analyzes the command. 
*   Returns 1 if it is invalid, 0 if it is a good command input.
*/
int get_Command(char *pointer,cmd *myCommand){
    /* ---- ANALYZE THE COMMAND ---- */
    if (pointer == NULL){
        err_com_name();
        return 1;
    }
    else {
        myCommand->user_cmd = process_command(pointer);                             /* Checks to see what command was inputted */
        if ( myCommand->user_cmd == INVALID ) {                                     /* If the command was invalid */
            if (check_cmd_name(pointer)){                                     /* Check if it was a good command with a comma */
                err_illegal_comma();
                return 1;
            }
            else{                                                             /* If it wasnt, return invalid command ! */
                err_com_name();
                return 1;
            }             
        }
    }
    return 0;
}


/*  if (comma_error_handler == 1) err_illegal_comma(), return 1
*   else if (comma_error_handler == 2) err_miss_comma(), return 1
*   else if (comma_error_handler == 3) err_consec_comma(), return 1
*/
int handle_comma_error(int comma_error_handler){
    if (comma_error_handler == 1) {
        err_illegal_comma(); 
        return 1;
    }
    else if (comma_error_handler == 2) {
        err_miss_comma(); 
        return 1;
    }
    else if (comma_error_handler == 3) {
        err_consec_comma(); 
        return 1;
    }
    return 0; 
}

/*  
*   This function frees the dynamicaly allocated memory (If it can)
*/
void free_data(char *input, char *inputCopy){
    if (input != NULL) {     /* Initializes input to NULL every time if TRUE */
        free(input);
        input = NULL;
    }
    if (inputCopy != NULL) {
        free(inputCopy);
        inputCopy = NULL;
    }
}

void stop(){
     exit(0);
}