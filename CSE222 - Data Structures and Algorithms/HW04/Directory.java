import java.sql.Timestamp;
import java.util.List;
import java.util.LinkedList;
import java.io.PrintWriter;

/**
 * A class representing a directory in a file system.
 * <p> This class is used to represent a directory in a file system. </p>
 * <p> It contains a list of children elements, which can be either files or directories. </p>
 * <p> It also contains methods for adding and removing children, as well as sorting them. </p>
 * <p> It extends the FileSystemElement class. </p>
 *
 * <p> The class has the following methods: </p>
 * <ul>
 * 	<li> {@link #Directory(String, Directory)}: Creates a new directory with a name and a parent directory. </li>
 * 	<li> {@link #Directory(String, Directory, Timestamp)}: Creates a new directory with a name, a parent directory, and a creation date. </li>
 * 	<li> {@link #add(FileSystemElement)}: Adds a child element to the directory. </li>
 * 	<li> {@link #remove(FileSystemElement)}: Removes a child element from the directory. </li>
 * 	<li> {@link #removeRef(FileSystemElement)}: Removes a single child element from the directory. </li>
 * 	<li> {@link #toString()}: Wanted format for printing the directory with '*' and '/'. </li>
 * 	<li> {@link #print(String)}: Prints the directorys full path to the console. </li>
 * 	<li> {@link #sortByDate()}: Sorts the children of the directory by name. </li>
 * 	<li> {@link #getChildren()}: Returns the children of the directory. </li>
 * 	<li> {@link #saveElement(PrintWriter)}: Saves the directory and its children to a file. </li>
 * 	<li> {@link #getChild(String)}: Returns the child element with the given name. </li>
 * </ul>
 */

public class Directory extends FileSystemElement {
	private List<FileSystemElement> children; // The children of the directory
	private static final int ASCII_ACK = 6; // ASCII value for ACK character (used for saving)

	/**
	 * Creates a new directory with a name and a parent directory.
	 *
	 * @param name   the name of the directory
	 * @param parent the parent directory
	 */
	public Directory(String name, Directory parent) {
		super(name, parent);
		children = new LinkedList<FileSystemElement>();
	}

	/**
	 * Creates a new directory with a name, a parent directory, and a creation date.
	 *
	 * @param name		the name of the directory
	 * @param parent	  the parent directory
	 * @param dateCreated the creation date of the directory
	 */
	public Directory(String name, Directory parent, Timestamp dateCreated) {
		super(name, parent, dateCreated);
		children = new LinkedList<FileSystemElement>();
	}

	/**
	 * Adds a child element to the directory.
	 *
	 * @param child the child element to add
	 */
	public void add(FileSystemElement child) {
		children.add(child);
		child.setParent(this);
	}

	/**
	 * Removes a child element from the directory recursively.
	 * <p> This method is used to remove a directory and all its children. and its helper method for remove(FileSystemElement child) </p>
	 *
	 * @param child the child element to remove
	 */
	private void removeRec(FileSystemElement child){
		if (child instanceof Directory){
			Directory dir = (Directory) child;
			for (var e : dir.getChildren()){
				removeRec(e);
			}
		}
		children.remove(child);
		child.setParent(null);

	}

	/**
	 * Removes a child element from the directory.
	 * <p> This method is used in deleting part of the file system. </p>
	 *
	 * @param child the child element to remove
	 */
	public void remove(FileSystemElement child) {
		removeRec(child);
		if (child instanceof Directory) {
			System.out.println("Directory deleted: " + child.getName() + "/");
		} else {
			System.out.println("File deleted: " + child.getName());
		}
	}

	/**
	 * Removes a single child element from the directory.
	 * <p> This method is used in moving part of the file system. </p>
	 *
	 * @param child the child element to remove
	 */
	public void removeRef(FileSystemElement child) {
		children.remove(child);
		child.setParent(null);
	}

	/**
	 * Wanted format for printing the directory with '*' and '/'
	 *
	 * @return the formatted string
	 */
	@Override
	public String toString(){
		return String.format("* %-15s", getName() + "/");
	}

	/**
	 * Prints the directorys full path to the console.
	 *
	 * @param prefix the prefix to print before the directory
	 */
	@Override
	public void print(String prefix) {
		System.out.println(prefix + getFullPath());
	}

	/**
	 * Sorts the children of the directory by name.
	 *
	 * <p> This method is used in sorting the children of the directory. </p>
	 * <br>
	 * postcondition: the children of the directory are sorted by name
	 */
	public void sortByDate() {
		children.sort((a, b) -> a.getDateCreated().compareTo(b.getDateCreated()));
	}

	/**
	 * Returns the children of the directory.
	 *
	 * @return the children of the directory
	 */
	public List<FileSystemElement> getChildren() {
		return children;
	}

	/**
	 * Saves the directory and its children to a file.
	 *
	 * <p> This method is externalized to the file system. </p>
	 * <p> I used the ASCII value of ACK character to understand the format of element. </p>
	 * <p> I add deleting and loading from the file system to make control of the file system. <like a tester> </p>
	 *
	 * @param writer the PrintWriter to write to the file
	 */
	@Override
	public void saveElement(PrintWriter writer) {
		if (getParent() != null) { // ignore root directory
			writer.println((char)ASCII_ACK + getName() + " " + getDateCreated().getTime() + " " + getParent().getFullPath());
		}
		for (var child : children) {
			child.saveElement(writer);
		}
	}

	/**
	 * Returns the child element with the given name.
	 *
	 * @param name the name of the child element
	 * @return the child element with the given name, or null if it does not exist
	 */
	public FileSystemElement getChild(String name){
		for (var e : children){
			if (e.getName().equals(name)){
				return e;
			}
		}
		return null;
	}
}
