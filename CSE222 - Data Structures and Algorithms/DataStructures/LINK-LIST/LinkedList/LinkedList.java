public class LinkedList<E> {
    private SList<E>    head;
    private int         size;

    public LinkedList(){
        size = 0;
        head = new SList<E>();
    }

    public boolean isEmpty(){
        return head.isEmpty();
    }
    public boolean contains(E element){
        return head.contains(element);
    }

    public void add(int index, E element) throws IndexOutOfBoundsException{
        head.add(index, element);
        size++;
    }
    public boolean remove(E obj){
        if (!contains(obj))
            return false;
        int index = head.indexOf(obj);
        head.remove(index);
        size--;
        return true;
    }
    public void addFirst(E element){
        head.add(0, element);
        size++;
    }
    public void addLast(E element){
        head.add(size, element);
        size++;
    }
    public E get(int index) throws IndexOutOfBoundsException{
        return (head.get(index));
    }
    public E getFirst() throws IndexOutOfBoundsException{
        return (head.get(0));
    }
    public E getLast() throws IndexOutOfBoundsException{
        return (head.get(size - 1));
    }
    public int size(){
        return size;
    }
}