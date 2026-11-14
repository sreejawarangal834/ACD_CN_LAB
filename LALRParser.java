import java.util.*;

public class LALRParser {

    static int[][] action = {
        {3, 4, 0},
        {0, 0, 9},
        {3, 4, 0},
        {3, 4, 0},  
        {-3, -3, -3},
        {0, 0, -1},
        {-2, -2, -2}
    };

    static int[][] goTo = {
        {1, 2},
        {-1, -1},
        {-1, 5},
        {-1, 6},
        {-1, -1},
        {-1, -1},
        {-1, -1}
    };

    static String[] productions = {
        "",
        "S->CC",
        "C->cC",
        "C->d"
    };

    static int getColumn(char ch) {
        switch (ch) {
            case 'c': return 0;
            case 'd': return 1;
            case '$': return 2;
            default: return -1;
        }
    }

    public static void main(String[] args) {

        Scanner sc = new Scanner(System.in);

        System.out.print("Enter input string: ");
        String input = sc.nextLine().trim().concat("$");

        Stack<Integer> stack = new Stack<>();

        stack.push(0);

        int pos = 0;

        while (true) {

            int state = stack.peek();

            int col = getColumn(input.charAt(pos));

            if (col == -1) {
                System.out.println("Invalid input symbol!");
                break;
            }

            int act = action[state][col];

            // ACCEPT
            if (act == 9) {
                System.out.println("Input Accepted!");
                break;
            }

            // ERROR
            if (act == 0) {
                System.out.println("Input Rejected!");
                break;
            }

            // SHIFT
            if (act > 0) {

                System.out.println("Shift " + input.charAt(pos)
                                   + " -> State " + act);

                stack.push(act);
                pos++;
            }

            // REDUCE
            else {

                int rule = -act;

                System.out.println("Reduce using "
                                   + productions[rule]);

                int length;

                switch (rule) {
                    case 1: length = 2; break;
                    case 2: length = 2; break;
                    default: length = 1;
                }

                // POP states
                for (int i = 0; i < length; i++) {
                    stack.pop();
                }

                int currentState = stack.peek();

                // Find GOTO columns
                int row = (rule == 1) ? 0 : 1;

                int nextState = goTo[currentState][row];

                if (nextState == -1) {
                    System.out.println("Parsing Error!");
                    break;
                }

                stack.push(nextState);
            }
        }

        sc.close();
    }
}
