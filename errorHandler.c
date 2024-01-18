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
    if (strlen(variables) > 6 ||
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
        if (com != INVALID && lc_cmd == ','){   /* If the new command is a real one, and also the last character is a comma , return 1, else 0. */
            return 1;
        }
       return 0;
}

/* 
*This function checks to see if the input in mat_b is a double (R)
*/
int check_R(char *mat_b){
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
double turn_to_R(char *mat_b){
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
    else {
        return INVALID; // Indicate an unknown command
    }
}

/*
* This function frees memory if it was previously allocated,
* and re-assignes the pointers to NULL.
*/
void my_free(char **operation, char **mat_a_name, char **mat_b_name, char **mat_c_name) {
    if (*operation != NULL)
        free(*operation);
    if (*mat_a_name != NULL)
        free(*mat_a_name);
    if (*mat_b_name != NULL)
        free(*mat_b_name);
    if (*mat_c_name != NULL)
        free(*mat_c_name);
    *operation = NULL;
    *mat_a_name = NULL;
    *mat_b_name = NULL;
    *mat_c_name = NULL;
}


void stop(){
     exit(0);
}