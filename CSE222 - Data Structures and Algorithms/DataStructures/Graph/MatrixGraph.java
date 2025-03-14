import java.util.Iterator;
import java.util.ArrayList;
import java.util.List;

public class MatrixGraph extends AbstractGraph {
	private double[][] edges;

	public MatrixGraph(int numVertices, int numEdges, boolean directed) {
		super(numVertices, numEdges, directed);
		edges = new double[numVertices][numVertices];
		for (int i = 0; i < numVertices; i++) {
			for (int j = 0; j < numVertices; j++) {
				edges[i][j] = Double.POSITIVE_INFINITY;
			}
		}
	}

	public Edge getEdge(int source, int target) {
		return new Edge(source, target, edges[source][target]);
	}

	public boolean isEdge(int source, int target) {
		return edges[source][target] != Double.POSITIVE_INFINITY;
	}

	public void insert(Edge edge) {
		edges[edge.getSource()][edge.getTarget()] = edge.getWeight();
		if (!isDirected()) { // If the graph is undirected, add an edge in the opposite direction
			edges[edge.getTarget()][edge.getSource()] = edge.getWeight();
		}
	}

	public Iterator<Edge> edgeIterator(int source) {
		List<Edge> list = new ArrayList<Edge>();
		for (int i = 0; i < getNumVertices(); i++) {
			if (edges[source][i] != Double.POSITIVE_INFINITY) {
				list.add(new Edge(source, i, edges[source][i]));
			}
		}
		return list.iterator();
	}

	public void printGraph() {
		for (int i = 0; i < getNumVertices(); i++) {
			System.out.print("Vertex " + i + " is connected to: ");
			Iterator<Edge> iter = edgeIterator(i);
			while (iter.hasNext()) {
				Edge edge = iter.next();
				System.out.print(edge.getTarget() + "(" + edge.getWeight() + ") ");
			}
			System.out.println();
		}
	}
}
