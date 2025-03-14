import java.util.HashMap;
import java.util.Map;
import java.util.LinkedHashSet;
import java.util.Set;
import java.util.Iterator;


/**
 * alphabet class is used to create a map that contains the English alphabet and its corresponding Vigenere cipher alphabet.
 * The class has the english_alphabet and Vigenère cipher alphabet as instance variables.
 */

public class alphabet {
	private Set<Character> english_alphabet = new LinkedHashSet<Character>();
	private Map<Character, Map<Character, Character>> map = new HashMap<Character,  Map<Character, Character>>();

	/**
	 * Creates a new alphabet object.
	 * <p> This constructor creates a new alphabet object. </p>
	 * <p> Method is given by the instructor so I do not edit it. </p>
	 */
	public alphabet() {
		// do not edit this method (given by the instructor)
		fill_english_alphabet();
		fill_map();
	}
	/**
	 * Fills the english_alphabet set with the English alphabet.
	 * <p> This method fills the english_alphabet set with the English alphabet. </p>
	 * <p> Method is given by the instructor so I do not edit it. </p>
	 */
	private void fill_english_alphabet() {
		// do not edit this method (given by the instructor)
		for(char c : "ABCDEFGHIJKLMNOPQRSTUVWXYZ".toCharArray()) {
			english_alphabet.add(c);
		}
	}
	/**
	 * Fills the map with the Vigenere cipher alphabet.
	 * <p> This method fills the map with the Vigenere cipher alphabet. </p>
	 * <p> The map is filled according to the Vigenere cipher formula. </p>
	 * <p> The formula for each letter is: (c2 + c % 26) + 'A' </p>
	 * <p> Where c2 is the index of the character in the alphabet, c is the index of the key character in the alphabet,
	 * and 26 is the size of the alphabet. </p>
	*/
	private void fill_map() {
		// You must use the "english_alphabet" variable in this method, to fill the "map" variable. (Is a must given by the instructor)
		// You can define 1 or 2 iterators to iterate through the set items. (advice given by the instructor)
		Iterator<Character> it1 = english_alphabet.iterator();
		while(it1.hasNext()){
			char c = it1.next(); // iterate through the characters of the alphabet
			Map<Character, Character> inner_map = new HashMap<Character, Character>(); // create a new map for each character
			Iterator<Character> it2 = english_alphabet.iterator();
			while(it2.hasNext()){
				char c2 = it2.next(); // iterate through the characters of the alphabet again
				// 'Z' - 'A' + 1 = 26 (size of the alphabet)
				// Vigenere cipher formula (c2 + c % 26 gives the index of the new character in the alphabet)
				char c3 = (char) ((c2 + c) % ('Z' - 'A' + 1) + 'A');
				inner_map.put(c2, c3);
			}
			map.put(c, inner_map);
		}
	}
	/**
	 * Prints the map.
	 * <p> This method prints the map. </p>
	 * <p> Method is given by the instructor so I do not edit it. </p>
	 */

	public void print_map() {
		// do not edit this method (given by the instructor)
		System.out.println("*** Viegenere Cipher ***\n\n");
		System.out.println("	" + english_alphabet);
		System.out.print("	------------------------------------------------------------------------------");
		for(Character k: map.keySet()) {
			System.out.print("\n" + k + " | ");
			System.out.print(map.get(k).values());
		}
		System.out.println("\n");

	}
	/**
	 * Returns the map.
	 * <p> This method returns the map. </p>
	 * <p> Method is given by the instructor so I do not edit it. </p>
	 *
	 * @return the map
	 */
	public Map get_map() {
		return map;
	}
}
