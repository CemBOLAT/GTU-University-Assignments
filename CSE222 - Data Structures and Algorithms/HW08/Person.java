import java.util.*;
import java.text.SimpleDateFormat;


/**
 * <p>
 * The Person class represents a person in the social network.
 * </p>
 *
 * <p> The Person class has the following attributes: </p>
 *
 * <ul>
 * <li> <strong>name</strong> - The name of the person. </li>
 * <li> <strong>age</strong> - The age of the person. </li>
 * <li> <strong>hobbies</strong> - The list of hobbies of the person. </li>
 * <li> <strong>timestamp</strong> - The timestamp when the person was added to the social network. </li>
 * </ul>
 */
public class Person {
    /**
     * Field given from the instructor.
    */
    String name;
    int age;
    List<String> hobbies;
    Date timestamp;

    /**
     * Creates a new person with the given name, age, and hobbies.
     * @param name The name of the person.
     * @param age The age of the person.
     * @param hobbies The list of hobbies of the person.
     */
    public Person(String name, int age, List<String> hobbies) {
        this.name = name;
        this.age = age;
        this.hobbies = new ArrayList<>(hobbies);
        this.timestamp = new Date();
    }

    /**
     * toString method given from the instructor.
     * <br>
     * This method prints user with their name, age, and hobbies.
     * @return The string representation of the person.
     */
    @Override
    public String toString() {
        return name + " (Age: " + age + ", Hobbies: " + hobbies + ")";
    }

    private String TimestampConverter(Date ts){
        String pattern = "yyyy-MM-dd HH:mm:ss";
        SimpleDateFormat simpleDateFormat = new SimpleDateFormat(pattern);

        return simpleDateFormat.format(ts);
    }

    /**
     * Prints the person with their name and timestamp.
     * @return The string representation of the person.
     */
    public String print(){
        return name + " (Timestamp: " + TimestampConverter(timestamp) + ")";
    }
}
