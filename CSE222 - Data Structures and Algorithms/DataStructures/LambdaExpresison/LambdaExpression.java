public class LambdaExpression {

	interface lambda{
		int f(int x);
	}
	interface lambda2{
		int f(int x, int y);
	}

	public static void main(String[] str){
		lambda l = (x) -> (x * x * 2);
		lambda2 l2 = (x, y) -> (x * 2 * 2);

		System.out.println(l.f(5));
		System.out.println(l2.f(5,2));
	}
}
