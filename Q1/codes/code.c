#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "libs/matfun.h"
#include "libs/geofun.h"

// Updated point_gen to accept matrix pointers (double**)
void point_gen(FILE *fptr, double **P, double **Q, int m, int n, double r1, double r2) {
    // Internal division point formula: ((r2 * P) + (r1 * Q)) / (r1 + r2)
    double sum_ratio = r1 + r2;
    double **internal_point = Matadd(Matscale(P, m, n, r2), Matscale(Q, m, n, r1), m, n);
    internal_point = Matscale(internal_point, m, n, 1 / sum_ratio);  // Scale result

    printf("Internal Division Point: %lf, %lf, %lf\n", internal_point[0][0], internal_point[1][0], internal_point[2][0]);
    fprintf(fptr, "%lf,%lf,%lf\n", internal_point[0][0], internal_point[1][0], internal_point[2][0]);
    freeMat(internal_point, m);  // Free the allocated memory

    // External division point formula: ((r2 * P) - (r1 * Q)) / (r2 - r1)
    double diff_ratio = r2 - r1;
    double **external_point = Matadd(Matscale(P, m, n, r2), Matscale(Q, m, n, -r1), m, n);
    external_point = Matscale(external_point, m, n, 1 / diff_ratio);  // Scale result

    printf("External Division Point: %lf, %lf, %lf\n", external_point[0][0], external_point[1][0], external_point[2][0]);
    fprintf(fptr, "%lf,%lf,%lf\n", external_point[0][0], external_point[1][0], external_point[2][0]);
    freeMat(external_point, m);  // Free the allocated memory
}

int main() {
    // Coordinates of the given points P(1, -2, 3) and Q(3, 4, -5)
    int m = 3, n = 1;
    double **P = createMat(m, n);  // Create matrix for point P
    double **Q = createMat(m, n);  // Create matrix for point Q
    P[0][0] = 1; P[1][0] = -2; P[2][0] = 3;
    Q[0][0] = 3; Q[1][0] = 4; Q[2][0] = -5;

    // Ratios for division
    double r1 = 2.0, r2 = 3.0;

    // Open the file for writing
    FILE *fptr;
    fptr = fopen("coordinates.txt", "w");
    if (fptr == NULL) {
        printf("Error opening file!\n");
        return 1;
    }

    // Generate the internal and external division points
    fprintf(fptr, "Internal Division Points:\n");
    point_gen(fptr, P, Q, m, n, r1, r2);  // Call with r1 and r2

    fprintf(fptr, "External Division Points:\n");
    point_gen(fptr, P, Q, m, n, r1, r2);  // Call with r1 and r2 for external division

    fclose(fptr);  // Close the file

    // Free allocated memory
    freeMat(P, m);
    freeMat(Q, m);

    return 0;
}

