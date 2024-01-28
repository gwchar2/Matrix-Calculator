/* USER INTERACTION AND MAIN HERE */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stddef.h>
#include <unistd.h>

#define MAT_SIZE 4
#define MAT_NAME_SIZE 6
#define COMMANDS_COUNT 9
#define WHITESPACE(c) ((c == ' ' || c == '\t' || c == '\n' || c == '\r' || c == '\f' || c == '\v'))     /* Checks if a character is a whitespace */
#define DELIMETER_1 (" ,\t\n\r\f\v") /* A delimeter for strtok function with a comma */
#define DELIMITER_2 (" \t\n\r\f\v") /* A delimeter for strtok function without a comma */
#define MY_FREE()  free_data(myCommand->user_input, inputCopy)
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
} cmd;

/**** MAIN COMMANDS ****/
int onStart(cmd *myCommand,mat **matrices,double *read_scalars);
void activate_command(cmd *myCommand);


/**** ERROR HANDLER COMMANDS ****/
int check_cmd_name(char* cmd);
int check_scalar(char *mat_b); /* Checks if the matrix is a double (R) */
double turn_to_scalar(char *mat_b); /* Converts the matrix to a double number */
enum Commands process_command(char* input);
int comma_handler(cmd *myCommand,size_t read);
int get_mat_A(char *pointer, cmd *myCommand, mat **matrices,int comma_error_handler);
int get_mat_B(char *pointer, cmd *myCommand, mat **matrices,int comma_error_handler);
int get_mat_C(char *pointer, cmd *myCommand, mat **matrices,int comma_error_handler);
int get_Command(char *pointer,cmd *myCommand);
int handle_comma_error(int comma_error_handler);
void free_data(char *input,char *inputCopy);
void stop(); /* Stops the program */


/**** promptsAndPrints COMMANDS ****/
void print_mat(mat *matrix);
void prompt_message();
void welcome();
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
void msg_stop();
void msg_read_mat(mat *matrix);
void msg_add_mat(mat *matrixA,mat *matrixB,mat *matrixC);
void msg_sub_mat(mat *matrixA,mat *matrixB,mat *matrixC);
void msg_mul_mat(mat *matrixA,mat *matrixB,mat *matrixC);
void msg_mul_scalar(mat *matrixA,mat *matrixB,double num);
void msg_trans_mat(mat *matrixA,mat *matrixB);

/**** mymat.c COMMANDS ****/
void add_mat(mat *MAT_A, mat *MAT_B, mat *MAT_C);
void sub_mat(mat *MAT_A, mat *MAT_B, mat *MAT_C);
void mul_mat(mat *MAT_A, mat *MAT_B, mat *MAT_C);
void mul_scalar(mat *MAT_A, double num, mat *MAT_B);
void trans_mat(mat *MAT_A, mat *MAT_B);


int main(){
    mat MAT_A = {"MAT_A",{{1, 2, 3, 4}, {5, 1, 2, 3}, {4, 5, 1, 2}, {3, 4, 5, 1}} };
    mat MAT_B = {"MAT_B",{{2, 3, 4, 5}, {1, 2, 3, 4}, {5, 1, 2, 3}, {4, 5, 1, 2}} };
    mat MAT_C = {"MAT_C",{ {0.0} } };
    mat MAT_D = {"MAT_D",{ {0.0} } };
    mat MAT_E = {"MAT_E",{ {0.0} } };
    mat MAT_F = {"MAT_F",{ {0.0} } };
    mat *matrices[6] = {&MAT_A, &MAT_B, &MAT_C, &MAT_D, &MAT_E, &MAT_F};
    double read_scalars[16] = {0};

    /* initialize all the pointers in myCommand with a NULL */
    cmd myCommand = {
    .user_input = NULL,
    .user_mat_a = NULL,                
    .user_mat_b = NULL,
    .user_mat_c = NULL,
    };

    welcome(); /* Calls for welcome message */
    while(1){
        if (onStart(&myCommand,matrices,read_scalars) != 1){
            printf("\nUser Input: %s",myCommand.user_input);
            activate_command(&myCommand);
            printf("\n****************************************************\n");
            printf("\n*******************  TESTS  ************************\n");
            printf("User input: %s",myCommand.user_input);
            printf("User CMD: %d\n",myCommand.user_cmd);
            printf("User CMD: %s\n",myCommand.user_mat_a->name);
            printf("User CMD: %s\n",myCommand.user_mat_b->name);
            printf("User CMD: %s\n",myCommand.user_mat_c->name);
            printf("User CMD: %f\n",myCommand.user_scalar);
            printf("****************************************************\n");
        }
	}
}

