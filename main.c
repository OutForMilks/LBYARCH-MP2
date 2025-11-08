#include <stdio.h>

int main() { // take in inputs here
    int rows, columns; // size of matrix
    scanf("%d %d", &rows, &columns); // user input (first line)

    double imgData[rows][columns]; // store the image pixel data

    for (int i = 0 ; i < rows ; i++) { // loop through rows
        for (int j = 0 ; j < columns ; j++) { // loop through columns per row
            scanf("%lf", &imgData[i][j]); // put the input in its respective spot in the array
        }
    }

    return 0;
}