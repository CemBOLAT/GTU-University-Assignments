/*
	* This class is a subclass of Person class. It has a wage and an array of customers. It has a method to define the customers of the operator.
	* It also has a method to print the operator's information and the customers of the operator.
*/
public class Operator extends Person
{
	private int wage;
	private Customer [] customers;
	private int customerCount;
	public Operator(String _name, String _surName, String _address,
					String _phoneNumber, int _ID, int _wage) throws Exception
	{
		// This is the constructor of the Operator class. It takes 6 parameters and calls the constructor of the Person class with 5 parameters.
		// It also initializes the wage attribute and creates an array of customers.
		super(_name, _surName, _address, _phoneNumber, _ID);
		// no need for my own validation here becuase no valid input creates a operator object
		// and it is not possible to create a person object without valid input
		// for modularity and reusability I will use the same validation method here
		if (_wage <= 0)
		{
			throw new Exception("Wage can't be less than or equal to 0.");
		}
		this.wage = _wage;
		this.customers = new Customer[100];
		this.customerCount = 0;
	}
	public int getWage()
	{
		return this.wage;
	}
	public int getCustomerCount()
	{
		return this.customerCount;
	}
	public void print_operator()
	{
		System.out.println("Name & Surname: " + this.getName() + " " + this.getSurName() + "\n" + "Address: " + this.getAddress() + "\n" + "Phone Number: " + this.getPhoneNumber() + "\n" + "ID: " + this.getID() + "\n" + "Wage: " + this.wage);
	}
	public void print_customers()
	{
		if (getCustomerCount() == 0)
		{
			System.out.println("This operator doesn't have any customer.");
			drawline();
			return;
		}
		for(int i = 0; i < this.customerCount; i++)
		{
			if (customers[i] instanceof Retail_customer){ // check if the customer is a retail customer
				System.out.println("Customer #" + (i+1) + " (a retail customer) :");
			}
			else if (customers[i] instanceof Corporate_customer){ // check if the customer is a corporate customer
				System.out.println("Customer #" + (i+1) + " (a corporate customer) :");
			}
			customers[i].print_customer();
			customers[i].print_orders();
			drawline();
		}
	}
	public void define_customers(Customer [] _customers)
	{
		int i = 0;
		while (_customers[i] != null)
		{
			if (((Customer)_customers[i]).getOperatorID() == this.getID())
			{
				this.customers[this.customerCount] = (Customer)_customers[i];
				this.customerCount++;
			}
			i++;
		}
	}
	public static void drawline()
	{
		System.out.println("-------------------------------------------------");
	}

}
