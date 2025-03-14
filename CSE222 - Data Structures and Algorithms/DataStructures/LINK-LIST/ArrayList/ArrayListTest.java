public class ArrayListTest {
    public static void main(String[] args) {
        ArrayList<Integer> list = new ArrayList<>();

        // Adding elements
        list.add(1);
        list.add(2);
        list.add(3);
        list.add(4);
        list.add(5);

        // Printing size
        System.out.println("Size: " + list.size()); // Expected output: 5

        // Getting element at index
        System.out.println("Element at index 2: " + list.get(2)); // Expected output: 3

        // Setting element at index
        System.out.println("Setting element at index 2 to 10: " + list.set(2, 10)); // Expected output: 3

        System.out.println("Element at index 2 after setting: " + list.get(2)); // Expected output: 10

        // Adding element at specific index
        list.add(1, 15);exc
        System.out.println("Element at index 1 after adding: " + list.get(1)); // Expected output: 15

        // Finding index of an element
        System.out.println("Index of element 4: " + list.indexOf(4)); // Expected output: 4

        // Removing element at index
        System.out.println("Removed element at index 3: " + list.remove(3)); // Expected output: 10

        // Printing size after removal
        System.out.println("Size after removal: " + list.size()); // Expected output: 5

        // Printing elements
        System.out.print("Elements: ");
        for (int i = 0; i < list.size(); i++) {
            System.out.print(list.get(i) + " ");
        }
        System.out.println();
        // Expected output: 1 15 2 10 5
    }
}
