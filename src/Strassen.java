package src;
import src.Matrix;

class Strassen {
    public static void main(String[] args) {
        int testcode = Integer.parseInt(args[0]);
        int dimension = Integer.parseInt(args[1]);
        String inputFile = args[2];
        
        Matrix m = new Matrix(dimension, inputFile);
        m.printMatrix();
    }
}
