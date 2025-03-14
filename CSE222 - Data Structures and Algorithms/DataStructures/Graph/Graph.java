import java.util.Iterator;

public interface Graph {
	// Accessors

	int getNumVertices();

	boolean isDirected();

	void insert(Edge edge);

	boolean isEdge(int source, int target);

	Edge getEdge(int source, int target);

	Iterator<Edge> edgeIterator(int source);
}
