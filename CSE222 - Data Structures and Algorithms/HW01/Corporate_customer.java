
/*
	* This class is a subclass of the Customer class. It has a company name attribute in addition to the attributes of the Customer class. \
	It has a constructor, getter and setter methods for the company name attribute. It also has a print_customer method to print the attributes of the customer.

 */
public class Corporate_customer extends Customer
{
	private String company_name;

	public Corporate_customer(String _name, String _surName, String _address, String _phoneNumber,
								int _ID, int _operator_ID, String _company_name) throws Exception
	{
		/*
			* This is the constructor of the Corporate_customer class. It takes 7 parameters and calls the constructor of the Customer class with 6 parameters.
			* It also initializes the company name attribute.
		*/
		super(_name, _surName, _address, _phoneNumber, _ID, _operator_ID);
		// no need for my own validation here becuase no valid input creates a corporate_customer object
		// and it is not possible to create a person object without valid input
		// for modularity and reusability I will use the same validation method here
		if (_company_name.equals(""))
		{
			throw new Exception("Company name can't be empty.");
		}
		this.company_name = _company_name;
	}
	public String getCompanyName()
	{
		return this.company_name;
	}
	/*
	* This method prints the attributes of the customer.
	* Its additional attribute is the company name.
	*/
	@Override
	public void print_customer()
	{
		System.out.println("Name & Surname: " + this.getName() + " " + this.getSurName() + "\n" + "Address: " + this.getAddress() + "\n" + "Phone Number: " + this.getPhoneNumber() + "\n" + "ID: " + this.getID() + "\n" + "Operator ID: " + this.getOperatorID() + "\n" + "Company Name: " + this.company_name);
	}
}
