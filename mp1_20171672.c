/*-------------------------------------*/


/*-------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int main(int argc, char *argv[]){

    if(argc != 3){
        printf("usage: %s input_filename algorithm_index.\n", argv[0]);
        return 0;
    }

    clock_t start_time = clock();

    char input_filename[200];
    strcpy(input_filename, argv[1]);

    int algorithm_index = atoi(argv[2]);
    int num_rows, num_cols;
    int i, j;

    FILE *infile;
    infile = fopen(input_filename, "r");
    if(infile == NULL){
        printf("Error: input file cannot be opened.\n");
        return 0;
    }

    /*------- Get data from the input file -------*/


    fscanf(infile, "%d %d\n", &num_rows, &num_cols);
    int array[num_rows][num_cols];

    for(i = 0; i < num_rows; i++){
        for(j = 0; j < num_cols; j++){
            fscanf(infile, "%d ", &array[i][j]);
        }
        fscanf(infile, "\n");
    }

    fclose (infile);



    int currentSum = 0, maxSum = 0, maxNeg = 0;
    int isAllNegative = 1;
    int start_i, start_j, end_i, end_j;
    int lineSum[num_rows];
    int sums[num_rows][num_cols];


    switch(algorithm_index){
      case 1:
        /*------- O(n^6) algorithm -------*/

        /*------- All numbers are negative case --------*/

        maxNeg = array[0][0];
        for(i = 0; i < num_rows; i++){
            for(j = 0; j < num_cols; j++){
                if(array[i][j] > 0) {
                    isAllNegative = 0;
                }
                else if(array[i][j] > maxNeg){
                  maxNeg = array[i][j];
                }
            }
        }

        if(isAllNegative == 1){
            maxSum = maxNeg; // If all elements are negative
            break;
        }

        for(start_i = 0; start_i < num_rows; start_i++){
            for(start_j = 0; start_j < num_cols; start_j++){

                for(end_i = start_i; end_i < num_rows; end_i++){
                    for(end_j = start_j; end_j < num_cols; end_j++){
                        
                        for(i = start_i; i <= end_i; i++){
                            for(j = start_j; j <= end_j; j++){
                                currentSum += array[i][j]; // Get the sum of elements starting from (start_i, start_j) to (end_i, end_j)
                            }
                        }
                        if(currentSum > maxSum) {
                            maxSum = currentSum; // Compare and update maxSum
                        }

                        currentSum = 0;

                    }
                }
            }
        }

        break;

          
      case 2:
        /*------- O(n^4) algorithm -------*/


        /*------- All numbers are negative case --------*/

        maxNeg = array[0][0];
        for(i = 0; i < num_rows; i++){
            for(j = 0; j < num_cols; j++){
                if(array[i][j] > 0) {
                    isAllNegative = 0;
                }
                else if(array[i][j] > maxNeg){
                  maxNeg = array[i][j];
                }
            }
        }

        if(isAllNegative == 1){
            maxSum = maxNeg; // If all elements are negative 
            break;
        }

        /*------- Using sum array of submatrix -------*/
        for(i = 0; i < num_rows; i++){
            for(j = 0; j < num_cols; j++){ // Get sums of elements in advance according to start points and end points
                if(i == 0 && j ==0) sums[i][j] = array[i][j]; // (0,0) case
                else if(j ==0) sums[i][j] = sums[i-1][j] + array[i][j]; // Sum of that row elements 
                else if(i ==0) sums[i][j] = sums[i][j-1] + array[i][j]; // Sum of that column elements
                else sums[i][j] = sums[i-1][j] + sums[i][j-1] - sums[i-1][j-1] + array[i][j]; // Getting the sum of the submatrix preventing the duplicates of sums

            }
        }

        for(start_i = 0; start_i < num_rows; start_i++){
            for(start_j = 0; start_j < num_cols; start_j++){

                for(end_i = start_i; end_i < num_rows; end_i++){
                    for(end_j = start_j; end_j < num_cols; end_j++){
                        if(start_i == 0 && start_j ==0) currentSum = sums[end_i][end_j]; // S1
                        else if(start_i == 0) currentSum = sums[end_i][end_j] - sums[end_i][start_j -1]; // S1 - S2
                        else if(start_j == 0) currentSum = sums[end_i][end_j] - sums[start_i-1][end_j]; // S1 - S3
                        else currentSum = sums[end_i][end_j] - sums[end_i][start_j-1] - sums[start_i-1][end_j] + sums[start_i-1][start_j-1]; // currentSum = S1 - S2 - S3 + S4

                        if(currentSum > maxSum) maxSum = currentSum; // Compare and update maxSum

                        currentSum = 0;
                    }
                }
                currentSum = 0;
            }
        }
        break;

      case 3:
        /*------- O(n^3) algorithm -------*/


        /*------- All numbers are negative case --------*/

        maxNeg = array[0][0];
        for(i = 0; i < num_rows; i++){
            for(j = 0; j < num_cols; j++){
                if(array[i][j] > 0) {
                    isAllNegative = 0;
                }
                else if(array[i][j] > maxNeg){
                  maxNeg = array[i][j];
                }
            }
        }

        if(isAllNegative == 1){
            maxSum = maxNeg;
            break;
        }

        /*------ Dynamic Programming -------*/

        for(start_i = 0; start_i < num_rows; start_i++){

            for(int t = 0; t < num_rows; t++) lineSum[t] = 0; // Initialize sum of each row
    
            for(start_j = start_i; start_j < num_cols; start_j++){

                for(i = 0; i < num_rows; i++){
                    lineSum[i] += array[i][start_j]; // Sum elements of that row and put into the lineSum
                }
                
                for(i = 0; i < num_rows; i++){
                    currentSum += lineSum[i];
                    if(currentSum < 0) currentSum = 0; // If it's negative, throw it away and start from this point
                    else if(currentSum > maxSum) maxSum = currentSum; // Update max sum
                }

                currentSum = 0;
            }
        }

        break;

      default:
        printf("You should choose 1 or 2 or 3 algorithm index.\n");
        return 0;
    }

    clock_t end_time = clock();

    
    /*------- Context of output file (result_inputfilename) -------*/
    FILE *resultfile;
    char result_filename[200] = "result_";
    strcat(result_filename, input_filename);

    resultfile = fopen(result_filename, "w");
    
    fprintf(resultfile, "%s\n", input_filename); //input file name
    fprintf(resultfile, "%d\n", algorithm_index); // algorithm index
    fprintf(resultfile, "%d\n", num_rows); // # of rows of the input
    fprintf(resultfile, "%d\n", num_cols); // # of cols of the input
    fprintf(resultfile, "%d\n", maxSum); // sum of the maximum sum subrectangle
    fprintf(resultfile, "%.2f\n", (double)(end_time - start_time)); // running time in milliseconds  

    fclose(resultfile);

    return 0;

}
