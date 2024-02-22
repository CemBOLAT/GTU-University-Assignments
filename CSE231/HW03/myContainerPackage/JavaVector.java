package myContainerPackage;
import myContainerPackage.JavaContainer;
import java.util.Iterator;
import java.security.InvalidParameterException;

/**
 * JavaVector class
 *
 * It is a generic class for JavaVector.
 * @param <T> type of data
 * It has 15 methods:
 *
 * 1. Add(T n) : add an element to the container
 * 2. Remove(T n) : remove an element from the container
 * 3. Size() : return the size of the container
 * 4. getCapacity() : return the capacity of the container
 * 5. getData(int index) : return the data at the given index
 * 6. isIn(T element) : return true if the element is in the container
 * 7. getIterator() : return an iterator of the container
 * 8. toString() : return a string representation of the container
 * 9. equals(Object obj) : return true if the given object is equal to the container
 * 10. JavaVector() : default constructor
 * 11. JavaVector(int n) : constructor with capacity
 * 12. JavaVector(JavaVector other) : copy constructor
 * 13. IteratorImpl : private class for iterator
 * 14. hasNext() : return true if the iterator has next element
 * 15. next() : return the next element of the iterator
*/
public class JavaVector<T> implements JavaContainer<T> {

	private T[]	data;
	private int	size;
	private int	capacity;

	/**
	 * JavaVector constructor
	 * It creates a JavaVector object with default capacity 2
	*/
	@SuppressWarnings("unchecked")
	public JavaVector() {
		data = (T[]) new Object[2];
		size = 0;
		capacity = 2;
	}
	/**
	 * JavaVector constructor
	 * It creates a JavaVector object with given capacity
	 * @param n capacity of the JavaVector
	 * @throws InvalidParameterException if the given capacity is invalid
	*/
	@SuppressWarnings("unchecked")
	public JavaVector(int n) {
		if (n <= 0){
			throw new InvalidParameterException("Size of Capacity is invalid !");
		}
		data = (T[]) new Object[n];
		size = 0;
		capacity = n;
	}
	/**
	 * JavaVector constructor
	 * It creates a JavaVector object with given JavaVector object
	 * @param other JavaVector object
	*/
	public JavaVector(JavaVector<T> other){
		size = other.size;
		capacity = other.capacity;
		data = (T[]) new Object[capacity];
		for(var i = 0 ; i < size ; i++){
			data[i] = other.data[i];
		}
	}
	/**
	 * getData method
	 * @param index index of the data
	 * @return data at the given index
	 * @throws InvalidParameterException if the given index is out of bounds
	*/
	public T getData(int index) {
		if (index < 0){
			throw new InvalidParameterException("Index is out of bounds !");
		}
		else if (index >= size){
			throw new InvalidParameterException("Index is out of bounds !");
		}
		return data[index];
	}
	/**
	 * getExactData method
	 * @param index index of the data
	 * @param newData new data of the given index
	 * @throws InvalidParameterException if the given index is out of bounds
	*/
	public void setExactData(int index, T newData){
		if (index < 0){
			throw new InvalidParameterException("Index is out of bounds !");
		} else if (index >= size){
			throw new InvalidParameterException("Index is out of bounds !");
		}

		data[index] = newData;
	}

	/**
	 * getCapacity method

	 * @return capacity of the container
	*/
	public int getCapacity() {
		return capacity;
	}

	/**
	 * getIterator method

	 * @return iterator of the container
	*/
	public Iterator<T> getIterator() {
		return new IteratorImpl();
	}

	/**
	 * Add method.
	 * It adds the given element to the container.
	 * If the size is equal to capacity, it doubles the capacity.
	 * If the size is equal to 0, it adds the element to the first index.
	 * Otherwise, it adds the element to the end of the container.
	 * It increases the size by 1.
	 * It gives a warning if the element is already in the container.
	 * @param element element to be added.
	 * @return true if the element is added to the container.
	 */
	@SuppressWarnings("unchecked")
	public boolean Add(T element) {
		if (size == capacity) {
			capacity *= 2;
			var newData = (T[]) new Object[capacity];
			for (int i = 0; i < size; i++) {
				newData[i] = data[i];
			}
			data = newData;
		}
		data[size++] = element;
		return true;
	}

	/**
	 * Remove method.
	 * It removes the given element from the container.
	 * If the size is less than or equal to capacity / 2, it halves the capacity.
	 * It creates a new array with the new capacity.
	 * It copies the elements except the given element to the new array.
	 * It assigns the new array to the data.
	 * It decreases the size by 1.
	 * @param element element to be removed.
	 * @return true if the element is removed from the container.
	 * @throws InvalidParameterException if the element is not in the container.
	 * @throws ArithmeticException if the container is empty.
	 */
	public boolean Remove(T element) {
		if (size == 0) {
			throw new ArithmeticException("Vector is empty");
		}
		if (!isIn(element)) {
			throw new InvalidParameterException("Element not in Vector");
		}
		if (size - 1 <= capacity / 2) {
			capacity /= 2;
		}
		var newData = (T[]) new Object[capacity];
		int newSize = 0;
		for (int i = 0; i < size; i++) {
			if (!data[i].equals(element)) {
				newData[newSize++] = data[i];
			}
		}
		data = newData;
		size = newSize;
		return true;
	}

	/**
	 * isIn method.
	 * It returns true if the element is in the container.
	 * Otherwise, it returns false.
	 * @param element element to be checked.
	 * @return true if the element is in the container.
	 */
	public boolean isIn(T element) {
		for (int i = 0; i < size; i++) {
			if (data[i].equals(element)) {
				return true;
			}
		}
		return false;
	}
	/**
	 * Size method.
	 * @return size of the container.
	 */
	@Override
	public int Size() {
		return size;
	}
	/**
	* equals(Object obj) method
	* @param obj object to be compared
	* @return true if the given object is equal to the container
	* @return false if the given object is not equal to the container
	* @return false if the given object is null or the given object is not a JavaSet object
	*/
	@Override
	public boolean equals(Object obj) {
		if (obj == null || getClass() != obj.getClass()) {
			return false;
		}

		var other = (JavaVector<T>) obj;

		if (size != other.size) {
			return false;
		}

		for (int i = 0; i < size; i++) {
			if (!data[i].equals(other.data[i])) {
				return false;
			}
		}

		return true;
	}
	/**
		* toString() method

		* @return string representation of the container
	*/
	@Override
	public String toString() {
		StringBuilder s = new StringBuilder("[");
		for (int i = 0; i < size; i++) {
			s.append(data[i]);
			if (i != size - 1) {
				s.append(", ");
			}
		}
		s.append("]");
		return String.format("Vector: %s, size: %d, capacity: %d", s.toString(), size, capacity);
	}

	/**
	 * IteratorImpl class.
	 * It is a private class for iterator.
	 */
	private class IteratorImpl implements Iterator<T> {
		private int index = 0;
		/**
		 * hasNext() method.
		 * @return true if the iterator has next element.
		 * It returns true if the iterator has next element.
		 * Otherwise, it returns false.
		 */
		@Override
		public boolean hasNext() {
			return index < Size();
		}
		/**
		 * next() method
		 * @return the next element of the iterator
		 * It returns the next element of the iterator.
		 */
		@Override
		public T next() {
			return data[index++];
		}
	}
}
