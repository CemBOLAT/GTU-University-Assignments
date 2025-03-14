public class LinkedListTest {
    public static void main(String[] args) {
        LinkedList<Integer> list = new LinkedList<>();

        // Adding elements
        list.add(0, 1);
        list.addLast(2);
        list.addFirst(0);
        System.out.print("Elements: ");
        for (int i = 0; i < list.size(); i++) {
            System.out.print(list.get(i) + " ");
        }
        System.out.println();
        // Printing size
        System.out.println("Size: " + list.size()); // Expected output: 3

        // Checking if list is empty
        System.out.println("Is empty? " + list.isEmpty()); // Expected output: false

        // Checking if list contains element 2
        System.out.println("Contains 2? " + list.contains(2)); // Expected output: true

        // Getting first element
        System.out.println("First element: " + list.getFirst()); // Expected output: 0

        // Getting last element
        System.out.println("Last element: " + list.getLast()); // Expected output: 2

        // Getting element at index 1
        System.out.println("Element at index 1: " + list.get(1)); // Expected output: 1

        // Removing element 1
        System.out.println("Removing element 1: " + list.remove(1)); // Expected output: true

        // Printing size after removal
        System.out.println("Size after removal: " + list.size()); // Expected output: 2

        // Printing elements
        System.out.print("Elements: ");
        for (int i = 0; i < list.size(); i++) {
            System.out.print(list.get(i) + " ");
        }
        // Expected output: 0 2
    }
}
