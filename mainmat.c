/* USER INTERACTION AND MAIN HERE */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stddef.h>
#include <unistd.h>

#define MAT_SIZE 4
#define MAT_NAME_SIZE 6

/* A matrix structure with a name and default size of 4x4. */
typedef struct{
    const char name[MAT_NAME_SIZE];
    float matrix[MAT_SIZE][MAT_SIZE];
} mat; 

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
int onStart(enum Commands *user_command,char **input,char **operation,char **mat_a_name,char **mat_b_name,char **mat_c_name);
enum Commands process_command(char* input);
int check_mat_name(char* name);
int check_cmd_name(char* cmd);
int check_R(char *mat_b); /* Checks if the matrix is a double (R) */
double turn_to_R(char *mat_b); /* Converts the matrix to a double number */
void my_free(char **operation,char **mat_a_name,char **mat_b_name,char **mat_c_name); /* Frees the allocated memory if it was previously allocated */



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
void stop(); /* Stops the program */
void welcome();
void msg_stop();
void desired_command();

int main(){
    mat MAT_A = {"MAT_A",{{1, 2, 3, 4}, {5, 1, 2, 3}, {4, 5, 1, 2}, {3, 4, 5, 1}} };
    mat MAT_B = {"MAT_B",{{2, 3, 4, 5}, {1, 2, 3, 4}, {5, 1, 2, 3}, {4, 5, 1, 2}} };
    mat MAT_C = {"MAT_C",{ {0.0} } };
    mat MAT_D = {"MAT_D",{ {0.0} } };
    mat MAT_E = {"MAT_E",{ {0.0} } };
    mat MAT_F = {"MAT_F",{ {0.0} } };
    mat user_mat_a, user_mat_b, user_mat_c;
    enum Commands user_command;
    int commas;

    /* Initializes The input variables to dynamic character arrays */

    char *input = NULL;
    char *operation = NULL;
    char *mat_a_name = NULL;
    char *mat_b_name = NULL;
    char *mat_c_name = NULL;
    
    welcome();
    while(1){
        if (onStart(&user_command, &input, &operation, &mat_a_name, &mat_b_name,&mat_c_name) != 1){
            printf(" // FOR TEST DELETE THIS LATER // Operation: %s\n", operation);
            printf(" // FOR TEST DELETE THIS LATER // Matrix A: %s\n", mat_a_name);
            printf(" // FOR TEST DELETE THIS LATER // Matrix B: %s\n", mat_b_name);
            printf(" // FOR TEST DELETE THIS LATER // Matrix C: %s\n", mat_c_name);
            if (user_command == STOP){ 
                free(input);
                my_free(&operation, &mat_a_name, &mat_b_name, &mat_c_name);
                msg_stop();
            /* NEED TO MAKE DYNAMIC MEMORY FOR THE INPUT ! */
            /* commas = count_commas(input);     Count Commas */
            /* check_mat_name                     Check the matrices inputted for legal variables */
            /* Pay attention - the onStart() gets strtok(input, " \t\n") <-- including \n on all variables */
        	}   
        else
            ;
    	}   
	}
}
int onStart(enum Commands *user_command, char **input, char **operation, char **mat_a_name, char **mat_b_name, char **mat_c_name){
    char *pointer; /* A character pointer that helps deal with the input */
	size_t len; /* Length of the array */
    ssize_t read; /* How many values were read in getline() */
	len = 0;

    /* Reset the values for every itteration of input.*/
    if (*input != NULL){
        free(*input);
        *input = NULL; /* Initialize input to NULL */
    }
    my_free(operation,mat_a_name,mat_b_name,mat_c_name);

    
    desired_command(); /* prompts the user for input */ 

    /* Get the input from the user into 'input' */
    if ((read = getline(input, &len, stdin)) == -1) {
        /* If the last line in stdin was not "stop" , frees the allocated memory & calls for err_no_stop() */
        if (strcmp(*input, "stop") != 0){
            err_no_stop();
        }    
        
    }
    
    /* GO to the first character after the next whitespaces */
    pointer = strtok(*input, " \t\n"); 

    /* FIRST VARIABLE ---- THE COMMAND ---- */
    if (pointer != NULL) {
        *operation = (char *)malloc(strlen(pointer) + 1);
        strcpy(*operation, pointer);                                             /* Copies to 'Operation' the first part of the input (The command) */        
        *user_command = process_command(*operation);                             /* Checks to see what command was inputted */
        pointer = strtok(NULL, " ,\t\n");                                        /* skip to the next part of the string */
        switch (*user_command){                         
            case READ_MAT:                                                       /* Need to go to different function to deal with the full input !*/
                break;
            case INVALID:                                                        /* If the command was invalid */
                if (check_cmd_name(*operation)){                                 /* Check if it was a good command with a comma */
                    err_illegal_comma();
                    return 1;
                }
                else{                                                           /* If it wasnt, return invalid command ! */
                    err_com_name();
                    return 1;
                }
			default:
	            break;             
        }

        /* SECOND VARIABLE ---- MAT_A ---- */
        if (pointer != NULL) {              
            if (*user_command == STOP){                                         /* If the user command is 'stop' and there is still text return error */
                err_text();
                return 1;
            }
            *mat_a_name = (char *)malloc(strlen(pointer) + 1);
            strcpy(*mat_a_name, pointer);                                       /* Copies to mat_a this part of the input segment */
            pointer = strtok(NULL, " ,\t\n");                                   /* Moves to the next segment of the input */

            /* THIRD VARIABLE ---- MAT_B ---- */
            if (pointer != NULL) {
                *mat_b_name = (char *)malloc(strlen(pointer) + 1);
                strcpy(*mat_b_name, pointer);                                   /* Copies to mat_b this part of the input segment */
                switch (*user_command){                     
                    case MUL_SCALAR:                                            /* If the command is mul_scalar, checks to see if MAT_B = (R) Number */
                        if (!check_R(*mat_b_name)){
                            err_not_scalar();
                            return 1;
                        }
                        break;
                    case PRINT_MAT:                                             /* If the command is a print_mat command, return extra txt error */
                        err_text();
                        return 1;
					default:
	            		break;
                }   
                pointer = strtok(NULL, " ,\t\n");                               /* Move to the next input segment */

                /* FOURTH VARIABLE ---- MAT_C ---- */
                if (pointer != NULL) {
                    if (*user_command == TRANS_MAT){                            /* If the command is trans_mat, return extra txt error */
                        err_text();
                        return 1;
                    }
                    *mat_c_name = (char *)malloc(strlen(pointer) + 1);
                    strcpy(*mat_c_name, pointer);
                    pointer = strtok(NULL, " ,\t\n");
                } 

                /* FIFTH VARIABLE ---- EXTRA TEXT ---- */
                if (pointer != NULL) {                                          /* If the point has not reached a NULL, clearly there is text left! */
                    err_text();                                                 /* NO COMMAND needs 4 variables...so return the extra txt error */
                    return 1;
                } 
            }
        } 
    }
    return 0;
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

/* 
*This function checks to see if the input in mat_b is a double (R)
*/
int check_R(char *mat_b){
    char *end_pointer;
    double numericValue = strtod(mat_b, &end_pointer);

    if (mat_b == end_pointer) {
        printf("No conversion performed.\n");
        return 0;
    } else {
        printf("Converted value: %.2f\n", numericValue);
        return 1;
    }
}

/* 
*This function checks to see if the input in mat_b is a double (R)
*/
double turn_to_R(char *mat_b){
    char *end_pointer;
    double numericValue = strtod(mat_b, &end_pointer);
    printf("//FOR TESTING DELETE THIS ! Returning Converted value: %.2f\n", numericValue);
    return numericValue;
}

/*
* This command processes the user input for desired command.
*/
enum Commands process_command(char *input) {

    if (strcmp(input, "print_mat") == 0) {
        printf("//FOR TEST ONLY Command is : PRINT_MAT\n");
        return PRINT_MAT;
    } else if (strcmp(input, "add_mat") == 0) {
        printf("//FOR TEST ONLY Command is : ADD_MAT\n");
        return ADD_MAT;
    } else if (strcmp(input, "sub_mat") == 0) {
        printf("//FOR TEST ONLY Command is : SUB_MAT\n");
        return SUB_MAT;
    }else if (strcmp(input, "mul_mat") == 0) {
        printf("//FOR TEST ONLY Command is : MUL_MAT\n");
        return MUL_MAT;
    }    else if (strcmp(input, "mul_scalar") == 0) {
        printf("//FOR TEST ONLY Command is : MUL_SCALAR\n");
        return MUL_SCALAR;
    }else if (strcmp(input, "trans_mat") == 0) {
        printf("//FOR TEST ONLY Command is : TRANS_MAT\n");
        return TRANS_MAT;
    }else if (strcmp(input, "stop") == 0) {
        printf("//FOR TEST ONLY Command is : STOP\n");
        return STOP;
    }
    else if (strcmp(input, "read_mat") == 0){
        printf("//FOR TEST ONLY Command is : READ_MAT\n");
        return READ_MAT;
    }
    else {
        printf("//FOR TEST ONLY Command is : INVALID\n");
        return INVALID; 
    } 
}

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
void msg_stop(){
    printf("Stopping the program...\n");
    stop();
}
void stop(){
    exit(0);
}


/* This function prompts the user for input */
void desired_command(){ 
    printf("\nEnter the desired command and matrices with the correct syntax!:  (e.g., mul_mat mat_a, mat_b, mat_c):\n");
}
void welcome(){
    printf("*************************************************************************************************\n");
    printf("*\t\t\t\t\t\t\t\t\t\t\t\t*\n*");
    printf("\t\t\tWelcome to the Matrix Calculator App!\t\t\t\t\t*\n");
    printf("*\t\t\t\t\t\t\t\t\t\t\t\t*\n");
    printf("*************************************************************************************************\n");
    printf("*\t\tThis application allows you to perform various matrix operations.\t\t*\n*\t\tHere is a list of commands at your disposal:\t\t\t\t\t*\n");
    printf("*\tprint_mat MAT_A              |  Prints the matrix in a nice 4x4. .2lf\t\t\t*\n"
            "*\tadd_mat MAT_A,MAT_B,MAT_C    |   MAT_C = MAT_A+MAT_B\t\t\t\t\t*\n"
            "*\tsub_mat MAT_A,MAT_B,MAT_C    |   MAT_C = MAT_A-MAT_B\t\t\t\t\t*\n"
            "*\tmul_mat MAT_A,MAT_B,MAT_C    |   MAT_C = MAT_A*MAT_B\t\t\t\t\t*\n"
            "*\tmul_scalar MAT_A,#R,MAT_B    |   MAT_B = MAT_A*#R\t\t\t\t\t*\n"
            "*\ttrans_mat MAT_A, MAT_B       |   MAT_B = Transpose(MAT_A)\t\t\t\t*\n"
            "*\tstop                         |   stops the program\t\t\t\t\t*\n");
    printf("*************************************************************************************************\n\n");
}
