/* USER INTERACTION AND MAIN HERE */
#include "mymat.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stddef.h>
#include <unistd.h>


int onStart(cmd *myCommand,mat **matrices);
void activate_command(cmd *myCommand);
int check_read_mat(cmd *myCommand,char *pointer,char *inputCopy,mat **matrices);
int main(){
    mat MAT_A = {"MAT_A",{{1, 2, 3, 4}, {5, 1, 2, 3}, {4, 5, 1, 2}, {3, 4, 5, 1}} };
    mat MAT_B = {"MAT_B",{{2, 3, 4, 5}, {1, 2, 3, 4}, {5, 1, 2, 3}, {4, 5, 1, 2}} };
    mat MAT_C = {"MAT_C",{ {0.0} } };
    mat MAT_D = {"MAT_D",{ {0.0} } };
    mat MAT_E = {"MAT_E",{ {0.0} } };
    mat MAT_F = {"MAT_F",{ {0.0} } };
    mat *matrices[6] = {&MAT_A, &MAT_B, &MAT_C, &MAT_D, &MAT_E, &MAT_F};        /* An array of pointers to the pre-defined matrices, for easier communication */
    

    /* initialize all the pointers in myCommand with a NULL */
    cmd myCommand = {
    .user_input = NULL,
    .user_mat_a = NULL,                
    .user_mat_b = NULL,
    .user_mat_c = NULL,
    .read_scalars = {0},
    };

    welcome(); /* Calls for welcome message */
    while(1){
        if (onStart(&myCommand,matrices) != 1){
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

int onStart(cmd *myCommand,mat **matrices){
    char *pointer;                                                            /* A character pointer that helps deal with the input */
	size_t len;                                                               /* Length of the array */
    ssize_t read;                                                             /* This variable will store how many values were read in getline() including null terminator */
	len = 0;                                                                  /* This variable will store the total size of the input recieved */
    char *inputCopy = NULL;
    int comma_error_handler;
    prompt_message();                                                         /* prompts the user for input */ 

    /* Get the input from the user into 'myCommand->user_input' */
    if ((read = getline(&(myCommand->user_input), &len, stdin)) == -1) {
        /* If the last line in stdin was not "stop" , frees the allocated memory & calls for err_no_stop() */
        if (strcmp(myCommand->user_input, "stop") != 0){
            err_no_stop();
        }      
    }

    inputCopy = (char *)malloc(len);                                          /* Copies the input to a trash string */
    strcpy(inputCopy,myCommand->user_input);

    pointer = strtok(inputCopy, DELIMITER_2); 

    /* Analyze the command segment & go to the next token */
    CHECK_AND_FREE(get_Command(pointer,myCommand));

    if (myCommand->user_cmd == READ_MAT){
        CHECK_AND_FREE(check_read_mat(myCommand,pointer,inputCopy,matrices));
    }

    comma_error_handler = comma_handler(myCommand,read);                        /* Stores the error value received from comma_handler*/
    pointer = strtok(NULL, DELIMETER_1);

    /* Analyze the first matrix variable & go to the next token  */
    CHECK_AND_FREE(get_mat_A(pointer,myCommand,matrices,comma_error_handler));
    pointer = strtok(NULL, DELIMETER_1);  

    /* Analyze the second matrix variable & go to the next token */
    CHECK_AND_FREE(get_mat_B(pointer,myCommand,matrices,comma_error_handler));  
    pointer = strtok(NULL, DELIMETER_1);  

    /* Analyze the third matrix variable & go to the next token */
    CHECK_AND_FREE(get_mat_C(pointer,myCommand,matrices,comma_error_handler));
    pointer = strtok(NULL,DELIMITER_2);

    /* FIFTH VARIABLE ---- EXTRA TEXT ----/ */
    if (pointer != NULL) {                                                      /* If the point has not reached a NULL, clearly there is text left! */
        err_text();                                                             /* NO COMMAND needs 4 variables...so return the extra txt error */
        MY_FREE();    
        return 1;
    }

    /* If the command and variables are ok, handle the comma error before activating the command. */
    CHECK_AND_FREE(handle_comma_error(comma_error_handler));

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



int check_read_mat(cmd *myCommand,char *pointer,char *inputCopy,mat **matrices){
    pointer = strtok(NULL, DELIMITER_2); 
    size_t pointer_size;

    /* Sets the matrix for reading */
    if (get_mat_A(pointer, myCommand, matrices,0)){
        return 1;
    }

    /* Cuts to the remainder of the input */
    pointer = strtok(NULL, "\n"); 
    pointer_size = strlen(pointer);

    if (pointer == NULL){
        err_miss_argument();
        return 1;
    }
    
    

    return 2; /* If its correct, returns 2. */
}















