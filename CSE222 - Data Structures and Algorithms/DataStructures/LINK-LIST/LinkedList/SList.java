public class SList<E> {
    private Node<E> head;
    private int     size;

    public SList(){
        size = 0;
        head = null;
    }

    public boolean isEmpty(){
        return size == 0;
    }

    public boolean contains(E element){
        Node<E> tmp = head;
        while(tmp != null){
            System.out.println(element + " " + tmp.data);
            if (element.equals(tmp.data))
                return true;
            tmp = tmp.next;
        }
        return false;
    }

    public  int indexOf(E element){
        Node<E> tmp = head;
        int     index = 0;
        while(tmp.next != null){
            if (element.equals(tmp.data))
                return index;
            tmp = tmp.next;
            index++;
        }
        return -1;
    }

    public void add(E element){
        Node<E> node = new Node<E>(element);
        if (size == 0){
            head = node;
        }
        else {
            Node<E> tmp = head;
            while (tmp.next != null){
                tmp = tmp.next;
            }
            tmp.next = node;
        }
        size++;
    }

    public void add(int index, E element) throws IndexOutOfBoundsException{
        if (index < 0 || index > size){
            throw new IndexOutOfBoundsException("Out of Bounds");
        }
        if (index == 0){
            Node<E> node = new Node<E>(element, head);
            head = node;

        } else {
            Node<E> tmp = head;
            Node<E> prev = head;
            for (int i = 0; i < index; i++){
                prev = tmp;
                tmp = tmp.next;
            }
            Node<E> node = new Node<>(element, tmp);
            prev.next = node;
        }
        size++;
    }
    public E remove(int index) throws IndexOutOfBoundsException{
        E returnVal = get(index);
        if (index == 0){
            head = head.next;
        }
        else {
            Node<E> tmp = head;
            Node<E> prev = head;
            for (int i = 0; i < index; i++){
                prev = tmp;
                tmp = tmp.next;
            }
            prev.next = tmp.next;
        }
        size--;
        return returnVal;
    }

    public E set(int index, E element) throws IndexOutOfBoundsException{
        E returnVal = get(index);
        Node<E> tmp = head;
        for (int i = 0; i < index; i++){
            tmp = tmp.next;
        }
        tmp.data = element;
        return returnVal;
    }

    public E get(int index) throws IndexOutOfBoundsException{
        if (index < 0 || index >= size){
            throw new IndexOutOfBoundsException("Out of Bounds");
        }
        Node<E> tmp = head;
        for (int i = 0; i < index; i++){
            tmp = tmp.next;
        }
        return (tmp.data);
    }
    public int size(){
        return size;
    }
    public void clear(){
        size = 0;
        head = null;
    }
    private static class Node<E> {
        private E data;
        private Node<E> next;

        private Node(E d){
            data = d;
            next = null;
        }
        private Node(E d, Node<E> n){
            data = d;
            next = n;
        }
    }
}