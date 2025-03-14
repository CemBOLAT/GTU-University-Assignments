public class Stack<E> {
    private SList<E> list;

    public Stack(){
        list = new SList<E>();
    }

    public boolean isEmpty(){
        return list.isEmpty();
    }

    public boolean push(E element){
        list.add(element);
        return true;
    }
    public E pop() throws IndexOutOfBoundsException{
        if (list.isEmpty())
            throw new IndexOutOfBoundsException();
        E element = list.get(list.size() - 1);
        list.remove(list.size() - 1);
        return element;
    }
    public E peek(){
        if (list.isEmpty())
            return null;
        return list.get(list.size() - 1);
    }
    public void clear(){
        list.clear();
    }
    public int size(){
        return list.size();
    }
}