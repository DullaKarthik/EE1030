#include <stdio.h>
#include <math.h>

#define MAX_SIZE 100  // Maximum matrix size

// Function Prototypes
void collect_matrix(double matrix[MAX_SIZE][MAX_SIZE], int size);
void initialize_identity_matrix(double matrix[MAX_SIZE][MAX_SIZE], int size);
void qr_decompose(double matrix[MAX_SIZE][MAX_SIZE], int size, double Q[MAX_SIZE][MAX_SIZE], double R[MAX_SIZE][MAX_SIZE]);
void multiply_matrices(double mat1[MAX_SIZE][MAX_SIZE], double mat2[MAX_SIZE][MAX_SIZE], double result[MAX_SIZE][MAX_SIZE], int size);
void qr_algorithm(double matrix[MAX_SIZE][MAX_SIZE], double T[MAX_SIZE][MAX_SIZE], int size, int max_steps);
void print_eigenvalues(double T[MAX_SIZE][MAX_SIZE], int size);

// Main function
int main() {
    int size;
    double matrix[MAX_SIZE][MAX_SIZE] = {0};
    double T[MAX_SIZE][MAX_SIZE] = {0};

    printf("Enter the size of the square matrix (max %d): ", MAX_SIZE);
    scanf("%d", &size);

    if (size > MAX_SIZE || size <= 0) {
        printf("Invalid matrix size.\n");
        return 1;
    }

    collect_matrix(matrix, size);

    qr_algorithm(matrix, T, size, 100);

    print_eigenvalues(T, size);

    return 0;
}

// Function Definitions

// Collects input matrix from the user
void collect_matrix(double matrix[MAX_SIZE][MAX_SIZE], int size) {
    printf("Enter each value of the %dx%d matrix:\n", size, size);
    for (int row = 0; row < size; row++) {
        for (int col = 0; col < size; col++) {
            printf("Element [%d][%d]: ", row + 1, col + 1);
            scanf("%lf", &matrix[row][col]);
        }
    }
}

// Initializes a matrix to be an identity matrix
void initialize_identity_matrix(double matrix[MAX_SIZE][MAX_SIZE], int size) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            matrix[i][j] = (i == j) ? 1.0 : 0.0;
        }
    }
}

// Performs QR decomposition using Gram-Schmidt orthogonalization
void qr_decompose(double matrix[MAX_SIZE][MAX_SIZE], int size, double Q[MAX_SIZE][MAX_SIZE], double R[MAX_SIZE][MAX_SIZE]) {
    for (int col = 0; col < size; col++) {
        double v[MAX_SIZE] = {0};

        // Copy column of matrix into vector v
        for (int row = 0; row < size; row++) {
            v[row] = matrix[row][col];
        }

        // Project onto previous Q columns
        for (int prev_col = 0; prev_col < col; prev_col++) {
            R[prev_col][col] = 0.0;
            for (int row = 0; row < size; row++) {
                R[prev_col][col] += Q[row][prev_col] * v[row];
            }
            for (int row = 0; row < size; row++) {
                v[row] -= R[prev_col][col] * Q[row][prev_col];
            }
        }

        // Normalize vector v
        R[col][col] = 0.0;
        for (int row = 0; row < size; row++) {
            R[col][col] += v[row] * v[row];
        }
        R[col][col] = sqrt(R[col][col]);

        for (int row = 0; row < size; row++) {
            Q[row][col] = (R[col][col] != 0) ? v[row] / R[col][col] : 0.0;
        }
    }
}

// Multiplies two matrices and stores the result
void multiply_matrices(double mat1[MAX_SIZE][MAX_SIZE], double mat2[MAX_SIZE][MAX_SIZE], double result[MAX_SIZE][MAX_SIZE], int size) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            result[i][j] = 0.0;
            for (int k = 0; k < size; k++) {
                result[i][j] += mat1[i][k] * mat2[k][j];
            }
        }
    }
}

// Executes the QR algorithm for Schur decomposition
void qr_algorithm(double matrix[MAX_SIZE][MAX_SIZE], double T[MAX_SIZE][MAX_SIZE], int size, int max_steps) {
    double Q[MAX_SIZE][MAX_SIZE] = {0};
    double R[MAX_SIZE][MAX_SIZE] = {0};
    double temp[MAX_SIZE][MAX_SIZE] = {0};

    for (int step = 0; step < max_steps; step++) {
        qr_decompose(matrix, size, Q, R);
        multiply_matrices(R, Q, matrix, size);
    }

    // Copy the result matrix into T
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            T[i][j] = matrix[i][j];
        }
    }
}
// Prints the eigenvalues from the diagonal of a triangular matrix
void print_eigenvalues(double T[MAX_SIZE][MAX_SIZE], int size) {
    printf("\nEigenvalues:\n");
    for (int i = 0; i < size; i++) {
        printf("%10.4f\n", T[i][i]);
    }
}
