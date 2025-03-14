
public class Edge {
	private int source;
	private int target;
	private double weight;

	public Edge(int source, int target, double weight) {
		this.source = source;
		this.target = target;
		this.weight = weight;
	}

	public int getSource() {
		return source;
	}

	public int getTarget() {
		return target;
	}

	public double getWeight() {
		return weight;
	}

	@Override
	public boolean equals(Object obj) {
		if (obj == null) {
			return false;
		}
		if (getClass() != obj.getClass()) {
			return false;
		}
		Edge other = (Edge) obj;
		return source == other.source && target == other.target;
	}

	@Override
	public int hashCode() {
		return source * 29 + target;
	}

	@Override
	public String toString() {
		return String.format("(%d, %d, %.2f)", source, target, weight);
	}
}
