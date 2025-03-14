/*
	* This file contains the Retail_customer class, which is a subclass of the Customer class.
	* It is used to create a retail customer object.
*/
public class Retail_customer extends Customer
{
	public Retail_customer(String _name, String _surName, String _address, String _phoneNumber, int _ID, int _operator_ID) throws Exception
	{
		/*
			* This is the constructor of the Retail_customer class. It takes 6 parameters and calls the constructor of the Customer class with 6 parameters.
		*/
	   super(_name, _surName, _address, _phoneNumber, _ID, _operator_ID);
	}
}
