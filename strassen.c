#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <math.h>

int n0 = 46;
int* tradMult(int *X, int *Y, int n);
int* strassen(int *X, int *Y, int n);
int* add(int *X, int *Y, int nSquared, int sub);
int compare(int *X, int* Y, int nSquared);
void printMatrix(int *M, int n);
void printDiagonal(int *M, int n);

int main(int argc, char *argv[]) {
	if (argc != 4) {
		printf("Usage: ./strassen 0 dimension file\n");
		return 1;
	}

	int testcode = atoi(argv[1]);
	int dimension = atoi(argv[2]);
	char *inputFile = argv[3];

    // Initialize "matrices"
    int dSquared = dimension * dimension;
    int *A;
    int *B;
    int *C;

    // Read input file
    if (testcode == 0) {
        A = malloc(dSquared * sizeof(int));
        B = malloc(dSquared * sizeof(int));
        C = malloc(dSquared * sizeof(int));

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

        C = strassen(A, B, dimension);
        printDiagonal(C, dimension);
    }

    // Generate random matrices
    srand(time(NULL));
	if (testcode == 1) {
        A = malloc(dSquared * sizeof(int));
        B = malloc(dSquared * sizeof(int));
        C = malloc(dSquared * sizeof(int));

        for (int i = 0; i < dSquared; i++) {
            A[i] = rand() % 3;
            B[i] = rand() % 3;
        }

        // Time how long strassen takes
        clock_t start, end;
        start = clock();
        C = strassen(A, B, dimension);
        end = clock();
        // printDiagonal(C, dimension);
        printf("\n");

        double time_taken = (double)(end - start) / CLOCKS_PER_SEC;
        printf("%f seconds\n", time_taken);
    }

    // Test multiple values of n0
    if (testcode == 2) {
        int i, j, k, n, nSquared;
        clock_t start, end;
        double time_trad, time_strassen;
        int trials = 1;
        
        printf("n0\ttime_trad\ttime_strassen\n");
        
        for (i = 1; i < 11; i++) {
            n0 = 100 * i;
            n = n0 * 2;
            nSquared = n * n;

            A = malloc(nSquared * sizeof(int));
            B = malloc(nSquared * sizeof(int));
            C = malloc(nSquared * sizeof(int));

            time_trad = 0;
            time_strassen = 0;

            for (j = 0; j < trials; j++)
            {
                // Generate random matrices
                for (k = 0; k < nSquared; k++) {
                    A[k] = rand() % 3;
                    B[k] = rand() % 3;
                }

                // Time how long traditional algorithm takes
                start = clock();
                C = tradMult(A, B, n);
                end = clock();
                time_trad += (double)(end - start) / CLOCKS_PER_SEC;

                // Time how long Strassen takes
                start = clock();
                C = strassen(A, B, n);
                end = clock();
                time_strassen += (double)(end - start) / CLOCKS_PER_SEC;        
            }
            free(C); free(B); free(A);
            printf("%d\t%f\t%f\n", n0, time_trad/trials, time_strassen/trials);
        }
    }

    // See where pure Strassen begins to beat traditional
    if (testcode == 3) {
        int i, j, n, nSquared;
        clock_t start, end;
        double time_trad, time_strassen;
        
        printf("n\ttime_trad\ttime_strassen\n");
        n0 = 2;
        
        for (i = 1; i < 21; i++) {
            n = 2048 + 32 * i;
            nSquared = n * n;
            A = malloc(nSquared * sizeof(int));
            B = malloc(nSquared * sizeof(int));
            C = malloc(nSquared * sizeof(int));

            time_trad = 0;
            time_strassen = 0;

            // Generate random matrices
            for (j = 0; j < nSquared; j++) {
                A[j] = rand() % 3;
                B[j] = rand() % 3;
            }

            // Time how long traditional algorithm takes
            start = clock();
            C = tradMult(A, B, n);
            end = clock();
            time_trad = (double)(end - start) / CLOCKS_PER_SEC;

            // Time how long Strassen takes
            start = clock();
            C = strassen(A, B, n);
            end = clock();
            time_strassen = (double)(end - start) / CLOCKS_PER_SEC;        
            
            free(C); free(B); free(A);
            printf("%d\t%f\t%f\n", n, time_trad, time_strassen);
            n = n * 2;
        }
    }

    // Perturb n0 and see how run time changes
    if (testcode == 4) {
        int i, j, k;
        clock_t start, end;
        double time_trad, time_strassen;
        int trials = 10;
        int n = 500;
        int nSquared = n * n;

        A = malloc(nSquared * sizeof(int));
        B = malloc(nSquared * sizeof(int));
        C = malloc(nSquared * sizeof(int));
        
        printf("n0\ttime_trad\ttime_strassen\n");
        // Test multiple values of n0
        for (i = n0 - 5; i < n0 + 6; i++) {
            n0 = i;

            time_trad = 0;
            time_strassen = 0;

            for (j = 0; j < trials; j++)
            {
                // Generate random matrices
                for (k = 0; k < nSquared; k++) {
                    A[k] = rand() % 3;
                    B[k] = rand() % 3;
                }

                // Time how long traditional algorithm takes
                start = clock();
                C = tradMult(A, B, n);
                end = clock();
                time_trad += (double)(end - start) / CLOCKS_PER_SEC;

                // Time how long Strassen takes
                start = clock();
                C = strassen(A, B, n);
                end = clock();
                time_strassen += (double)(end - start) / CLOCKS_PER_SEC;        
            }
            printf("%d\t%f\t%f\n", n0, time_trad/trials, time_strassen/trials);
        }
    }

    // Triangles in graph
    if (testcode == 5) {
        int i, j, k, sum, trial;
        double avg, t;
        int n = 1024;
        int nSquared = n * n;
        
        A = malloc(nSquared * sizeof(int));
        B = malloc(nSquared * sizeof(int));
        C = malloc(nSquared * sizeof(int));
        
        // Generate random edges
        for (i = 0; i < 5; i++) {
            printf("%.2f, ", (double) (i + 1) / 100);
            avg = 0;
            for (trial = 0; trial < 10; trial++) {
                for (j = 0; j < n; j++) {
                    for (k = j; k < n; k++) {
                        if (rand() % 100 <= i) {
                            A[n * j + k] = 1;
                            A[n * k + j] = 1;
                        }
                        else {
                            A[n * j + k] = 0;
                            A[n * k + j] = 0;
                        }
                    }
                }

                B = strassen(A, A, n);
                C = strassen(B, A, n);
                
                sum = 0;
                for (j = 0; j < n; j++) {
                    sum += C[(n + 1) * i];
                }
                t = (double) sum / 6;
                avg += t;
            }
            printf("%f\n", avg / 10);
        }
    }
}

