import java.io.FileWriter;
import java.io.PrintWriter;
import java.util.Scanner;
import java.sql.Timestamp;

/** 
 * A class for testing the file system.
 * 
 * <p> This class is used to test the file system. </p>
 * <p> It contains a main method that allows the user to interact with the file system. </p>
 * <p> The user can change directories, list directory contents, create files and directories, delete files and directories, move files and directories, search for files and directories, print the directory tree, sort contents by date created, and exit the program. </p>
 * 
 * <p> The file system is saved to a file called "filesystem.txt" when the user exits the program. (external property) </p>
 * <p> The file system is loaded from the file "filesystem.txt" when the program starts. (external property) </p>
 */

public class Main {

	private static final String FILE_SYSTEM_FILE = "filesystem.txt"; // external property
	private static Directory currentDirectory; // current directory as teacher showed in ps
	private static FileSystem fileSystem = new FileSystem(); // file system as teacher showed in ps
	private static final int ASCII_ACK = 6; // ASCII code for ACK character (used to differentiate between files and directories while saving and loading) external property

	/**
	 * Main method to test the file system
	 * 
	 * <p> The user can change directories, list directory contents, create files and directories, delete files and directories, move files and directories, search for files and directories, print the directory tree, sort contents by date created, and exit the program. </p>
	 * <p> The file system is saved to a file called "filesystem.txt" when the user exits the program. (external property) </p>
	 * <p> The file system is loaded from the file "filesystem.txt" when the program starts. (external property) </p>
	 * <br>
	 * <p> The user can enter the following options: </p>
	 * <p> 1. Change directory </p>
	 * <p> 2. List directory contents </p>
	 * <p> 3. Create file/directory </p>
	 * <p> 4. Delete file/directory </p>
	 * <p> 5. Move file/directory </p>
	 * <p> 6. Search file/directory </p>
	 * <p> 7. Print directory tree </p>
	 * <p> 8. Sort contents by date created </p>
	 * <p> 9. Exit </p>
	 * 
	 * @param args the command line arguments
	 */
	public static void main(String[] args){
		currentDirectory = fileSystem.getRoot(); // initial directory is root
		loadFileSystem(fileSystem); // load file system from file
		boolean exit = false;
		while (!exit){
			printMenu();
			try {
				int option = Integer.parseInt(System.console().readLine()); // read user input
				switch (option){
					case 1: changeDirectory(); break;
					case 2: listDirectoryContents(); break;
					case 3: createFileOrDirectory(); break;
					case 4: deleteFileOrDirectory(); break;
					case 5: moveFileOrDirectory(); break;
					case 6: searchFileOrDirectory(); break;
					case 7: printDirectoryTree(); break;
					case 8: sortContentsByDateCreated(); break;
					case 9:
						exit = true;
						System.out.println("Saving and Exiting...");
						saverFileSystem();
						break;
					default:
						System.out.println("Invalid option. Please try again.");
				}
			} catch (NumberFormatException e){ // catch invalid input (non-integer)
				System.out.println("Invalid option. Please try again.");
			} catch (Exception e){
				System.out.println(e.getMessage()); // catch other exceptions
			}
		}
	}

	/**
	 * Method to get non-empty string input
	 * @param message the message to display to the user
	 * @return the non-empty string input
	 * @throws IllegalArgumentException if the input is empty
	 */
	private static String getString(String message) throws IllegalArgumentException { // method to get non-empty string input
		System.out.print(message);
		String input = System.console().readLine();
		if (input.isEmpty()) {
			throw new IllegalArgumentException("Input cannot be empty.");
		} else {
			return input;
		}
	}

	/**
	 * Method to change the current directory
	 */
	private static void changeDirectory(){
		currentDirectory.print("Current directory: ");
		String path = getString("Enter new directory path: ");
		currentDirectory = fileSystem.changeDirectory(currentDirectory, path);
		currentDirectory.print("Directory changed to: ");
	}

	/**
	 * Method to list the contents of the current directory
	 */
	private static void listDirectoryContents(){
		currentDirectory.print("Listing contents of ");
		fileSystem.listContents(currentDirectory);
	}

