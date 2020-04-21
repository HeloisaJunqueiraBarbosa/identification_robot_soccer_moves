using System;
using System.Collections;
using System.Collections.Generic;
using System.Linq;
using Path = Common.Path;
using Node = Common.Node;

namespace ClusteringSpace
{
	public enum Metrics
	{
		Frechet = 0,
		AreaDistTriangulation,
		AreaDistInterpolation3D,
		Hausdorff
	}
	
	public enum Dimensions
	{
		X = 0,
		Y,
		Time
	}
	
	public class Clustering
	{
		public static double[][] distances;
		public static Path[] normalizedPaths;
	
		public static void initWithPaths(List<Path> paths, bool normalize)
		{
			distances = new double[paths.Count()][];
			for (int count = 0; count < paths.Count(); count ++)
			{
				distances[count] = new double[paths.Count()];
				for (int count2 = 0; count2 < paths.Count(); count2 ++)
				{
					distances[count][count2] = -1;
				}
			}
			
			normalizedPaths = new Path[paths.Count()];

			if (normalize)
				normalizePaths(paths);
			else
			{
				for (int count = 0; count < paths.Count(); count ++)
				{
					normalizedPaths[count] = paths[count];
				}
			}
		}
	
		public static void reset()
		{
			if (distances != null)
				Array.Clear(distances, 0, distances.Count());
			if (normalizedPaths != null)
				Array.Clear(normalizedPaths, 0, normalizedPaths.Count());
		}
		
		private static void normalizePaths(List<Path> paths) 
		{
			Array.Clear(normalizedPaths, 0, normalizedPaths.Count());
			float maxX = -1f, maxY = -1f, maxT = -1f; 
			float minX = Single.PositiveInfinity, minY = Single.PositiveInfinity, minT = Single.PositiveInfinity;
			foreach (Path p in paths)
			{
				foreach (Node n in p.points)
				{
					if (n.x > maxX) maxX = (float)n.xD;
					if (n.y > maxY) maxY = (float)n.yD;
					if (n.t > maxT) maxT = (float)n.tD;
					
					if (n.x < minX) minX = (float)n.xD;
					if (n.y < minY) minY = (float)n.yD;
					if (n.t < minT) minT = (float)n.tD;
				}					
			}
			
			float maxVal = 1000f;
						
			for (int count = 0; count < paths.Count; count ++)
			{
				int index = Convert.ToInt32(paths[count].name);
				normalizedPaths[index] = new Path(paths[count]);
				foreach (Node n in normalizedPaths[index].points)
				{
					n.xD = (((n.xD - minX) * maxVal) / (maxX - minX));
					n.yD = (((n.yD - minY) * maxVal) / (maxY - minY));
					n.tD = (((n.tD - minT) * maxVal) / (maxT - minT));
					
					n.x = (int)n.xD;
					n.y = (int)n.yD;
					n.t = (int)n.tD;
				}						
			}
		}
	}
}