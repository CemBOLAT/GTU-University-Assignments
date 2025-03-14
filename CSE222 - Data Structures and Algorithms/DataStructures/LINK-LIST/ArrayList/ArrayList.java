public  class ArrayList<E> {
    private E[] data;
    private int cap;
    private int size;
    private static final int STANDART_CAP = 10;
    @SuppressWarnings("unchecked")
    public  ArrayList(){
        cap = STANDART_CAP;
        data = (E[]) new Object[cap];
        size = 0;
    }

    public E get(int index) throws ArrayIndexOutOfBoundsException{
        if (index < 0 | index >= size)
            throw new ArrayIndexOutOfBoundsException("Out Of Bounds");
        return data[index];
    }

    public E set(int index, E newData) throws  ArrayIndexOutOfBoundsException{
        E returnVal = get(index);
        data[index] = newData;
        return returnVal;
    }

    public int size(){
        return size;
    }

    public boolean add(E el){
        if (size + 1 == cap){
            reallocate();
        }
        data[size] = el;
        size++;
        return true;
    }
    @SuppressWarnings("unchecked")
    private void reallocate(){
        int newCap = cap * 2;
        E[] newData = (E[]) new Object[newCap];
        for (int i = 0; i < size; i++){
            newData[i] = data[i];
        }
        data = newData;
        cap = newCap;
    }
    public void add(int index, E el) throws  ArrayIndexOutOfBoundsException{
        if (index < 0 | index >= size)
            throw new ArrayIndexOutOfBoundsException("Out Of Bounds");
        if (size + 1 == cap){
            reallocate();
        }
        for (int i = size; i > index; i--){
            data[i] = data[i - 1];
        }
        data[index] = el;
        size++;
    }
    public int indexOf(E target){
        for (int i = 0; i < size; i++){
            if (data[i].equals(target))
                return i;
        }
        return -1;
    }
    public E remove(int index) throws  ArrayIndexOutOfBoundsException{
        E returnVal = get(index);
        for (int i = index; i < size - 1; i++){
            data[i] = data[i + 1];
        }
        size--;
        return returnVal;
    }
}