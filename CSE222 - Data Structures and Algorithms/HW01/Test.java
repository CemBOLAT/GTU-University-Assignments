import java.io.File;
import java.util.Scanner;

public class Test
{
	public static final int isReaderTest = 0; // 1 for testing the reader class, 0 for the main program handmade assert function
	// This method prints the orders in the array after reading txt file.
	public static void printOrders(Order [] order){
		for (int i = 0; i < order.length; i++)
		{
			if (order[i] == null)
				break;
			order[i].print_order();
			drawline();
		}
	}
	// This method prints the customers in the array.
	public static void printCustomers(Customer [] customer){
		for (int i = 0; i < customer.length; i++)
		{
			if (customer[i] == null)
				break;
			customer[i].print_customer();
			drawline();
		}
	}
	// This method prints the operators in the array.
	public static void printOperators(Operator [] operator){
		for (int i = 0; i < operator.length; i++)
		{
			if (operator[i] == null)
				break;
			operator[i].print_operator();
			drawline();
		}
	}
	public static void drawline()
	{
		System.out.println("-------------------------------------------------");
	}
	public static int isValidInput(String input) throws Exception
	{
		if(input.length() > 0 && input.length() < 11) // max int is 214 748 3647
		{
			for(int i = 0; i < input.length(); i++)
			{
				if (input.charAt(i) < '0' || input.charAt(i) > '9'){
					System.out.println("Invalid input. Please enter a valid ID.");
					return 0;
				}
			}
			long d = Long.parseLong(input);
			if (d <= Integer.MAX_VALUE && d >= Integer.MIN_VALUE){
				if (d == 0){
					System.out.println("Invalid input. Please enter a valid ID.");
					return 0;
				}
				return 1;
			}
			System.out.println("Invalid input its over max int. Please enter a valid ID.");
			return 0;
		}
		System.out.println("Invalid length of input. Please enter an integer as a valid ID.");
		return 0;
	}
	// This method is used for testing the reader class.
	// It prints the orders, customers and operators in the arrays.
	public static void testReader(Order [] orders, Customer [] customers, Operator [] operators) throws Exception
	{
		drawline();
		printOrders(orders);
		printCustomers(customers);
		printOperators(operators);
	}
	public static void main(String[] args)
	{
		try{
			File dosya = new File("./content.txt");
			/*
				As your permisson I used fixed size arrays with size 100.
				-- You can define the size of the arrays you use as 100. (as pdf file says)
			*/
			Order [] orders = new Order[100];
			Customer [] customers = new Customer[100];
			Operator [] operators = new Operator[100];
			FileReader.fillData(dosya, orders, customers, operators);
			if (isReaderTest == 1){
				testReader(orders, customers, operators); // for testing the reader class
				return;
			}
			Scanner scanner = new Scanner(System.in);
			System.out.println("Please enter your ID...");
			String input = scanner.nextLine();
			if (isValidInput(input) == 0){
				return;
			}
			int ID = Integer.parseInt(input);
			int found = 0;
			for (int i = 0; i < operators.length; i++)
			{
				if (operators[i] == null)
					break;
				if (operators[i].getID() == ID)
				{
					found = 1;
					System.out.println("*** Operator Screen ***");
					drawline();
					Operator operator = operators[i];
					operator.print_operator();
					drawline();
					operator.print_customers();
				}
			}
			if (found == 0)
			{
				for (int i = 0; i < customers.length; i++)
				{
					if (customers[i] == null)
						break;
					if (customers[i].getID() == ID)
					{
						found = 1;
						System.out.println("*** Customer Screen ***");
						Customer customer = customers[i];
						customer.print_customer();
						customer.print_orders();
						drawline();
					}
				}
			}
			if(found == 0)
				System.out.println("No operator/customer was found with ID " + input + ". Please try again.");

		} catch (Exception e) { /* ... */ }
	}
}
