#include <stdio.h>

#define DIMENSIONS 3 // For 3D points

// Function to find division points internally and externally
void get_division_points(double *internal, double *external) {
    // Coordinates of the given points
    double x1 = 1.0, y1 = -2.0, z1 = 3.0;
    double x2 = 3.0, y2 = 4.0, z2 = -5.0;
    
    // Ratio for division
    double m = 2.0, n = 3.0;

    // Internal division point calculation
    internal[0] = (m * x2 + n * x1) / (m + n);
    internal[1] = (m * y2 + n * y1) / (m + n);
    internal[2] = (m * z2 + n * z1) / (m + n);

    // External division point calculation
    external[0] = (m * x2 - n * x1) / (m - n);
    external[1] = (m * y2 - n * y1) / (m - n);
    external[2] = (m * z2 - n * z1) / (m - n);
}

int main() {
    // Arrays to store the division points
    double internal[DIMENSIONS];
    double external[DIMENSIONS];

    // Get the division points
    get_division_points(internal, external);

    // Print the results
    printf("Internal Division Point: (%.2f, %.2f, %.2f)\n", internal[0], internal[1], internal[2]);
    printf("External Division Point: (%.2f, %.2f, %.2f)\n", external[0], external[1], external[2]);

    return 0;
}

