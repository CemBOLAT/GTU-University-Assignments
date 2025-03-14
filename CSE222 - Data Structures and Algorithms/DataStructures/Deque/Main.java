public class Main{
    public static void main(String[] args){
        Deque<Integer> deque = new Deque<Integer>();
        for (int i = 0; i < 10; i++){
            deque.offerFirst(i);
        }
        System.out.println(deque); // 9 8 7 6 5 4 3 2 1 0
        for (int i = 0; i < 10; i++){
            deque.offerLast(i);
        }
        System.out.println(deque); // 9 8 7 6 5 4 3 2 1 0 0 1 2 3 4 5 6 7 8 9
        for (int i = 0; i < 5; i++){
            deque.pollFirst(); // 4 3 2 1 0 0 1 2 3 4 5 6 7 8 9
        }
        System.out.println(deque);
        for (int i = 0; i < 5; i++){
            deque.pollLast(); // 4 3 2 1 0 0 1 2 3 4
        }
        System.out.println(deque);
        System.out.println(deque.peekFirst()); // 4
        System.out.println(deque.peekLast()); // 4
        System.out.println(deque.size()); // 10
        System.out.println(deque.removeFirstOccurence(3)); // true
        System.out.println(deque); // 4 2 1 0 0 1 2 3 4
        System.out.println(deque.removeLastOccurence(2)); // true
        System.out.println(deque); // 4 2 1 0 0 1 3 4
        for (int i = 0; i < 10; i++){
            deque.offerLast(i);
        }
        System.out.println(deque); // 4 2 1 0 0 1 3 4

    }
}
