import java.util.*;

/**
 * <p>
 * The SocialNetworkGraph class represents a social network graph.
 * </p>
 *
 * <p> The SocialNetworkGraph class has the following attributes: </p>
 * <ul>
 * <li> <strong>people</strong> - The map of people in the social network. </li>
 * <li> <strong>friendships</strong> - The map of friendships in the social network. </li>
 * </ul>
 *
 * <p> The SocialNetworkGraph class has the following methods: </p>
 * <ul>
 * <li> <strong>addPerson</strong> - Adds a person to the social network. </li>
 * <li> <strong>removePerson</strong> - Removes a person from the social network. </li>
 * <li> <strong>addFriendship</strong> - Adds a friendship between two people in the social network. </li>
 * <li> <strong>removeFriendship</strong> - Removes a friendship between two people in the social network. </li>
 * <li> <strong>findShortestPath</strong> - Finds the shortest path between two people in the social network. </li>
 * <li> <strong>countClusters</strong> - Counts the number of clusters in the social network. </li>
 * <li> <strong>suggestFriends</strong> - Suggests friends for a person in the social network. </li>
 * </ul>
 */
public class SocialNetworkGraph {
	/**
	 * The data fields given from the instructor.
	 */
	Map<String, Person> people = new HashMap<>();
	Map<Person, List<Person>> friendships = new HashMap<>();

	// Easy to calculate the frendship score
	private static double MUTUAL_FRIENDS = 1;
	private static double COMMON_HOBBIES = 0.5;

	/**
	 *
	 * <p> The method adds a person to the social network with the given name, age, and hobbies. </p>
	 * <p> The method informs the user if the person is already in the network. </p>
	 *
	 * <p> The method adds total of 2 entries: </p>
	 * <ul>
	 * <li> The person to the people map. </li>
	 * <li> The person to the friendships map. </li>
	 * </ul>
	 *
	 * @param name The name of the person.
	 * @param age The age of the person.
	 * @param hobbies The list of hobbies of the person.
	 */
	public void addPerson(String name, int age, List<String> hobbies) {
		Person person = new Person(name, age, hobbies);

		if (people.get(name) == null) {
			people.put(name, person);
			friendships.put(person, new ArrayList<>());
			System.out.println("Person added: " + person.print());
		} else {
			System.out.println("Person already exists in the network.");
		}
	}


	/**
	 * <p> The method removes a person from the social network with the given name. </p>
	 * <p> The method informs the user if the person is not found or removed. </p>
	 *
	 * <p> The method removes total of 3 entries: </p>
	 * <ul>
	 * <li> The person from the people map. </li>
	 * <li> The person from the friendships map. </li>
	 * <li> The person from the friendships list of other people. </li>
	 * </ul>
	 * @param name The name of the person.
	 */
	public void removePerson(String name) {
		Person person = people.get(name);
		if (person != null) {
			people.remove(name);
			friendships.remove(person);
			for (List<Person> friends : friendships.values()) {
				friends.remove(person);
			}
			System.out.println("Person removed: " + person.print());
		} else {
			System.out.println("Person not found in the network.");
		}
	}

	/**
	 * <p> The method adds a friendship between two people in the social network with the given names. </p>
	 * <p> The method informs the user if one or both persons are not found in the network. </p>
	 *
	 * <p> The method adds total of 2 entries because the graph is undirectd: </p>
	 * <ul>
	 * <li> The second person to the friendship list of the first person. </li>
	 * <li> The first person to the friendship list of the second person. </li>
	 * </ul>
	 *
	 * @param name1 The name of the first person.
	 * @param name2 The name of the second person.
	 */
	public void addFriendship(String name1, String name2) {
		Person person1 = people.get(name1);
		Person person2 = people.get(name2);
		if (person1 != null && person2 != null) {
			// if the friendship already exists, do not add it again
			if (friendships.get(person1).contains(person2)) {
				System.out.println("Friendship already exists between " + person1.name + " and " + person2.name);
				return;
			}
			friendships.get(person1).add(person2);
			friendships.get(person2).add(person1);
			System.out.println("Friendship added between " + person1.name + " and " + person2.name);
		} else {
			System.out.println("One or both persons not found in the network.");
		}
	}

