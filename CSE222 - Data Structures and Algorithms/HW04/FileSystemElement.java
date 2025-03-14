import java.sql.Timestamp;
import java.io.PrintWriter;

/**
 * Represents a file system element.
 * <p> This class is used to represent a file system element. </p>
 * <p> It is the superclass of the Directory and File classes. </p>
 * <p> It contains the name of the file system element, the date created, and the parent directory. </p>
 *
 * <p> The class has the following methods: </p>
 * <ul>
 *  <li> {@link #FileSystemElement(String, FileSystemElement)}: Creates a new file system element with a name and a parent directory. </li>
 *  <li> {@link #FileSystemElement(String, FileSystemElement, Timestamp)}: Creates a new file system element with a name, a parent directory, and a creation date. </li>
 *  <li> {@link #getName()}: Returns the name of the file system element. </li>
 *  <li> {@link #getDateCreated()}: Returns the date created. </li>
 *  <li> {@link #getParent()}: Returns the parent directory. </li>
 *  <li> {@link #setParent(FileSystemElement)}: Sets the parent directory. </li>
 *  <li> {@link #getFullPath()}: Returns the full path of the file system element. </li>
 *  <li> {@link #print(String)}: Prints the file system element with a prefix. </li>
 *  <li> {@link #saveElement(PrintWriter)}: Saves the file system element to a file. </li>
 * </ul>
 *
 */
public abstract class FileSystemElement {
	private final String		name;
	private final Timestamp	 dateCreated;
	private FileSystemElement   parent;

	/**
	 * Creates a new file system element.
	 * @param name the name of the file system element
	 * @param parent the parent directory
	 */
	public FileSystemElement(String name, FileSystemElement parent) {
		this.name = name;
		this.dateCreated = new Timestamp(System.currentTimeMillis());
		this.parent = parent;
	}

	/**
	 * Creates a new file system element.
	 * @param name the name of the file system element
	 * @param parent the parent directory
	 * @param dateCreated the date created
	 */
	public FileSystemElement(String name, FileSystemElement parent, Timestamp dateCreated) {
		this.name = name;
		this.dateCreated = dateCreated;
		this.parent = parent;
	}

	/**
	 * Returns the name of the file system element.
	 * @return the name of the file system element
	 */
	public String getName() {
		return name;
	}

	/**
	 * Returns the date created.
	 * @return the date created
	 */
	public Timestamp getDateCreated() {
		return dateCreated;
	}

	/**
	 * Returns the parent directory.
	 * @return the parent directory
	 */
	public FileSystemElement getParent() {
		return parent;
	}

	/**
	 * Sets the parent directory.
	 * @param parent the parent directory
	 */
	public void setParent(FileSystemElement parent) {
		this.parent = parent;
	}

	/**
	 * Returns the path of the file system element.
	 * @return the path of the file system element
	 */
	private String getPathRecursive() {
		if (getParent() == null) {
			return "";
		}
		return getParent().getPathRecursive() + "/" + getName();
	}

	/**
	 * Returns the full path of the file system element.
	 * @return the full path of the file system element
	 */
	public String getFullPath() {
		if (getParent() == null) {
			return "/";
		}
		return getPathRecursive();
	}

	/**
	 * Prints the file system element with a prefix.
	 * @param prefix the prefix to print
	 */
	public abstract void print(String prefix);
	/**
	 * Saves the file system element to a file.
	 * @param writer the writer to save the file
	 */
	public abstract void saveElement(PrintWriter writer);
}
