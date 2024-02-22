package myContainerPackage;
import java.util.Iterator;

/***
 * JavaContainer interface
 *
 * It is a generic interface for JavaSet and JavaVector
 * @param <T> type of data
 * It has 4 methods:
 * 1. Add(T n) : add an element to the container
 * 2. Remove(T n) : remove an element from the container
 * 3. Size() : return the size of the container
 * 4. getIterator() : return an iterator of the container
*/
public interface JavaContainer <T> {
	/**
	 * Add method
	 *
	 * It adds the given element to the container
	 * @param n element to be added
	*/
	public boolean		Add(T n);
	/**
	 * Remove method
	 *
	 * It removes the given element from the container
	 * @param n element to be removed
	 * @return true if the element is removed
	 * @throws InvalidParameterException if the element is not in the container
	 * @throws ArithmeticException if the container is empty
	*/
	public boolean		Remove(T n);
	/**
	 * Size method
	 *
	 * @return size of the container
	*/
	public int			Size();
	/**
	 * getIterator method
	 *
	 * @return iterator of the container
	*/
	public Iterator<T>	getIterator();

}