	/**
	 * <p> The method removes a friendship between two people in the social network with the given names. </p>
	 * <p> The method informs the user if one or both persons are not found in the network. </p>
	 *
	 * <p> The method removes total of 2 entries because the graph is undirectd: </p>
	 * <ul>
	 * <li> The second person from the friendship list of the first person. </li>
	 * <li> The first person from the friendship list of the second person. </li>
	 * </ul>
	 *
	 * @param name1 The name of the first person.
	 * @param name2 The name of the second person.
	 */
	public void removeFriendship(String name1, String name2) {
		Person person1 = people.get(name1);
		Person person2 = people.get(name2);
		if (person1 != null && person2 != null) {
			if (!friendships.get(person1).contains(person2)) {
				System.out.println("Friendship does not exist between " + person1.name + " and " + person2.name);
				return;
			}
			friendships.get(person1).remove(person2);
			friendships.get(person2).remove(person1);
			System.out.println("Friendship removed between " + person1.name + " and " + person2.name);
		} else {
			System.out.println("One or both persons not found in the network.");
		}
	}

	/**
	 * <p> The method finds the shortest path between two people in the social network with the given names. </p>
	 * <p> The method informs the user if one or both persons are not found in the network. </p>
	 *
	 * <p> The method uses the breadth-first search algorithm to find the shortest path. </p>
	 *
	 * @param startName The name of the start person.
	 * @param endName The name of the end person.
	 */
	public void findShortestPath(String startName, String endName) {
		Person start = people.get(startName);
		Person end = people.get(endName);

		if (start == null || end == null) {
			System.out.println("One or both persons not found in the network.");
			return;
		}

		Map<Person, Person> prev = new HashMap<>();
		Queue<Person> queue = new LinkedList<>();

		queue.add(start);
		prev.put(start, null);

		/*
			Firstly add the first element to the queue and mark it as visited.
			Prev map is used to store the previous person of the current person.

			Then, while the queue is not empty, poll the first element from the queue.
			For each neighbor of the current element, if it is not visited, add it to the queue and mark it as visited.

			Do it till the queue is empty.
		*/

		while (!queue.isEmpty()) { // BFS algorithm
			Person current = queue.poll();
			if (current == end) {
				printPath(start, end, prev);  // Print the path
				return;
			}

			for (Person neighbor : friendships.get(current)) {
				if (!prev.containsKey(neighbor)) {  // Key point of BFS algorithm
					queue.add(neighbor);
					prev.put(neighbor, current);
				}
			}
		}
		System.out.println("No path found between " + startName + " and " + endName);
	}

	/**
	 * <p> The method prints the shortest path between two people in the social network. </p>
	 *
	 * @param start The start person.
	 * @param end The end person.
	 * @param prev The map of previous persons.
	 */
	private void printPath(Person start, Person end, Map<Person, Person> prev) {
		List<Person> path = new ArrayList<>();
		StringBuilder sb = new StringBuilder();
		for (Person at = end; at != null; at = prev.get(at)) {
			path.add(at);
		}
		Collections.reverse(path);
		for (Person person : path) {
			sb.append(person.name).append(" -> ");
		}
		System.out.println("Shortest path: " + sb.substring(0, sb.length() - 4)); // Remove the last " -> "
	}

	/**
	 * <p> The method counts the number of clusters in the social network. </p>
	 * <p> The method uses the breadth-first search algorithm to find the clusters. </p>
	 *
	 * <p> The must to be cluster is that the path must be circular. </p>
	 * <p> The method prints the number of clusters and the people in each cluster. </p>
	 */
	public void countClusters() {

		Set<Person> visited = new HashSet<>();
		List<List<Person>> clusters = new ArrayList<>();
		int count = 0;

		for (Person person : people.values()) {
			if (!visited.contains(person)) {
				List<Person> cluster = new ArrayList<>();
				bfs(person, visited, cluster);
				count++;
				clusters.add(cluster);
			}
		}
		System.out.println("Number of clusters: " + count + "\n");
		for (int i = 0; i < clusters.size(); i++) {
			System.out.println("Cluster " + (i + 1) + ":");
			for (Person person : clusters.get(i)) {
				System.out.println(person.name);
			}
			System.out.println();
		}
	}

