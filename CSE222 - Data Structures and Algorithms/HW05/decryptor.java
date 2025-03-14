import java.util.Map;
import java.util.Iterator;

/**
 * decryptor class is used to decrypt a given text using the Vigenere cipher.
 * The class has the map as vinegere cipher map, key as the key, and text as the cipher text.
 * and key as instance variables.
*/

public class decryptor {
	private Map<Character, Map<Character, Character>> map;
	private String key;
	private String keystream = "";
	private String plain_text = "";
	private String cipher_text;

	/**
	 * Creates a new decryptor object.
	 * <p> This constructor creates a new decryptor object. </p>
	 * @param _map the map
	 * @param _key the key
	 * @param text the text
	 */
	public decryptor(Map<Character, Map<Character, Character>> _map, String _key, String text) {
		map = _map;
		key = _key;
		cipher_text = text;
	}
	/**
	 * Decrypts the given text using the Vigenere cipher.
	 * <p> This method decrypts the given text using the Vigenere cipher. </p>
	 * <p> The method generates the keystream and the plain text. </p>
	 * <p> The method uses the map to decrypt the text. </p>
	 */
	public void decrypt() {
		// do not edit this method (given by the instructor)
		generate_keystream();
		generate_plain_text();
	}
	/**
	 * Generates the keystream. (Method is same as Encryptor class)
	 * <p> This method generates the keystream. </p>
	 * <p> The method uses the key to generate the keystream. </p>
	 * I used a StringBuilder to append the characters to the keystream. Because it is more efficient than using the + operator.
	 * '+' operator creates a new string object each time it is used. and it is bad for memory space and time complexity.
	 * StringBuilder is more efficient because it does not create a new object each time it is used.
	 * -----------------------------------
	 * Algorithm:
	 * 1. Iterate through the cipher text.
	 * 2. Append the key character to the keystream.
	 * 3. Repeat step 2 until the length of the key is equal to the length of the cipher text.
	 * Avoiding out of bounds exception by using the modulo operator. 
	 */
	private void generate_keystream() {
		StringBuilder sb = new StringBuilder();
		for (int i = 0; i < cipher_text.length(); i++) { // iterate through the cipher text 
			sb.append(key.charAt(i % key.length()));
		}
		keystream = sb.toString();
	}
	/**
	 * Generates the plain text.
	 * <p> This method generates the plain text. </p>
	 * <p> The method uses the map to generate the plain text. </p>
	 * I used a StringBuilder to append the characters to the plain text. Because it is more efficient than using the + operator.
	 * '+' operator creates a new string object each time it is used. and it is bad for memory space and time complexity.
	 * StringBuilder is more efficient because it does not create a new object each time it is used.
	 */
	private void generate_plain_text() {
		// You must use map.get(x).keySet() with an iterator in this method (is a must given by the instructor)
		StringBuilder sb = new StringBuilder();
		for (int i = 0; i < cipher_text.length(); i++) { // length of the cipher text and the keystream are equal.
			char c = keystream.charAt(i); // find the key character
			char k = cipher_text.charAt(i); // find the cipher text character
			// Variable is Map<Character, Map<Character, Character>> -- map
			// Variable is Map<Character, Character> -- map.get(c)
			// Variable is key of Map<Character, Character> as Set<Character> -- map.get(c).keySet()
			Iterator<Character> it = map.get(c).keySet().iterator();
			while(it.hasNext()){
				char c2 = it.next();
				if(map.get(c).get(c2) == k){
					sb.append(c2);
					break;
				}
			}
		}
		plain_text = sb.toString();
	}
	
	/**
	 * Returns the keystream.
	 * <p> This method returns the keystream. </p>
	 * @return the keystream
	 */
	public String get_keystream() {
		return keystream;
	}
	/**
	 * Returns the plain text.
	 * <p> This method returns the plain text. </p>
	 * @return the plain text
	 */
	public String get_plain_text() {
		return plain_text;
	}
}
