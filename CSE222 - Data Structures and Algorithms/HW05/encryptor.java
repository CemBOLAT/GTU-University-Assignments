import java.util.Map;

public class encryptor {
	private Map<Character, Map<Character, Character>> map;
	private String key;
	private String keystream = "";
	private String plain_text;
	private String cipher_text = "";
	
	/**
	 * Creates a new encryptor object.
	 * <p> This constructor creates a new encryptor object. </p>
	 * @param _map the map
	 * @param _key the key
	 * @param text the text
	 */
	public encryptor(Map<Character, Map<Character, Character>> _map, String _key, String text) {
		map = _map;
		key = _key;
		plain_text = text;
	}
	/** 
	 * Encrypts the plain text.
	 * <p> This method encrypts the plain text. </p>
	 * <p> The method generates the keystream and the cipher text. </p>
	 * <p> Method given by the instructor so do not edit this method. </p>
	*/
	public void encrypt() {
		// do not edit this method
		generate_keystream();
		generate_cipher_text();
	}
	/**
	 * Generates the keystream. (Method is same as Decryptor class)
	 * <p> This method generates the keystream. </p>
	 * <p> The method uses the key to generate the keystream. </p>
	 * I used a StringBuilder to append the characters to the keystream. Because it is more efficient than using the + operator.
	 * '+' operator creates a new string object each time it is used. and it is bad for memory space and time complexity.
	 * StringBuilder is more efficient because it does not create a new object each time it is used.
	 * -----------------------------------
	 * Algorithm:
	 * 1. Iterate through the plain text.
	 * 2. Append the key character to the keystream.
	 * 3. Repeat step 2 until the length of the key is equal to the length of the plain text.
	 * Avoiding out of bounds exception by using the modulo operator. 
	 */
	private void generate_keystream() {
		// Vinegere cipher
		StringBuilder sb = new StringBuilder();
		for (int i = 0; i < plain_text.length(); i++) { // iterate through the plain text
			sb.append(key.charAt(i % key.length()));
		}
		keystream = sb.toString();
	}
	/**
	 * Generates the cipher text.
	 * <p> This method generates the cipher text. </p>
	 * <p> The method uses the map to generate the cipher text. </p>
	 * I used a StringBuilder to append the characters to the cipher text. Because it is more efficient than using the + operator.
	 * '+' operator creates a new string object each time it is used. and it is bad for memory space and time complexity.
	 * StringBuilder is more efficient because it does not create a new object each time it is used.
	 */
	private void generate_cipher_text() {
		// Vinegere cipher
		StringBuilder sb = new StringBuilder(); 
		for (int i = 0; i < plain_text.length(); i++) { // length of the plain text and keystream are the same
			char c = plain_text.charAt(i); 
			char k = keystream.charAt(i);
			// Variable is Map<Character, Map<Character, Character>> -- map
			// map.get(c) returns a Map<Character, Character> object
			// map.get(c).get(k) returns a Character object
			sb.append(map.get(c).get(k));
		}
		cipher_text = sb.toString();
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
	 * Returns the cipher text.
	 * <p> This method returns the cipher text. </p>
	 * @return the cipher text
	 */
	public String get_cipher_text() {
		return cipher_text;
	}
}