int onStart(cmd *myCommand,mat **matrices,double *read_scalars){
    char *pointer; /* A character pointer that helps deal with the input */
	size_t len; /* Length of the array */
    ssize_t read; /* This variable will store how many values were read in getline() including null terminator */
	len = 0; /* This variable will store the total size of the input recieved */
    char *inputCopy = NULL;
    int comma_error_handler;
    prompt_message(); /* prompts the user for input */ 
    /* Get the input from the user into 'input' */
    if ((read = getline(&(myCommand->user_input), &len, stdin)) == -1) {
        /* If the last line in stdin was not "stop" , frees the allocated memory & calls for err_no_stop() */
        if (strcmp(myCommand->user_input, "stop") != 0){
            err_no_stop();
        }      
    }
    inputCopy = (char *)malloc(len);
    strcpy(inputCopy,myCommand->user_input);
    pointer = strtok(inputCopy, DELIMITER_2); 

    /* Analyze the command segment */
    if (get_Command(pointer,myCommand)){
        MY_FREE();    /* resets the data if needed to */ 
        return 1;
    }
    comma_error_handler = comma_handler(myCommand,read);            /* Stores the error value received from comma_handler*/
    pointer = strtok(NULL, DELIMETER_1);

    /* Analyze the first matrix variable */
    if (get_mat_A(pointer,myCommand,matrices,comma_error_handler)){
        MY_FREE();    /* resets the data if needed to */ 
        return 1;
    }
    pointer = strtok(NULL, DELIMETER_1);  

    /* Analyze the second matrix variable */
    if (get_mat_B(pointer,myCommand,matrices,comma_error_handler)){
        MY_FREE();    /* resets the data if needed to */ 
        return 1;
    }   
    pointer = strtok(NULL, DELIMETER_1);  

    /* Analyze the third matrix variable */
    if (get_mat_C(pointer,myCommand,matrices,comma_error_handler)){
        MY_FREE();    /* resets the data if needed to */ 
        return 1;
    }
    pointer = strtok(NULL,DELIMITER_2);

    /* FIFTH VARIABLE ---- EXTRA TEXT ----/ */
    if (pointer != NULL) {                                          /* If the point has not reached a NULL, clearly there is text left! */
        err_text();                                                 /* NO COMMAND needs 4 variables...so return the extra txt error */
        MY_FREE();    /* resets the data if needed to */ 
        return 1;
    }
    if (handle_comma_error(comma_error_handler)){
        MY_FREE();
        return 1;
    }
    return 0;
}

