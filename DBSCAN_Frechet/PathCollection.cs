//PathCollection.cs
//modified from source at http://codeding.com/articles/k-means-algorithm

using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Path = Common.Path;
using Node = Common.Node;
namespace ClusteringSpace
{
    public class PathCollection : List<Path>
    {
        #region Properties

        public Path Centroid { get; set; }
		
		public bool changed = false;

        #endregion

        #region Constructors

        public PathCollection()
            : base()
        {
            Centroid = new Path();
        }
		
        public PathCollection(List<Path> paths)
            : base()
        {
            Centroid = new Path();

			int clustAlg=1;
			
			foreach (Path p in paths)
			{
				this.Add(p);
			}
            UpdateCentroid(clustAlg);
        }
		
		public PathCollection(Path centroid_) : base()
		{
			Centroid = centroid_;
		}

        #endregion

        #region Methods

        public void AddPath(Path p)
        {
            this.Add(p);
			changed = true;
        }

        public Path RemovePath(Path p)
        {
            Path removedPath = new Path(p);
            this.Remove(p);
			changed = true;

            return (removedPath);
        }

        #endregion

        #region Internal-Methods

		public Path getAveragedCentroid()
		{
			// first, make a copy of all the paths in the cluster...
			List<Path> interpolatedPaths = new List<Path>();
			foreach (Path p in this)
			{
				interpolatedPaths.Add(new Path(p)); // make a copy
			}

			double maxTime = Double.NegativeInfinity;
			foreach (Path p in this)
			{ // find the highest time value over all paths in this cluster
				foreach (Node n in p.points)
				{
					if (n.tD > maxTime)
					{
						maxTime = n.tD;
					}
				}
			}
			
			
			Node[] averagedNodes = new Node[interpolatedPaths[0].points.Count()];
			for (int count = 0; count < interpolatedPaths[0].points.Count(); count ++)
			{
				averagedNodes[count] = new Node(0, 0, 0);
			}
            float avgDanger = 0f, avgLOS = 0f, avgNM = 0f;
			foreach (Path p in interpolatedPaths)
			{
				for (int count = 0; count < p.points.Count; count ++)
				{
					averagedNodes[count].x += Math.Abs(p.points[count].x);
					averagedNodes[count].y += Math.Abs(p.points[count].y);
					averagedNodes[count].t += Math.Abs(p.points[count].t);
					averagedNodes[count].xD += Math.Abs(p.points[count].xD);
					averagedNodes[count].yD += Math.Abs(p.points[count].yD);
					averagedNodes[count].tD += Math.Abs(p.points[count].tD);
				}
			}

            avgDanger /= interpolatedPaths.Count;
            avgLOS /= interpolatedPaths.Count;
            avgNM /= interpolatedPaths.Count;
			foreach(Node n in averagedNodes)
			{
				n.x /= interpolatedPaths.Count;
				n.y /= interpolatedPaths.Count;
				n.t /= interpolatedPaths.Count;
				n.xD /= interpolatedPaths.Count;
				n.yD /= interpolatedPaths.Count;
				n.tD /= interpolatedPaths.Count;
			}
        
            Path averagedPath = new Path(new List<Node>(averagedNodes));
		
			return averagedPath;
		}

        public void UpdateCentroid(int ClustAlg)
        {	
			int clustAlg = ClustAlg;
			double pathTotalMinDist = double.PositiveInfinity;
			int pIndex = -1;
			for (int i = 0; i < this.Count; i ++)
			{
				if (clustAlg == 0 && KMeans.weights.Count() < Convert.ToInt32(this[i].name))
				{
					Console.WriteLine("KMeans.weights size: " + KMeans.weights.Count() + " but need index " + Convert.ToInt32(this[i].name));
				}
				double weightOfI = (clustAlg == 0 ? KMeans.weights[Convert.ToInt32(this[i].name)] : 1.0);
				double currentPathTotalMinDist = 0;
				for (int j = 0; j < this.Count; j ++)
				{
					if (i == j) continue;

					currentPathTotalMinDist += (weightOfI * KMeans.FindDistance(this[i], this[j]));
				}
				if (currentPathTotalMinDist < pathTotalMinDist)
				{
					pathTotalMinDist = currentPathTotalMinDist;
					pIndex = i;
				}
			}
			
			if (pIndex == -1)
			{
				Console.WriteLine("-1");
				Centroid = null;
				return;
			}
		
			Centroid = new Path(this[pIndex]);
			}
		#endregion
		}
        
}