	/**
	 * <p> The method uses the breadth-first search algorithm to find the clusters in the social network. </p>
	 *
	 * @param start The start person.
	 * @param visited The set of visited persons.
	 * @param cluster The list of people in the cluster.
	 */
	private void bfs(Person start, Set<Person> visited, List<Person> cluster) {
		Queue<Person> queue = new LinkedList<>();
		queue.add(start);
		visited.add(start);

		while (!queue.isEmpty()) {
			Person current = queue.poll();
			cluster.add(current);

			for (Person neighbor : friendships.get(current)) {
				if (!visited.contains(neighbor)) {
					queue.add(neighbor);
					visited.add(neighbor);
				}
			}
		}
	}

	// Helper class to store the score, number of mutual friends and number of common hobbies
	private static class SuggestionHelperClass {
		private double score;
		private int nbr_of_mutual_friends;
		private int nbr_of_common_hobbies;

		public SuggestionHelperClass(double score, int nbr_of_mutual_friends, int nbr_of_common_hobbies) {
			this.score = score;
			this.nbr_of_mutual_friends = nbr_of_mutual_friends;
			this.nbr_of_common_hobbies = nbr_of_common_hobbies;
		}

	}

	/**
	 * <p> The method is helper method to suggest friends for a person in the social network. </p>
	 *
	 * <p> The method uses the mutual friends and common hobbies to suggest friends. </p>
	 * <p> The method prints the suggested friends with their scores, number of mutual friends, and number of common hobbies. </p>
	 * <p> The method prints the maximum number of friends to suggest. </p>
	 *
	 * @param person The person to suggest friends.
	 * @param maxFriends The maximum number of friends to suggest.
	 */
	private void suggestFriends(Person person, int maxFriends) {
		Map<Person, SuggestionHelperClass> scores = new HashMap<>();
		for (var people : people.values()){
			if (people == person) continue;
			if (friendships.get(person).contains(people)) continue;

			int mutualFriends = 0;
			for (Person friend : friendships.get(person)) {
				if (friendships.get(people).contains(friend)) {
					mutualFriends++;
				}
			}

			int commonHobbies = 0;
			for (String hobby : person.hobbies) {
				if (people.hobbies.contains(hobby)) {
					commonHobbies++;
				}
			}

			double score = mutualFriends * MUTUAL_FRIENDS + commonHobbies * COMMON_HOBBIES;
			if (score == 0) continue; // If the score is 0, do not add it to the list
			scores.put(people, new SuggestionHelperClass(score, mutualFriends, commonHobbies));
		}

		List<Person> suggestedFriends = new ArrayList<>(scores.keySet());
		suggestedFriends.sort((p1, p2) -> scores.get(p2).score > scores.get(p1).score ? 1 : -1);

		System.out.println("Suggested friends for " + person.name + ":\n");

		for (int i = 0; i < Math.min(maxFriends, suggestedFriends.size()); i++) {
			System.out.println(suggestedFriends.get(i).name + " (Score: " + scores.get(suggestedFriends.get(i)).score + ", " + scores.get(suggestedFriends.get(i)).nbr_of_mutual_friends + " mutual friends, " + scores.get(suggestedFriends.get(i)).nbr_of_common_hobbies + " common hobbies)");
		}
	}


	/**
	 * <p> The method suggests friends for a person in the social network with the given name. </p>
	 * <p> The method informs the user if the person is not found in the network. </p>
	 * <p> The method uses the mutual friends and common hobbies to suggest friends. </p>
	 *
	 * @param name The name of the person.
	 * @param maxFriends The maximum number of friends to suggest.
	 */
	public void suggestFriends(String name, int maxFriends) {
		Person person = people.get(name);
		if (person == null) {
			System.out.println("Person not found in the network.");
			return;
		}

		suggestFriends(person, maxFriends);
	}
}
