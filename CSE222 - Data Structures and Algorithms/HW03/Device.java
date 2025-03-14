import java.io.FileWriter;
import java.io.IOException;
/**
 * This interface is used to define the methods that are used in any device
 * @author - Cemal BOLAT
 */

public interface Device {
	/**
	 * This method is used to get the category of the device
	 *
	 * @return String - category of the device
	 */
	String getCategory();
	/**
		* This method is used to get the name of the device
		*
		* @return String - name of the device
	*/
	String getName();
	/**
		* This method is used to get the price of the device
		*
		* @return double - price of the device
	*/
	double getPrice();
	/**
		* This method is used to get the quantity of the device
		*
		* @return int - quantity of the device
	*/
	int getQuantity();
	/**
		* This method is used to set the category of the device
		*
		* @param category - category of the device
		* @throws Exception - if the category is not valid
	*/
	void setCategory(String category) throws Exception;
	/**
		* This method is used to set the name of the device
		*
		* @param name - name of the device
		* @throws Exception - if the name is not valid
	*/
	void setName(String name) throws Exception;
	/**
		* This method is used to set the price of the device
		*
		* @param price - price of the device
		* @throws Exception - if the price is not valid
	*/
	void setPrice(double price) throws Exception;
	/**
		* This method is used to set the quantity of the device
		*
		* @param quantity - quantity of the device
		* @throws Exception - if the quantity is not valid
	*/
	void setQuantity(int quantity) throws Exception;
	/**
		* This method is used to increase the stock of the device
		*
		* @param stock - stock to be added
	*/
	void addStock(int stock);
	/**
		* This method is used to decrease the stock of the device
		*
		* @param stock - stock to be removed
	*/
	void removeStock(int stock);
	/**
		* This method is used to print the device information for the export format
		*
		* @param index - index of the device
		* @param fileWriter - fileWriter to write to the file
		* @throws IOException - if the fileWriter is not valid
	*/
	void exportFilePrint(int index, FileWriter fileWriter) throws IOException;
}
