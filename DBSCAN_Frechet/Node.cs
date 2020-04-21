using System;
using System.Collections.Generic;
using System.Xml;
using System.Xml.Serialization;

namespace Common {
	[Serializable]
		public class Node : Priority_Queue.PriorityQueueNode {
		public int x, y, t;
		public double xD, yD, tD;
		
		
		public Node() { }
		
		public Node(Node n)
		{
			x = n.x;
			y = n.y;
			t = n.t;
			xD = n.xD;
			yD = n.yD;
			tD = n.tD;
		}
		
		public Node(int x_, int y_, int t_)
		{
			xD = x = x_;
			yD = y = y_;
			tD = t = t_;
		}
		
		public Node(double x_, double y_, double t_)
		{
			xD = x_;
			x = (int)xD;
			yD = y_;
			y = (int)yD;
			tD = t_;
			t = (int)tD;
		}

		public double[] GetArray () {
			return new double[] {x, y};
		}

		public Boolean equalTo (Node b) {
			if (this.x == b.x & this.y == b.y & this.t == b.t)
				return true;
			return false; 
		}

		public override string ToString () {
			return  x + "," + y + ",";
		}

		public int Axis (int axis) {
			switch (axis) {
			case 0:
				return x;
			case 1:
				return t;
			case 2:
				return y;
			default:
				throw new ArgumentException ();
			}
		}
	}
}