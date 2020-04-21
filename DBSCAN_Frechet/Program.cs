using System;
using System.Collections.Generic;
using System.IO;
using System.Globalization;
using System.Linq;
using Common;
using System.Drawing;
using Path = Common.Path;
using ClusteringSpace;




namespace sample_1
{
    class Program
    {
        public static List<Path> paths = new List<Path> ();
        private static int distMetric = 0, minPathsForCluster = 3;
        public static int clustAlg=0 , noise;
        public static bool[] dimensionEnabled = new bool[] { true, true, false, false, false, false, false };
        private static float dbsScanEps = 10.0f;
        
                    

        static void Main(string[] args)
        {
                
                List<float> points = new List<float> ();
                string[] str_points;

                //change location  
                string textFile = @".../data/HELIOS2019";
                
                if (File.Exists(textFile))
                { 
                    // Read a text file line by line.  
                    string[] lines = File.ReadAllLines(textFile);
                    foreach(string line in lines)
                    {
                        List<Node> nodes = new List<Node> ();
                        
                        str_points = line.Remove(line.Length-2).Split(',').ToArray();
                        for(int i=0; i<str_points.Count(); i+=2)
                        {
                            points.Add(float.Parse(str_points[i], CultureInfo.InvariantCulture));
                            points.Add(float.Parse(str_points[i+1], CultureInfo.InvariantCulture));
                            
                            nodes.Add(new Node(points[i]*1000,points[i+1]*1000,0.0));
                        }
                        points.Clear();
                        paths.Add (new Path (nodes));
                    }
                        
                }
                else Console.WriteLine("FALSE");

                int j=0;
                foreach(Path path in paths){
                    path.name = j.ToString();
                    j++;
                }    
                
                noise = 0;   
                List<PathCollection> clusters = DBSCAN.DoDBSCAN(paths, distMetric, dbsScanEps, minPathsForCluster, noise); 
                
                int countCluster = 0;
                foreach(PathCollection c in clusters)
                {
                    countCluster = countCluster + c.Count();
                }

                List<Path> clusterCentroids = new List<Path>();
                clustAlg=1;
                foreach(PathCollection c in clusters)
                {
                    c.UpdateCentroid(clustAlg);
                    clusterCentroids.Add(c.Centroid);
                }

                using(StreamWriter writetext = new StreamWriter(@".../data/resultCluster_HELIOS2019.txt"))
                {
                    foreach (Path path in clusterCentroids)
                    {
                        writetext.WriteLine("{0}", path.ToString());
                    }

                }

         
        }

    }
} 