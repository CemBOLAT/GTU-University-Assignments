import java.sql.Timestamp;
import java.io.PrintWriter;

/**
 * A class representing a file system.
 * <p> This class is used to represent a file system. </p>
 * <p> It contains a root directory. </p>
 * <p> It contains methods for creating, deleting, moving, and searching for files and directories. </p>
 * <p> It also contains methods for printing the directory tree, listing the contents of a directory, and sorting the contents of a directory by date created. </p>
 * <p> It also contains methods for changing the current directory and getting the current path. </p>
 * 
 * <p> The class has the following methods: </p>
 * <ul>
 * <li> {@link #FileSystem()} </li>
 * <li> {@link #createFile(String, Directory)} </li>
 * <li> {@link #createDirectory(String, Directory)} </li>
 * <li> {@link #deleteFileOrDirectory(String, Directory)} </li>
 * <li> {@link #moveElement(String, String, Directory)} </li>
 * <li> {@link #search(String)} </li>
 * <li> {@link #printDirectoryTree(Directory)} </li>
 * <li> {@link #listContents(Directory)} </li>
 * <li> {@link #sortDirectoryByDate(Directory)} </li>
 * <li> {@link #getCurrentPath(Directory)} </li>
 * <li> {@link #changeDirectory(Directory, String)} </li>
 * <li> {@link #getRoot()} </li>
 * </ul>
 * 
 */

public class FileSystem {
	private final Directory	root; // The root directory
	private static final int ASCII_ACK = 6; // ASCII value for ACK character (used for saving)
	/**
	 * Creates a new file system.
	 *
	 * <p> The file system initially contains a root directory. </p>
	 */
	public FileSystem() {
		root = new Directory("/", null);
	}

	/**
	 * Creates new file to parent directory.
	 *
	 * @param name the name of the file
	 * @param parent the parent directory
	 * @throws IllegalArgumentException if the same named element already exists
	 */
	public void createFile(String name, Directory parent){
		FileSystemElement element = parent.getChild(name);
		if (element != null){
			throw new IllegalArgumentException("Same named element already exists.");
		}
		File newFile = new File(name, parent);
		parent.add(newFile); // use add method from Directory class
	}

	/**
	 * Creates new file to parent directory.
	 *
	 * @param name the name of the file
	 * @param parent the parent directory
	 * @throws IllegalArgumentException if the same named element already exists
	 */
	public void createDirectory(String name, Directory parent) throws IllegalArgumentException{
		FileSystemElement element = parent.getChild(name);
		if (element != null){
			throw new IllegalArgumentException("Same named element already exists.");
		}
		Directory newDirectory = new Directory(name, parent);
		parent.add(newDirectory);

	}
	/**
	 * Deletes a file or directory.
	 *
	 * @param name the name of the file or directory
	 * @param parent the parent directory
	 */
	public void deleteFileOrDirectory(String name, Directory parent){
		// Delete a element recursively
		int found = 0;
		for (var e : parent.getChildren()){
			if (e.getName().equals(name)){
				parent.remove(e); // use recursive remove method from Directory class
				found += 1;
				return;
			}
		}
		if (found == 0){
			System.out.println("Element not found.");
		}
	}

	/**
	 * Moves a file or directory to a new parent directory.
	 *
	 * @param name the name of the file or directory
	 * @param path the path of the new parent directory
	 * @param parent the parent directory
	 * @throws IllegalArgumentException if the element is not found in parent directory
	 * @throws IllegalArgumentException if the path is invalid
	 * @throws IllegalArgumentException if the same named element already exists in the new parent directory
	 */
	public void moveElement(String name, String path, Directory parent) throws IllegalArgumentException{
		FileSystemElement element = parent.getChild(name); // getting the element to move
		if (element == null){
			throw new IllegalArgumentException("Element not found.");
		}
		Directory newParent = changeDirectory(root, path); // getting the new parent directory
		if (newParent == null){
			throw new IllegalArgumentException("Invalid path.");
		}

		FileSystemElement e = newParent.getChild(name); // checking if the same named element already exists in the new parent directory
		if (e != null){
			throw new IllegalArgumentException("Element already exists in the new parent directory.");
		}

		parent.removeRef(element); // removing the reference of the element from the parent directory
		newParent.add(element); // adding the element to the new parent directory

		// printing the moved element information
		if (element instanceof Directory){
			System.out.println("Directory moved: " + element.getName() + " to " + path);
		}
		else {
			System.out.println("File moved: " + element.getName() + " to " + path);
		}
	}

	/**
	 * Search for an element in the file system recursively
	 * 
	 * <p> This method is used to search for an element in the file system recursively. </p>
	 * <p> This method is a helper method for the search method. </p>
	 * 
	 * @param directory the directory to search in
	 * @param name the name of the element to search for
	 * @param found the number of elements found
	 * @return the number of elements found
	 */
	private int searchRec(Directory directory, String name, int found){
		// Search for an element in a directory recursively
		for (var e : directory.getChildren()){
			if (e.getName().equals(name)){
				e.print("Found: ");
				found += 1;
			}
			if (e instanceof Directory){
				found = searchRec((Directory)e, name, found);
			}
		}
		return found;
	}

