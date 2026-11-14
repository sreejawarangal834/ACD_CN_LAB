
import java.util.*;

public class ThreeAddressCode {

    static int t = 1;

    static int prec(char op) {
        if (op == '*' || op == '/')
            return 2;
        if (op == '+' || op == '-')
            return 1;
        return 0;
    }

    static void generate(String s) {

        Stack<Character> op = new Stack<>();
        Stack<Character> val = new Stack<>();

        int i = 0;

        while (i < s.length()) {

            char ch = s.charAt(i);

            if (Character.isLetterOrDigit(ch)) {
                val.push(ch);
                i++;
            }

            else if (ch == '(') {
                op.push(ch);
                i++;
            }

            else if (ch == ')') {

                while (!op.isEmpty() && op.peek() != '(') {

                    char operator = op.pop();

                    char b = val.pop();
                    char a = val.pop();

                    char temp = (char)('A' + t - 1);

                    System.out.println("t" + t + " = " +
                            a + " " + operator + " " + b);

                    t++;

                    val.push(temp);
                }

                op.pop();  // Remove '('
                i++;
            }

            else {

                while (!op.isEmpty() && op.peek() != '(' &&
                       prec(op.peek()) >= prec(ch)) {

                    char operator = op.pop();

                    char b = val.pop();
                    char a = val.pop();

                    char temp = (char)('A' + t - 1);

                    System.out.println("t" + t + " = " +
                            a + " " + operator + " " + b);

                    t++;

                    val.push(temp);
                }

                op.push(ch);
                i++;
            }
        }

        while (!op.isEmpty()) {

            char operator = op.pop();

            char b = val.pop();
            char a = val.pop();

            char temp = (char)('A' + t - 1);

            System.out.println("t" + t + " = " +
                    a + " " + operator + " " + b);

            t++;

            val.push(temp);
        }
    }

    public static void main(String[] args) {

        Scanner sc = new Scanner(System.in);

        System.out.print("Enter expression: ");
        String s = sc.next();

        System.out.println("Three Address Code:");
        generate(s);

        sc.close();
    }
}
