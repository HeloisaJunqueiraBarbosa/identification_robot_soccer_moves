using System;
using System.IO;
using System.Collections.Generic;
using System.Xml.Serialization;
using System.Collections;
namespace Common {
	[Serializable]
	public class Path : IEquatable<Path> {
		public String name;
		public List<Node> points;
        public float time;
		
		public const int NOISE = -1;
		public const int UNCLASSIFIED = 0;
		public int clusterID;
		
		public Path () {
			points = new List<Node>();
		}
		
		public Path (List<Node> points) {
			this.points = points;
			if (points == null)
				throw new ArgumentNullException ("Points can't be null");
		}
		
		public Path (Path p) {
			this.points = new List<Node>();
			foreach (Node n in p.points)
			{
				this.points.Add(new Node(n));
			}
			this.name = p.name;
			this.time = p.time;
			this.clusterID = p.clusterID;
			
			if (points == null)
				throw new ArgumentNullException ("Points can't be null");
		}

		
		
		public void ZeroValues () {
			time = 0f;
		}

		public override string ToString () {
			string str="";
			foreach(Node node in points)
			{
				str += node.ToString();
			}
			if(str.Length==0){
				return("()");
			}
			return str.Remove(str.Length-1);
		}
		
		public bool Equals(Path other)
		{
			if (points.Count != other.points.Count) return false;
			
			for (int i = 0; i < points.Count; i ++)
			{
				if (!points[i].equalTo(other.points[i])) return false;
			}
			
			return true;
		}

	}
	

	[XmlRoot("bulk"), XmlType("bulk")]
	public class PathBulk {
		public List<Path> paths;
		
		public PathBulk () {
			paths = new List<Path> ();
		}
		
		public static void SavePathsToFile (string file, List<Path> paths) {
			XmlSerializer ser = new XmlSerializer (typeof(PathBulk));
			
			PathBulk bulk = new PathBulk ();
			bulk.paths.AddRange (paths);
			
			using (FileStream stream = new FileStream (file, FileMode.Create)) {
				ser.Serialize (stream, bulk);
				stream.Flush ();
				stream.Close ();
			}
		}
		
		public static List<Path> LoadPathsFromFile (string file) {
			XmlSerializer ser = new XmlSerializer (typeof(PathBulk));
			
			PathBulk loaded = null;
			using (FileStream stream = new FileStream (file, FileMode.Open)) {
				loaded = (PathBulk)ser.Deserialize (stream);
				stream.Close ();
			}
			
			return loaded.paths;
		}
	}
}