// Preprocessor class works on the given string and preprocesses it by capitalizing 
// all the characters and removing all the non-alphabetic characters.
public class preprocessor {
	private String initial_string;
	private String preprocessed_string;
	/**
	 * Constructs a preprocessor object with the given string.
	 * <p> This constructor constructs a preprocessor object with the given string. </p>
	 * @param str The string to be preprocessed.
	 */
	public preprocessor(String str) {
		initial_string = str;
		preprocessed_string = "";
	}
	/**
	 * Preprocesses the string.
	 * <p> This method preprocesses the string by capitalizing all the characters and removing all the non-alphabetic characters. </p>
	 * <p> Method is given by the instructor so I do not edit it. </p>
	 */
	public void preprocess() {
		// do not edit this method (given by the instructor)
		capitalize();
		clean();
	}
	/**
	 * Capitalizes the string.
	 * <p> This method capitalizes the string. </p>
	 * <p> I used StringBuilder to append the characters to the string. Because it is more efficient than using the + operator. </p>
	 * <p> '+' operator creates a new string object each time it is used. and it is bad for memory space and time complexity. </p>
	 * <p> StringBuilder is more efficient because it does not create a new object each time it is used. </p>
	 */
	private void capitalize() {
		// I didn't use toUpperCase() method because it may depends on the locale. 
		StringBuilder sb = new StringBuilder(); 
		for (int i = 0; i < initial_string.length(); i++) {
			char c = initial_string.charAt(i);
			if (c >= 'a' && c <= 'z') {
				sb.append((char) (c - 32)); // -32 is the difference between the ASCII values of the lowercase and uppercase letters.
			} else {
				sb.append((char) c);
			}
		}
		preprocessed_string = sb.toString();
	}

	/**
	 * Cleans the string.
	 * <p> This method cleans the string by removing all the non-alphabetic characters. </p>
	 * <p> I used StringBuilder to append the characters to the string. Because it is more efficient than using the + operator. </p>
	 * <p> '+' operator creates a new string object each time it is used. and it is bad for memory space and time complexity. </p>
	 * <p> StringBuilder is more efficient because it does not create a new object each time it is used. </p>
	 */
	private void clean() {
		StringBuilder sb = new StringBuilder();
		for (int i = 0; i < preprocessed_string.length(); i++) { // I used preprocessed_string because it is already capitalized.
			char c = preprocessed_string.charAt(i);
			if (c >= 'A' && c <= 'Z') { // I used 'A' and 'Z' because the string is already capitalized.
				sb.append(c);
			}
		}
		preprocessed_string = sb.toString();
	}
	
	/**
	 * Returns the preprocessed string.
	 * <p> This method returns the preprocessed string. </p>
	 * @return The preprocessed string.
	 */
	public String get_preprocessed_string() {
		return preprocessed_string;
	}
}