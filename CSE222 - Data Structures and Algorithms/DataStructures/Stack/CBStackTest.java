import java.util.Stack;

public class CBStackTest {
    public static boolean isClosed(char c){
        return c == ')' || c == ']' || c == '}';
    }
    public static boolean isOpen(char c){
        return c == '(' || c == '[' || c == '{';
    }


    public static void isBalanced(){
        CBStack<Character> stack = new CBStack<Character>();
        String test = new String("({[2[3(3){3}]])");
        for (int i = 0; i < test.length(); i++){
            char c = test.charAt(i);
            if (isOpen(c)){
                stack.push(c);
            } else if (isClosed(c)){
                if (stack.empty()){
                    System.out.println("Unbalanced at index " + i);
                    return;
                }
                char popped = stack.pop();
                if (c == ')' && popped != '('){
                    System.out.println("Unbalanced at index " + i);
                    return;
                } else if (c == ']' && popped != '['){
                    System.out.println("Unbalanced at index " + i);
                    return;
                } else if (c == '}' && popped != '{'){
                    System.out.println("Unbalanced at index " + i);
                    return;
                }
            }
        }
        if (!stack.empty()){
            System.out.println("Unbalanced at index " + test.length());
        } else {
            System.out.println("Balanced");
        }
    }

    public static void postFix(){
        CBStack<Integer> stack = new CBStack<Integer>();
        String test = new String("2 3 4 * + 5 -"); // 9
        String[] tokens = test.split(" ");
        for (int i = 0; i < tokens.length; i++){
            String token = tokens[i];
            if (token.equals("+")){
                int a = stack.pop();
                int b = stack.pop();
                stack.push(b + a);
            } else if (token.equals("-")){
                int a = stack.pop();
                int b = stack.pop();
                stack.push(b - a);
            } else if (token.equals("*")){
                int a = stack.pop();
                int b = stack.pop();
                stack.push(b * a);
            } else if (token.equals("/")){
                int a = stack.pop();
                int b = stack.pop();
                stack.push(b / a);
            } else {
                stack.push(Integer.parseInt(token));
            }
        }
        if (stack.size() != 1){
            System.out.println("Invalid expression");
            return;
        }
        System.out.println(stack.pop());
    }
    public static int precedence(char c){
        if (c == '+' || c == '-'){
            return 1;
        } else if (c == '*' || c == '/'){
            return 2;
        } else {
            return 0;
        }
    }
    public static void infixToPostfix(){
        CBStack<Character> stack = new CBStack<Character>();
        String test = new String("2 + 3 * 4 - 5");
        String[] tokens = test.split(" ");
        for (int i = 0; i < tokens.length; i++){
            String token = tokens[i];
            if (token.equals("+") || token.equals("-") || token.equals("*") || token.equals("/")){
                while (!stack.empty() && precedence(stack.peek()) >= precedence(token.charAt(0))){
                    System.out.print(stack.pop() + " ");
                }
                stack.push(token.charAt(0));
            } else {
                System.out.print(token + " ");
            }
        }
        while (!stack.empty()){
            System.out.print(stack.pop() + " ");
        }
        System.out.println();
    }
    public static void main(String[] args){
        isBalanced();
        postFix();
        // infixToPostfix();
    }
}