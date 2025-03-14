public class Queue<E> {
    private CircularArray<E> data;
    public Queue(){
        data = new CircularArray<E>();
    }
    public void add(E element){
        data.offer(element);
    }
    public E remove() throws Exception{
        return data.remove();
    }
    public E poll(){
        return data.poll();
    }
    public E element() throws Exception{
        return data.element();
    }
    public E peek(){
        return data.peek();
    }
    public boolean offer(E element){
        return data.offer(element);
    }
    public E get(int index) throws Exception{
        return data.get(index);
    }
    public E set(int index, E element) throws Exception{
        return data.set(index, element);
    }
}