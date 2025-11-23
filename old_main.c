#include <stdio.h>

extern void imgCvtGrayDoubleToInt(double* input, int* output, int size, int _255);

int main() {
    // take in inputs here
    int rows, columns; // size of matrix
    printf("Row:");
    scanf("%d", &rows); // user input (first line)
    printf("Col:");
    scanf("%d", &columns);

    double imgData[rows][columns]; // store the image pixel data
    int convertedOutput[rows][columns]; 

    for (int i = 0 ; i < rows ; i++) { // loop through rows
        for (int j = 0 ; j < columns ; j++) { // loop through columns per row
        	printf("Row: %d | Col %d | Input: ", i, j);
            scanf("%lf", &imgData[i][j]); // put the input in its respective spot in the array

            if (imgData[i][j] < 0 || imgData[i][j] > 1) { // input validity checking
                printf("Array has an invalid input. Inputs must be between 0 and 1.");
                return 0;
            }
        }
    }

    int size = rows * columns;

    imgCvtGrayDoubleToInt(&imgData[0][0], &convertedOutput[0][0], size); // assembly call here

    // print output here
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            printf("%d ", convertedOutput[i][j]);
        }
           printf("\n");
    }
    int wait;
    printf("\nEnter 1 to end: ");
    scanf("%d", &wait);
	
    return 0;
}
