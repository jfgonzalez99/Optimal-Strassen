package src;
import java.util.Random;

class Matrix {
    int[][] m;
    int dimension;
    Random rand = new Random();

    /**
     * Constructor for a new matrix object
     * @param d : dimension of matrix
     * @param file : file to fill matrix
     *               the string "random" generates a random matrix
     */
    public Matrix(int d, String file) {
        dimension = d;
        m = new int[d][d];
        if (file.equals("random")) {
            for (int i = 0; i < d; i++) {
                for (int j = 0; j < d; j++) {
                    m[i][j] = rand.nextInt(3);
                }
            }
        }
    }

    public void printMatrix() {
        for (int i = 0; i < dimension; i++) {
            for (int j = 0; j < dimension - 1; j++) {
                System.out.print(m[i][j] + " ");
            }
            System.out.println(m[i][dimension - 1]);
        }
    }
}