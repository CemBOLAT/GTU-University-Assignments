import java.util.Scanner;
/**
 * Main.java
 * <br>
 * Main class for the Electronics Inventory Management System.
 * <br>
 * This class contains the main method which is used to run the Electronics Inventory Management System.
 * <br>
 * The main method contains a loop which will keep running until the user chooses to exit the program.
 * <br>
 * The user can choose from a list of options to add, remove, update, list, find the cheapest, sort by price, calculate total value, restock, and export the inventory.
 * <br>
 * The user can also choose to exit the program.
 */
public class Main {
	/**
	 * Main method for the Electronics Inventory Management System.
	 * <br>
	 * This method contains a loop which will keep running until the user chooses to exit the program.
	 * <br>
	 * The user can choose from a list of options to add, remove, update, list, find the cheapest, sort by price, calculate total value, restock, and export the inventory.
	 * <br>
	 * Time Complexity: O(n ^ 2) (worst case) where n is the number of devices in the inventory
	 * @param args Command line arguments
	 */
	public static void main(String[] args) {
		Inventory inventory = new Inventory();
		System.out.println("Welcome to the Electronics Inventory Management System!\n");
		try{
			Scanner scanner = new Scanner(System.in);
			boolean	 isExit = false;
			int option = -1;

			inventory.loadFromFile(Inventory.importFile);
			while (!isExit){
				option = -1;
				try {
					do {
						printMenu();
						String input = scanner.nextLine();
						try {
							option = Integer.parseInt(input);
						} catch (NumberFormatException e){
							System.out.println("Invalid option, please try again.");
							continue;
						}
						if (option < 0 || option > 9)
							System.out.println("Invalid option, please try again.");
					} while (option < 0 || option > 9);
					switch(option){
						case 1:
							inventory.addDevice(scanner);
						break;
						case 2:
							inventory.removeDevice(scanner);
						break;
						case 3:
							inventory.updateDevice(scanner);
						break;
						case 4:
							inventory.listDevices();
						break;
						case 5:
							inventory.findCheapestDevice();
						break;
						case 6:
							inventory.sortDevicesByPrice();
						break;
						case 7:
							inventory.calculateTotalValue();
						break;
						case 8:
							inventory.restockDevice(scanner);
						break;
						case 9:
							inventory.exportInventoryReport();
						break;
						case 0:
							isExit = true;
							inventory.saveToFile(Inventory.importFile);
							System.out.println("Goodbye!");
						break;
					}
				} catch (Exception e){
					System.out.println(e.getMessage());
				}
			}
		} catch (Exception e){
			System.err.println(e.getMessage());
			inventory.saveToFile(Inventory.importFile);
		}
	}
	/**
	 * This method is used to print the menu options
	 * <br>
	 * Time Complexity: O(1)
	 * <br>
	 * Because printing the menu options has constant time complexity
	 */
	private static void printMenu(){
		drawLine();
		System.out.println("Please select an option:");
		System.out.println("1. Add a new device");
		System.out.println("2. Remove a device");
		System.out.println("3. Update device details");
		System.out.println("4. List all devices");
		System.out.println("5. Find the cheapest device");
		System.out.println("6. Sort devices by price");
		System.out.println("7. Calculate total inventory value");
		System.out.println("8. Restock a device");
		System.out.println("9. Export inventory report");
		System.out.println("0. Exit");
		drawLine();
		System.out.print("Your Choice >> ");
	}
	/**
	 * This method is used to draw a line
	 * <br>
	 * Time Complexity: O(1)
	 * <br>
	 * Because drawing a line has constant time complexity
	 */
	private static void drawLine(){
		System.out.println("-------------------------------------------------");
	}
}
