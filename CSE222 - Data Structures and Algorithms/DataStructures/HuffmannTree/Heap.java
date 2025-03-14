import java.util.ArrayList;
import java.util.Comparator;

public class Heap<E extends Comparable<E>> {
	private ArrayList<E> arr;

	public Heap(){
		arr = new ArrayList<>();
	}
	public boolean offer(E element){
		arr.add(element);
		int i = size() - 1;
		while (i >= 0){
			int pi = getParent(i);
			if (arr.get(pi).compareTo(arr.get(i)) > 0){
				swap(pi, i);
				i = pi;
			}
			else {
				break;
			}
		}
		return true;
	}
	public E poll(){
		if (size() == 0)
			return null;
		E tmp = arr.get(0);
		arr.set(0, arr.get(size() - 1));
		arr.remove(size() - 1);
		if (size() == 0)
			return tmp;
		int i = 0;
		while (i < size())
		{
			int child = getRightChild(i);
			int lchild = getLeftChild(i);
			int minChild = child;
			if (child < size() && arr.get(child).compareTo(arr.get(lchild)) > 0){
				minChild = lchild;
			}
			if (minChild < size() && arr.get(i).compareTo(arr.get(minChild)) > 0){
				swap(i, minChild);
				i = minChild;
			}
			else{
				break;
			}
		}
		return tmp;
	}
	public E peek(){
		if (size() == 0)
			return null;
		return arr.get(0);
	}
	public int size(){
		return arr.size();
	}
	public boolean isEmpty(){
		return arr.isEmpty();
	}
	private int getLeftChild(int i){
		return ((i * 2) + 1);
	}
	private int getRightChild(int i){
		return ((i * 2) + 2);
	}
	private int getParent(int i){
		return (i / 2);
	}
	private void swap(int a, int b){
		E tmp = arr.get(a);
		arr.set(a, arr.get(b));
		arr.set(b, tmp);
	}
	public String toString(){
		String str = new String();
		for (int i = 0; i < size(); i++){
			str = str + arr.get(i) + " ";
		}
		return str;
	}
}
