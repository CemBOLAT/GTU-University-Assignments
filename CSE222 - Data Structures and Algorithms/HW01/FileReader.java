import java.io.File;
import java.util.Scanner;

/*
* This class reads the file and fills the arrays with the data in the file.
* It also checks if the data in the file is in the correct format.
*/

public class FileReader
{
	private static final int ORDER_SPLIT_LENGTH = 6; // order;product_name;count;total_price;status;customer_id
	private static final int RETAIL_CUSTOMER_SPLIT_LENGTH = 7; // retail_customer;name;surname;address;phone;ID;operator_ID
	private static final int CORPORATE_CUSTOMER_SPLIT_LENGTH = 8; // retail_customer;name;surname;address;phone;ID;operator_ID;company_name
	private static final int OPERATOR_SPLIT_LENGTH = 7; // operator;name;surname;address;phone;ID;wage

	/*
	* This method checks if the ID is unique.
	* It takes an ID and an array of customers and an array of operators as parameters.
	* It returns 1 if the ID is unique, otherwise it returns 0.
	*/
	public static int isUniqueID(int ID, Customer [] customer, Operator [] operators)
	{
		for (int i = 0; i < customer.length; i++) // check if the ID is unique
		{
			if (customer[i] == null)
				break;
			if (customer[i].getID() == ID)
				return 0;
		}
		for (int i = 0; i < operators.length; i++)
		{
			if (operators[i] == null)
				break;
			if (operators[i].getID() == ID)
				return 0;
		}
		return 1;
	}
	/*
	* This method fills the orders, customers and operators arrays with the data in the file.
	* It takes a file and arrays of orders, customers and operators as parameters.
	* It throws an exception if the file is not found or if there is an error while reading the file.
	* It ingores the lines that are not in the correct format.
	* It also ingores the lines that have the same ID with the other customers or operators.
	*/
	public static void fillData(File file, Order[] orders, Customer [] customers, Operator [] operators) throws Exception
	{
		try {
			Scanner scanner = new Scanner(file);
			String line;
			String [] tokens;
			int orderCount = 0, customerCount = 0, operatorCount = 0;
			while (scanner.hasNextLine()) {
				try {
					line = scanner.nextLine();
					tokens = line.split(";", -1);
					for (int i = 0; i < tokens.length; i++)
					{
						if (tokens[i].equals(""))
						{
							throw new Exception("");
						}
					}
					if (tokens[0].equals("order"))
					{

						if (tokens.length != ORDER_SPLIT_LENGTH)
						{
							throw new Exception("");
						}
						orders[orderCount] = new Order(tokens[1], Integer.parseInt(tokens[2]), Integer.parseInt(tokens[3]), Integer.parseInt(tokens[4]), Integer.parseInt(tokens[5]));
						orderCount++;
					}
					else if (tokens[0].equals("retail_customer"))
					{
						if (tokens.length != RETAIL_CUSTOMER_SPLIT_LENGTH)
						{
							throw new Exception("");
						}
						if (isUniqueID(Integer.parseInt(tokens[5]), customers, operators) == 0)
						{
							throw new Exception("");
						}
						Retail_customer retail_customer = new Retail_customer(tokens[1], tokens[2], tokens[3], tokens[4], Integer.parseInt(tokens[5]), Integer.parseInt(tokens[6]));
						retail_customer.define_orders(orders);
						customers[customerCount] = retail_customer;
						customerCount++;
					}
					else if (tokens[0].equals("corporate_customer"))
					{
						if (tokens.length != CORPORATE_CUSTOMER_SPLIT_LENGTH)
						{
							throw new Exception("");
						}
						if (isUniqueID(Integer.parseInt(tokens[5]), customers, operators) == 0)
						{
							throw new Exception("");
						}
						Corporate_customer corporate_customer = new Corporate_customer(tokens[1], tokens[2], tokens[3], tokens[4], Integer.parseInt(tokens[5]), Integer.parseInt(tokens[6]), tokens[7]);
						corporate_customer.define_orders(orders);
						customers[customerCount] = corporate_customer;
						customerCount++;
					}
					else if (tokens[0].equals("operator"))
					{
						if (tokens.length != OPERATOR_SPLIT_LENGTH)
						{
							throw new Exception("");
						}
						if (isUniqueID(Integer.parseInt(tokens[5]), customers, operators) == 0)
						{
							throw new Exception("");
						}
						Operator operator = new Operator(tokens[1], tokens[2], tokens[3], tokens[4], Integer.parseInt(tokens[5]), Integer.parseInt(tokens[6]));
						operator.define_customers(customers);
						operators[operatorCount] = operator;
						operatorCount++;
					}
					else {
						throw new Exception("");
					}
				} catch (Exception e) { /* ignore the line */ }
			}
		} catch (Exception e) {
			throw e;
		}
	}
}
