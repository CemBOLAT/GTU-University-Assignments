import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.util.ArrayList;
import javax.swing.SwingUtilities;


/**
 * Main class to process the input file and perform performance analysis
 */
public class Main {

    // ArrayLists to store the x and y points for the performance analysis
    private static ArrayList<Integer> generalXPoints = new ArrayList<>();
    private static ArrayList<Long> addDataPointsY = new ArrayList<>();
    private static ArrayList<Long> removeDataPointsY = new ArrayList<>();
    private static ArrayList<Long> searchDataPointsY = new ArrayList<>();
    private static ArrayList<Long> updateDataPointsY = new ArrayList<>();
    private static int xSize = 50;
    private static int growthFactor = 1000;

    /**
     * <p>
     * Main method to process the input file and perform performance analysis.
     * </p>
     * Main method has the following steps:
     * <ul>
     * <li>Check for correct number of arguments</li>
     * <li>Get the input file</li>
     * <li>Process input file</li>
     * <li>Print time taken to process input file</li>
     * <li>Perform performance analysis for the operations (ADD, SEARCH, UPDATE, REMOVE)</li>
     * <li>Create GUIVisualizations for the performance analysis</li>
     * </ol>
     * @param args command line arguments (input file)
     */
    public static void main(String[] args) {

        // Check for correct number of arguments
        if (args.length != 1) {
            System.out.println("Usage: java Main <input_file>");
            return;
        }

        // Get the input file and add file
        String inputFile = args[0];
        long startTime, endTime;
        StockDataManager manager = new StockDataManager();

        // Process input file
        startTime = System.nanoTime();
        try (BufferedReader br = new BufferedReader(new FileReader(inputFile))) {
            String line;
            while ((line = br.readLine()) != null) {
                processCommand(line, manager);
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
        endTime = System.nanoTime();

        // Print time taken to process input file
        System.out.println("Time taken to process input file: " + (endTime - startTime) + " ns");

        for(int i = 1; i < xSize; i++)
        {
            generalXPoints.add(i * growthFactor); // Add data points for the performance analysis
            performPerformanceAnalysis(manager, i * growthFactor);  // Perform performance analysis for the operations
            System.gc(); // Call garbage collector to free up memory
        }

        // Create GUIVisualizations for the performance analysis
        SwingUtilities.invokeLater(() -> {
            String plotType = "scatter"; // Change to "scatter" for scatter plot
            generalXPoints.add(xSize * growthFactor); // Add data points for the performance analysis
            addDataPointsY.add(addDataPointsY.get(addDataPointsY.size() - 1) * (long)1.5);
            GUIVisualization frame = new GUIVisualization(plotType, generalXPoints, addDataPointsY, "Add Data Plots"); // Create a new instance of GUIVisualization
            frame.setVisible(true); // Make the frame visible

            removeDataPointsY.add(removeDataPointsY.get(removeDataPointsY.size() - 1) * (long)1.5);
            GUIVisualization frame2 = new GUIVisualization(plotType, generalXPoints, removeDataPointsY, "Remove Data Plots"); // Create a new instance of GUIVisualization
            frame2.setVisible(true); // Make the frame visible


            searchDataPointsY.add(searchDataPointsY.get(searchDataPointsY.size() - 1) * (long)1.5);
            GUIVisualization frame3 = new GUIVisualization(plotType, generalXPoints, searchDataPointsY, "Search Data Plots"); // Create a new instance of GUIVisualization
            frame3.setVisible(true); // Make the frame visible

            updateDataPointsY.add(updateDataPointsY.get(updateDataPointsY.size() - 1) * (long)1.5);
            GUIVisualization frame4 = new GUIVisualization(plotType, generalXPoints, updateDataPointsY, "Update Data Plots"); // Create a new instance of GUIVisualization
            frame4.setVisible(true); // Make the frame visible

        });

    }
    /**
     * Process the command from the input file
     * @param line command from the input file
     * @param manager StockDataManager object
     */
    private static void processCommand(String line, StockDataManager manager) {
        String[] tokens = line.split(" ");
        String command = tokens[0];

        switch (command) {
            case "NODE":
                manager.addOrUpdateStock(tokens[1], Double.parseDouble(tokens[2]), Long.parseLong(tokens[3]), Long.parseLong(tokens[4]));
                System.out.println("Node added: " + tokens[1]);
                break;
            case "ADD":
                manager.addOrUpdateStock(tokens[1], Double.parseDouble(tokens[2]), Long.parseLong(tokens[3]), Long.parseLong(tokens[4]));
                System.out.println("Stock added: " + tokens[1]);
                break;
            case "REMOVE":
                manager.removeStock(tokens[1]);
                System.out.println("Stock removed: " + tokens[1]);
                break;
            case "SEARCH":
                Stock stock = manager.searchStock(tokens[1]);
                if (stock != null) {
                    System.out.println("Stock found: " + tokens[1]);
                }
                else {
                    System.out.println("Stock not found: " + tokens[1]);
                }
                break;
            case "UPDATE":
                manager.updateStock(tokens[1], Double.parseDouble(tokens[2]), Long.parseLong(tokens[3]), Long.parseLong(tokens[4]));
                System.out.println("Stock updated: " + tokens[1]);
                break;
            default:
                System.out.println("Unknown command: " + command);
                break;
        }
    }

    /**
     * Perform performance analysis for the operations
     * @param manager StockDataManager object
     * @param size size of the data
     */
    private static void performPerformanceAnalysis(StockDataManager manager, int size) {
        long startTime, endTime;

        // Measure time for ADD operation
        startTime = System.nanoTime();
        for (int i = 0; i < size; i++) {
            manager.addOrUpdateStock("SYM" + i, Math.random() * 100, (long) (Math.random() * 1000000), (long) (Math.random() * 1000000000));
        }
        endTime = System.nanoTime();
        System.out.println("Average ADD time: " + (endTime - startTime) / size + " ns");

        // Add data points for the performance analysis
        addDataPointsY.add((endTime - startTime) / (size));

        // Measure time for SEARCH operation
        startTime = System.nanoTime();
        for (int i = 0; i < size; i++) {
            manager.searchStock("SYM" + i);
        }
        endTime = System.nanoTime();
        System.out.println("Average SEARCH time: " + (endTime - startTime) / size + " ns");

        // Add data points for the performance analysis
        searchDataPointsY.add((endTime - startTime) / (size));

        // Measure time for UPDATE operation
        startTime = System.nanoTime();
        for (int i = 0; i < size; i++) {
            manager.updateStock("SYM" + i, Math.random() * 100, (long) (Math.random() * 1000000), (long) (Math.random() * 1000000000));
        }
        endTime = System.nanoTime();
        System.out.println("Average UPDATE time: " + (endTime - startTime) / size + " ns");

        // Add data points for the performance analysis
        updateDataPointsY.add((endTime - startTime) / (size));

        // Measure time for REMOVE operation
        startTime = System.nanoTime();
        for (int i = 0; i < size; i++) {
            manager.removeStock("SYM" + i);
        }
        endTime = System.nanoTime();
        System.out.println("Average REMOVE time: " + (endTime - startTime) / size + " ns");

        // Add data points for the performance analysis
        removeDataPointsY.add((endTime - startTime) / (size));
        System.out.println("*".repeat(50));
    }
}
