import java.io.File;
import java.io.FileWriter;
import java.io.PrintWriter;
import java.util.Set;
import java.util.HashSet;

/**
 * RandomInputGenerator class to generate random input for the stock data manager.
 * <br>
 * 
 * These operations are performed on the stock data manager:
 * <ol>
 * <li>NODE</li> 
 * <li>ADD</li>
 * <li>REMOVE</li>
 * <li>SEARCH</li>
 * <li>UPDATE</li>
 * </ol>
 * 
 * The input file is generated with the following format:
 * <br>
 * <code>
 * NODE &lt;symbol&gt; &lt;price&gt; &lt;volume&gt; &lt;market_cap&gt;<br>
 * ADD &lt;symbol&gt; &lt;price&gt; &lt;volume&gt; &lt;market_cap&gt;<br>
 * REMOVE &lt;symbol&gt;<br>
 * SEARCH &lt;symbol&gt;<br>
 * UPDATE &lt;symbol&gt; &lt;price&gt; &lt;volume&gt; &lt;market_cap&gt;<br>
 * </code>
 * <br>
 */
public class RandomInputGenerator {
    /**
     * Maximum number of stocks to generate
     */
    public static int MAX_STOCKS;
    /**
     * Array to store the deleted stocks 
     */
    public static int deleted[];
    /**
     * Set to store the symbols of the stocks
     */
    public static Set<String> symbols = new HashSet<>();

    /**
     * Generate a random price for the stock between 0 and 1000
     * @return random price
     */
    public double generateRandomPrice() {
        return Math.random() * 1000;
    }
    /**
     * Generate a random volume for the stock between 0 and 1000000
     * @return random volume
     */
    public long generateRandomVolume() {
        return (long) (Math.random() * 1000000);
    }
    /**
     * Generate a random market cap for the stock between 0 and 1000000000
     * @return random market cap
     */
    public long generateRandomMarketCap() {
        return (long) (Math.random() * 1000000000);
    }
    /**
     * Generate a random number between min and max
     * @param min minimum value
     * @param max maximum value
     * @return random number
     */
    public int getRandomNumberInRange(int min, int max) {
        return min + (int) (Math.random() * (max - min));
    }

    /**
     * Generate a random string of length
     * @param length length of the string
     * @return random string
     */
    public String generateRandomString(int length) {
        String characters = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
        StringBuilder result = new StringBuilder();
        for (int i = 0; i < length; i++) {
            result.append(characters.charAt(getRandomNumberInRange(0, characters.length())));
        }
        return result.toString();
    }

    /**
     * Generate random inputs for the stock data manager
     * @param inputFile input file to write the random inputs
     * @param numNode number of nodes to add
     * @param numAdd number of stocks to add
     * @param numRemove number of stocks to remove
     * @param numSearch number of stocks to search
     * @param numUpdate number of stocks to update
     */
    public void generateRandomInputs(String inputFile, int numNode, int numAdd, int numRemove, int numSearch, int numUpdate) {
        // Implement this method
        File file = new File(inputFile);
        MAX_STOCKS = numAdd + numNode;
        deleted = new int[MAX_STOCKS];

        // create a new file if it does not exist
        if (!file.exists()) {
            try {
                file.createNewFile();
            } catch (Exception e) {
                e.printStackTrace();
            }
        }

        try (PrintWriter writer = new PrintWriter(new FileWriter(file))) {
            //Add 1000 random nodes
            for (int i = 0; i < numNode; i++) {
                do {
                    String symbol = generateRandomString(5);
                    if (!symbols.contains(symbol)) {
                        symbols.add(symbol);
                        writer.println("NODE " + symbol + " " + generateRandomPrice() + " " + generateRandomVolume() + " " + generateRandomMarketCap());
                        break;
                    }
                } while (true);
            }
            //Add 1000 random stocks
            for (int i = 0; i < numAdd; i++) {
                do {
                    String symbol = generateRandomString(5);
                    if (!symbols.contains(symbol)) {
                        symbols.add(symbol);
                        writer.println("ADD " + symbol + " " + generateRandomPrice() + " " + generateRandomVolume() + " " + generateRandomMarketCap());
                        break;
                    }
                } while (true);
            }
            // Remove 1000 random stocks
            if (numRemove > MAX_STOCKS) {
                numRemove = MAX_STOCKS;
                numSearch = 0;
                numUpdate = 0;
            }

            for (int i = 0; i < numRemove; i++) {
                do {
                    int nbr = getRandomNumberInRange(0, MAX_STOCKS);
                    if (deleted[nbr] != 1) {
                        //  get the element at that index in set
                        String symbol = (String) symbols.toArray()[nbr];
                        writer.println("REMOVE " + symbol);
                        deleted[nbr] = 1;
                        break;
                    }
                } while (true);
            }
            // Search 1000 random stocks
            if (numSearch > MAX_STOCKS) {
                numSearch = MAX_STOCKS;
            }
            for (int i = 0; i < numSearch; i++) {
               do {
                   int nbr = getRandomNumberInRange(0, MAX_STOCKS);
                   if (deleted[nbr] != 1) {
                        String symbol = (String) symbols.toArray()[nbr];
                        writer.println("SEARCH " + symbol);
                        break;
                   }
               } while (true);
            }
            if (numUpdate > MAX_STOCKS) {
                numUpdate = MAX_STOCKS;
            }
            // Update 1000 random stocks
            for (int i = 0; i < numUpdate; i++) {
               do {
                   int nbr = getRandomNumberInRange(0, MAX_STOCKS);
                   if (deleted[nbr] != 1) {
                        String symbol = (String) symbols.toArray()[nbr];
                        writer.println("UPDATE " + symbol + " " + generateRandomPrice() + " " + generateRandomVolume() + " " + generateRandomMarketCap());
                        break;
                   }
               } while (true);
            }
            writer.close();
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
    /**
     * Main method to generate random inputs for the stock data manager
     * @param args command line arguments
     */
    public static void main(String[] args) {
        if (args.length != 6) {
            System.out.println("Usage: java RandomInputGenerator <input_file> <nodeNum> <addNum> <removeNum> <searchNum> <updateNum>");
            return;
        }

        RandomInputGenerator randomInputGenerator = new RandomInputGenerator();
        randomInputGenerator.generateRandomInputs(args[0], Integer.parseInt(args[1]), Integer.parseInt(args[2]), Integer.parseInt(args[3]), Integer.parseInt(args[4]), Integer.parseInt(args[5]));
    }
}
