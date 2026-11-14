#include <stdio.h>
#include <ctype.h>

int t = 1;

int prec(char op) {
    if (op == '*' || op == '/') return 2;
    if (op == '+' || op == '-') return 1;
    return 0;
}

void generate(char s[]) {
    char op[50], val[50];
    int i = 0, top1 = -1, top2 = -1;

    while (s[i] != '\0') {
        if (isalnum(s[i])) {
            val[++top2] = s[i++];
        }
        else if (s[i] == '(') {
            op[++top1] = s[i++];
        }
        else if (s[i] == ')') {
            while (top1 >= 0 && op[top1] != '(') {
                char ch = op[top1--];
                char b = val[top2--];
                char a = val[top2--];

                char temp = 'A' + t - 1;
                printf("t%d = %c %c %c\n", t++, a, ch, b);
                val[++top2] = temp;
            }
            top1--;
            i++;
        }
        else {
            while (top1 >= 0 && op[top1] != '(' &&
                   prec(op[top1]) >= prec(s[i])) {
                char ch = op[top1--];
                char b = val[top2--];
                char a = val[top2--];

                char temp = 'A' + t - 1;
                printf("t%d = %c %c %c\n", t++, a, ch, b);
                val[++top2] = temp;
            }
            op[++top1] = s[i++];
        }
    }

    while (top1 >= 0) {
        char ch = op[top1--];
        char b = val[top2--];
        char a = val[top2--];

        char temp = 'A' + t - 1;
        printf("t%d = %c %c %c\n", t++, a, ch, b);
        val[++top2] = temp;
    }
}

int main() {
    char s[100];

    printf("Enter expression: ");
    scanf("%99s", s);

    printf("Three Address Code:\n");
    generate(s);

    return 0;
}

