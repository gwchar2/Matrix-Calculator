#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "valid.c"

tאokenized_line* analayze(char *input){
    tokenized_line* curr_line = (tokenized_line*)malloc(sizeof(tokenized_line));
    char* curr_word = strtok(input, " \t\n\r\f\v");
    if (curr_word == NULL){
        return NULL;

        }
    curr_line -> op = isValidMatrixCommand(curr_word);
    tokenized_argument (curr_line); 

}
int tokenized_argument(tokenized_line *curr_line){
    char* curr_arg = NULL; 
    char*  rest_of_line = strtok(NULL, "");
    if (rest_of_line == NULL){
        return 0;
    }
    char* first_arg = strtok (rest_of_line, " ,\t\n\r\f\v");
     
    char* second_arg = strtok (rest_of_line, " ,\t\n\r\f\v");

    char* third_arg = strtok (rest_of_line, " ,\t\n\r\f\v");

   // commaCheck();-- to be implemented
    // check rest_of_line check ech arguments- type an
}