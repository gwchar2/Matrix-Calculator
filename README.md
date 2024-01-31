# Matrix Calculator
 A fully functional user-interactive 4x4 Matrix Calculator.

# Table of Contents
#### 1) Instructions on how to install, set up, and run the project.

#### 2) Usage:
- A brief guide about the available user input & output.

- Errors.

## Instructions
##### Step 1 -

 - Clone the project to your IDE, using HTTPS / SSH / GitHub CLI.
   For example:
 ```bash
 $ git clone https://github.com/gwchar2/Matrix-Calculator.git
 ```
 - If you do not wish to do this through your IDE, you can can Open the command prompt terminal ,navigate to your wanted repository, and clone the project to there.
 ```bash   
 $ cd "Path to file here"
 $ git clone https://github.com/gwchar2/Matrix-Calculator.git
 ```  
    
   You can also download the file physically to your computer via the "Download ZIP" option.    
 - Extract the downloaded folder to your chosen repository.

##### Step 2 -

 - After cloning the project or importing the project to a folder, you will now need to compile the files.
   This can be done by pressing the 'Run' button in your IDE. 
    OR
 - Open the command prompt terminal and navigate to your repository
 ```bash   
 $ cd "Path to file here"
 ```
 - If the file multimat is not in the folder, run the following command. If it is in the folder, you can skip this step.
 ```bash
 $ make
 ```   

##### Step 3 -

 - Run the program.
 ```bash   
 $ ./mainmat
 ```            

## Usage  
### Available User Input
##### A list of variables at the disposal of the user:
The user can choose between 6 different matrices.
Please use there exact name, or else the program will not work.
MAT_A, MAT_B, MAT_C, MAT_D, MAT_E, MAT_F

####### *Please notice that the matrices in the table below are meerly for example.
##### A list of commands at the disposal of the user:

| Command | Output |
|----------|----------|
| read_mat MAT_A, [up to 16 doubles seperated with commas] | Inputs to the wanted Matrix |
| print_mat MAT_A              |  Prints the matrix in a nice 4x4. |
| add_mat MAT_A , MAT_B , MAT_C    |   MAT_C = MAT_A + MAT_B |
| sub_mat MAT_A , MAT_B , MAT_C    |   MAT_C = MAT_A - MAT_B |
| mul_mat MAT_A , MAT_B , MAT_C    |   MAT_C = MAT_A * MAT_B |
| mul_scalar MAT_A , #R , MAT_B    |   MAT_B = MAT_A * (R Number)    |
| trans_mat MAT_A , MAT_B       |   MAT_B = Transpose(MAT_A)|
| stop                         |   Stops the program |

PLEASE ENTER THE CORRECT COMMAND NAME AND AMOUNT OF VARIABLES ! 
##### Note:
- There are exactly 6 matrices for your disposal. MAT_A -> MAT_F
- All the matrices are initiated as zero matrices. If you want to add or initiate them with different values, use the read_mat command.
- The program will not automatically print the matrices after changing them. If you want to print them you can use the print_mat command.
- The program will only stop with the stop command.

### Errors
These errors will appear when you did not enter the correct command name, name of variables, variable type, amount of variables or the correct amount of commas.
| Output | Error |
|----------|----------|
|Missing argument| You did not enter all the variables |
|Undefined matrix name| Wrong matrix name |
|Undefined command name| Wrong command name |
|Argument is not a real number| You did not enter a R type number for read_mat |
|Extraneous text after end of command| To many arguments! |
|Missing comma| You are missing a comma in the syntax |
|Illegal comma| To many commas in the syntax |
|Multiple consecutive commas| Two or more commas in a row |
|Argument is not a scalar| You did not enter a scalar for mul_scalar|



