
using System;

public class PolyhedralDistanceFunction {

    public static PolyhedralDistanceFunction L1(int dimensions) {

        int k = (int) Math.Round(Math.Pow(2, dimensions));
        double[][] facetdescripts = new double[k][];
		for (int i = 0; i < k; i++) facetdescripts[i] = new double[dimensions];

        double val = 1.0 / (double) dimensions;

        int totalblock = k;
        for (int d = 0; d < dimensions; d++) {

            int halfblock = totalblock / 2;

            for (int f = 0; f < k; f++) {

                if (f % totalblock < halfblock) {
                    facetdescripts[f][d] = val;
                } else {
                    facetdescripts[f][d] = -val;
                }
            }

            totalblock = halfblock;
        }

        return new PolyhedralDistanceFunction(facetdescripts);
    }

    public static PolyhedralDistanceFunction LInfinity(int dimensions) {

        double[][] facetdescripts = new double[2 * dimensions][];
		for (int i = 0; i < 2 * dimensions; i++) facetdescripts[i] = new double[dimensions];
        for (int i = 0; i < dimensions; i++) {
            for (int j = 0; j < dimensions; j++) {
                facetdescripts[2 * i][j] = i == j ? 1 : 0;
                facetdescripts[2 * i + 1][j] = i == j ? -1 : 0;
            }
        }

        return new PolyhedralDistanceFunction(facetdescripts);
    }

    public static PolyhedralDistanceFunction epsApproximation2D(double eps) {

        int k;
        if (eps >= Math.Sqrt(2)) {
            k = 4;
        } else {
            k = (int) Math.Ceiling((float)(Math.PI * 2.0 / Math.Acos((float)(1.0 / eps))));
            if (k % 2 == 1) {
                k++;
            }
        }

        return kRegular2D(k);
    }

    public static PolyhedralDistanceFunction kRegular2D(int k) {

        double[][] facetdescripts = new double[k][];
		for (int i = 0; i < k; i++) facetdescripts[i] = new double[2];
		
        double alpha = 2 * Math.PI / (double) k;

        for (int i = 0; i < k; i++) {
            facetdescripts[i][0] = 0.5 * (Math.Cos((float)(i * alpha)) + Math.Cos((float)((i + 1) * alpha)));
            facetdescripts[i][1] = 0.5 * (Math.Sin((float)(i * alpha)) + Math.Sin((float)((i + 1) * alpha)));
        }

        return new PolyhedralDistanceFunction(facetdescripts);
    }

    public static PolyhedralDistanceFunction custom(double[][] facetNormals, double[][] facetPoints, bool normalize) {
        double[][] facetdescripts = new double[facetNormals.Length][];

        for (int i = 0; i < facetdescripts.Length; i++) {
            double[] N = facetNormals[i];
            if (normalize) {
                N = VectorUtil.normalize(N);
            }
            facetdescripts[i] = VectorUtil.scale(VectorUtil.dotProduct(facetNormals[i], facetPoints[i]), facetNormals[i]);
        }

        return new PolyhedralDistanceFunction(facetdescripts);
    }

    private double[][] facets;
    private double[] facetSqrLength;
 
    private PolyhedralDistanceFunction(double[][] facets) {  //OK
        this.facets = facets;
        this.facetSqrLength = new double[facets.Length];
        for (int i = 0; i < this.facetSqrLength.Length; i++) {
            this.facetSqrLength[i] = VectorUtil.squaredLength(this.facets[i]);
        }
    }

    public int getComplexity() {
        return facets.Length;
    }

    public double[] getFacet(int facet) {
        return facets[facet];
    }

    public double getDistance(double[] p, double[] q) {
        return getDistance(VectorUtil.subtract(q, p));
    }

    public double getDistance(double[] d) {
        double max = double.NegativeInfinity;
        for (int i = 0; i < facets.Length; i++) {
            double fd = getFacetDistance(d, i);
            max = Math.Max((float)max, (float)fd);
        }
        return max;
    }

    public double getFacetDistance(double[] p, double[] q, int facet) {
        return getFacetDistance(VectorUtil.subtract(q, p), facet);
    }

    public double getFacetDistance(double[] d, int facet) {
        return VectorUtil.dotProduct(facets[facet], d) / facetSqrLength[facet];
    }

    public double getFacetSlope(double[] p1, double[] p2, int facet) {
        return getFacetDistance(VectorUtil.subtract(p2, p1), facet);
    }
}
