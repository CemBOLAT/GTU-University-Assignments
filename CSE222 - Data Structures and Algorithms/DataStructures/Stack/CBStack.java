import java.util.Vector;

public class CBStack<E> extends Vector<E> {
    public int size;
    private Node<E> head;

    public CBStack(){
        head = null;
        size = 0;
    }
    public void push(E data){
        head = new Node<>(data, head);
        size++;
    }
    public E pop(){
        if (head == null)
            return null;
        E data = head.data;
        head = head.next;
        size--;
        return data;
    }
    public E peek(){
        if (head == null)
            return null;
        return head.data;
    }
    public void clear(){
        head = null;
        size = 0;
    }
    public int size(){
        return size;
    }
    public boolean empty(){
        return size == 0;
    }
    public void printStack(){
        Node<E> temp = head;
        while (temp != null){
            System.out.print(temp.data + "-");
            temp = temp.next;
        }
        System.out.println();
    }
    private static class Node<E> {
        private final E data;
        private final Node<E> next;

        private Node(E stored){
            data = stored;
            next = null;
        }
        private Node(E stored, Node<E> newNext){
            data = stored;
            next = newNext;
        }
    }
}