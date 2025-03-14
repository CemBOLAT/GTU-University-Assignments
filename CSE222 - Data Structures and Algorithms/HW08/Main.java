import java.util.*;

/**
 * Main class to demonstrate the SocialNetworkGraph class.
 * The class provides a menu to interact with the social network.
 * The user can add/remove people, add/remove friendships, find shortest path between two people,
 * suggest friends for a person, and count clusters in the social network.
 */
public class Main {
	/**
	 * Main method to demonstrate the SocialNetworkGraph class.
	 * @param args Command line arguments.
	 */
	public static void main(String[] args) {
		SocialNetworkGraph network = new SocialNetworkGraph();

		// Adding some people to test easily
		network.addPerson("John Doe", 25, Arrays.asList("reading", "hiking", "cooking"));
		network.addPerson("Jane Smith", 22, Arrays.asList("swimming", "cooking"));
		network.addPerson("Alice Johnson", 27, Arrays.asList("hiking", "painting"));
		network.addPerson("Bob Brown", 30, Arrays.asList("reading", "swimming"));
		network.addPerson("Emily Davis", 28, Arrays.asList("running", "swimming"));
		network.addPerson("Frank Wilson", 26, Arrays.asList("reading", "hiking"));
		network.addPerson("Cemal Bolat", 21, Arrays.asList("swimming", "hiking", "cooking"));
		network.addPerson("Kendrick Lamar", 35, Arrays.asList("singing", "jogging"));
		network.addPerson("Drake", 30, Arrays.asList("singing", "climbing"));
		network.addPerson("Donald Trump", 75, Arrays.asList("reading", "swimming"));

		// Adding some friendships to test easily
		network.addFriendship("John Doe", "Jane Smith");
		network.addFriendship("John Doe", "Alice Johnson");
		network.addFriendship("Jane Smith", "Alice Johnson");
		network.addFriendship("Bob Brown", "Emily Davis");
		network.addFriendship("Bob Brown", "Frank Wilson");
		network.addFriendship("Emily Davis", "Frank Wilson");

		network.addFriendship("Cemal Bolat", "Kendrick Lamar");
		network.addFriendship("Cemal Bolat", "Alice Johnson");
		network.addFriendship("Emily Davis", "Drake");
		network.addFriendship("Bob Brown", "John Doe");

		try {
			boolean exit = false;
			while (!exit) {
				printMenu();
				try{
					int option;
					option = Integer.parseInt(System.console().readLine());
					switch (option) {
						case 1:
							addPerson(network);
						break;
						case 2:
							removePerson(network);
						break;
						case 3:
							addFriendship(network);
						break;
						case 4:
							removeFriendship(network);
						break;
						case 5:
							findShortestPath(network);
						break;
						case 6:
							suggestFriends(network);
						break;
						case 7:
							countClusters(network);
						break;
						case 8:
							exit = true;
						break;
						default:
							System.out.println("Invalid option. Please select a valid option.");
					}
				} catch (NumberFormatException e) {
					System.out.println("Invalid option. Please select a valid option.");
				} catch (Exception e) {
					System.out.println(e.getMessage());
				}

			}
		} catch (Exception e) {
			e.printStackTrace();
		}
	}

	/**
	 * Helper method to get a non-empty string from the user.
	 * @param message Message to display to the user.
	 * @return Non-empty string entered by the user.
	 * @throws Exception If the input is empty or null.
	*/
	private static String getString(String message) throws Exception {
		String output = "";
		System.out.print(message + " ");
		output = System.console().readLine();
		if (output == null || output.isEmpty()) {
			throw new Exception("Invalid input. Please enter a valid string.");
		}
		return output;
	}


	/**
	 * Add a person to the social network.
	 * @param network Social network graph object.
	 * @throws Exception If the input is invalid.
	 */
	private static void addPerson(SocialNetworkGraph network) throws Exception {
		String name = getString("Enter the name of the person:");

		System.out.print("Enter the age of the person: ");
		int age = Integer.parseInt(System.console().readLine());


		String hobbie = getString("Enter the hobbies of the person:");
		String[] hobbies = hobbie.split(",");
		network.addPerson(name, age, Arrays.asList(hobbies));
	}

	/**
	 * Remove a person from the social network.
	 * @param network Social network graph object.
	 * @throws Exception If the input is invalid.
	 */
	private static void removePerson(SocialNetworkGraph network) throws Exception {
		String name = getString("Enter the name of the person to remove:");
		network.removePerson(name);
	}

	/**
	 * Add a friendship between two people in the social network.
	 * @param network Social network graph object.
	 * @throws Exception If the input is invalid.
	 */
	private static void addFriendship(SocialNetworkGraph network) throws Exception {
		String name1 = getString("Enter first person’s name:");
		String name2 = getString("Enter second person’s name:");
		network.addFriendship(name1, name2);
	}

	/**
	 * Remove a friendship between two people in the social network.
	 * @param network Social network graph object.
	 * @throws Exception If the input is invalid.
	 */
	private static void removeFriendship(SocialNetworkGraph network) throws Exception {
		String name1 = getString("Enter first person’s name:");
		String name2 = getString("Enter second person’s name:");
		network.removeFriendship(name1, name2);
	}

	/**
	 * Find the shortest path between two people in the social network.
	 * @param network Social network graph object.
	 * @throws Exception If the input is invalid.
	 */
	private static void findShortestPath(SocialNetworkGraph network) throws Exception {
		String name1 = getString("Enter first person’s name:");
		String name2 = getString("Enter second person’s name:");
		network.findShortestPath(name1, name2);
	}

	/**
	 * Suggest friends for a person in the social network.
	 * @param network Social network graph object.
	 * @throws Exception If the input is invalid.
	 */
	private static void suggestFriends(SocialNetworkGraph network) throws Exception {
		String name = getString("Enter the name of the person:");
		System.out.print("Enter maximum number of friends to suggest: ");
		int maxFriends = Integer.parseInt(System.console().readLine());
		network.suggestFriends(name, maxFriends);
	}

	/**
	 * Count clusters in the social network.
	 * @param network Social network graph object.
	 */
	private static void countClusters(SocialNetworkGraph network) {
		System.out.println("Counting clusters in the social network...");
		network.countClusters();
	}

	/**
	 * Print the menu options.
	 */
	private static void printMenu() {
		System.out.println("===== Social Network Analysis Menu =====");
		System.out.println("1. Add person");
		System.out.println("2. Remove person");
		System.out.println("3. Add friendship");
		System.out.println("4. Remove friendship");
		System.out.println("5. Find shortest path");
		System.out.println("6. Suggest friends");
		System.out.println("7. Count clusters");
		System.out.println("8. Exit");
		System.out.print("Please select an option: ");
	}
}
