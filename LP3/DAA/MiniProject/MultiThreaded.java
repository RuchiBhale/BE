import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;

class MultiThreadedMatrixMultiplication {
    private static final int THREAD_COUNT = 3; // Number of threads (equal to number of rows)

    // Multi-threaded matrix multiplication (one thread per row)
    public static int[][] multiplyMatrices(int[][] matrixA, int[][] matrixB) {
        int rowsA = matrixA.length;
        int colsA = matrixA[0].length;
        int colsB = matrixB[0].length;

        int[][] result = new int[rowsA][colsB];

        // Executor service to manage threads
        ExecutorService executor = Executors.newFixedThreadPool(THREAD_COUNT);

        for (int i = 0; i < rowsA; i++) {
            final int row = i;
            executor.execute(() -> {
                for (int j = 0; j < colsB; j++) {
                    for (int k = 0; k < colsA; k++) {
                        result[row][j] += matrixA[row][k] * matrixB[k][j];
                    }
                }
            });
        }

        executor.shutdown();
        while (!executor.isTerminated()) {
            // Wait for all threads to finish
        }

        return result;
    }

    // Print matrix
    public static void printMatrix(int[][] matrix) {
        for (int[] row : matrix) {
            for (int val : row) {
                System.out.print(val + " ");
            }
            System.out.println();
        }
    }

    public static void main(String[] args) {
        int[][] matrixA = {
            {1, 2, 3},
            {4, 5, 6},
            {7, 8, 9}
        };

        int[][] matrixB = {
            {1, 2, 3},
            {4, 5, 6},
            {7, 8, 9}
        };

        long startTime = System.currentTimeMillis();
        int[][] result = multiplyMatrices(matrixA, matrixB);
        long endTime = System.currentTimeMillis();
        System.out.println("Multi-threaded matrix multiplication result (One thread per row):");
        printMatrix(result);
        System.out.println("Time taken: " + (endTime - startTime) + "ms");
    }
}