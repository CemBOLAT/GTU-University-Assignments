/**
 * Tv.java
 * <br>
 * Tv class is a subclass of AbsDevice class.
 * <br>
 * It has a constructor that takes 4 parameters and calls the constructor of the superclass with the same parameters.
*/
public class Tv extends AbsDevice {
	/**
	 * Constructor for Tv class
	 * <br>
	 * Time Complexity: O(1)
	 * <br>
	 * Because the constructor has constant time complexity
	 * @param category The category of the device
	 * @param name The name of the device
	 * @param price The price of the device
	 * @param quantity The quantity of the device
	 * @throws IllegalArgumentException if any of the parameters are invalid
	*/
	public Tv(String category, String name, double price, int quantity) throws IllegalArgumentException{
		super(category, name, price, quantity);
	}

}
