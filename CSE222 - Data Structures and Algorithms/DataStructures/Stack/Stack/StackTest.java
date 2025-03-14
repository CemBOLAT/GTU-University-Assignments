import java.util.EmptyStackException;

public class StackTest {
    private static boolean isOperation(String c){
        return c.equals("+") || c.equals("-") || c.equals("*") || c.equals("/");
    }
    private static boolean isP(String c){
        return isOP(c) || isCP(c);
    }
    private static boolean isOP(String c){
        return c.equals("(");
    }
    private static boolean isCP(String c){
        return c.equals(")");
    }
    private static int evaluatePostfix(String[] str) throws Exception {
        Stack<Integer> stack = new Stack<>();
        Stack<String>  stringStack = new Stack<>();

        int     res = 0;

        for (int i = 0; i < str.length; i++){
            if (isOperation(str[i])){
                if (stack.size() < 2){
                    throw new Exception("AAAA");
                }
                int f = stack.pop();
                int s = stack.pop();
                String fs = stringStack.pop();
                String ss = stringStack.pop();

                if (str[i].equals("+")){
                    stack.push(f + s);
                }
                else if (str[i].equals("-")){
                    stack.push(s - f);
                }
                else if (str[i].equals("/")){
                    if (f == 0){
                        throw new Exception("AAAA");
                    }
                    stack.push(s / f);
                }
                else if (str[i].equals("*")){
                    stack.push(f * s);
                }
                stringStack.push("(" + ss + " " + str[i] + " " + fs + ")");
            }
            else {
                stack.push(Integer.parseInt(str[i]));
                stringStack.push(str[i]);
            }
        }
        if (stack.size() != 1){
            throw new Exception("b");
        }
        System.out.println(stringStack.pop());
        return
         stack.pop();
    }
    private static boolean highPrese(String sta, String str){
        if (sta.equals("*") && (str.equals("+") || str.equals("-"))){
            return true;
        }
        else if (sta.equals("/") && (str.equals("+") || str.equals("-")))
        {
            return true;
        }
        return false;
    }
    private static String evaluateInfix(String[] str) throws Exception {
        Stack<String> stack = new Stack<>();
        StringBuilder sb = new StringBuilder();

        for (int i = 0; i < str.length; i++){
            if (!isOperation(str[i]) && !isP(str[i])){
                sb.append(str[i] + " ");
            }
            else if (isOP(str[i])){
                stack.push(str[i]);
            }
            else if (isCP(str[i])){
                while (!isOP(stack.peek())){
                    sb.append(stack.pop() + " ");
                }
                stack.pop();
            }
            else {
                if(stack.isEmpty()){
                    stack.push(str[i]);
                }
                else if (highPrese(stack.peek(), str[i])){
                    sb.append(stack.pop() + " ");
                    stack.push(str[i]);
                }
                else {
                    stack.push(str[i]);
                }
            }
        }
        while (!stack.isEmpty()){
            sb.append(stack.pop() + " ");
        }
        return sb.toString();
    }

    public static void main(String[] args) {
        String postfix = "4 7 + 8 5 3 * - +";
        String infix = "( ( 4 + 7 ) + ( 8 - ( 5 * 3 ) ) )";
        String prefix = "+ + 4 7 + 8 - * 5 3";

        String[] tok = postfix.split(" ");

        try {
            int result = evaluatePostfix(tok);
            System.out.println("Postfix: " + postfix + " = " + result); // 4
            System.out.println("Infix: " + evaluateInfix(infix.split(" "))); // 4
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}
