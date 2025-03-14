import java.sql.Timestamp;
import java.io.PrintWriter;

/**
 * A class representing a file in a file system.
 * <p> This class is used to represent a file in a file system. </p>
 * <p> It extends the FileSystemElement class. </p>
 *
 * <p> The class has the following methods: </p>
 * <ul>
 *  <li> {@link #File(String, FileSystemElement)}: Creates a new file with a name and a parent directory. </li>
 * 	<li> {@link #File(String, FileSystemElement, Timestamp)}: Creates a new file with a name, a parent directory, and a creation date. </li>
 *  <li> {@link #toString()}: Wanted format for printing the file. </li>
 *	<li> {@link #print(String)}: Prints the file with a prefix. </li>
 *	<li> {@link #saveElement(PrintWriter)}: Saves the file to a file. </li>
 * </ul>
 */

public class File extends FileSystemElement {

	/**
	 * Creates a new file with a name and a parent directory.
	 *
	 * @param name   the name of the file
	 * @param parent the parent directory
	 */
	public File(String name, FileSystemElement parent) {
		super(name, parent);
	}

	/**
	 * Creates a new file with a name, a parent directory, and a creation date.
	 *
	 * @param name		the name of the file
	 * @param parent	  the parent directory
	 * @param dateCreated the creation date of the file
	 */
	public File(String name, FileSystemElement parent, Timestamp dateCreated) {
		super(name, parent, dateCreated);
	}

	/**
	 * Wanted format for printing the file.
	 *
	 * @return the formatted string
	 */
	@Override
	public String toString(){
		return String.format("%-17s", getName());
	}

	/**
	 * Prints the file with a prefix.
	 *
	 * @param prefix the prefix to print
	 */
	@Override
	public void print(String prefix) {
		System.out.println(prefix + getFullPath());
	}

	/**
	 * Saves the file to a file.
	 *
	 * @param writer the writer to save the file
	 */
	@Override
	public void saveElement(PrintWriter writer){
		writer.println(getName() + " " + getDateCreated().getTime() + " " + getParent().getFullPath());
	}
}
