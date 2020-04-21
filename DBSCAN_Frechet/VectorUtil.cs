
using System;
public class VectorUtil {

    public static double[] subtract(double[] A, double[] B) {

        double[] R = new double[A.Length];
        for (int i = 0; i < R.Length; i++) {
            R[i] = A[i] - B[i];
        }
        return R;
    }

    public static double dotProduct(double[] A, double[] B) {

        double dot = 0;
        for (int i = 0; i < A.Length; i++) {
            dot += A[i] * B[i];
        }
        return dot;
    }

    public static double length(double[] A) {
        return Math.Sqrt((float)squaredLength(A));
    }

    public static double squaredLength(double[] A) { //OK
        double sum = 0;
        for (int i = 0; i < A.Length; i++) {
            sum += A[i] * A[i];
        }
        return sum;
    }

    public static double[] scale(double S, double[] A) {
        double[] R = new double[A.Length];
        for (int i = 0; i < R.Length; i++) {
            R[i] = S * A[i];
        }
        return R;
    }

    public static double[] normalize(double[] A) {
        return scale(1.0 / length(A), A);
    }
}