/*
*   This function activates the prompted command.
*/
void activate_command(cmd *myCommand){
    switch(myCommand->user_cmd){
        /*case READ_MAT:
        void msg_read_mat(mat *matrix);
        */
        case PRINT_MAT:
            print_mat(myCommand->user_mat_a);
            break;
        case ADD_MAT:
            msg_add_mat(myCommand->user_mat_a, myCommand->user_mat_b, myCommand->user_mat_c);
            add_mat(myCommand->user_mat_a, myCommand->user_mat_b, myCommand->user_mat_c);
            break;
        case SUB_MAT:
            msg_sub_mat(myCommand->user_mat_a, myCommand->user_mat_b, myCommand->user_mat_c);
            sub_mat(myCommand->user_mat_a, myCommand->user_mat_b, myCommand->user_mat_c);
            break;
        case MUL_MAT:
            msg_mul_mat(myCommand->user_mat_a, myCommand->user_mat_b, myCommand->user_mat_c);
            mul_mat(myCommand->user_mat_a, myCommand->user_mat_b, myCommand->user_mat_c);
            break;
        case MUL_SCALAR:
            msg_mul_scalar(myCommand->user_mat_a, myCommand->user_mat_c, myCommand->user_scalar);
            mul_scalar(myCommand->user_mat_a, myCommand->user_scalar, myCommand->user_mat_c);
            break;
        case TRANS_MAT:
            msg_trans_mat(myCommand->user_mat_a, myCommand->user_mat_b);
            trans_mat(myCommand->user_mat_a, myCommand->user_mat_b);
            break;
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
            //if (total_comma_in_a_row != 0 && noSpace[newSize - 1] != ','){
            //    total_comma_in_a_row--;
            //}
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

// if (comma_error_handler == 1) err_illegal_comma(), return 1;
//else if (comma_error_handler == 2) err_miss_comma(), return 1;
//else if (comma_error_handler == 3) err_consec_comma(), return 1;
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
*This function checks to see if the input in mat_b is a double (R)
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
void prompt_message(){ 
    printf("\nEnter the desired command and matrices with the correct syntax!:  (e.g., mul_mat mat_a, mat_b, mat_c):\n");
}
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

/* Adds two matrices and stores the result in MAT_C */
void add_mat(mat *MAT_A, mat *MAT_B, mat *MAT_C) {
    int i, j;
    for (i = 0; i < MAT_SIZE; i++) {
        for (j = 0; j < MAT_SIZE; j++) {
            MAT_C->matrix[i][j] = MAT_A->matrix[i][j] + MAT_B->matrix[i][j];
        }
    }
}

/* Subtracts MAT_B from MAT_A and stores the result in MAT_C */
void sub_mat(mat *MAT_A, mat *MAT_B, mat *MAT_C) {
    int i, j;
    for (i = 0; i < MAT_SIZE; i++) {
        for (j = 0; j < MAT_SIZE; j++) {
            MAT_C->matrix[i][j] = MAT_A->matrix[i][j] - MAT_B->matrix[i][j];
        }
    }
}

/* Multiplies two matrices and stores the result in MAT_C */
void mul_mat(mat *MAT_A, mat *MAT_B, mat *MAT_C) {
    mat result = { "RESULT", { {0.0} } };
    int i, j, k;
    for (i = 0; i < MAT_SIZE; i++) {
        for (j = 0; j < MAT_SIZE; j++) {
            for (k = 0; k < MAT_SIZE; k++) {
                result.matrix[i][j] += MAT_A->matrix[i][k] * MAT_B->matrix[k][j];
            }
        }
    }
    for (i = 0; i < MAT_SIZE; i++) {
        for (j = 0; j < MAT_SIZE; j++) {
            MAT_C->matrix[i][j] = result.matrix[i][j];
        }
    }
}

/* Multiplies a matrix by a scalar and stores the result in MAT_B */
void mul_scalar(mat *MAT_A, double num, mat *MAT_B) {
    int i, j;
    for (i = 0; i < MAT_SIZE; i++) {
        for (j = 0; j < MAT_SIZE; j++) {
            MAT_B->matrix[i][j] = MAT_A->matrix[i][j] * num;
        }
    }
}

/* Transposes MAT_A and stores the result in MAT_B */
void trans_mat(mat *MAT_A, mat *MAT_B) {
    mat result = { "RESULT", { {0.0} } };
    int i, j;
    for (i = 0; i < MAT_SIZE; i++) {
        for (j = 0; j < MAT_SIZE; j++) {
            result.matrix[i][j] = MAT_A->matrix[j][i];
        }
    }
    for (i = 0; i < MAT_SIZE; i++) {
        for (j = 0; j < MAT_SIZE; j++) {
            MAT_B->matrix[i][j] = result.matrix[i][j];
        }
    }
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
