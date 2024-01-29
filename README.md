# Matrix Calculator
 A fully functional 4x4 Matrix Calculator.

# Table of Contents
#### 1) Instructions on how to install, set up, and run the project.

#### 2) Usage:

    i) A brief guide about the available user input

    ii) Output

    iii) Errors

#### 3) Code examples & Tutorial

## Instructions
##### Step 1 -

    Clone the project to your IDE, using HTTPS / SSH / GitHub CLI.
    For example:
```bash
$ git clone https://github.com/gwchar2/Matrix-Calculator.git
```
    If you do not wish to do this through your IDE, you can can
    Open the command prompt terminal and navigate to your wanted repository, and clone the project to there.
```bash   
$ cd "Path to file here"
$ git clone https://github.com/gwchar2/Matrix-Calculator.git
```  
    
    Download the file physically to your computer via the "Download ZIP" option.    
    Extract the downloaded folder to your chosen repository.

##### Step 2 -

    After cloning the project or importing the project to a folder, you will now need to compile the files.
    This can be done by pressing the 'Run' button in your IDE. 
    OR
    Open the command prompt terminal and navigate to your repository, and make the makefile
```bash   
$ cd "Path to file here"
$ make
```   

##### Step 3 -

    Run the program.
```bash   
$ ./mainmat
```            

## Usage  
### Available User Input

##### A list of commands at the disposal of the user:

| Command | Output |
|----------|----------|
| print_mat MAT_A              |  Prints the matrix in a nice 4x4. |
| add_mat MAT_A , MAT_B , MAT_C    |   MAT_C = MAT_A + MAT_B |
| sub_mat MAT_A , MAT_B , MAT_C    |   MAT_C = MAT_A - MAT_B |
| mul_mat MAT_A , MAT_B , MAT_C    |   MAT_C = MAT_A * MAT_B |
| mul_scalar MAT_A , #R , MAT_B    |   MAT_B = MAT_A * (R Number)    |
| trans_mat MAT_A , MAT_B       |   MAT_B = Transpose(MAT_A)|
| stop                         |   Stops the program |


    ii) Output

    iii) Errorst
