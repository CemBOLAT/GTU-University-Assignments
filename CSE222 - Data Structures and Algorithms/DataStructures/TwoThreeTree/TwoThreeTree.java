
import java.util.LinkedList;
import java.util.Queue;

// Predecessor : kendisinden küçük en büyük sayı
// Successor : kendisinden büyük en küçük sayı
public class TwoThreeTree {

	private Node root;

	private static class Node {
		private int[] keys;
		private Node[] children;
		private int numKeys;
		private int numOfChildren;
		private boolean isLeaf;

		private Node() {
			keys = new int[3]; // one extra space for splitting
			children = new Node[4]; // one extra space for splitting
			numKeys = 0;
			numOfChildren = 0;
			isLeaf = true;
		}

		public void addKey(int key) {
			keys[numKeys++] = key;
			for (int i = numKeys - 1; i > 0; i--) {
				if (keys[i] < keys[i - 1]) {
					int temp = keys[i];
					keys[i] = keys[i - 1];
					keys[i - 1] = temp;
				} else {
					break;
				}
			}
		}
		/**
		 * Cases:
		 * Splitting a leaf node
		 * Splitting a non-leaf node
		 */
		public void split(){
			Node left = new Node();
			Node right = new Node();
			left.addKey(keys[0]);
			right.addKey(keys[2]);
			if (!isLeaf) { // if not leaf, split children
				left.children[0] = children[0];
				left.children[1] = children[1];
				right.children[0] = children[2];
				right.children[1] = children[3];
			}
			keys[0] = keys[1];
			numKeys = 1;
			children[0] = left;
			children[1] = right;
			children[2] = null;
			children[3] = null;
			isLeaf = false;
		}

		public int removeLargest() {
			if (isLeaf) {
				return keys[--numKeys];
			} else {
				return children[numKeys].removeLargest();
			}
		}

		public int indexOf(int key) {
			for (int i = 0; i < numKeys; i++) {
				if (keys[i] == key) {
					return i;
				}
			}
			return -1;
		}

		public void removeKey(int key) {
			int index = indexOf(key);
			for (int i = index; i < numKeys - 1; i++) {
				keys[i] = keys[i + 1];
			}
			numKeys--;
		}

		public int subtreeIndex(int key) {
			for (int i = 0; i < numKeys; i++) {
				if (key < keys[i]) {
					return i;
				}
			}
			return numKeys;
		}

		public void replaceChild(Node oldChild, Node newChild) {
			for (int i = 0; i < numOfChildren; i++) {
				if (children[i] == oldChild) {
					children[i] = newChild;
					return;
				}
			}
		}
	}

	public TwoThreeTree() {
		root = null;
	}

	public void insert(int key) {
		if (root == null) {
			root = new Node();
			root.addKey(key);
		} else {
			insert(root, key);
		}
	}

	private void insert(Node node, int key) {
		if (node.isLeaf) {
			node.addKey(key);
			if (node.numKeys == 3) {
				node.split();
			}
		} else {
			if (key < node.keys[0]) {
				insert(node.children[0], key);
			} else if (node.numKeys == 1 || key < node.keys[1]) {
				insert(node.children[1], key);
			} else {
				insert(node.children[2], key);
			}
		}
	}

	private void printInOrder(Node node) {
		if (node == null) {
			return;
		}
		printInOrder(node.children[0]);
		System.out.println(node.keys[0]);
		printInOrder(node.children[1]);
		if (node.numKeys == 2) {
			System.out.println(node.keys[1]);
			printInOrder(node.children[2]);
		}
	}

	public void printInOrder(){
		printInOrder(root);
	}

	private int height(Node node) {
		if (node == null) {
			return 0;
		}
		if (node.isLeaf) {
			return 1;
		}
		return 1 + Math.max(height(node.children[0]), Math.max(height(node.children[1]), height(node.children[2])));
	}

	public int height() {
		return height(root);
	}

	private void printLevelOrder(Node node, int h) {
		if (node == null) {
			return;
		}

		if (h == 1) {
			System.out.println(node.keys[0]);
			if (node.numKeys == 2) {
				System.out.println(node.keys[1]);
			}
		} else {
			printLevelOrder(node.children[0], h - 1);
			printLevelOrder(node.children[1], h - 1);
			if (node.numKeys == 2) {
				printLevelOrder(node.children[2], h - 1);
			}
		}
	}

	public void printLevelOrder() {
		int h = height(root);

		for (int i = 1; i <= h; i++) {
			System.out.println("Level " + i);
			printLevelOrder(root, i);
		}
	}

	public static void main(String[] args) {
		TwoThreeTree tree = new TwoThreeTree();
		//for (int i = 1; i <= 10; i++) {
		//	tree.insert((int)(Math.random() * 100));
		//}
		for (int i = 1; i <= 10; i++) {
			tree.insert(i);
		}
		tree.printInOrder();
		System.out.println();
		//tree.printLevelOrder();

	}
}
