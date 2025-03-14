

/*
	Root is always black
	Every path from root to null has same number of black nodes
	Every new node is red
	Every leaf node is black
	Every red node has black children

	// silme yok1
*/

public class RedBlackTree {

	private Node root;

	public RedBlackTree() {
		root = null;
	}

	private int height(Node node) {
		if (node == null) {
			return 0;
		}
		return 1 + Math.max(height(node.left), height(node.right));
	}

	public int height() {
		return height(root);
	}

	private void leftRotate(Node node) {
		Node newParent = node.right;
		node.right = newParent.left;

		if (newParent.left != null) {
			newParent.left.parent = node;
		}

		newParent.parent = node.parent;

		if (node.parent == null) {
			root = newParent;
		} else if (node == node.parent.left) {
			node.parent.left = newParent;
		} else {
			node.parent.right = newParent;
		}

		newParent.left = node;
		node.parent = newParent;
	}

	private void rightRotate(Node node) {
		Node newParent = node.left;
		node.left = newParent.right;

		if (newParent.right != null) {
			newParent.right.parent = node;
		}

		newParent.parent = node.parent;

		if (node.parent == null) {
			root = newParent;
		} else if (node == node.parent.left) {
			node.parent.left = newParent;
		} else {
			node.parent.right = newParent;
		}

		newParent.right = node;
		node.parent = newParent;
	}

	private void recoverRedRedViolation(Node node) {
		/*
			Case 1: Parent is null (root)
			Case 2: Parent is black (no violation)
			Case 3: Uncle is red (recoloring) (and recall on grandparent)
			Case 4: Uncle is black or null (rotation)
		*/
		if (node == root) {
			node.isRed = false;
			return;
		}
		if (node.parent == null || node.parent.parent == null) {
			return;
		}

		Node parent = node.parent;
		Node grandparent = parent.parent;
		Node uncle = (parent == grandparent.left) ? grandparent.right : grandparent.left;

		if (parent.isRed) {
			if (uncle != null && uncle.isRed) {
				parent.isRed = false;
				uncle.isRed = false;
				grandparent.isRed = true;
				recoverRedRedViolation(grandparent);
			} else {
				if (parent == grandparent.left) {
					if (node == parent.right) {
						leftRotate(parent);
						node = parent;
						parent = node.parent;
					}
					rightRotate(grandparent);
				} else {
					if (node == parent.left) {
						rightRotate(parent);
						node = parent;
						parent = node.parent;
					}
					leftRotate(grandparent);
				}
				parent.isRed = false;
				grandparent.isRed = true;
			}
		}
	}

	private Node insertRecursive(Node root, Node node) {
		if (root == null) {
			return node;
		}

		if (node.data < root.data) {
			root.left = insertRecursive(root.left, node);
			root.left.parent = root;
		} else if (node.data > root.data) {
			root.right = insertRecursive(root.right, node);
			root.right.parent = root;
		} else {
			return root; // Duplicate values are not allowed
		}

		return root;
	}


	public void insert(int data) {
		Node node = new Node(data, null);
		root = insertRecursive(root, node);
		recoverRedRedViolation(node);
		root.isRed = false;
	}


	private void print(Node node) {
		if (node == null) {
			return;
		}
		print(node.left);
		System.out.println(node.data + " " + (node.isRed ? "Red" : "Black"));
		print(node.right);
	}

	public void print() {
		print(root);
	}

	private static class Node {
		int data;
		Node left, right;
		Node parent;
		boolean isRed;
		Node(int d, Node p) {
			parent = p;
			this.data = d;
			left = null;
			right = null;
			this.isRed = true;
		}
	}

	public static void main(String[] args){
		RedBlackTree tree = new RedBlackTree();
		// for (int i = 0; i < 10; i++){
		// 	int data = (int)(Math.random() * 100);
		// 	System.out.println("Inserting " + data);
		// 	tree.insert(data);
		// }

		tree.insert(25);
		tree.insert(98);
		tree.insert(85);
		tree.insert(6);
		tree.insert(45);
		tree.insert(57);
		tree.insert(22);
		tree.insert(91);
		tree.insert(60);
		tree.print();
		System.out.println("Height: " + tree.height());

		tree.delete(25);
		tree.delete(98);
		tree.print();
		System.out.println("Height: " + tree.height());
	}
}
