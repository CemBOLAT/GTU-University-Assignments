import java.util.Iterator; // Make sure to import Iterator from java.util
import myContainerPackage.JavaVector;
import myContainerPackage.JavaContainer;
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

public class JavaVectorTest {
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
	// While saving it to file, I used the toString method of JavaVector class.
	// I also used the save method of this class.
	public static <T extends Comparable<T>> void save(JavaVector<T> set, String fileName) {
		try {
			FileWriter fileWriter = new FileWriter(fileName, true);
			fileWriter.write(set.toString() + "\n");
			fileWriter.close();
		} catch (Exception e) {
			System.out.println(e);
		}
	}
	// I used this method to test the JavaVector class.
	public static void testInteger(){
		JavaVector<Integer> v = new JavaVector<Integer>(); // define outside of try-catch to use in finally
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
			var iterator = v.getIterator();
			int index = 0;
			while (iterator.hasNext()) {
				Integer element = iterator.next();
				v.setExactData(index, element * 2);
				index++;
			}
			JavaVector<Integer> cloneV = new JavaVector<>(v);
			if (cloneV.equals(v)){
				System.out.println("1 -- Equal to ! ");
			} else {
				System.out.println("1 -- Not Equal to ! ");
			}
			JavaVector<Integer> notClone = new JavaVector<>(v.Size());
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
			save(v, "vector.txt"); // saving to file
		} catch (Exception e) {
			throw e;
		} finally {
			System.out.println(v);// last mapped vector !
		}
	}
	// I used this method to test the JavaVector class.
	public static void testString(){
		JavaVector<String> v = new JavaVector<String>(); // define outside of try-catch to use in finally
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
			while (iterator.hasNext()) {
				String element2 = iterator.next();
				v.setExactData(index, element2 + " ");
				index++;
			}
			JavaVector<String> cloneV = new JavaVector<>(v);
			if (cloneV.equals(v)){
				System.out.println("1 -- Equal to ! ");
			} else {
				System.out.println("1 -- Not Equal to ! ");
			}
			JavaVector<String> notClone = new JavaVector<>(v.Size());
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
			save(v, "vector.txt"); // saving to file
		} catch (Exception e) {
			throw e;
		} finally {
			System.out.println(v);// last mapped vector !
		}
	}
	public static void testDefault(){
		JavaVector<Integer> v = new JavaVector<Integer>(); // define outside of try-catch to use in finally
		try {
			for (int i = 0; i < 5; i++) {
				v.Add(i * 2);
				v.Add(i * 5 + 6);
			}
			v.Add(0);
			v.Add(0);
			v.Add(443);
			v.Add(4);
			v.Remove(4); // removes all 4s
			v.Remove(0); // removes all 0s
			v.Remove(1111); // throws exception
			if (v.isIn(443)) {
				System.out.println("The element is in the vector"); // this line must be printed
			} else {
				System.out.println("The element is not in the vector");
			}

			var iterator = v.getIterator();
			int index = 0;
			while (iterator.hasNext()) {
				Integer element = iterator.next();
				v.setExactData(index, element * 2);
				index++;
			}


			JavaVector<Integer> cloneV = new JavaVector<Integer>(v);
			if (cloneV.equals(v)){
				System.out.println("1 -- Equal to ! "); // this line must be printed
			} else {
				System.out.println("1 -- Not Equal to ! ");
			}
			JavaVector<Integer> notClone = new JavaVector<>(v.Size());
			if (cloneV.equals(notClone)){
				System.out.println("2 -- Equal to ! ");
			} else {
				System.out.println("2 -- Not Equal to ! "); // this line must be printed
			}
			//System.out.println(v.getData(-4)); //exception occurs
			//System.out.println(v.getData(100)); //exception occurs
			//JavaVector<Integer> vv = new JavaVector<>(-2); //exception occurs
			Integer	total = 0;
			var it = v.getIterator();
			while (it.hasNext()) {
				total += it.next();
			}
			System.out.println("Total = " + total);

		} catch (Exception e) {
			throw e;
		} finally {
			System.out.println(v);// last mapped vector !
		}
	}
}
