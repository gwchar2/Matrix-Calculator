
#include "mymat.h"

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
