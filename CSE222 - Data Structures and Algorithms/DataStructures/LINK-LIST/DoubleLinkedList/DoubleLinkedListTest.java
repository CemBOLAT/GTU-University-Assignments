import java.util.Iterator;

public class DoubleLinkedListTest {
	public static void main(String[] args) {
		// Creating a new double linked list
		DoubleLinkedList<Integer> list = new DoubleLinkedList<Integer>();

		// Adding elements to the list
		list.add(5);
		list.add(10);
		list.add(15);
		list.add(20);

		// Displaying elements using Iterator
		System.out.println("Elements in the list:");
		Iterator<Integer> it = list.iterator();
		while (it.hasNext()) {
			System.out.println(it.next());
		}

		// Displaying elements in reverse order using ListIterator
		System.out.println("Elements in the list in reverse order:");
		DoubleLinkedList<Integer>.ListIterator lit = list.new ListIterator();
		while (lit.hasPrevious()) {
			System.out.println(lit.previous());
		}
		// Clearing the list
		list.clear();
		System.out.println("List is cleared.");

		// Displaying elements using Iterator
		System.out.println("Elements in the list:");
		it = list.iterator();
		while (it.hasNext()) {
			System.out.println(it.next());
		}
		// Adding elements to the list
		list.add(5);
		list.add(10);
		list.add(15);
		list.add(20);

		// Displaying elements using Iterator
		System.out.println("Elements in the list:");
		it = list.iterator();
		while (it.hasNext()) {
			System.out.println(it.next());
		}

		// Removing elements from the with iterator
		it = list.iterator();
		while (it.hasNext()) {
			if (it.next() == 10) {
				it.remove();
			}
		}
		// Displaying elements using Iterator
		System.out.println("Elements in the list:");
		it = list.iterator();
		while (it.hasNext()) {
			System.out.println(it.next());
		}
	}
}
