#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <math.h>
#include <time.h>


//4 kernel functions
extern double asmkernel(const double* A, int n);
extern double xmmkernel(const double* A, int n);
extern double ymmkernel(const double* A, int n);
double ckernel(const double* A, int n);


void generate_values(double* A, int n);                              //generate random values
typedef double (*kernel_func)(const double*, int);                   //kernel functions
double benchmark_kernel(kernel_func kernel, const double* A, int n); //benchmark kernel for 30 runs


int main(int argc, char* argv[]) {

    //n = 2^20, 2^26, 2^30 for testing
    //n = my laptop couldnt handle 2^30 so just test it on your device

    //TO DO: boundary situations (ex: 1003)
    int testSizes[] = { 1 << 20,1 << 21,1 << 22 };
    int numTests = 3;

    for (int t = 0; t < numTests; t++) {
        int n = testSizes[t];

        //initialize memory allocation
        double* A = (double*)malloc(n * sizeof(double));

        //verify allocation
        if (A == NULL) {
			printf("Memory allocation failed at n = %d\n", n);
            return 1;
        }

        //generate values
        printf("\n----------------------------------------\n");
        printf("Testing n = %d\n", n);
        generate_values(A, n);


        //TO DO: implement asm, xmm, and ymm
        double time_c = benchmark_kernel(ckernel, A, n);
        double result_c = ckernel(A, n);


        //TO DO: display 4 results
		printf("\nC Results:\n");
        printf("ASUM: %.2f\n", result_c);
        printf("Average Time: %.9f seconds\n", time_c);


        //TO DO: comparison check with C as basis
       

        //free memory
        free(A);
    }
    return 0;
}


//generate random values
void generate_values(double* A, int n) {

    srand(67);

    for (int i = 0; i < n; i++) {
        A[i] = ((double)rand() / RAND_MAX) * 100.0 - 50.0;
        //random values between 50 and -50
    }
}

//kernel formula asum
double ckernel(const double* A, int n) {

    double sum = 0.0;

    for (int i = 0; i < n; i++) {
        sum += fabs(A[i]);
        }
    
    return sum;
}


//benchmark kernel function for 30 runs
double benchmark_kernel(kernel_func kernel, const double* A, int n) {

    LARGE_INTEGER frequency;
    LARGE_INTEGER start;
    LARGE_INTEGER end;

    QueryPerformanceFrequency(&frequency);
    double totalTime = 0.0;
    double test = kernel(A, n);

    for (int i = 0; i < 30; i++) {
        QueryPerformanceCounter(&start);
        kernel(A, n);
        QueryPerformanceCounter(&end);

        totalTime += (double)(end.QuadPart - start.QuadPart) / frequency.QuadPart;
    }

    return totalTime / 30.0;
}
