/*
	Person class is the base class for all the other classes. It has the basic attributes of a person.
	It has a constructor, getter and setter methods for each attribute.
*/
public class Person
{
	private String name;
	private String surName;
	private String address;
	private String phoneNumber;
	private int ID;

	public Person(String _name, String _surName, String _address, String _phoneNumber, int _ID) throws Exception
	{
		// no need for my own validation here becuase no valid input creates a person object
		// and it is not possible to create a person object without valid input
		// for modularity and reusability I will use the same validation method here
		if (_name.equals("") || _surName.equals("") || _address.equals("") || _phoneNumber.equals("") || _ID <= 0)
		{
			throw new Exception("Invalid input for person.");
		}
		this.name = _name;
		this.surName = _surName;
		this.address = _address;
		this.phoneNumber = _phoneNumber;
		this.ID = _ID;
	}
	public String getName()
	{
		return this.name;
	}
	public String getSurName()
	{
		return this.surName;
	}
	public String getAddress()
	{
		return this.address;
	}
	public String getPhoneNumber()
	{
		return this.phoneNumber;
	}
	public int getID()
	{
		return this.ID;
	}
}
