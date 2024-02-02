/* USER INTERACTION AND MAIN HERE */
#include "mymat.h"
#include <string.h>

int onStart(cmd *myCommand,mat **matrices);
void activate_command(cmd *myCommand);
int main(){
	cmd myCommand = {NULL, INVALID, NULL, NULL, NULL, 0, {0}};	/* initialize all the pointers in myCommand with a NULL */
	mat *matrices[6];                                           /* An array of pointers to the pre-defined matrices, for easier communication */
    mat MAT_A = {"MAT_A",{{1, 2, 3, 4}, {5, 1, 2, 3}, {4, 5, 1, 2}, {3, 4, 5, 1}} };
    mat MAT_B = {"MAT_B",{{2, 3, 4, 5}, {1, 2, 3, 4}, {5, 1, 2, 3}, {4, 5, 1, 2}} };
    mat MAT_C = {"MAT_C",{ {0.0} } };
    mat MAT_D = {"MAT_D",{ {0.0} } };
    mat MAT_E = {"MAT_E",{ {0.0} } };
    mat MAT_F = {"MAT_F",{ {0.0} } };

	matrices[0] = &MAT_A;
    matrices[1] = &MAT_B;
    matrices[2] = &MAT_C;
    matrices[3] = &MAT_D;
    matrices[4] = &MAT_E;
    matrices[5] = &MAT_F;
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
    size_t read;                                                             /* This variable will store how many values were read in getline() including null terminator */
    char *inputCopy;
    int comma_error_handler;
	inputCopy = NULL;
	len = 0;                                                                  /* This variable will store the total size of the input recieved */

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
    pointer = strtok(inputCopy, DELIMETER_2); 

    /* Analyze the command segment & go to the next token */
    CHECK_AND_FREE(get_Command(pointer,myCommand));
    comma_error_handler = comma_handler(myCommand,read);                        /* Stores the error value received from comma_handler*/
    pointer = strtok(NULL, DELIMETER_1);

    /* Analyze the first matrix variable & go to the next token  */
    CHECK_AND_FREE(get_mat_A(pointer,myCommand,matrices,comma_error_handler));

/* CHECK_AND_FREE(c) IF c==0 returns, if c == 1 frees*/
    if (myCommand->user_cmd == READ_MAT){ /* If the command is READ_MAT, and we have a legal matrix, go to check_read_mat for the remainder of the user input */
        if(check_read_mat(myCommand,pointer) != 0)
            return 1; /* ADD FREE !!!!!*/
        else
            return 0;
    }  
                  
    pointer = strtok(NULL, DELIMETER_1);  

    /* Analyze the second matrix variable & go to the next token */
    CHECK_AND_FREE(get_mat_B(pointer,myCommand,matrices,comma_error_handler));  
    pointer = strtok(NULL, DELIMETER_1);  

    /* Analyze the third matrix variable & go to the next token */
    CHECK_AND_FREE(get_mat_C(pointer,myCommand,matrices,comma_error_handler));
    pointer = strtok(NULL,DELIMETER_2);

    /* FIFTH VARIABLE EXISTS ---- EXTRA TEXT ----/ */
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
        case READ_MAT:
            read_mat(myCommand->user_mat_a,myCommand->read_scalars);
            print_mat(myCommand->user_mat_a);
            break;
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
		default:
			break;
    }
}
















