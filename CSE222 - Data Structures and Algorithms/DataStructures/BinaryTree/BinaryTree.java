import java.util.Comparator;

public class BinaryTree<E extends Comparable<E>> {
	private Node<E> root;

	public BinaryTree() {
		root = null;
	}

	public boolean isEmpty() {
		return root == null;
	}

	public void clear() {
		root = null;
	}

	public int	height() {
		if (isEmpty()) {
			return 0;
		}
		return height(root);
	}

	private int height(Node<E> node) {
		if (node == null) {
			return 0;
		}
		else if (isLeaf(node)) {
			return 1;
		}
		return 1 + Math.max(height(node.left), height(node.right));
	}

	public int size(){
		if (isEmpty()) {
			return 0;
		}
		return size(root);
	}
	private int size(Node<E> node) {
		if (node == null) {
			return 0;
		}
		return 1 + size(node.left) + size(node.right);
	}
	public E getLargest(){
		if (isEmpty()) {
			return null;
		}
		return getLargest(root);
	}

	private E getLargest(Node<E> node) {
		if (node.right == null) {
			return node.data;
		}
		return getLargest(node.right);
	}

	public E getSmallest(){
		if (isEmpty()) {
			return null;
		}
		return getSmallest(root);
	}

	private E getSmallest(Node<E> node) {
		if (node.left == null) {
			return node.data;
		}
		return getSmallest(node.left);
	}

	public boolean isLeaf(Node<E> root) {
		return root.left == null && root.right == null;
	}

	public void remove (E data){
		if (isEmpty()) {
			System.out.println("Tree is empty");
			return;
		}
		root = remove(data, root);
	}

	private Node<E> remove(E data, Node<E> node){
		if (node == null) {
			System.out.println("Data not found");
			return root;
		}
		else if (data.compareTo(node.data) < 0) {
			node.left = remove(data, node.left);
		}
		else if (data.compareTo(node.data) > 0) {
			node.right = remove(data, node.right);
		}
		else {
			if (node.left == null) {
				return node.right;
			}
			else if (node.right == null) {
				return node.left;
			}
			else {
				node.data = getSmallest(node.right);
				node.right = remove(node.data, node.right);
			}
		}
		return node;
	}

	public void add(E data) {
		if (isEmpty()) {
			root = new Node<E>(data);
		} else {
			add(data, root);
		}
	}

	public void preOrderTre(){
		StringBuilder sb = new StringBuilder();
		if (root == null){
			return;
		}
		preOrderTreRec(root, sb);
		System.out.println("Preorder: " + sb.toString());
	}

	private void preOrderTreRec(Node<E> root, StringBuilder sb){
		if (root == null){
			return;
		}
		sb.append(root.data.toString() + " ");
		preOrderTreRec(root.left, sb);
		preOrderTreRec(root.right, sb);
	}


	public void inOrderTre(){
		StringBuilder sb = new StringBuilder();
		if (root == null){
			return;
		}
		inOrderTreRec(root, sb);
		System.out.println("Inorder: " + sb.toString());
	}

	private void inOrderTreRec(Node<E> root, StringBuilder sb){
		if (root == null){
			return;
		}
		inOrderTreRec(root.left, sb);
		sb.append(root.data.toString() + " ");
		inOrderTreRec(root.right, sb);
	}

	public void postOrderTre(){
		StringBuilder sb = new StringBuilder();
		if (root == null){
			return;
		}
		postOrderTreRec(root, sb);
		System.out.println("PostOrder: " + sb.toString());
	}

	private void postOrderTreRec(Node<E> root, StringBuilder sb){
		if (root == null){
			return;
		}
		postOrderTreRec(root.left, sb);
		postOrderTreRec(root.right, sb);
		sb.append(root.data.toString() + " ");
	}


	private void add(E data, Node<E> node) {
		if (data.compareTo(node.data) < 0) {
			if (node.left == null) {
				node.left = new Node<E>(data);
			} else {
				add(data, node.left);
			}
		} else {
			if (node.right == null) {
				node.right = new Node<E>(data);
			} else {
				add(data, node.right);
			}
		}
	}

	public BinaryTree(E data) {
		root = new Node<E>(data);
	}

	private static class Node<E>{
		private E data;
		private Node<E> left;
		private Node<E> right;

		public Node(E data) {
			this.data = data;
			left = null;
			right = null;
		}
		// LEFT - RIGHT
		public Node(E data, Node<E> left, Node<E> right) {
			this.data = data;
			this.left = left;
			this.right = right;
		}
	}

	private void toString(Node<E> root, int d, StringBuilder sb){
		for (int i = 0; i < d + 2; i++){
			sb.append(" ");
		}
		if (root == null){
			sb.append("null\n");
			return;
		}
		sb.append(root.data + "\n");
		toString(root.left, d + 1, sb);
		toString(root.right, d + 1, sb);
	}

	@Override
	public String toString(){
		StringBuilder sb = new StringBuilder();
		toString(root, 0, sb);
		return sb.toString();
	}
}
