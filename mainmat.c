/* USER INTERACTION AND MAIN HERE */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAT_SIZE 4
#define MAT_NAME_SIZE 6
/* A matrix structure with a name and default size of 4x4. */
typedef struct{
    const char name[MAT_NAME_SIZE];
    float matrix[MAT_SIZE][MAT_SIZE];
} mat; 

void read_mat(mat *MAT_A);
void print_mat(mat *matrix);
void add_mat(mat *MAT_A, mat *MAT_B, mat *MAT_C);
void sub_mat(mat *MAT_A, mat *MAT_B, mat *MAT_C);
void mul_mat(mat *MAT_A, mat *MAT_B, mat *MAT_C);
void mul_scalar(mat *MAT_A, float num, mat *MAT_B);
void trans_mat(mat *MAT_A, mat *MAT_B);
void stop();


int main(){
    mat MAT_A = {"MAT_A",{{1, 2, 3, 4}, {5, 1, 2, 3}, {4, 5, 1, 2}, {3, 4, 5, 1}} };
    mat MAT_B = {"MAT_B",{{2, 3, 4, 5}, {1, 2, 3, 4}, {5, 1, 2, 3}, {4, 5, 1, 2}} };
    mat MAT_C = {"MAT_C",{ {0.0} } };
    mat MAT_D = {"MAT_D",{ {0.0} } };
    mat MAT_E = {"MAT_E",{ {0.0} } };
    mat MAT_F = {"MAT_F",{ {0.0} } };
    trans_mat(&MAT_A,&MAT_A);
    print_mat(&MAT_A);

}

void print_mat(mat *matrix) {
    int i,j;
    printf("Printing %s:\n", matrix->name); /* NEED TO REMOVE THIS LINE !!*/
    for (i = 0; i < MAT_SIZE; i++) {
        for (j = 0; j < MAT_SIZE; j++) {
            printf("%.2f\t", matrix->matrix[i][j]);
        }
        printf("\n");
    }
}
void add_mat(mat *MAT_A, mat *MAT_B, mat *MAT_C){
    int i,j;
    for (i = 0; i < MAT_SIZE; i++) {
        for (j = 0; j < MAT_SIZE; j++) {
            MAT_C->matrix[i][j] = MAT_A->matrix[i][j] + MAT_B->matrix[i][j];
        }
    }
}
void sub_mat(mat *MAT_A, mat *MAT_B, mat *MAT_C){
    int i,j;
    for (i = 0; i < MAT_SIZE; i++) {
        for (j = 0; j < MAT_SIZE; j++) {
            MAT_C->matrix[i][j] = MAT_A->matrix[i][j] - MAT_B->matrix[i][j];
        }
    }
}
void mul_mat(mat *MAT_A, mat *MAT_B, mat *MAT_C){
    mat result = { "RESULT", { {0.0} } };
    int i,j,k;
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
void mul_scalar(mat *MAT_A, float num, mat *MAT_B){
    int i,j;
    for (i = 0; i < MAT_SIZE; i++) {
        for (j = 0; j < MAT_SIZE; j++) {
            MAT_B->matrix[i][j] = MAT_A->matrix[i][j] * num;
        }
    }
}
void trans_mat(mat *MAT_A, mat *MAT_B){
    mat results = { "RESULT", { {0.0} } };
    int i,j;
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

void stop(){
    /* msg_stop();*/
    exit(0);
}
void read_mat(mat *MAT_A){
    ;
}
