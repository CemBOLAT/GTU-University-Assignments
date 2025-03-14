
public class CircularArray<E extends Object>{
    private E[] data;
    private int cap = 8;
    private int size;
    private int front;
    private int rear;

    public CircularArray(){
        cap = 8;
        size = 0;
        front = 0;
        rear = 0;
        data = (E[]) new Object[cap];
    }
    public CircularArray(int c){
        cap = c;
        size = 0;
        front = 0;
        rear = 0;
        data = (E[]) new Object[cap];
    }
    public E get(int index) throws Exception{
        if (index < 0 || index >= size){
            throw new Exception("Out of Bounds");
        }
        return data[(front + index) % cap];
    }
    public E set(int index, E element) throws Exception{
        if (index < 0 || index >= size){
            throw new Exception("Out of Bounds");
        }
        E ret = data[(front + index) % cap];
        data[(front + index) % cap] = element;
        return ret;
    }
    public E element() throws Exception{
        if (size == 0)
            throw new Exception("No such element");
        return (data[front]);
    }
    public E peek(){
        if (size == 0)
            return null;
        return (data[front]);
    }
    public boolean offer(E element){ // insert rear
        if (size + 1 == cap){
            realloc();
        }
        if (size == 0){
            data[size] = element; 
        }
        else {
            rear = (rear + 1) % cap;
            data[rear] = element;
        }
        size++;
        return true;
    }
    public E remove()  throws Exception{ // remove front
        if (size == 0){
            throw new Exception("No such element");
        }
        else {
            E returnVal = data[front];
            front = (front + 1) % cap;
            size--;
            return returnVal;
        }
    }
    public E poll() { // remove front
        if (size == 0){
            return null;
        }
        else {
            E returnVal = data[front];
            front = (front + 1) % cap;
            size--;
            return returnVal;
        }
    }
    public String toString(){
        StringBuilder sb = new StringBuilder();
        for (int i = 0; i < size; i++){
            sb.append(data[(front + i) % cap] + " ");
        }
        return sb.toString();
    }
    public int size(){
        return size;
    }
    private void realloc(){
        E[] newData = (E[]) new Object[cap * 2];
        for (int i = 0; i < size; i++){
            newData[i] = data[front];
            front = (front + 1) % cap;
        }
        data = newData;
        front = 0;
        rear = size - 1;
        cap *= 2;
    }
}