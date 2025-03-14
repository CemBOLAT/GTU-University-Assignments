public class SListTest {
    public static void main(String[] args) {
        //SList<Integer> list = new SList<>();
//
        //// Adding elements
        //list.add(1);
        //list.add(2);
        //list.add(3);
        //list.add(4);
        //list.add(5);
        //System.out.print("Elements: ");
        //for (int i = 0; i < list.size(); i++) {
        //    System.out.print(list.get(i) + " ");
        //}
        //System.out.println();
        //// Printing size
        //System.out.println("Size: " + list.size()); // Expected output: 5
//
        //// Checking if list is empty
        //System.out.println("Is empty? " + list.isEmpty()); // Expected output: false
//
        //// Checking if list contains element 3
        //System.out.println("Contains 3? " + list.contains(3)); // Expected output: true
//
        //// Getting index of element 3
        //System.out.println("Index of 3: " + list.indexOf(3)); // Expected output: 2
//
        //// Setting element at index 2 to 10
        //System.out.println("Setting element at index 2 to 10: " + list.set(2, 10)); // Expected output: 3
//
        //// Adding element 15 at index 1
        //list.add(1, 15);
        //System.out.println("Element at index 1 after adding 15: " + list.get(1)); // Expected output: 15
//
        //// Removing element at index 3
        //System.out.println("Removed element at index 3: " + list.remove(3)); // Expected output: 10
//
        //// Printing size after removal
        //System.out.println("Size after removal: " + list.size()); // Expected output: 4
//
        //// Printing elements
        //System.out.print("Elements: ");
        //for (int i = 0; i < list.size(); i++) {
        //    System.out.print(list.get(i) + " ");
        //}
        //System.out.println();
        //list.clear();
        //System.out.println("Is empty? " + list.isEmpty()); // Expected output: true;
//
        //// Expected output: 1 15 2 5


        SList<Integer> list = new SList<>();
        list.add(1);
        list.add(2);
        list.add(3);
        list.add(4);
        list.add(5);

        SList<Integer> list2 = new SList<>();

        list2.add(1);
        list2.add(2);
        list2.add(3);
        list2.add(4);
        list2.add(5);

        System.out.println(list.recEquals(list2));
        System.out.println(list.recEqualsIter(list2));
    }
}
