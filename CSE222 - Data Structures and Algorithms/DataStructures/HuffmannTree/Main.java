public class Main {
    public static void main(String[] args) {
        // Create a priority queue of integers
        Heap<Integer> pq = new Heap<>();

        // Add elements to the priority queue
        pq.offer(3);
        pq.offer(6);
        pq.offer(1);
        pq.offer(9);
        pq.offer(2);
        pq.offer(-3);
        pq.offer(-5);

        // Print the priority queue
        System.out.println("Priority Queue: " + pq);

        // Peek the top element
        System.out.println("Peek: " + pq.peek());

        // Poll elements from the priority queue
        System.out.println("Poll: " + pq.poll());
        System.out.println("Priority Queue after polling: " + pq);

        System.out.println("Poll: " + pq.poll());

        // Print the priority queue after polling
        System.out.println("Priority Queue after polling: " + pq);

        // Check if the priority queue is empty
        System.out.println("Is empty: " + pq.isEmpty());
        pq.offer(16);
        pq.offer(0);
        pq.offer(555);
        pq.offer(333);
        System.out.println("Priority Queue: " + pq);
    }
}
