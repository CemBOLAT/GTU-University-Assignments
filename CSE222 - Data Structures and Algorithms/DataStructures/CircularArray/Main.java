public class Main {
    public static void main(String[] args) {
        try {
            CircularArray<Integer> ca = new CircularArray<>(2);
            for (int i = 0; i < 10; i++){
                ca.offer(i);
            }

            System.out.println("Size: " + ca.size()); // Expected: 10
            System.out.println("Element: " + ca.element()); // Expected: 0
            System.out.println("Peek: " + ca.peek()); // Expected: 0
            System.out.println("Remove: " + ca.remove()); // Expected: 0
            System.out.println("Poll: " + ca.poll()); // Expected: 1
            System.out.println("Size: " + ca.size()); // Expected: 8
            System.out.println("Element: " + ca.element()); // Expected: 2
            System.out.println("Peek: " + ca.peek()); // Expected: 2

            for(int i = 0; i < 3; i++){
                System.out.println("Remove: " + ca.remove()); // Expected: 2, 3, 4
            }
            System.out.println("Size: " + ca.size()); // Expected: 5
            for (int i = 0; i < 5; i++){
                ca.offer(i * 10);
            }
            System.out.println("Size: " + ca.size()); // Expected: 10
            for (int i = 0; i < ca.size(); i++){
                System.out.println("Element: " + ca.get(i)); // Expected: 5, 6, 7, 8, 9, 0, 1, 10, 20, 30
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}