/*
	* This is the Customer class. It is a subclass of the Person class. It has 2 additional attributes: operator ID and an array of orders.
	* It has 2 additional methods: print_customer and print_orders.
	* The print_customer method prints the customer's information and the print_orders method prints the customer's orders.
	* It also has a define_orders method which takes an array of orders as a parameter and assigns the orders of the customer to the orders array.
*/
public class Customer extends Person
{
	private Order [] orders;
	private int operator_ID;
	private int orderCount;

	public Customer(String _name, String _surName, String _address,
					String _phoneNumber, int _ID, int _operator_ID) throws Exception
	{
		/*
			* This is the constructor of the Customer class. It takes 6 parameters and calls the constructor of the Person class with 5 parameters.
			* It also initializes the operator ID attribute and creates an array of orders.
		*/
		super(_name, _surName, _address, _phoneNumber, _ID);
		// no need for my own validation here becuase no valid input creates a customer object
		// and it is not possible to create a person object without valid input
		// for modularity and reusability I will use the same validation method here
		if (_operator_ID <= 0)
		{
			throw new Exception("Operator ID can't be less than or equal to 0.");
		}
		if (_ID == _operator_ID)
		{
			throw new Exception("Operator ID can't be the same as the customer ID.");
		}
		this.operator_ID = _operator_ID;
		this.orders = new Order[100];
		this.orderCount = 0;
	}
	public int getOperatorID()
	{
		return this.operator_ID;
	}
	public int getOrderCount()
	{
		return this.orderCount;
	}
	public void print_customer()
	{
		System.out.println("Name & Surname: " + this.getName() + " " + this.getSurName() + "\n" + "Address: " + this.getAddress() + "\n" + "Phone Number: " + this.getPhoneNumber() + "\n" + "ID: " + this.getID() + "\n" + "Operator ID: " + this.operator_ID);
	}
	/*
	* This method prints the customer's orders. It calls the print_order method of the Order class for each order in the orders array.
	*/
	public void print_orders()
	{
		if (this.orderCount == 0)
		{
			drawline();
			System.out.println("This customer doesn't have any order.");
			return;
		}
		for(int i = 0; i < this.orderCount; i++)
		{
			System.out.print("Order #" + (i+1) + " => ");
			orders[i].print_order();
		}
	}
	/*
	* This method takes an array of orders as a parameter and assigns the orders of the customer to the orders array.
	*/
	public void define_orders(Order [] _orders)
	{
		int i = 0;
		while (_orders[i] != null)
		{
			if (_orders[i].getCustomerID() == this.getID())
			{
				this.orders[this.orderCount] = _orders[i];
				this.orderCount++;
			}
			i++;
		}
	}
	public static void drawline()
	{
		System.out.println("-------------------------------------------------");
	}
}
