
public class SkipList{

	private static int LAYER = 4;
	private static int MAX_LEVEL = 16;
	private static int MIN_VALUE = Integer.MIN_VALUE;
	private static int MAX_VALUE = Integer.MAX_VALUE;

	private class Node{
		int value;
		Node[] next;

		Node(int value, int level){
			this.value = value;
			next = new Node[level];
		}
	}

	private Node head;
	private int level;

	public SkipList(){
		head = new Node(MIN_VALUE, MAX_LEVEL);
		level = 1;
	}

	public boolean search(int target){
		Node current = head;
		for(int i = level - 1; i >= 0; i--){
			while(current.next[i] != null && current.next[i].value < target){
				current = current.next[i];
			}
		}
		current = current.next[0];
		return current != null && current.value == target;
	}

	public void add(int num){
		Node[] update = new Node[MAX_LEVEL];
		Node current = head;
		for(int i = level - 1; i >= 0; i--){
			while(current.next[i] != null && current.next[i].value < num){
				current = current.next[i];
			}
			update[i] = current;
		}
		current = current.next[0];
		if(current != null && current.value == num){
			return;
		}
		int newLevel = randomLevel();
		if(newLevel > level){
			for(int i = level; i < newLevel; i++){
				update[i] = head;
			}
			level = newLevel;
		}
		Node newNode = new Node(num, newLevel);
		for(int i = 0; i < newLevel; i++){
			newNode.next[i] = update[i].next[i];
			update[i].next[i] = newNode;
		}
	}

	public boolean erase(int num){
		Node[] update = new Node[MAX_LEVEL];
		Node current = head;
		for(int i = level - 1; i >= 0; i--){
			while(current.next[i] != null && current.next[i].value < num){
				current = current.next[i];
			}
			update[i] = current;
		}
		current = current.next[0];
		if(current == null || current.value != num){
			return false;
		}
		for(int i = 0; i < level; i++){
			if(update[i].next[i] != current){
				break;
			}
			update[i].next[i] = current.next[i];
		}
		while(level > 1 && head.next[level - 1] == null){
			level--;
		}
		return true;
	}

	private int randomLevel(){
		int newLevel = 1;
		while(newLevel < MAX_LEVEL && Math.random() < 0.5){
			newLevel++;
		}
		return newLevel;
	}

	public void printList(){
		Node current = head;
		while(current.next[0] != null){
			System.out.print(current.next[0].value + " ");
			current = current.next[0];
		}
		System.out.println();
	}

	public void printLayers(){
		for(int i = level - 1; i >= 0; i--){
			Node current = head;
			while(current.next[i] != null){
				System.out.print(current.next[i].value + " ");
				current = current.next[i];
			}
			System.out.println();
		}
	}

	public static void main(String[] args){
		SkipList skipList = new SkipList();
		for (int i = 0; i < 10; i++){
			skipList.add(Math.abs((int)(Math.random() * 100)));
		}

		skipList.printList();
		System.out.println("Layers: ");
		skipList.printLayers();
	}

}
