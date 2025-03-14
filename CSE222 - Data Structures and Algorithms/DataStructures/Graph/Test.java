
import java.io.File;
import java.io.IOException;
import java.util.Scanner;

public class Test {
	public static void main(String[] args) {
		// Create a graph from a file
		try (Scanner scan = new Scanner(new File("graph.txt"))) {
			int numVertices = scan.nextInt();
			int numEdges = scan.nextInt();
			AbstractGraph graph = new MatrixGraph(numVertices, numEdges, true);

			graph.loadEdgesFromFile(scan);
			graph.printGraph();

		} catch (IOException e) {
			e.printStackTrace();
		}
	}
}
