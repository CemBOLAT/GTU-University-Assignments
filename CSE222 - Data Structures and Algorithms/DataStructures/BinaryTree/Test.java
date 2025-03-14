public class Test {
	public static void main(String[] args) {
		BinaryTree<Integer> tree = new BinaryTree<Integer>();
		//tree.add(3);
		//tree.add(5);
		//tree.add(7);
		//tree.add(1);
		//tree.remove(1);
		//tree.remove(7);
		//System.out.println(tree.getLargest());
		//System.out.println(tree.getSmallest());
		//System.out.println(tree.height());
		//System.out.println(tree.size());

		tree.add(5);
		tree.add(3);
		tree.add(7);
		tree.add(1);
		tree.add(4);
		tree.add(6);
		tree.add(8);
		tree.add(2);
		tree.add(9);
		tree.add(10);
		tree.add(11);
		tree.add(12);
		tree.add(13);

		tree.postOrderTre(); // 2 1 4 3 6 8 7 9 11 13 12 10 5
		tree.inOrderTre(); // 1 2 3 4 5 6 7 8 9 10 11 12 13 (sorted)
		tree.preOrderTre(); // 5 3 1 2 4 7 6 8 10 9 12 11 13
		System.out.println(tree);
	}
}
