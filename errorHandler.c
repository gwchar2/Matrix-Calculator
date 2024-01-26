/* HANDLES ALL THE ERRORS POSSIBLE. CHECKS THE DATA AND INPUT FROM USER !! ??*/
#include <stdio.h>
#include <string.h>
#include "promptsAndPrints.c"
#include "mainmat.c"
#include "mymat.c"
#include "mymat.h"

/*
* This method checks if a user-inputted matrix name is correct.
* Returns 1 if it isnt, 0 if it is.
*/
int check_mat_name(char *variables){
    if (strlen(variables) > 5 ||
             (strcmp(variables,"MAT_A") != 0 && strcmp(variables,"MAT_B") != 0 &&
              strcmp(variables,"MAT_C") != 0 && strcmp(variables,"MAT_D") != 0 &&
               strcmp(variables,"MAT_E") != 0 && strcmp(variables,"MAT_F") != 0)){
                return 1;
            }
    return 0;
}
/*
* This method checks if a user-inputted command name is correct - but with a comma after it !
* Returns 1 if the command is correct but has a comma at the end, 0 else.
*/
int check_cmd_name(char *cmd){
    size_t length_cmd = strlen(cmd);            /* Gets the size of the user-input command */
    char temp[MAX_CMD_LENGTH];                  /* Makes a new temporary char array */
    char lc_cmd = cmd[length_cmd-1];            /* Stores the last character from cmd */
    enum Commands com;
    strcpy(temp,cmd);
        if (length_cmd > 0) {                   /* If the size is greater than 0*/
            temp[length_cmd - 1] = '\0';        /* Reduce the size by one */
        }
        com = process_command(temp);            /* Send the new array reduced by 1 to be checked for a viable command */
        if (com != INVALID && lc_cmd == ','){   /* If the new command is a valid one, and also the last character is a comma , return 1, else 0. */
            return 1;
        }
       return 0;
}

/* 
*This function checks to see if the input in mat_b is a double (R)
*/
int check_scalar(char *mat_b){
    char *end_pointer;  /* Pointer to the end of the string */
    double numericValue = strtod(mat_b, &end_pointer); /* Checks to see if the string is a double from the start to finish */
    if (*end_pointer == '\0') {
        return 1;       /* If its a double, returns 1, 0 otherwise. */
    } else {
        return 0;
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
    int i=0;
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
    else {
        return INVALID; // Indicate an unknown command
    }
}

void stop(){
     exit(0);
}



/*
*   This Function handles the amount of commas in the user input.
*   If it belove or below the needed amount - returns 1, as well as if there are more than 2 in a row.
*   Otherwise, it returns 0.
*/
int comma_handler(char *input,size_t read,double read_scalars,enum Commands *user_command){
    size_t i = 0;
    size_t newSize = 0;
    int j = 0;
    int total_comma = 0, total_comma_in_a_row = 0;
    char *noSpace = NULL;
    for (i = 0; i < read; i++){
        if (!WHITESPACE(input[i])){
            newSize++;
            noSpace = realloc(noSpace, newSize);
            noSpace[newSize - 1] = input[i];
        }
        if (noSpace[newSize - 1] == ','){
            total_comma++;
            total_comma_in_a_row++;
            if (total_comma_in_a_row == 2){
                err_consec_comma();
                return 3;
            }
        }
        else {
            if (total_comma_in_a_row != 0 && noSpace[newSize - 1] != ','){
                total_comma_in_a_row--;
            }
        }
    }
    if (total_comma > 2 && (*user_command == ADD_MAT || *user_command == SUB_MAT ||
        *user_command == MUL_MAT || *user_command == MUL_SCALAR)){
            err_illegal_comma();
            return 1;
    }
    else if (total_comma < 2 && (*user_command == ADD_MAT || *user_command == SUB_MAT ||
        *user_command == MUL_MAT || *user_command == MUL_SCALAR)){
            err_miss_comma();
            return 2;
    }
    else if (total_comma > 1 && (*user_command == TRANS_MAT)){
            err_illegal_comma();
            return 1;
    }  
    else if (total_comma < 1 && (*user_command == TRANS_MAT)){
            err_miss_comma();
            return 2;
    }  
    else if (total_comma >= 1 && (*user_command == STOP || *user_command == PRINT_MAT)){
        err_illegal_comma();
        return 1;
    }
    return 0;
}



/*
*   This function analyzes the third variable. 
*   Returns 1 if it is invalid, 0 if it is a good input.
*/
int get_mat_C(char *pointer, enum Commands *user_command,mat **user_mat_c, mat **matrices){
    /* ---- MAT_C ---- */
    int i = 0;
    int numcheck = 0;
    printf("///// ARE WE GETTING HERE? IN C\n");
    if (pointer == NULL && (*user_command == ADD_MAT || *user_command == MUL_SCALAR || *user_command == SUB_MAT || *user_command == MUL_MAT)) {
        err_miss_argument();
        return 1;
    }
    else if (pointer != NULL){
        if (*user_command == TRANS_MAT || *user_command == PRINT_MAT ){                                    /* If the command is trans_mat, return extra text error */
            err_text();
            return 1;
        }
        for (i = 0; i < 6  ; i++){
            if (strcmp(matrices[i]-> name , pointer) == 0){
                *user_mat_c = matrices[i];
                numcheck = 1;
                break;
            }
        }
        if (numcheck != 1){
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
int get_mat_B(char *pointer, enum Commands *user_command,mat **user_mat_b, mat **matrices,double user_scalar){
    /* ---- MAT_B ---- */
    int i=0;
    int numcheck = 0;
    if (pointer == NULL && *user_command != PRINT_MAT && *user_command != READ_MAT){
        err_miss_argument();
        return 1;
    }
    if (pointer != NULL) {
        switch (*user_command){                     
            case MUL_SCALAR:                                            /* If the command is mul_scalar, checks to see if MAT_B = (R) Number */
                if (!check_scalar(pointer)){
                    err_not_scalar();
                    return 1;
                }
                else{
                    user_scalar = turn_to_scalar(pointer);
                    return 0;
                }
            case PRINT_MAT:                                             /* If the command is a print_mat command, return extra txt error */
                err_text();
                return 1;
            case READ_MAT:
                printf("// FOR TEST DELETE THIS LATER // READ_MAT get_mat_b");
                return 0;
			default:
                for (i = 0; i < 6 ; i++){
                    if (strcmp(matrices[i]->name , pointer) == 0){
                        *user_mat_b = matrices[i];
                        numcheck = 1;
                        break;
                    }
                }
                if (numcheck != 1){
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
int get_mat_A(char *pointer, enum Commands *user_command,mat **user_mat_a, mat **matrices){
    /*  ---- MAT_A ---- */
    int i=0;
    int numcheck = 0;
    if (pointer == NULL && *user_command != STOP){
        err_miss_argument();
        return 1;
    }
    else if (pointer == NULL && *user_command == STOP){
        msg_stop();
        stop();
    }
    else { 
        switch (*user_command){
            case STOP:
                err_text();
                return 1;
            default:
                for (i = 5; i >= 0  ; i--){
                    if (strcmp(matrices[i]-> name , pointer) == 0){
                        *user_mat_a = matrices[i];
                        numcheck = 1;
                        break;
                    }
                }
                if (numcheck != 1){
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
int get_Command(char *pointer,enum Commands *user_command){
    /* ---- ANALYZE THE COMMAND ---- */
    if (pointer == NULL){
        err_com_name();
    }
    else {
        *user_command = process_command(pointer);                             /* Checks to see what command was inputted */
        if ( *user_command == INVALID ) {                                     /* If the command was invalid */
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
