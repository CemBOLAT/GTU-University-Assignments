public class Deque<E extends Object> {
    private CircularArray<E> data;
    public Deque(){
        data = new CircularArray<E>();
    }
    public boolean offerFirst(E element){
        return data.offerFirst(element);
    }
    public void addFirst(E element){
        data.offerFirst(element);
    }
    public boolean offerLast(E element){
        return data.offer(element);
    }
    public void addLast(E element){
        data.offer(element);
    }
    public E pollFirst(){
        return data.poll();
    }
    public E pollLast(){
        return data.pollLast();
    }
    public E removeFirst() throws Exception{
        return data.remove();
    }
    public E removeLast() throws Exception{
        return data.removeLast();
    }
    public E peekFirst(){
        return data.peek();
    }
    public E peekLast(){
        return data.peekLast();
    }
    public boolean removeLastOccurence(E element){
        return data.removeLastOccurence(element);  
    }
    public boolean removeFirstOccurence(E element){
        return data.removeFirstOccurence(element);  
    }
    public int size(){
        return data.size();
    }
    public String toString(){
        return data.toString();
    }
}