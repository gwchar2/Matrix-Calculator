File list:
    []mainmat.c - /* USER INTERACTION AND MAIN HERE, SENDS THE INPUT TO FUNCTIONS IN []errorHandler FOR CHECKING, AND PRINTS ERRORS ACCORDING TO promptsAndPrints. CORRECT INPUT IS HANDLED BY FUNCTIONS IN mymat.c 
                   AND PRINTED BY promptsAndPrints */
    []mymat.c - /* ONLY THE MATHEMATICAL FUNCTIONS HERE */
    []mymat.h - /* HEADER FILE INCLUDES THE FOLLOWING: 
                 Declarations of functions, data structures, constants and other constructs that can be shared across multiple source files. 
                 The purpose of header files is to declare the interface of a module, allowing other modules to use its functionality without having access to the implementation details. */
    [x]promptsAndPrints - /* THIS FILE INCLUDES ALL THE PROMPTS TO USER AND ALL THE PRINT FUNCTIONS (HELPER FOR mainmat.c) */
    []errorHandler - /* FUNCTIONS THAT HANDLE ALL THE ERRORS POSSIBLE. CHECKS THE DATA AND INPUT FROM USER !!*/


Instructions:
[x] User input can arrive from stdin (text file OR input)
[x] After receiving the user input, and BEFORE doing commands according to it,
    must print the same text input (if it is correct), and only afterwords do the command.
    This way, when receiving a command from txt file - the command will be printed, and only than will the action be done.

[x] Every command must be received only in ONE LINE, and it must be COMPLETE. If it is not complete --> Error! (For example, mul_scalar Mat_A,MAT_B <-- Missing the scalar)

[x] The command and the first argument are seperated by spaces or tabs (one or more) 


[x] Between two arguments, there is only one ',' Before the ',' there can be an unlimited amount of spaces and/or tabs.

[x] A comma is NOT ALLOWED after the last argument!
[x] There can be an unlimited amount of tabs and/or spaces BEFORE the name of the command and AFTER the last argument.
[x] There can not be any useless characters after the last argument.
[x] The commands will be in lowercase letters only, and the arguments in capital letters only.
[x] The program prints a user-friendly message when it is ready to recieve the next command.
[x] INPUT STOPS ONLY WHEN USER TYPES "stop" EVEN IF ITS FROM FILE!!!
[x] If there is no 'stop' command from a file -> Prints an error message, and only than will the program terminate.




[x] Must use typedef to assign a matrix 'mat' which holds a 4x4 matrix. The numbers in the matrix are R values.
[x] Must initialize in the main function 6 matris' named MAT_A MAT_B MAT_C MAT_D MAT_E MAT_F
[x] When the program starts, must initialize them all with 0.




Functions that the matrix does:
Before the program initiates the function - it must print a user friendly message !!!
[]) Initiates variables in the matrix. read_mat MAT_A, 5, 6.253, -7, -200.5, 23
    If the list of variables includes LESS than 16 numbers - it will initialize the missing numbers to 0.
    If the list includes MORE Than 16 numbers - it will ignore the ones after the first 16.
[x] Prints the matrix. print_mat MAT_A - Prints it in a nice 4x4. %.2lf
[x] add_mat MAT_A,MAT_B,MAT_C    |   MAT_C = MAT_A+MAT_B
[x] sub_mat MAT_A,MAT_B,MAT_C    |   MAT_C = MAT_A-MAT_B
[x] mul_mat MAT_A,MAT_B,MAT_C    |   MAT_C = MAT_A*MAT_B
[x] mul_scalar MAT_A,#R,MAT_B    |   MAT_B = MAT_A*#R
[x] trans_mat MAT_A, MAT_B       |   MAT_B = Transpose(MAT_A)
[x] stop                         |   stops the program


IMPORTANT:
[x] Same matrix can be used twice in same function, for example: sub_mat MAT_A,MAT_B,MAT_A  | MAT_A = MAT_A-MAT_B
    Must be taken into consideration!


Example for bad commands, and error messages:
[]    read_mat MAT_G, 3.2, 8 - Undefined matrix name
[]    read_mat mat_a, 3.2, -5.3 - Undefined matrix name
[]   read_mat MAT_A, abc, 567 - Argument is not a real number
[]   read_mat MAT_A, 3, -4.2, 6, - Extraneous text after end of command
[]   read_mat MAT_A - Missing argument

[x]   trans_mat MAT_A MAT_B - Missing comma
[x]   sub_mat MAT_A, , MAT_B, MAT_C - Multiple consecutive commas

[x]   trans_mat MAT_B, MAT_C, MAT_D  - Extraneous text after end of command
[x]   mul_scalar MAT_A, MAT_B, MAT_C - Argument is not a scalar
[x]   stop now - Extraneous text after end of command
[x]   do_it MAT_A, MAT_B, MAT_C - Undefined command name
[x]   Add_Mat MAT_A, MAT_B, MAT_C - Undefined command name
[x]   print_mat, MAT_A - Illegal comma
[x]   mul_mat MAT_B, MAT_C - Missing argument


A correct list of commands:

read_mat MAT_A, 1, 2, 3, 3, 4, 5, 6, 7, 8, 9, 1, 2, 3, 4, 5, 6, 6, 6, 6, 6, 6
read_mat MAT_B, 1, 2.3456, -7.89
read_mat MAT_C, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16
read_mat MAT_B, 0


print_mat MAT_A
print_mat MAT_B
print_mat MAT_C
print_mat MAT_A
print_mat MAT_B
print_mat MAT_C
add_mat MAT_A, MAT_B, MAT_D
print_mat MAT_D
x sub_mat MAT_B, MAT_A, MAT_E
print_mat MAT_E
mul_mat MAT_B, MAT_C, MAT_F
print_mat MAT_F
mul_scalar MAT_A, 12.5, MAT_A
print_mat MAT_A
trans_mat MAT_C, MAT_C
print_mat MAT_C
print_mat MAT_B
mul_mat MAT_A,MAT_A,MAT_A
print_mat MAT_A
stop


