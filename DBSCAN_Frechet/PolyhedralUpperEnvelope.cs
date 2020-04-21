using System;
using System.Collections;
using System.Collections.Generic;

public class PolyhedralUpperEnvelope : UpperEnvelope {

    protected class FacetList : Deque<FacetListElement>, IComparable<FacetList> {

        public int facet;
        public double slope;

        public FacetList(int facet, double[] p1, double[] p2, PolyhedralDistanceFunction distfunc) {
            this.facet = facet;
            this.slope = distfunc.getFacetSlope(p1, p2, facet);
        }
		
	    public int CompareTo(FacetList comparePart)
	    {
	        if (comparePart == null)
	            return 1;

	        else 
	            return this.slope.CompareTo(comparePart.slope);
	    }
    }

    protected class FacetListElement : DequeItem<FacetListElement> {

        public int index;
        public double height;
        public double slope;
    }
    protected PolyhedralDistanceFunction distfunc;
    protected double[] p1, p2;
    protected List<FacetList> sortedfacets;


    public PolyhedralUpperEnvelope(PolyhedralDistanceFunction distfunc, double[] p1, double[] p2) {
        this.distfunc = distfunc;
        this.p1 = p1;
        this.p2 = p2;

        sortedfacets = new List<FacetList>();

        for (int i = 0; i < distfunc.getComplexity(); i++) {
            sortedfacets.Add(new FacetList(i, p1, p2, distfunc));
        }
		
//		IComparer myComparer = new sortClass();
		sortedfacets.Sort(); // myComparer );
    }

 //   @Override
    public void add(int i, double[] P1, double[] P2, double[] Q) {
   //     assert P1 == p1;
     //   assert P2 == p2;

        for (int f = 0; f < distfunc.getComplexity(); f++) {

            FacetList fl = sortedfacets[f];

            FacetListElement fle = new FacetListElement();
            fle.index = i;
            fle.slope = fl.slope;
            fle.height = distfunc.getFacetDistance(VectorUtil.subtract(p1, Q), fl.facet);

            while (fl.getSize() > 0 && fl.getFirst().height <= fle.height) {
                fl.removeFirst();
            }
            fl.addFirst(fle);
        }
    }

//    @Override
    public void removeUpto(int i) {
        foreach (FacetList fl in sortedfacets) {
            while (fl.getSize() > 0 && fl.getLast().index <= i) {
                fl.removeLast();
            }

        }
    }

 //   @Override
    public void clear() {
        foreach (FacetList fl in sortedfacets) {
            fl.clear();
        }
    }

    private double findMinimumFullProcedure() {
        FacetListElement[] upperenvelope = new FacetListElement[distfunc.getComplexity()];

        FacetListElement first = sortedfacets[0].getLast();
        upperenvelope[0] = first;
        double[] intersectPreviousAt = new double[distfunc.getComplexity()];
        intersectPreviousAt[0] = double.NegativeInfinity;
        int n = 1;

        for (int i = 1; i < distfunc.getComplexity(); i++) {
            FacetList fl = sortedfacets[i];
            FacetListElement fle = fl.getLast();


            upperenvelope[n] = fle;
            intersectPreviousAt[n] = findIntersection(upperenvelope[n - 1], fle);
            n++;

            if (double.IsInfinity(intersectPreviousAt[n - 1]) || double.IsNaN(intersectPreviousAt[n - 1])) {
                // NB: can only occur with the first previous one (slopes are unique in UE)
                if (upperenvelope[n - 1].height > upperenvelope[n - 2].height) {
                    upperenvelope[n - 2] = upperenvelope[n - 1];
                    if (n > 2) {
                        intersectPreviousAt[n - 2] = findIntersection(upperenvelope[n - 3], fle);
                    } else {
                    }
                    n--;
                } else {
                    n--;
                }
            }

            while (n > 1 && intersectPreviousAt[n - 1] < intersectPreviousAt[n - 2]) {

                upperenvelope[n - 2] = upperenvelope[n - 1];
                intersectPreviousAt[n - 2] = findIntersection(upperenvelope[n - 3], fle);

                n--;
            }
        }
        // minimum given by first point with positve slop
        int min_index = -1;
        for (int i = 0; i < n; i++) {
            if (upperenvelope[i].slope > 0) {
                min_index = i;
                break;
            }
        }

        double min;
        if (intersectPreviousAt[min_index] < 0) {
            while (min_index < n - 1 && intersectPreviousAt[min_index + 1] < 0) {
                min_index++;
            }
            min = upperenvelope[min_index].height;

        } else if (intersectPreviousAt[min_index] > 1) {
            while (min_index > 0 && intersectPreviousAt[min_index] > 1) {
                min_index--;
            }
            min = upperenvelope[min_index].slope + upperenvelope[min_index].height;

        } else {
            min = upperenvelope[min_index].slope * intersectPreviousAt[min_index] + upperenvelope[min_index].height;
        }

        return min;
    }

