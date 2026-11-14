   #include <stdio.h>
#include <string.h>
#include <ctype.h>

#define P 8

char lhs[P] = {'E','A','A','T','B','B','F','F'};
char *rhs[P] = {"TA","+TA","#","FB","*FB","#","(E)","i"};

int FIRST[128][128], FOLLOW[128][128];

int add(int set[], char c)
{
    if (!set[(int)c]) {
        set[(int)c] = 1;
        return 1;
    }
    return 0;
}

// Find FIRST o  a string
void firstString(char *s, int result[])
{
    int i, nullable = 1;

    for (i = 0; s[i] != '\0'; i++) {
        char c = s[i];

        if (!isupper((unsigned char)c)) {
            add(result, c);
            nullable = 0;
            break;
        }

        for (int j = 0; j < 128; j++)
            if (j != '#' && FIRST[(int)c][j])
                add(result, j);

        if (!FIRST[(int)c]['#']) {
            nullable = 0;
            break;
        }
    }

    if (nullable)
        add(result, '#');
}

int main()
{
    int changed, temp[128];

    // Calculate FIRST
    do {
        changed = 0;

        for (int i = 0; i < P; i++) {
            memset(temp, 0, sizeof(temp));
            firstString(rhs[i], temp);

            for (int j = 0; j < 128; j++)
                if (temp[j])
                    changed |= add(FIRST[(int)lhs[i]], j);
        }
    }
  while (changed);

    // Calculate FOLLOW
    add(FOLLOW['E'], '$');

    do {
        changed = 0;

        for (int i = 0; i < P; i++) {
            char *s = rhs[i];

            for (int j = 0; s[j] != '\0'; j++) {

                if (isupper((unsigned char)s[j])) {
                    char c = s[j];
                    char beta[100];

                    strcpy(beta, s + j + 1);

                    memset(temp, 0, sizeof(temp));
                    firstString(beta, temp);

                    for (int k = 0; k < 128; k++)
                        if (k != '#' && temp[k])
                            changed |= add(FOLLOW[(int)c], k);

                    if (temp['#']) {
                        for (int k = 0; k < 128; k++)
                            if (FOLLOW[(int)lhs[i]][k])
                                changed |= add(FOLLOW[(int)c], k);
                    }
                }
            }
        }
    } while (changed);

    // Display FIRST
    char nts[] = {'E','A','T','B','F'};

    printf("FIRST SETS:\n");

    for (int i = 0; i < 5; i++) {
        char c = nts[i];

        printf("FIRST(%c) = { ", c);

        for (int j = 0; j < 128; j++)
            if (FIRST[(int)c][j]) {
                if (j == 'i')
                    printf("id ");
                else if (j == '#')
                    printf("epsilon ");
                else
                    printf("%c ", j);
            }

        printf("}\n");
    }

    // Display FOLLOW
    printf("\nFOLLOW SETS:\n");

    for (int i = 0; i < 5; i++) {
        char c = nts[i];

        printf("FOLLOW(%c) = { ", c);

        for (int j = 0; j < 128; j++)
            if (FOLLOW[(int)c][j])
                printf("%c ", j);

        printf("}\n");
    }

    return 0;
}

