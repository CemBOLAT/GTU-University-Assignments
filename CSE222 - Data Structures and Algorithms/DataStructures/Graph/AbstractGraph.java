import java.util.Scanner;
import java.io.IOException;

public abstract class AbstractGraph implements Graph {

	private int numVertices;
	private int numEdges;
	private boolean directed;


	public AbstractGraph(int numVertices, int numEdges, boolean directed) {
		this.numVertices = numVertices;
		this.numEdges = numEdges;
		this.directed = directed;
	}

	@Override
	public int getNumVertices() {
		return numVertices;
	}

	@Override
	public boolean isDirected() {
		return directed;
	}

	public void loadEdgesFromFile(Scanner scan) throws IOException {
		for (int i = 0; i < numEdges; i++) {
			int source = scan.nextInt();
			int target = scan.nextInt();
			double weight = scan.nextDouble();
			insert(new Edge(source, target, weight));
		}
	}

	public static Graph createGraph(Scanner scan, boolean isDirected, String type) throws IOException {
		int numVertices = scan.nextInt();
		int numEdges = scan.nextInt();
		AbstractGraph graph = null;
		if (type.equalsIgnoreCase("Matrix")) {
			graph = new MatrixGraph(numVertices, numEdges, isDirected);
		} else if (type.equalsIgnoreCase("List")) {
			graph = new ListGraph(numVertices, numEdges, isDirected);
		}
		else {
			throw new IllegalArgumentException();
		}
		graph.loadEdgesFromFile(scan);
		return graph;
	}

	public abstract void printGraph();

}
