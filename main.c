#include <stdio.h>

extern void imgCvtGrayDoubleToInt(double* input, double* output, int size);

int main() {
    // take in inputs here
    int rows, columns; // size of matrix
    scanf("%d %d", &rows, &columns); // user input (first line)

    double imgData[rows][columns]; // store the image pixel data
    double convertedOutput[rows][columns]; // converted output. FIXME: change to int datatype; temporarily changed to double for testing

    for (int i = 0 ; i < rows ; i++) { // loop through rows
        for (int j = 0 ; j < columns ; j++) { // loop through columns per row
            scanf("%lf", &imgData[i][j]); // put the input in its respective spot in the array

            if (imgData[i][j] < 0 || imgData[i][j] > 1) { // input validity checking
                printf("Array has an invalid input. Inputs must be between 0 and 1.");
                return 0;
            }
        }
    }

    int size = rows * columns; // FIXME: size of entire array. might need rows and columns individually for actual project

    imgCvtGrayDoubleToInt(&imgData[0][0], &convertedOutput[0][0], size); // assembly call here

    // print output here
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            printf("%lf ", convertedOutput[i][j]); // FIXME: change to %d for actual project
        }
        printf("\n");
    }

    return 0;
}