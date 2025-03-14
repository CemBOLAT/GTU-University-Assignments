
import java.util.List;
import java.util.LinkedList;
import java.util.Iterator;

public class ListGraph extends AbstractGraph {
	private List<Edge>[] edges;

	public ListGraph(int numVertices, int numEdges, boolean directed) {
		super(numVertices, numEdges, directed);
		edges = new List[numVertices];
		for (int i = 0; i < numVertices; i++) {
			edges[i] = new LinkedList<Edge>();
		}
	}

	public Edge getEdge(int source, int target){
		for (Edge edge : edges[source]) {
			if (edge.getTarget() == target) {
				return edge;
			}
		}
		return null;
	}

	public boolean isEdge(int source, int target) {
		return getEdge(source, target) != null;
	}

	public void insert(Edge edge) {
		edges[edge.getSource()].add(edge);
		if (!isDirected()) { // If the graph is undirected, add an edge in the opposite direction
			edges[edge.getTarget()].add(new Edge(edge.getTarget(), edge.getSource(), edge.getWeight()));
		}
	}

	public Iterator<Edge> edgeIterator(int source) {
		return edges[source].iterator();
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
