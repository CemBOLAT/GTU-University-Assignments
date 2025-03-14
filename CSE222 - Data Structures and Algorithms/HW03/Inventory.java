import java.util.ArrayList;
import java.util.LinkedList;
import java.util.Scanner;
import java.io.FileWriter;
import java.io.IOException;
import java.io.PrintWriter;
import java.io.File;
import java.io.FileNotFoundException;
import java.time.LocalDate;
import java.util.Locale;
import java.text.DecimalFormat;

/**
 * Inventory.java
 * <br>
 * Inventory represents a collection of devices.
 * <br>
 * It provides methods for adding, removing, restocking, and updating devices.
 * <br>
 * It also provides methods for exporting inventory report, finding the cheapest device, sorting devices by price, calculating total value of all devices, loading and saving inventory to a file, and listing all devices in the inventory.
 */
public class Inventory {
	/**
	 * The list of devices
	 */
	public LinkedList<ArrayList<Device>> devices;
	private int totalDevices = 0; // The total number of devices
	private final String[] categories = {"Laptop", "Tablet", "Tv", "Headphones", "Printer"}; // The list of categories
	private final String exportFile = "export.txt"; // The file to export to
	/**
	 * The file to import from
	 */
	public static final String importFile = "inventory.txt";
	/**
	 * Inventory constructor
	 * <br>
	 * Time Complexity: O(1)
	 * <br>
	 * Initializes the devices list has constant time complexity
	 */
	public Inventory(){
		devices = new LinkedList<>();
	}
	/**
	 * Add a device to the inventory
	 * <br>
	 * Average Time Complexity: O(n) where n is the number of categories
	 * <br>
	 * Worst Time Complextity: O(n * k) where n is the number of categories and k is the number of devices in the category
	 * <br>
	 * It iterates through the devices list to find the category of the device. If the category is not found, it creates a new category and adds the device to it. Otherwise, it adds the device to the existing category.
	 * <br>
	 * After taking input from the user, it adds the device to the inventory.
	 *
	 * @param scanner The scanner object to take input from
	 * @throws IllegalArgumentException if the category is invalid
	 */
	public void addDevice(Scanner scanner) throws IllegalArgumentException{
		Device device = takeDeviceInput(scanner);
		String category = device.getCategory();
		if (category == null){
			throw new IllegalArgumentException("Invalid category");
		}
		int index = -1;
		for (int i = 0; i < devices.size(); i++){
			if (!devices.get(i).isEmpty() && devices.get(i).get(0).getCategory().equals(category)){
				index = i;
				break;
			}
		}
		if (index == -1){
			ArrayList<Device> newCategory = new ArrayList<>();
			newCategory.add(device);
			devices.add(newCategory);
		} else {
			devices.get(index).add(device);
		}
		totalDevices++;
		System.out.printf("%s, %s, %.2f$, %d amount added...\n", device.getCategory(), device.getName(), device.getPrice(), device.getQuantity()); // Time Complexity: O(1)
	}
	/**
	 * Add a device to the inventory
	 * <br>
	 * Average Time Complexity: O(n) where n is the number of categories
	 * <br>
	 * Worst Time Complextity: O(n * k) where n is the number of categories and k is the number of devices in the category
	 * <br>
	 * It makes no sense to write javadoc for a private method, but I did it for assignment.
	 * Using this method to add devices from a file.
	 *
	 * @param device The device to add
	 * @throws IllegalArgumentException if the category is invalid
	 */
	private void addDevice(Device device) throws IllegalArgumentException{
		String category = device.getCategory();
		if (category == null){
			throw new IllegalArgumentException("Invalid category");
		}
		int index = -1;
		for (int i = 0; i < devices.size(); i++){
			if (devices.get(i).get(0).getCategory().equals(category)){
				index = i;
				break;
			}
		}
		if (index == -1){
			ArrayList<Device> newCategory = new ArrayList<Device>();
			newCategory.add(device);
			devices.add(newCategory);
		} else {
			devices.get(index).add(device);
		}
		totalDevices++;
	}
	/**
	 * Remove a device from the inventory
	 * <br>
	 * Time Complexity: O(n^2) which one n comes from the number of devices in the inventory and the other n comes fron remove method of the linked list
	 * <br>
	 * After taking input from the user, it removes the device from the inventory.
	 *
	 * @param scanner The scanner object to take input from
	 */
	public void removeDevice(Scanner scanner){
		String name = Inventory.getStringInput(scanner, "Enter name of device to remove: ");
		boolean isRemoved = false;
		// Time Complexity: O(n) because number of nodes times number of devices in each node is n
		for (var device : devices) { // Time Complexity: O(n) where n is the number of linked lists in the devices list
			for (int j = 0; j < device.size(); j++) { // Time Complexity: O(n) where n is the number of devices in the node of the linked list
				if (device.get(j).getName().equals(name)) { // Time Complexity: O(1)
					device.remove(j); // Time complexity is O(n) because it shifts all the elements after the removed element
					isRemoved = true;
					break;
				}
			}
		}
		if (isRemoved){
			printGreen(name + " removed.");
			totalDevices--;
		} else {
			printRed(name + " not found.");
		}
	}
	/**
	 * Take input from the user to determine if they want to add or remove stock
	 * <br>
	 * Time Complexity: O(1) because it takes input from the user and returns true or false.
	 * <br>
	 * It makes no sense to write javadoc for a private method, but I did it for assignment.
	 *
	 * @param scanner The scanner object to take input from
	 * @return true if the user wants to add stock, false if the user wants to remove stock
	*/
	private static boolean isAddDevice(Scanner scanner){
		String input;
		do {
			System.out.print("Do you want to add or remove stock? (Add/Remove): ");
			input = scanner.nextLine();
			if (input.equals("Add") || input.equals("Remove")){
				return input.equals("Add");
			} else {
				printRed("Invalid input, please try again.");
			}
		} while (true);
	}
	/**
	 * Restock a device in the inventory
	 * <br>
	 * Time Complexity: O(n) where n is the number of devices in the inventory
	 * <br>
	 * After taking input from the user, it restocks the device in the inventory.
	 * <br>
	 * Method lineer time complexity because it iterates through the devices list to find the device to restock.
	 *
	 * @param scanner The scanner object to take input from
	 */
	public void restockDevice(Scanner scanner){
		String name = Inventory.getStringInput(scanner, "Enter name of device to restock: ");
		boolean isRestocked = false;
		// Time Complexity: O(n) because number of nodes times number of devices in each node is n
		for (var device : devices) {
			for (var value : device) {
				if (value.getName().equals(name)) {
					boolean isAdd = isAddDevice(scanner);
					int quantity = Inventory.getIntInput(scanner, (isAdd ? "Enter quantity to add: " : "Enter quantity to remove: "));
					if (isAdd) {
						value.addStock(quantity); // Time Complexity: O(1)
					} else {
						value.removeStock(quantity); // Time Complexity: O(1)
					}
					isRestocked = true;
					break;
				}
			}
		}
		if (isRestocked){
			printGreen(name + " restocked.");
		} else {
			printRed(name + " not found.");
		}
	}
	/**
	 * Return the current date
	 * <br>
	 * Time Complexity: O(1) because it gets the current date and formats it to a string has constant time complexity
	 * It makes no sense to write javadoc for a private method, but I did it for assignment.
	 *
	 * @return The current date
	*/
	private String returnDate(){
		LocalDate date = LocalDate.now();
		String month = date.getMonth().toString().charAt(0) + date.getMonth().toString().substring(1).toLowerCase();
		String day = date.getDayOfMonth() + (date.getDayOfMonth() % 10 == 1 ? "st" : (date.getDayOfMonth() % 10 == 2 ? "nd" : (date.getDayOfMonth() == 3 ? "rd" : "th")));
		int year = date.getYear();
		return day + " " + month + " " + year;
	}
	/**
	 * Get the total value of all devices in the inventory
	 * <br>
	 * Time Complexity: O(n) where n is the number of devices in the inventory
	 * <br>
	 * Method lineer time complexity because it iterates through the devices list to find the total value of all devices.
	 * <br>
	 * It makes no sense to write javadoc for a private method, but I did it for assignment.
	 *
	 * @return The total value of all devices in the inventory
	*/
	private double getTotalValue(){
		double totalValue = 0;
		for (var device : devices) {
			for (var value : device) {
				totalValue += value.getPrice() * value.getQuantity();
			}
		}
		return totalValue;
	}
	/**
	 * Write a message to a file and print it to the console
	 * <br>
	 * Time Complexity: O(1)
	 * Method has constant time complexity because it writes a message to a file.
	 * It makes no sense to write javadoc for a private method, but I did it for assignment.
	 * @param writer The file writer object to write to
	 * @param message The message to write and print
	 */
	private void writeFile(FileWriter writer, String message){
		try {
			writer.write(message);
		} catch (IOException e) {
			System.err.println("Error writing to file: " + e.getMessage());
		}
	}
	/**
	 * Export an inventory report to the console with the details of all devices in the inventory
	 * <br>
	 * Time Complexity: O(n) where n is the number of devices in the inventory
	 * <br>
	 * Method lineer time complexity because it iterates through the devices list to print the details of all devices.
	 * @throws IOException if the file is the export file is invalid
	*/
	public void exportInventoryReport() throws IOException{
		FileWriter writer = new FileWriter(exportFile);
		writeFile(writer, "Electronics Shop Inventory Report\n");
		writeFile(writer, "Generated on: " + returnDate() + "\n\n");
		writeFile(writer, String.format("| %-3s | %-10s | %-4s | %-5s | %-8s |\n", "No.", "Category", "Name", "Price", "Quantity"));
		writeFile(writer, "-------------------------------------------------\n");
		int index = 1;
		for (var device : devices) {
			for (var value : device) {
				value.exportFilePrint(index, writer);
				index++;
			}
		}
		writeFile(writer, "\nSummary: \n");
		writeFile(writer, "- Total Number of Devices: " + totalDevices + "\n");

		double totalValue = getTotalValue(); // Time Complexity: O(n) where n is the number of devices in the inventory
		DecimalFormat df = new DecimalFormat("#,###,###.##");
		String str = df.format(totalValue);

		writeFile(writer, String.format("- Total Inventory Value:  $%s\n", str));
		writeFile(writer, "\nEnd of Report\n");
		writeFile(writer, "-----------------------------\n");
		writer.close();
	}
	/**
	 * Find the cheapest device in the inventory and prints it to the console with its details
	 * <br>
	 * Time Complexity: O(n) where n is the number of devices in the inventory
	 * <br>
	 * Method lineer time complexity because it iterates through the devices list to find the cheapest device.
	*/
	public void findCheapestDevice(){
		double cheapestPrice = Double.MAX_VALUE;
		Device cheapestDevice = null;
		for (var device : devices) {
			for (var value : device) {
				if (value.getPrice() < cheapestPrice) {
					cheapestPrice = value.getPrice();
					cheapestDevice = value;
				}
			}
		}
		if (cheapestDevice != null){
			System.out.println("The cheapest device is:\n" + cheapestDevice);
		} else {
			printRed("No devices found.");
		}
	}
	/**
	 * Sort devices by price
	 * <br>
	 * Time Complexity: O(n^2) where n is the number of devices in the inventory
	 * <br>
	 * Method has quadratic time complexity because it implements bubble sort to sort the devices by price.
	*/
	public void sortDevicesByPrice(){
		ArrayList<Device> allDevices = new ArrayList<Device>();
		int index = 1;
		for (var device : devices) {
			allDevices.addAll(device);
		}
		for (int i = 0; i < allDevices.size(); i++){
			for (int j = i + 1; j < allDevices.size(); j++){
				if (allDevices.get(i).getPrice() > allDevices.get(j).getPrice()){
					Device temp = allDevices.get(i);
					allDevices.set(i, allDevices.get(j)); // Time Complexity: O(1)
					allDevices.set(j, temp); // Time Complexity: O(1)
				}
			}
		}
		System.out.println("Devices sorted by price:");
		for (var allDevice : allDevices) {
			System.out.println(index + ". " + allDevice);
			index++;
		}
	}
	/**
	 * Calculate the total value of all devices in the inventory
	 * <br>
	 * Time Complexity: O(n) where n is the number of devices in the inventory
	 * <br>
	 * Method lineer time complexity because it calculates the total value of all devices in the inventory.
	*/
	public void calculateTotalValue(){
		double totalValue = getTotalValue(); // Time Complexity: O(n) where n is the number of devices in the inventory
		DecimalFormat df = new DecimalFormat("#,###,###.##");
		String str = df.format(totalValue);
		System.out.printf("Total value of all devices: $%s\n", str);
	}
	/**
	 * Check if a string is blank
	 * <br>
	 *
	 * Time Complexity: O(1) because it checks if the string is null or empty and trims the string if it is not null
	 * @param str The string to check
	 * @return true if the string is blank, false otherwise
	 */
	private static boolean isStringBlank(String str){
		return str == null || str.trim().isEmpty();
	}
	/**
	 * Update a device in the inventory
	 * <br>
	 * Time Complexity: O(n) where n is the number of devices in the inventory
	 * <br>
	 * Method lineer time complexity because it iterates through the devices list to find the device to update.
	 * @param scanner The scanner object to take input from
	 * @throws Exception if the device is not found
	*/
	public void updateDevice(Scanner scanner) throws Exception{
		String name = Inventory.getStringInput(scanner, "Enter the name of the device to update: ");
		boolean isUpdated = false;
		for (var device : devices) {
			for (var value : device) {
				if (value.getName().equals(name)) {
					System.out.print("Enter new price (leave blank to keep current price): ");
					String price = scanner.nextLine();
					if (!isStringBlank(price)) {
						try {
							value.setPrice(Double.parseDouble(price));
							printGreen("Price updated.");
						} catch (NumberFormatException e) {
							printRed("Invalid price, not updated.");
						}
					}
					System.out.print("Enter new quantity (leave blank to keep current quantity): ");
					String quantity = scanner.nextLine();
					if (!isStringBlank(quantity)) {
						try {
							value.setQuantity(Integer.parseInt(quantity));
							printGreen("Quantity updated.");
						} catch (NumberFormatException e) {
							printRed("Invalid quantity, not updated.");
						}
					}
					isUpdated = true;
					System.out.printf("%s details updated: Price - %.2f$, Quantity - %d\n", name, value.getPrice(), value.getQuantity());
					break;
				}
			}
		}
		if (isUpdated){
			printGreen(name + " updated.");
		} else {
			printRed(name + " not found.");
		}
	}
	/**
	 * List all devices in the inventory
	 * <br>
	 * Time Complexity: O(n) where n is the number of devices in the inventory
	 * <br>
	 * Method lineer time complexity because it iterates through the devices list to print the details of all devices.
	*/
	public void listDevices(){
		System.out.println("Device List:");
		System.out.print(this);
	}
	/**
	 * Return the string representation of the inventory
	 * <br>
	 * Time Complexity: O(n) where n is the number of devices in the inventory
	 * @return The string representation of the inventory
	*/
	public String toString(){
		StringBuilder   result = new StringBuilder();
		int totalDevices = 1;
		for (var device : devices) {
			for (var value : device) {
				result.append(totalDevices).append(". ").append(value).append("\n");
				totalDevices++;
			}
		}
		return result.toString();
	}
	/**
	 * Take String input from the user
	 * <br>
	 * Time Complexity: O(1)
	 * It makes no sense to write javadoc for a private method, but I did it for assignment.
	 * <br>
	 * Method has constant time complexity because it takes input from the user and returns it.
	 * @param scanner The scanner object to take input from
	 * @param message The message to display to the user
	 * @return The string input from the user
	 * @throws IllegalArgumentException if the scanner is invalid
	*/
	private static String getStringInput(Scanner scanner, String message) throws IllegalArgumentException{
		String result;
		if (scanner == null){
			throw new IllegalArgumentException("Invalid scanner");
		}
		do {
			System.out.print(message);
			result = scanner.nextLine();
			if (result.isEmpty()){
				printRed("Invalid input, please try again.");
			}
		} while (result.isEmpty());
		return result;
	}
	/**
	 * Take double input from the user
	 * <br>
	 * Time Complexity: O(1)
	 * It makes no sense to write javadoc for a private method, but I did it for assignment.
	 * <br>
	 * Method has constant time complexity because it takes input from the user and returns it.
	 *
	 * @param scanner The scanner object to take input from
	 * @param message The message to display to the user
	 * @return The double input from the user
	 * @throws IllegalArgumentException if the scanner is invalid
	*/
	private static double getDoubleInput(Scanner scanner, String message) throws IllegalArgumentException{
		double result = -1;
		if (scanner == null){
			throw new IllegalArgumentException("Invalid scanner");
		}
		do {
			System.out.print(message);
			String input = scanner.nextLine();
			try {
				result = Double.parseDouble(input);
			} catch (NumberFormatException e){
				printRed("Invalid input, please try again.");
				continue;
			}
			if (result < 0)
				printRed("Invalid input, please try again.");
		} while (result < 0);
		return result;
	}
	/**
	 * Take integer input from the user
	 * <br>
	 * Time Complexity: O(1)
	 * It makes no sense to write javadoc for a private method, but I did it for assignment.
	 * <br>
	 * Method has constant time complexity because it takes input from the user and returns it.
	 * @param scanner The scanner object to take input from
	 * @param message The message to display to the user
	 * @return The integer input from the user
	 * @throws IllegalArgumentException if the scanner is invalid
	*/
	private static int getIntInput(Scanner scanner, String message) throws IllegalArgumentException{
		int result = -1;
		if (scanner == null){
			throw new IllegalArgumentException("Invalid scanner");
		}
		do {
			System.out.print(message);
			String input = scanner.nextLine();
			try {
				result = Integer.parseInt(input);
			} catch (NumberFormatException e){
				printRed("Invalid input, please try again.");
				continue;
			}
			if (result < 0)
				printRed("Invalid input, please try again.");
		} while (result < 0);
		return result;
	}
	/**
	 * Print a message in red
	 * <br>
	 * Time Complexity: O(1)
	 * It makes no sense to write javadoc for a private method, but I did it for assignment.
	 * Method has constant time complexity because it prints a message in red.
	 * @param message The message to print
	*/
	private static void printRed(String message){
		System.out.println("\u001B[31m" + message + "\u001B[0m");
	}
	/**
	 * Print a message in green
	 * <br>
	 * Time Complexity: O(1)
	 * It makes no sense to write javadoc for a private method, but I did it for assignment.
	 * Method has constant time complexity because it prints a message in green.
	 * @param message The message to print
	*/
	private static void printGreen(String message){
		System.out.println("\u001B[32m" + message + "\u001B[0m");
	}
	/**
	 * Load inventory from a file
	 * <br>
	 * Time Complexity: O(n ^ 2) where n is the number of devices in the inventory
	 * <br>
	 * Method has quadratic time complexity because it reads the file line by line and splits the line by comma to get the category, name, price, and quantity of the device.
	 * <br>
	 * The method then adds the device to the inventory. The addDevice method has average time complexity of O(n) where n is the number of devices in the inventory.
	 * @param str The file name to load from
	 * @throws IllegalArgumentException if the file format is invalid
	*/
	public void loadFromFile(String str){
		System.out.println("Loading from file...");
		try {
			Scanner scanner = new Scanner(new File(str));
			while (scanner.hasNextLine()){
				String line = scanner.nextLine();
				String[] parts = line.split(",");
				if (parts.length != 4)
					throw new IllegalArgumentException("Invalid file format");
				String category = parts[0];
				String name = parts[1];
				double price = Double.parseDouble(parts[2]);
				int quantity = Integer.parseInt(parts[3]);
				switch (category) {
					case "Laptop":
						addDevice(new Laptop(category, name, price, quantity));
						break;
					case "Tablet":
						addDevice(new Tablet(category, name, price, quantity));
						break;
					case "Tv":
						addDevice(new Tv(category, name, price, quantity));
						break;
					case "Headphones":
						addDevice(new Headphones(category, name, price, quantity));
						break;
					case "Printer":
						addDevice(new Printer(category, name, price, quantity));
						break;
					default:
						throw new IllegalArgumentException("Invalid category");
				}
			}
			scanner.close();
		} catch (FileNotFoundException e){
			System.err.println("Error loading from file: " + e.getMessage());
		}
	}
	/**
	 * Save inventory to a file
	 * <br>
	 * Time Complexity: O(n) where n is the number of devices in the inventory
	 * <br>
	 * Method has linear time complexity because it iterates through the devices list to save the details of all devices to a file.
	 *
	 * @param str The file name to save to
	*/
	public void saveToFile(String str){
		System.out.println("Saving to file...");
		try {
			PrintWriter writer = new PrintWriter(new FileWriter(str));
			for (var ll : devices ){
				for (var node : ll){
					writer.printf(Locale.US, "%s,%s,%.2f,%d%n",
							node.getCategory(),
							node.getName(),
							node.getPrice(),
							node.getQuantity());
				}
			}
			writer.close();
		} catch (IOException e) {
			System.err.println("Error saving to file: " + e.getMessage());
		}
	}
	/**
	 * Print a line
	 * <br>
	 * Time Complexity: O(1)
	 * It makes no sense to write javadoc for a private method, but I did it for assignment.
	 * Method has constant time complexity because it prints a line.
	*/
	private static void drawLine(){
		System.out.println("-------------------------------------------------");
	}
	/**
	 * Take category input from the user
	 * <br>
	 * Time Complexity: O(n) where n is the number of categories
	 * <br>
	 * Method has linear time complexity because it iterates through the categories list to find the category input from the user.
	 * It makes no sense to write javadoc for a private method, but I did it for assignment.
	 * @param scanner The scanner object to take input from
	 * @return The category input from the user
	 */
	private String takeCategoryInput(Scanner scanner){
		String category;
		do {
			category = getStringInput(scanner, "Enter category: ");
			boolean isValid = false;
			for (int i = 0; i < categories.length; i++){
				if (categories[i].equals(category)){
					isValid = true;
					break;
				}
			}
			if (isValid){
				break;
			}
			printRed("Invalid category, please try again.");
		} while (true);
		return category;
	}
	/**
	 * Take input from the user to add a device to the inventory
	 * <br>
	 * Time Complexity: O(1)
	 * It makes no sense to write javadoc for a private method, but I did it for assignment.
	 * <br>
	 * The method takes input from the user and returns the device to add for the addDevice method.
	 * @param scanner The scanner object to take input from
	 * @return The device to add
	 * @throws IllegalArgumentException if the scanner is invalid
	 * @throws IllegalArgumentException if any of the inputs are invalid
	*/
	public Device takeDeviceInput(Scanner scanner) throws IllegalArgumentException{
		if (scanner == null){
			throw new IllegalArgumentException("Invalid scanner");
		}
		String category;

		category = takeCategoryInput(scanner);
		String name = getStringInput(scanner, "Enter name: ");
		double price = getDoubleInput(scanner, "Enter price: ");
		int quantity = getIntInput(scanner, "Enter quantity: ");

		if (category.equals("Laptop")){
			return new Laptop(category, name, price, quantity);
		} else if (category.equals("Tablet")){
			return new Tablet(category, name, price, quantity);
		} else if (category.equals("Tv")){
			return new Tv(category, name, price, quantity);
		} else if (category.equals("Headphones")){
			return new Headphones(category, name, price, quantity);
		} else if (category.equals("Printer")){
			return new Printer(category, name, price, quantity);
		} else {
			throw new IllegalArgumentException("Invalid category");
		}
	}
}
