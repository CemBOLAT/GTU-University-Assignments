import java.util.Iterator;
import myContainerPackage.JavaContainer;
import myContainerPackage.JavaSet;
import java.io.FileWriter;
import java.util.Scanner;

/*
	Taken from pdf file !
	Your driver code will be in a separate class.
	*It will do the following
		**Test each methodat least 2 times and printing the results.
		**Do not forget to test the constructors.
		***Writes some sets to text files. Do not forget to include your saved files.
*/

public class JavaSetTest {
	public static void main(String[] args) {
		try{
			testDefault(); // not saving to file
			//testInteger();
			//testString();
		} catch (Exception e) {
			System.out.println(e);
		} finally {
			System.out.println("Done");
		}
	}

	// ***Writes some sets to text files. Do not forget to include your saved files.
	// I dont know what is meant by this line. I just saved the set to file.
	// While saving it to file, I used the toString method of JavaSet class.
	// I also used the save method of this class.
	public static <T extends Comparable<T>> void save(JavaSet<T> set, String fileName) {
		try {
			FileWriter fileWriter = new FileWriter(fileName, true);
			fileWriter.write(set.toString() + "\n");
			fileWriter.close();
		} catch (Exception e) {
			System.out.println(e);
		}
	}
	// I used this method to test the JavaSet class.
	public static void testInteger(){
		JavaSet<Integer> v = new JavaSet<Integer>(); // define outside of try-catch to use in finally
		try {
			Scanner scanner = new Scanner(System.in);
			System.out.println("Enter the number of elements to add:");
			int numElements = scanner.nextInt();
			if (numElements < 0) {
				throw new RuntimeException("Number of elements is invalid !");
			}
			System.out.println("Enter the elements:");
			for (int i = 0; i < numElements; i++) {
				int element = scanner.nextInt();
				v.Add(element);
			}
			System.out.println("Enter the element to remove:");
			numElements = scanner.nextInt();
			v.Remove(numElements);
			System.out.println("Enter the element to search:");
			numElements = scanner.nextInt();
			if (v.isIn(numElements)) {
				System.out.println("The element is in the set");
			} else {
				System.out.println("The element is not in the set");
			}
			scanner.close();
			JavaSet<Integer> cloneV = new JavaSet<>(v);
			if (cloneV.equals(v)){
				System.out.println("1 -- Equal to ! ");
			} else {
				System.out.println("1 -- Not Equal to ! ");
			}
			JavaSet<Integer> notClone = new JavaSet<>(v.Size());
			if (cloneV.equals(notClone)){
				System.out.println("2 -- Equal to ! ");
			} else {
				System.out.println("2 -- Not Equal to ! ");
			}
			Integer	total = 0;
			var it = v.getIterator();
			while (it.hasNext()) {
				total += it.next();
			}
			System.out.println("Total = " + total);
			save(v, "set.txt"); // saving to file
		} catch (Exception e) {
			throw e;
		} finally {
			System.out.println(v);// last mapped vector !
		}
	}
	// I used this method to test the JavaSet class.
	public static void testString(){
		JavaSet<String> v = new JavaSet<String>(); // define outside of try-catch to use in finally
		try {
			Scanner scanner = new Scanner(System.in);
			System.out.println("Enter the number of elements to add:");
			int numElements = scanner.nextInt();
			if (numElements < 0) {
				throw new RuntimeException("Number of elements is invalid !");
			}
			System.out.println("Enter the elements:");
			for (int i = 0; i < numElements; i++) {
				String element = scanner.next();
				v.Add(element);
			}
			System.out.println("Enter the element to remove:");
			String element = scanner.next();
			v.Remove(element);
			System.out.println("Enter the element to search:");
			element = scanner.next();
			if (v.isIn(element)) {
				System.out.println("The element is in the set");
			} else {
				System.out.println("The element is not in the set");
			}
			scanner.close();
			var iterator = v.getIterator();
			int index = 0;
			JavaSet<String> cloneV = new JavaSet<>(v);
			if (cloneV.equals(v)){
				System.out.println("1 -- Equal to ! ");
			} else {
				System.out.println("1 -- Not Equal to ! ");
			}
			JavaSet<String> notClone = new JavaSet<>(v.Size());
			if (cloneV.equals(notClone)){
				System.out.println("2 -- Equal to ! ");
			} else {
				System.out.println("2 -- Not Equal to ! ");
			}
			String	total = "";
			var it = v.getIterator();
			while (it.hasNext()) {
				total += it.next();
			}
			System.out.println("Total = " + total);
			save(v, "set.txt"); // saving to file
		} catch (Exception e) {
			throw e;
		} finally {
			System.out.println(v);// last mapped vector !
		}
	}
	public static void testDefault(){
		JavaSet<Integer> v = new JavaSet<Integer>(); // define outside of try-catch to use in finally
		try {
			for (int i = 0; i < 5; i++) {
				v.Add(i * 2);
			}
			v.Add(0); // throwing exception because it is already in the set
			v.Add(550); // adding 550
			v.Add(443); // adding 443
			v.Add(4); // throwing exception because it is already in the set
			v.Remove(4); // removing 4
			v.Remove(0); // removing 0
			v.Remove(1111); // throwing exception because it is not in the set

			if (v.isIn(443)) {
				System.out.println("The element is in the vector"); // this line must be printed
			} else {
				System.out.println("The element is not in the vector");
			}

			JavaSet<Integer> cloneV = new JavaSet<Integer>(v);
			if (cloneV.equals(v)){
				System.out.println("1 -- Equal to ! "); // this line must be printed
			} else {
				System.out.println("1 -- Not Equal to ! ");
			}
			JavaSet<Integer> notClone = new JavaSet<>(v.Size());
			if (cloneV.equals(notClone)){
				System.out.println("2 -- Equal to ! ");
			} else {
				System.out.println("2 -- Not Equal to ! "); // this line must be printed
			}
			//System.out.println(v.getData(-4)); //exception occurs
			//JavaSet<Integer> vv = new JavaSet<>(-2); //exception occurs
			Integer	total = 0;
			var it = v.getIterator();
			while (it.hasNext()) {
				total += it.next();
			}
			System.out.println("Total = " + total);

		} catch (Exception e) {
			throw e;
		}
		finally {
			System.out.println(v);// last mapped vector !
		}
	}
}


