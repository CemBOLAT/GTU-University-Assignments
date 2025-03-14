/*
	* This class is used to create an order object.
	* It contains the product name, count, total price, status, and customer ID.
	* It also contains the methods to get and set the values of the order object.
	* It also contains the method to print the order.
*/
public class Order
{
	private String product_name;
	private int count;
	private int total_price;
	private int status;
	private int customer_ID;

	public static final String STATUS[] = {"Initialized", "Processing", "Completed", "Cancelled"};

	public Order(String _product_name, int _count, int _total_price, int _status, int _customer_ID) throws Exception
	{
		if (_product_name.equals("") || _count <= 0 || _total_price <= 0 || _status < 0 || _status > 3 || _customer_ID <= 0)
		{
			throw new Exception("Invalid input for order.");
		}
		this.product_name = _product_name;
		this.count = _count;
		this.total_price = _total_price;
		this.status = _status;
		this.customer_ID = _customer_ID;
	}
	public String getProductName()
	{
		return this.product_name;
	}
	public int getCount()
	{
		return this.count;
	}
	public int getTotalPrice()
	{
		return this.total_price;
	}
	public int getStatus()
	{
		return this.status;
	}
	public int getCustomerID()
	{
		return this.customer_ID;
	}
	public void print_order()
	{
		System.out.println("Product Name: " + this.product_name + " - " + "Count: " + this.count + " - " + "Total Price: " + this.total_price + " - " + "Status: " + STATUS[status]);
	}
}