	/**
	 * Search for an element in the file system
	 * @param name the name of the element to search for
	 * @return true if the element is found, false otherwise
	 */
	public boolean search(String name){
		int f = searchRec(root, name, 0);
		return f > 0;
	}

	/**
	 * Print the directory tree recursively
	 * <br>
	 * <p> It calculates the path of the directory and prints the tree according to '/' in the path </p>
	 
	 * @param directory the directory to print
	 */
	public void printDirectoryTree(Directory directory){
		String path = getCurrentPath(directory);

		int nbrOfSpace = 0;
		if (!path.equals("/")){
			String[] token = path.split("/");
			for (int j = 0; j < token.length - 1; j++){
				for (int i = 0; i < nbrOfSpace; i++){
					System.out.print(" ");
				}
				System.out.println("* " + token[j] + "/");
				nbrOfSpace += 2;
			}
		}
		for (int i = 0; i < nbrOfSpace; i++){
			System.out.print(" ");
		}
		System.out.println((directory.getParent() == null) ? ("* / (Current Directory)") : ("* " + directory.getName() + "/ (Current Directory)"));
		for (var t : directory.getChildren()){
			for (int i = 0; i < nbrOfSpace + 2; i++){
				System.out.print(" ");
			}
			System.out.println(t);
		}
	}

	/**
	 * List the contents of a directory
	 *
	 * @param directory the directory to list the contents of
	 */
	public void listContents(Directory directory){
		// List the contents of a directory
		for (var e : directory.getChildren()){
			if (e instanceof File){
				System.out.println(e);
			} else {
				System.out.println(e);
			}
		}
	}
	/**
	 * Sort the contents of a directory by date created
	 * <p> This method is used to sort the contents of a directory by date created. </p>
	 * <p> I used java.util.Collections.sort() method to sort the contents of a directory. </p>
	 * <p> I used the compareTo() method to compare the date created of the files. </p>
	 * 
	 * @param directory the directory to sort the contents of
	 */
	public void sortDirectoryByDate(Directory directory){
		// Sort the contents of a directory by date created
		directory.sortByDate(); // use sortByDate method from Directory class
		for (var e : directory.getChildren()){
			String date = e.getDateCreated().toString();
			int index = date.indexOf(".");
			date = date.substring(0, index);
			if (e instanceof File){
				System.out.println(e + " (" + date + ")");
			} else {
				System.out.println(e + " (" + date + ")");
			}
		}
	}

	/**
	 * Get the path of a directory recursively
	 * <p> This method is used to get the path of a directory recursively. </p>
	 * <p> This method is a helper method for the getCurrentPath method. </p>
	 * 
	 * @param dir the directory to get the path of
	 * @param path the path of the directory
	 * @return the path of the directory
	 */
	private String getPathRec(Directory dir, String path){
		// Get the path of a directory recursively
		if (dir.getParent() == null)
			return path;
		return getPathRec((Directory)dir.getParent(), "/" + dir.getName() + path);
	}

	/**
	 * Get the current path of a directory
	 * @param directory the directory to get the path of
	 * @return the current path of the directory
	 */
	public String getCurrentPath(Directory directory){
		// Get the current path of a directory recursively
		if (directory.getParent() == null)
			return "/";
		return getPathRec(directory, "");
	}

	/**
	 * Change the current directory recursively
	 * <p> This method is used to change the current directory recursively. </p>
	 * <p> This method is a helper method for the changeDirectory method. </p>
	 * 
	 * @param directory the current directory
	 * @param path the path to change to
	 * @return the new directory
	 * @throws IllegalArgumentException if the path is invalid
	 */
	private Directory changeDirectoryRec(Directory directory, String path) throws IllegalArgumentException{
		// Change the current directory recursively
		if (path.length() == 0){
			return directory;
		}
		if (path.charAt(0) == '/'){ // // get rid of the first '/' for each recursive call /gtu/cpp/ -> gtu/cpp/ (split)-> /cpp/(this else if block) -> cpp/
			return changeDirectoryRec(directory, path.substring(1));
		}
		else {
			String[] parts = path.split("/");
			for (var e : directory.getChildren()){
				if (e.getName().equals(parts[0])){
					if (e instanceof Directory){
						if (parts.length == 1){
							return (Directory)e;
						}
						return changeDirectoryRec((Directory)e, path.substring(parts[0].length()));
					}
					else {
						throw new IllegalArgumentException("Invalid path.");
					}
				}
			}
		}
		throw new IllegalArgumentException("Invalid path.");
	}

	/**
	 * Change the current directory recursively
	 * <p> This method is used to change the current directory recursively. </p>
	 * 
	 * @param directory the current directory
	 * @param path the path to change to
	 * @return the new directory
	 * @throws IllegalArgumentException if the path is invalid
	 */
	public Directory changeDirectory(Directory directory , String path) throws IllegalArgumentException{
		// Change the current directory recursively
		if (path.equals("/")){ // if path is root
			return root;
		}
		else if (path.equals(".")){ // if path is current directory
			return directory;
		}
		else if (path.equals("..")){ // if path is parent directory
			if (directory.getParent() == null){
				return directory;
			}
			return (Directory)directory.getParent();
		}
		return changeDirectoryRec(root, path);
	}

	/**
	 * Returns the root directory.
	 * @return the root directory
	 */
	public Directory getRoot() {
		return root;
	}
}
