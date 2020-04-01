#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

int dimension;
int dSquared;
int* tradMult(int *A, int *B);
void printMatrix(int *M);

int main(int argc, char *argv[]) {
	if (argc != 4) {
		printf("Usage: ./strassen 0 dimension file\n");
		return 1;
	}

	int testcode = atoi(argv[1]);
	dimension = atoi(argv[2]);
	char *inputFile = argv[3];

    // Initialize "matrices"
    dSquared = dimension * dimension;
    int *A = malloc(dSquared * sizeof(int));
    int *B = malloc(dSquared * sizeof(int));
    int *C = malloc(dSquared * sizeof(int));

    // Read input file
    if (testcode == 0) {
        FILE *f = fopen(inputFile, "r");
        if (f == NULL) {
            printf("Could not open %s\n", inputFile);
            return 2;
        }

        int i = 0;
        int num;
        while (fscanf(f, "%d", &num) != EOF) {
            if (i < dSquared) {
                A[i] = num;
            }
            else {
                B[i - dSquared] = num;
            }
            i++;
        }
        fclose(f);
    }

    // Generate random matrices
    srand(time(NULL));
	if (testcode == 1) {
        for (int i = 0; i < dSquared; i++) {
            A[i] = rand() % 3;
            B[i] = rand() % 3;
        }
    }

    printMatrix(A);
    printf("\n");
    printMatrix(B);
    printf("\n");

    int n0 =  122;
    if (dimension < n0) {
        C = tradMult(A, B);
        printMatrix(C);
    }
}

void printMatrix(int *M) {
    for (int i = 0; i < dimension; i++) {
        for (int j = 0; j < dimension - 1; j++) {
            printf("%d ", M[dimension * i + j]);
        }
        printf("%d\n", M[dimension * (i + 1) - 1]);
    }
}

int* tradMult(int *A, int *B) {
    int *C = malloc(dSquared * sizeof(int));
    int i, j, k;
    for (i = 0; i < dimension; i++) {
        for (j = 0; j < dimension; j++) {
            int sum = 0;
            for (k = 0; k < dimension; k++) {
               sum += A[dimension * i + k] * B[dimension * k + j];
            }
            C[dimension * i + j] = sum;
        }
    }
    return C;
}
