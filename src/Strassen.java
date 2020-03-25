package src;

class Strassen {
    public static void main(String[] args) {
        int testcode = Integer.parseInt(args[0]);
        int dimension = Integer.parseInt(args[1]);
        String inputFile = args[2];
        
        Matrix m = new Matrix(dimension, inputFile);
        m.printMatrix();
    }

    public int[][] twoDimMult(Matrix A, Matrix B) {
        int[][] a = A.m;
        int[][] C = {{}};
        
    }

    public int[][] traditional(Matrix A, Matrix B) {
        if (A.dimension == 2) {
            return twoDimMult(A,B);
        }
    }
}
