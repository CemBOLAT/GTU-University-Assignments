/**
 * Laptop.java
 * <br>
 * Laptop class is a subclass of AbsDevice class.
 * <br>
 * It has a constructor that takes in 4 parameters and passes them to the super class constructor
 */

public class Laptop extends AbsDevice {
	/**
	 * Constructor for Laptop class
	 * <br>
	 * Time Complexity: O(1)
	 * <br>
	 * Because the constructor has constant time complexity
	 *
	 * @param category The category of the device
	 * @param name The name of the device
	 * @param price The price of the device
	 * @param quantity The quantity of the device
	 * @throws IllegalArgumentException if any of the parameters are invalid
	 */
	public Laptop(String category, String name, double price, int quantity) throws IllegalArgumentException{
		super(category, name, price, quantity);
	}

}
