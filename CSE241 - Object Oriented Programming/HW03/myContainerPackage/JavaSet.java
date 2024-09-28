package myContainerPackage;

import myContainerPackage.JavaContainer;
import java.util.Iterator;
import java.security.InvalidParameterException;

/**
 * JavaSet class
 *
 * It is a generic class for JavaSet.
 * @param <T> type of data
 * It has 15 methods:
 * 1. Add(T n) : add an element to the container
 * 2. Remove(T n) : remove an element from the container
 * 3. Size() : return the size of the container
 * 4. getCapacity() : return the capacity of the container
 * 5. getData(int index) : return the data at the given index
 * 6. isIn(T element) : return true if the element is in the container
 * 7. getIterator() : return an iterator of the container
 * 8. toString() : return a string representation of the container
 * 9. equals(Object obj) : return true if the given object is equal to the container
 * 10. JavaSet() : default constructor
 * 11. JavaSet(int n) : constructor with capacity
 * 12. JavaSet(JavaSet other) : copy constructor
 * 13. IteratorImpl : private class for iterator
 * 14. hasNext() : return true if the iterator has next element
 * 15. next() : return the next element of the iterator
 */

public class JavaSet<T extends Comparable<T>> implements JavaContainer<T> {
	private T[] data;
	private int size;
	private int capacity;

	/**
		* JavaSet constructor

		* It creates a JavaSet object with default capacity 2
	*/
	public JavaSet() {
		data = (T[]) new Comparable[2];
		capacity = 2;
		size = 0;
	}

	/**
		* JavaSet constructor

		* It creates a JavaSet object with given capacity
		* @param n capacity of the JavaSet
		* @throws InvalidParameterException if the given capacity is invalid
	*/
	public JavaSet(int n) {
		if (n <= 0) {
			throw new InvalidParameterException("Size of Capacity is invalid !");
		}
		capacity = n;
		data = (T[]) new Comparable[n];
		size = 0;
	}

	/**
		* JavaSet constructor

		* It creates a JavaSet object with given JavaSet object
		* @param other JavaSet object
	*/
	public JavaSet(JavaSet<T> other) {
		size = other.size;
		capacity = other.capacity;
		data = (T[]) new Comparable[capacity];
		for (int i = 0; i < size; i++) {
			data[i] = other.data[i];
		}
	}

	/**
		* getData() method

		* @param index index of the data
		* @return data at the given index
		* @throws InvalidParameterException if the given index is out of bounds
	*/
	public T getData(int index) {
		if (index < 0) {
			throw new InvalidParameterException("Index is out of bounds !");
		}
		else if (index >= size) {
			throw new InvalidParameterException("Index is out of bounds !");
		}
		return data[index];
	}

	/**
		* Size() method

		* @return size of the container
	*/
	@Override
	public int Size() {
		return size;
	}

	/**
		* getCapacity() method

		* @return capacity of the container
	*/
	public int getCapacity() {
		return capacity;
	}
	/**
		* getIterator() method

		* @return iterator of the container
	*/
	public Iterator<T> getIterator() {
		return new IteratorImpl();
	}
	/**
		* Add(T n) method

		* It adds the given element to the container
		* It doubles the capacity if the size is equal to the capacity
		* It adds the element to the container in order
		* It shifts the elements after the given element
		* It adds the element to the end if the element is the largest
		* It increases the size by 1
		* @param n element to be added
		* @return true if the element is added to the container
		* @throws InvalidParameterException if the element is already in the container
	*/
	public boolean Add(T n) {
		if (isIn(n)){
			throw new InvalidParameterException("Element is already in the Set");
		}
		if (size == capacity) {
			capacity *= 2;
		}
		if (size == 0) {
			data[0] = n;
			size++;
			return true;
		}
		T[] newData = (T[]) new Comparable[capacity];
		int index = 0;
		for (int i = 0; i < size; i++) {
			if (data[i].compareTo(n) < 0) {
				newData[index++] = data[i];
			} else {
				newData[index++] = n;
				for (int j = i; j < size; j++) {
					newData[index++] = data[j];
				}
				break;
			}
		}
		if (index == size) { // if the element is the largest
			newData[index] = n;
		}
		data = newData;
		size++;
		return true;
	}
	/**
		* Remove(T n) method

		* It removes the given element from the container
		* It halves the capacity if the size is equal to half of the capacity
		* It removes the element from the container
		* It shifts the elements after the given element
		* It decreases the size by 1
		* @param n element to be removed
		* @return true if the element is removed from the container
		* @throws InvalidParameterException if the given element is not in the container
		* @throws ArithmeticException if the container is empty
	*/
	public boolean Remove(T n) {
		if (size == 0){
			throw new ArithmeticException("Set is empty");
		}
		if (!isIn(n)){
			throw new InvalidParameterException("Element not in Set");
		}
		if (size - 1 == capacity / 2)
			capacity /= 2;
		var newData = (T[]) new Comparable[capacity];
		int index = 0;
		for (var i = 0; i < size; i++) {
			if (!data[i].equals(n))
				newData[index++] = data[i];
		}
		data = newData;
		size--;
		return true;
	}
	/**
		* isIn(T element) method

		* @param element element to be checked
		* @return true if the element is in the container
	*/
	public boolean isIn(T element) {
		for (var i = 0; i < size; i++) {
			if (data[i].equals(element)) {
				return true;
			}
		}
		return false;
	}

	/**
		* toString() method

		* @return string representation of the container
	*/
	@Override
	public String toString() {
		StringBuilder s = new StringBuilder("[");
		for (var i = 0; i < size; i++) {
			s.append(data[i]);
			if (i != size - 1) {
				s.append(", ");
			}
		}
		s.append("]");
		return String.format("Set: %s, size: %d, capacity: %d", s.toString(), size, capacity);
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

		var other = (JavaSet<T>) obj;

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
		* IteratorImpl class

		* It is a private class for iterator
	*/
	private class IteratorImpl implements Iterator<T> {
		private int index = 0;

		/**
			* hasNext() method

			* @return true if the iterator has next element
		*/
		@Override
		public boolean hasNext() {
			return index < size;
		}
		/**
			* next() method

			* @return next element of the iterator
		*/
		@Override
		public T next() {
			return data[index++];
		}
	}
}
