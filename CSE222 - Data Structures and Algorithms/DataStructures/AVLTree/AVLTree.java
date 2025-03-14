
public class AVLTree {

	private Node root;

	public AVLTree() {
		this.root = null;
	}

	private int height(Node node) {
		if (node == null) {
			return 0;
		}
		return node.height;
	}

	private int getBalance(Node node) {
		if (node == null) {
			return 0;
		}
		return height(node.left) - height(node.right);
	}

	private Node rightRotate(Node node){
		Node temp = node.left;
		Node temp_right = temp.right;

		temp.right = node;
		node.left = temp_right;

		node.height = 1 + Math.max(height(node.left), height(node.right));
		temp.height = 1 + Math.max(height(temp.left), height(temp.right));

		return temp;
	}

	private Node leftRotate(Node node){
		Node temp = node.right;
		Node temp_left = temp.left;

		temp.left = node;
		node.right = temp_left;

		node.height = 1 + Math.max(height(node.left), height(node.right));
		temp.height = 1 + Math.max(height(temp.left), height(temp.right));

		return temp;
	}

	private Node rotate(Node node, int data, int balance) {
		if (balance > 1 && getBalance(node.left) > 0) {
			return rightRotate(node);
		}
		if (balance < -1 && getBalance(node.right) < 0) {
			return leftRotate(node);
		}
		if (balance > 1 && getBalance(node.left) < 0) {
			node.left = leftRotate(node.left);
			return rightRotate(node);
		}
		if (balance < -1 && getBalance(node.right) > 0) {
			node.right = rightRotate(node.left);
			return leftRotate(node);
		}

		return node;
	}

	private Node insert(Node node, int data) {
		if (node == null) {
			return new Node(data);
		}

		if (data < node.data) {
			node.left = insert(node.left, data);
		} else if (data > node.data) {
			node.right = insert(node.right, data);
		} else {
			return node;
		}

		node.height = 1 + Math.max(height(node.left), height(node.right));

		int balance = getBalance(node);

		return rotate(node, data, balance);
	}

	public void insert(int data) {
		root = insert(root, data);
	}

	private Node delete(Node node, int data) {
		if (node == null) {
			return node;
		}

		if (data < node.data) {
			node.left = delete(node.left, data);
		} else if (data > node.data) {
			node.right = delete(node.right, data);
		} else {
			if (node.left == null && node.right == null){
				node = null;
			} else if (node.left == null) {
				node = node.right;
			} else if (node.right == null) {
				node = node.left;
			}
			else {
				Node temp = minValueNode(node.right);
				node.data = temp.data;
				node.right = delete(node.right, temp.data);
			}
		}

		if (node == null) {
			return node;
		}

		node.height = 1 + Math.max(height(node.left), height(node.right));

		int balance = getBalance(node);

		return rotate(node, data, balance);
	}

	private Node minValueNode(Node node) {
		Node current = node;
		while (current.left != null) {
			current = current.left;
		}
		return current;
	}

	public void delete(int data) {
		root = delete(root, data);
	}


	private static class Node {
		int data;
		Node left;
		Node right;
		int height;

		Node(int data) {
			this.data = data;
			this.height = 1;
		}
	}
}
