#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

int dimension;
int dSquared;
int* tradMult(int *X, int *Y);
int* strassen(int *X, int *Y, int n);
int* add(int *X, int *Y, int nSquared, int sub);
void printMatrix(int *M, int n);

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

    printMatrix(A, dimension);
    printf("\n");
    printMatrix(B, dimension);
    printf("\n");

    int n0 =  122;
    if (dimension < n0) {
        C = tradMult(A, B);
        printMatrix(C, dimension);
        printf("\n");
    }

    C = strassen(A, B, dimension);
    printMatrix(C, dimension);
}

int* tradMult(int *X, int *Y) {
    int *Z = malloc(dSquared * sizeof(int));
    int i, j, k;
    for (i = 0; i < dimension; i++) {
        for (j = 0; j < dimension; j++) {
            int sum = 0;
            for (k = 0; k < dimension; k++) {
               sum += X[dimension * i + k] * Y[dimension * k + j];
            }
            Z[dimension * i + j] = sum;
        }
    }
    return Z;
}

int* strassen(int *X, int *Y, int n) {
    if (n == 2) {
        return tradMult(X,Y);
    }

    int m = n / 2;
    int mS = m * m;
    int *Z = malloc(n * n * sizeof(int));

    int *A = malloc(m * sizeof(int));
    int *B = malloc(m * sizeof(int));
    int *C = malloc(m * sizeof(int));
    int *D = malloc(m * sizeof(int));
    int *E = malloc(m * sizeof(int));
    int *F = malloc(m * sizeof(int));
    int *G = malloc(m * sizeof(int));
    int *H = malloc(m * sizeof(int));

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i < m && j < m) {
                A[m * i + j] = X[n * i + j];
                E[m * i + j] = Y[n * i + j];
            }
            else if (i < m && j >= m) {
                B[m * i + (j - m)] = X[n * i + j];
                F[m * i + (j - m)] = Y[n * i + j];
            }
            else if (i >= m && j < m) {
                C[m * (i - m) + j] = X[n * i + j];
                G[m * (i - m) + j] = Y[n * i + j];
            }
            else if (i >= m && j >= m) {
                D[m * (i - m) + j - m] = X[n * i + j];
                H[m * (i - m) + j - m] = Y[n * i + j];
            }
        }
    }

    // printMatrix(A, m);
    // printf("\n");
    // printMatrix(B, m);
    // printf("\n");
    // printMatrix(C, m);
    // printf("\n");
    // printMatrix(D, m);
    // printf("\n");
    // printMatrix(E, m);
    // printf("\n");
    // printMatrix(F, m);
    // printf("\n");
    // printMatrix(G, m);
    // printf("\n");
    // printMatrix(H, m);

    // A(F-H)
    int *P1 = strassen(A, add(F, H, mS, 1), m);
    // (A+B)H
    int *P2 = strassen(add(A, B, mS, 0), H, m);
    // (C+D)E
    int *P3 = strassen(add(C, D, mS, 0), E, m);
    // D(G-E)
    int *P4 = strassen(D, add(G, E, mS, 1), m);
    // (A+D)(E+H)
    int *P5 = strassen(add(A, D, mS, 0), add(E, H, mS, 0), m);
    // (B-D)(G+H)
    int *P6 = strassen(add(B, D, mS, 1), add(G, H, mS, 0), m);
    // (A-C)(E+F)
    int *P7 = strassen(add(A, C, mS, 1), add(E, F, mS, 0), m);

    printMatrix(Z1, m);
    printf("\n");
    printMatrix(Z1, m);
    printf("\n");
    printMatrix(Z1, m);
    printf("\n");
    printMatrix(Z1, m);
    printf("\n");
    printMatrix(Z1, m);
    printf("\n");
    printMatrix(Z1, m);
    printf("\n");
    printMatrix(Z1, m);
    printf("\n");

    // AE + BG
    int *Z1 = add(P4, add(P5, add(P6, P2, mS, 1), mS, 0), mS, 0);
    // AF + BH
    int *Z2 = add(P2, P1, mS, 0);
    // CE + DG
    int *Z3 = add(P4, P3, mS, 0);
    // CF + DH
    int *Z4 = add(add(P5, P3, mS, 1),add(P1, P7, mS, 1), mS, 0);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i < m && j < m) {
                Z[n * i + j] = Z1[m * i + j];
            }
            else if (i < m && j >= m) {
                Z[n * i + j] = Z2[m * i + (j - m)];
            }
            else if (i >= m && j < m) {
                Z[n * i + j] = Z3[m * (i - m) + j];
            }
            else if (i >= m && j >= m) {
                Z[n * i + j] = Z4[m * (i - m) + j - m];
            }
        }
    }
    
    return Z;
}

int* add(int *X, int *Y, int nSquared, int sub) {
    int *Z = malloc(nSquared * sizeof(int));
    if (sub == 1) {
        for (int i = 0; i < nSquared; i++) {
            Z[i] = X[i] - Y[i];
        }
        return Z;
    }
    for (int i = 0; i < nSquared; i++) {
        Z[i] = X[i] + Y[i];
    }
    return Z;
}

void printMatrix(int *M, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n - 1; j++) {
            printf("%d ", M[n * i + j]);
        }
        printf("%d\n", M[n * (i + 1) - 1]);
    }
}