	/**
	 * Method to create a file or directory
	 * 
	 * @throws IllegalArgumentException if the input is invalid
	 */
	private static void createFileOrDirectory() throws IllegalArgumentException {
		currentDirectory.print("Current directory: "); 
		String option = getString("Create file or directory (f/d): "); // get user input
		if (option.equals("d")){
			String name = getString("Enter name for new directory: "); // get user input
			fileSystem.createDirectory(name, currentDirectory);
			System.out.println("Directory created: " + name + "/");
		} else if (option.equals("f")){ // create file
			String name = getString("Enter name for new file: "); // get user input
			fileSystem.createFile(name, currentDirectory);
			System.out.println("File created: " + name);
		} else {
			throw new IllegalArgumentException("Invalid option. Please try again.");
		}
	}

	/**
	 * Method to delete a file or directory
	 */
	private static void deleteFileOrDirectory(){
		currentDirectory.print("Current directory: ");
		String option = getString("Enter name of file/directory to delete: ");
		fileSystem.deleteFileOrDirectory(option, currentDirectory);

	}

	/**
	 * Method to move a file or directory
	 */
	private static void moveFileOrDirectory(){
		currentDirectory.print("Current directory: ");
		String name = getString("Enter name of file/directory to move: ");
		String path = getString("Enter new directory path: ");

		fileSystem.moveElement(name, path, currentDirectory);
	}

	/**
	 * Method to search for a file or directory
	 */
	private static void searchFileOrDirectory(){
		String name = getString("Search query: ");
		System.out.println("Searching from root...");
		if (!fileSystem.search(name)){
			System.out.println("Element not found: " + name);
		}
	}


	/**
	 * Method to print the directory tree
	 */
	private static void printDirectoryTree(){
		System.out.println("Path to current directory from root: ");
		fileSystem.printDirectoryTree(currentDirectory);
	}

	/**
	 * Method to sort the contents of the current directory by date created
	 */

	private static void sortContentsByDateCreated(){
		System.out.println("Sorting contents of " + fileSystem.getCurrentPath(currentDirectory) + " by date created:");
		fileSystem.sortDirectoryByDate(currentDirectory);
	}


	/**
	 * Method to save the file system to a file (external property)
	 */
	private static void saverFileSystem(){
		try{
			PrintWriter writer = new PrintWriter(new FileWriter(FILE_SYSTEM_FILE)); // save file system to file
			Directory root = fileSystem.getRoot();
			root.saveElement(writer); // save elements recursively
			writer.close();
		} catch (Exception e){
			System.out.println("Error saving file system.");
			/* Handle exception */
		}
	}

	/**
	 * Method to load the file system from a file (external property)
	 * 
	 * @param fileSystem the file system to load
	 */

	private static void loadFileSystem(FileSystem fileSystem){
		try {
			Scanner scanner = new Scanner(new java.io.File(FILE_SYSTEM_FILE)); // load file system from file
			String line;
			while (scanner.hasNextLine()){
				line = scanner.nextLine();
				String[] parts = line.split(" "); // split line into parts
				if (parts.length != 3){
					System.out.println("Error loading file system.");
					return;
				}
				if (parts[2].charAt(0) == '/' && parts[2].length() > 1){ // remove leading slash from path
					parts[2] = parts[2].substring(1);
				}
				if (parts[0].charAt(0) == (char)ASCII_ACK){ // differentiate between files and directories (directories start with ACK character)
					Directory parent = fileSystem.changeDirectory(fileSystem.getRoot(), parts[2]);
					if (parent != null){
						Directory newDirectory = new Directory(parts[0].substring(1), parent, new Timestamp(Long.parseLong(parts[1])));
						parent.add(newDirectory);
					}
				} else {
					Directory parent = fileSystem.changeDirectory(fileSystem.getRoot(), parts[2]); // create new file
					if (parent != null){
						File newFile = new File(parts[0], parent, new Timestamp(Long.parseLong(parts[1])));
						parent.add(newFile);
					}
				}
			}
			scanner.close();
		} catch (Exception e){
			System.out.println("Error loading file system.");
			/* Handle exception */
		}
	}
	/**
	 * Method to print the menu options
	 */
	private static void printMenu(){
		System.out.println("===== File System Management Menu =====");
		System.out.println("1. Change directory");
		System.out.println("2. List directory contents");
		System.out.println("3. Create file/directory");
		System.out.println("4. Delete file/directory");
		System.out.println("5. Move file/directory");
		System.out.println("6. Search file/directory");
		System.out.println("7. Print directory tree");
		System.out.println("8. Sort contents by date created");
		System.out.println("9. Exit");
		System.out.print("Please select an option: ");
	}
}
