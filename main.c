#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

#define RUNS 30

/*
    Assembly version of the image conversion function
    @params input: pointer to the first element of a 2D array of doubles representing grayscale pixel values (0.0 to 1.0)
    @params output: pointer to the first element of a 2D array of integers to store converted pixel values (0 to 255)
    @params size: total number of elements in the image (rows * columns)
    @params _255: integer value 255 used for scaling
*/ 
extern void imgCvtGrayDoubleToInt(double* input, int* output, int size, int _255);


/*  C version of the image conversion function
    @params row: number of rows in the image
    @params col: number of columns in the image
    @params input: 2D array of doubles representing grayscale pixel values (0.0 to 1.0)
    @params output: 2D array of integers to store converted pixel values (0 to 255)
    @params _255: integer value 255 used for scaling
*/
void c_vimgCvtGrayDoubleToInt(int row, int col, double input[row][col], int output[row][col], int _255){
    for (int i = 0 ; i < row ; i++) {
        for (int j = 0 ; j < col ; j++) {
            output[i][j] = (int)(input[i][j] * _255 + 0.5); // Added rounding
        }
    }
}

/*
    Function to generate random image data
    @params rows: number of rows in the image
    @params columns: number of columns in the image
    @params imgData: 2D array of doubles to store generated pixel values (0.0 to 1.0)
*/
void generate_data(int rows, int columns, double imgData[rows][columns]){
    for (int i = 0 ; i < rows ; i++) {
        for (int j = 0 ; j < columns ; j++) {
            imgData[i][j] = (double)rand() / RAND_MAX;
        }
    }
}

/*
    Function to compare assembly and C outputs
    @params rows: number of rows in the image
    @params columns: number of columns in the image
    @params asmOutput: 2D array of integers from assembly conversion
    @params cOutput: 2D array of integers from C conversion
*/ 
bool output_comparison_test(int rows, int columns, int asmOutput[rows][columns], int cOutput[rows][columns]){
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            if (asmOutput[i][j] != cOutput[i][j]) {
                printf("Mismatch at Row %d, Col %d: ASM=%d, C=%d\n",
                       i, j, asmOutput[i][j], cOutput[i][j]);
                return false;
            }
        }
    }
    return true;
}

/*
    Function to compare performance between assembly and C implementations
    @params rows: number of rows in the image
    @params columns: number of columns in the image
*/
void performance_comparison_test(int rows, int columns){

    printf("=====================================\n");
    printf("Image Size: %d x %d\n", rows, columns);

    /* Allocate on heap to avoid stack overflow */
    double (*imgData)[columns] = malloc(sizeof(double) * rows * columns);
    int (*asmOutput)[columns] = malloc(sizeof(int) * rows * columns);
    int (*cOutput)[columns] = malloc(sizeof(int) * rows * columns);

    if (!imgData || !asmOutput || !cOutput) {
        printf("Memory allocation failed!\n");
        return;
    }

    generate_data(rows, columns, imgData);

    double total_time = 0.0;

    for (int i = 0; i < RUNS; i++) {
        clock_t start = clock();
        imgCvtGrayDoubleToInt(&imgData[0][0], &asmOutput[0][0], rows * columns, 255);
        clock_t end = clock();
        total_time += (double)(end - start) / CLOCKS_PER_SEC;
    }

    double avg_time = total_time / RUNS;

    /* Correctness check */
    c_vimgCvtGrayDoubleToInt(rows, columns, imgData, cOutput, 255);
    bool pass = output_comparison_test(rows, columns, asmOutput, cOutput);

    printf("Average ASM Time (30 runs): %f seconds\n", avg_time);
    printf("Correctness Check: %s\n\n", pass ? "PASSED" : "FAILED");

    free(imgData);
    free(asmOutput);
    free(cOutput);
}

int main() {

    srand(time(NULL));

    performance_comparison_test(10, 10);
    performance_comparison_test(100, 100);
    performance_comparison_test(1000, 1000);

    int wait;
    scanf("%d", &wait);

    return 0;
}
