public interface UpperEnvelope {
    
    void add(int i, double[] P1, double[] P2, double[] Q);
     void removeUpto(int i);
     void clear();
    
     double findMinimum(params double[] constants);
    
     void truncateLast();
}