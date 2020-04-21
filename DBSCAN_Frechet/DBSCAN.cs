using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using Path = Common.Path;


namespace ClusteringSpace
{
    public class DBSCAN
    {
		public static int numSelectedDimensions = -1;
		static FrechetDistance frechet;

        public static bool[] dimensionEnabled = new bool[] { true, true, false, false, false, false, false };        
		private static int distMetric = 0;
		
		public static int numPaths = -1;

		
		public static void reset()
		{
			distMetric = -1;
			numPaths = -1;
			numSelectedDimensions = -1;
			Clustering.reset();
		}
		
        public static List<PathCollection> DoDBSCAN(List<Path> paths, int distMetric_, float eps, int minPathsForCluster, int noise)
		{

			if (paths.Count == 0)
			{ 
				Console.WriteLine("No paths to cluster!");
				return null;
			}
			
			setDistMetric(distMetric_);
			
			Clustering.initWithPaths(paths, (numSelectedDimensions > 1) ? true : false);

			List<PathCollection> clusters = cluster(paths, System.Convert.ToDouble(eps), minPathsForCluster, noise);

			return clusters;
        }
		
		public static List<PathCollection> cluster(List<Path> points, double eps, int minPts, int noise)
		{
			if (points == null) return null;

			List<PathCollection> clusters = new List<PathCollection>();
			eps *= eps; // square eps
			int clusterID = 1;
			for (int i = 0; i < points.Count; i++)
			{
			   Path p = points[i];
			   if (p.clusterID == Path.UNCLASSIFIED)
			   {
			       if (ExpandCluster(points, p, clusterID, eps, minPts)) { 
				   		clusterID++;
				   }
                   
			   }
			}
			int maxclusterID = points.OrderBy(p => p.clusterID).Last().clusterID;
			if (maxclusterID < 1) return clusters; // no clusters, so list is empty
			for (int i = 0; i < maxclusterID; i++) clusters.Add(new PathCollection());
            
			foreach (Path p in points)
			{
			   if (p.clusterID > 0){ 
                    clusters[p.clusterID - 1].Add(p);
               }
			}
			return clusters;
		}

		static List<Path> GetRegion(List<Path> points, Path p, double eps)  
	    {
	        List<Path> region = new List<Path>();
	        for (int i = 0; i < points.Count; i++)
	        {
	            double dist = FindDistance(p, points[i]);
	            if (dist <= eps) 
				{
					region.Add(points[i]);
				}
	        }
	        return region;
	    }
	    static bool ExpandCluster(List<Path> points, Path p, int clusterID, double eps, int minPts)  
	    {
			List<Path> seeds = GetRegion(points, p, eps); 
	        
			if (seeds.Count < minPts) // no core point
	        {
				p.clusterID = Path.NOISE;
	            return false;
	        }
	        else // all points in seeds are density reachable from point 'p'
	        {
				
	            for (int i = 0; i < seeds.Count; i++) seeds[i].clusterID = clusterID;
	            seeds.Remove(p);
	            while (seeds.Count > 0)
	            {
	                Path currentP = seeds[0];
	                List<Path> result = GetRegion(points, currentP, eps);
	                if (result.Count >= minPts)
	                {
	                    for (int i = 0; i < result.Count; i++)
	                    {
	                        Path resultP = result[i];
	                        if (resultP.clusterID == Path.UNCLASSIFIED || resultP.clusterID == Path.NOISE)
	                        {
	                            if (resultP.clusterID == Path.UNCLASSIFIED) seeds.Add(resultP);
	                            resultP.clusterID = clusterID;
	                        }
	                    }
	                }
	                seeds.Remove(currentP);
	            }
							
				return true;
	        }
	    }
		
		private static void setDistMetric(int distMetric_) 
		{
			distMetric = distMetric_;
			
			if (distMetric == (int)Metrics.Frechet || distMetric == (int)Metrics.Hausdorff)
			{
				numSelectedDimensions = 0;
				for (int dim = 0; dim < dimensionEnabled.Count(); dim ++)
				{
					if (dimensionEnabled[dim])
					{
						numSelectedDimensions ++;
					}
				}
				
				if (distMetric == (int)Metrics.Frechet)
					frechet = new PolyhedralFrechetDistance(PolyhedralDistanceFunction.L1(numSelectedDimensions));
			}
		}

        public static double FindDistance(Path path1_, Path path2_) 
        {
			if (path1_.points == null) { Console.WriteLine(("P1NULL")); return -1; }  ////{ Debug.Log("P1NULL"); return -1; }
			else if (path2_.points == null) { Console.WriteLine(("P2NULL")); return -1; } ////{ Debug.Log("P2NULL"); return -1; }
			int p1num = Convert.ToInt32(path1_.name);
			int p2num = Convert.ToInt32(path2_.name);

			if (path1_.name == path2_.name)
			{ // same path
				return 0.0;
			}

			Path path1, path2;
			
			bool saveDistances = false;

			if (p1num <= Clustering.distances.Count() && p2num <= Clustering.distances.Count())
			{
				if (Clustering.distances[p1num][p2num] != -1) return Clustering.distances[p1num][p2num];
				if (Clustering.distances[p2num][p1num] != -1) return Clustering.distances[p2num][p1num];
				
				path1 = Clustering.normalizedPaths[p1num];
				path2 = Clustering.normalizedPaths[p2num];
				
				saveDistances = true;
			}
			else
			{
				Console.WriteLine("Note - not storing this distance."); ////Debug.Log("Note - not storing this distance.");
				
				path1 = path1_;
				path2 = path2_;
			}

			double result = 0.0;
			
			if (distMetric == (int)Metrics.Frechet || distMetric == (int)Metrics.Hausdorff)
			{
				double[][] curveA = new double[path1.points.Count][];
				double[][] curveB = new double[path2.points.Count][];

				for (int i = 0; i < path1.points.Count; i ++)
				{
					double[] curve = new double[numSelectedDimensions];
					int curvePos = 0;
					for (int j = 0; j < dimensionEnabled.Count(); j ++)
					{
						if (dimensionEnabled[j])
						{
							if (j == (int)Dimensions.X)
							{
								curve[curvePos] = path1.points[i].xD;
							}
							 
							else if (j == (int)Dimensions.Y)
							{
								curve[curvePos] = path1.points[i].yD;
							} 
							else if (j == (int)Dimensions.Time) curve[curvePos] = path1.points[i].tD;
							curvePos ++;
						}
					}
					curveA[i] = curve;
				}
				
				for (int i = 0; i < path2.points.Count; i ++)
				{
					double[] curve = new double[numSelectedDimensions];
					int curvePos = 0;
					for (int j = 0; j < dimensionEnabled.Count(); j ++)
					{
						if (dimensionEnabled[j])
						{
							if (j == (int)Dimensions.X){
								curve[curvePos] = path2.points[i].xD;
							} 
							else if (j == (int)Dimensions.Y){
							 	curve[curvePos] = path2.points[i].yD;
							}
							else if (j == (int)Dimensions.Time) curve[curvePos] = path2.points[i].tD;
							curvePos ++;
						}
					}
					curveB[i] = curve;
				}
				
				if (distMetric == (int)Metrics.Frechet)
					result = frechet.computeDistance(curveA, curveB);
			}

			else
			{
				Console.WriteLine("Invalid distance metric ("+distMetric+")!");  ////Debug.Log("Invalid distance metric ("+distMetric+")!");
				return -1;
			}
			
			if (saveDistances)
			{
				Clustering.distances[p1num][p2num] = result;
				Clustering.distances[p2num][p1num] = result;
			}            
			return result;
        }
    }
}