int* tradMult(int *X, int *Y, int n) {
    int *Z = malloc(n * n * sizeof(int));
    int i, j, k;
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            int sum = 0;
            for (k = 0; k < n; k++) {
               sum += X[n * i + k] * Y[n * k + j];
            }
            Z[n * i + j] = sum;
        }
    }
    return Z;
}

int* strassen(int *X, int *Y, int n) {
    if (n < n0) {
        return tradMult(X, Y, n);
    }

    // Add padding to odd matrices
    int padded = 0;
    if (n % 2 == 1) {
        padded = 1;
        int n1Squared = (n + 1) * (n + 1);
        int *M = malloc(n1Squared * sizeof(int));
        int *N = malloc(n1Squared * sizeof(int));

        int i, j;
        for (i = 0; i < n; i++) {
            for (j = 0; j < n; j++) {
                M[(n + 1) * i + j] = X[n * i + j];
                N[(n + 1) * i + j] = Y[n * i + j];
            }
            M[(n + 1) * i + n] = 0;
            N[(n + 1) * i + n] = 0;
        }
        int lastRow = (n + 1) * n;
        for (i = 0; i < n + 1; i++) {
            M[lastRow + i] = 0;
            N[lastRow + i] = 0;
        }

        X = malloc(n1Squared * sizeof(int));
        Y = malloc(n1Squared * sizeof(int));
        X = M;
        Y = N;

        n++;
    }

    int m = n / 2;
    int mS = m * m;
    int *Z = malloc(n * n * sizeof(int));

    // Split the matrices into quarters
    int *A = malloc(mS * sizeof(int));
    int *B = malloc(mS * sizeof(int));
    int *C = malloc(mS * sizeof(int));
    int *D = malloc(mS * sizeof(int));
    int *E = malloc(mS * sizeof(int));
    int *F = malloc(mS * sizeof(int));
    int *G = malloc(mS * sizeof(int));
    int *H = malloc(mS * sizeof(int));

    int i, j;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            // Top left
            if (i < m && j < m) {
                A[m * i + j] = X[n * i + j];
                E[m * i + j] = Y[n * i + j];
            }
            // Top right
            else if (i < m && j >= m) {
                B[m * i + (j - m)] = X[n * i + j];
                F[m * i + (j - m)] = Y[n * i + j];
            }
            // Bottom left
            else if (i >= m && j < m) {
                C[m * (i - m) + j] = X[n * i + j];
                G[m * (i - m) + j] = Y[n * i + j];
            }
            // Bottom right
            else if (i >= m && j >= m) {
                D[m * (i - m) + (j - m)] = X[n * i + j];
                H[m * (i - m) + (j - m)] = Y[n * i + j];
            }
        }
    }

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

    // AE + BG
    int *Z1 = add(P4, add(P5, add(P6, P2, mS, 1), mS, 0), mS, 0);
    // AF + BH
    int *Z2 = add(P2, P1, mS, 0);
    // CE + DG
    int *Z3 = add(P4, P3, mS, 0);
    // CF + DH
    int *Z4 = add(add(P5, P3, mS, 1),add(P1, P7, mS, 1), mS, 0);

    // Recombine to form output matrix
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
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

    // Free memory
    free(Z4); free(Z3); free(Z2); free(Z1);
    free(P7); free(P6); free(P5); free(P4);
    free(P3); free(P2); free(P1);
    free(H) ; free(G) ; free(F) ; free(E) ; 
    free(D) ; free(C) ; free(B) ; free(A) ;

    // Remove padding if it was added
    if (padded == 1) {
        int q = n - 1;
        int *Q = malloc(q * q * sizeof(int));
        for (i = 0; i < q; i++) {
            for (j = 0; j < q; j++) {
                Q[q * i + j] = Z[n * i + j];
            }
        }
        free(Z);
        return Q;
    }

    return Z;
}

// Adds (or subtracts) two matrices
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

int compare(int *X, int* Y, int nSquared) {
    for (int i = 0; i < nSquared; i++) {
        if (X[i] != Y[i]) {
            printf("%d is not correct\n", i);
            return 1;
        }
    }
    printf("Correct\n");
    return 0;
}

// Prints a matrix
void printMatrix(int *M, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n - 1; j++) {
            printf("%d ", M[n * i + j]);
        }
        printf("%d\n", M[n * (i + 1) - 1]);
    }
}

// Prints the diagonal of a matrix
void printDiagonal(int *M, int n) {
    for (int i = 0; i < n; i++) {
        printf("%d\n", M[(n + 1) * i]);
    }
}