    private double findMinimumTrimmedProcedure() {
        FacetListElement[] upperenvelope = new FacetListElement[distfunc.getComplexity()];

        FacetListElement first = sortedfacets[0].getLast();
        upperenvelope[0] = first;
        double[] intersectPreviousAt = new double[distfunc.getComplexity()];
        intersectPreviousAt[0] = 0;
        int n = 1;

        for (int i = 1; i < distfunc.getComplexity(); i++) {
            FacetList fl = sortedfacets[i];
            FacetListElement fle = fl.getLast();


            upperenvelope[n] = fle;
            intersectPreviousAt[n] = findIntersection(upperenvelope[n - 1], fle);
            n++;

            if (double.IsInfinity(intersectPreviousAt[n - 1]) || double.IsNaN(intersectPreviousAt[n - 1])) {
                // NB: can only occur with the first previous one (slopes are unique in UE)
                if (upperenvelope[n - 1].height > upperenvelope[n - 2].height) {
                    // toss previous
                    upperenvelope[n - 2] = upperenvelope[n - 1];
                    if (n > 2) {
                        intersectPreviousAt[n - 2] = findIntersection(upperenvelope[n - 3], fle);
                    } else {
                        // nothing to intersect
                    }
                    n--;
                } else {
                    // toss this one
                    n--;
                }
            }

            while (n > 1 && intersectPreviousAt[n - 1] < intersectPreviousAt[n - 2]) {
                // [n-2] not on upper envelope
                upperenvelope[n - 2] = upperenvelope[n - 1];
                if (n == 2) {
                    // intersectPreviousAt[n-2] = 0; // doesn't change                    
                } else {
                    intersectPreviousAt[n - 2] = findIntersection(upperenvelope[n - 3], fle);
                }
                n--;
            }

            if (intersectPreviousAt[n - 1] > 1) {
//                assert n > 1;
                n--;
            } else if (n > 1 && upperenvelope[n - 2].slope > 0) {
                n--;
            }
        }

        double min;
        if (upperenvelope[n - 1].slope > 0) {
            if (n > 1) {
                // get height at intersection with previous
                min = upperenvelope[n - 1].slope * intersectPreviousAt[n - 1] + upperenvelope[n - 1].height;
            } else {
                // get height at 0
                min = upperenvelope[n - 1].height;
            }
        } else {
            // get height at 1            
            min = upperenvelope[n - 1].slope + upperenvelope[n - 1].height;
        }

        return min;
    }

//    @Override
    public double findMinimum(params double[] constants) {
        // find min in range [0,1]

        //double min = findMinimumFullProcedure();
        double min = findMinimumTrimmedProcedure();

        foreach (double c in constants) {
            min = Math.Max((float)min, (float)c);
        }
        return min;
    }

    private double findIntersection(FacetListElement fle1, FacetListElement fle2) {
        double xint = (fle2.height - fle1.height) / (fle1.slope - fle2.slope);
        return xint;
    }

 //   @Override
    public void truncateLast() {
        int i = distfunc.getComplexity() - 1;
        while (i >= 0 && sortedfacets[i].slope > 0) {
            sortedfacets[i].clear();
            i--;
        }
    }
}
