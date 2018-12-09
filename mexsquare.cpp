#include "mex.h"

void mexFunction( int nlhs, mxArray *plhs[], // for output
                  int nrhs, const mxArray *prhs[] ) // for input
{   
    printf("~~~~~~~~~~ Processing in Mex File ~~~~~~~~~~\n");
    // Get Input Data Information
    int ndim = mxGetNumberOfDimensions(prhs[0]);
    const int* dimArray = mxGetDimensions(prhs[0]);    
    const int nrow = dimArray[0];
    const int ncol = dimArray[1];
    const int ndepth = dimArray[2];
    printf("Input in mexfile is %d x %d x %d matrix: \n", nrow, ncol, ndepth);

    // Read Input Data
    // *Note that mex file read the input data as 1D vector
    double* pr0 = (double*)mxGetPr(prhs[0]);
    double X[nrow][ncol][ndepth];
    int pr0IDX = 0;
    for(int k=0; k<ndepth; k++){
        printf("depth %d \n", k);
        for(int i=0; i<nrow; i++){
            for(int j=0; j<ncol; j++){
                // index of 1D vector should be shifted by number of pre-dimension as:
                pr0IDX = i + j * nrow + k * (nrow * ncol);
                X[i][j][k] = pr0[pr0IDX];
                printf("%f ", X[i][j][k]);
            }
            printf("\n");
        }
    }
    
    // Square of Input
    printf("\n");
    double output[nrow][ncol][ndepth];
    printf("Square of input: \n");
    for(int k=0; k<ndepth; k++){ 
        printf("depth %d \n", k);
        for(int i=0; i<nrow; i++){
            for(int j=0; j<ncol; j++){
                output[i][j][k] = X[i][j][k]*X[i][j][k];
                printf("%f ", output[i][j][k]);
            }
            printf("\n");
        }
    }
    
    // Definition for Output Data 
    int dims[ndim];
    dims[0] = nrow;
    dims[1] = ncol;
    dims[2] = ndepth;
    plhs[0] = mxCreateNumericArray(ndim, dims, mxDOUBLE_CLASS, mxREAL); // output array
    double* pl0 = (double*)mxGetPr(plhs[0]);
    
    int pl0IDX = 0;
    for(int k=0; k<ndepth; k++){ 
        for(int i=0; i<nrow; i++){
            for(int j=0; j<ncol; j++){    
                // index of 1D vector should be shifted by number of pre-dimension as:
                pl0IDX = i + j * nrow + k * (nrow * ncol);  
                pl0[pl0IDX] = output[i][j][k]; 
            }
        }
    }
    
    printf("~~~~~~~~~~ Done ~~~~~~~~~~\n");
    printf("\n");
    
}