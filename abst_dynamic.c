
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

struct Node
{
    char value;
    struct Node *left, *right;
};

int regCount = 0;
char exp[100];
int pos = 0;

// Create a node
struct Node* createNode(char ch)
{
    struct Node *newNode = malloc(sizeof(struct Node));

    newNode->value = ch;
    newNode->left = NULL;
    newNode->right = NULL;

    return newNode;
}

// Parse expression
struct Node* expression();
struct Node* term();
struct Node* factor();

struct Node* expression()
{
    struct Node *root = term();

    while (exp[pos] == '+' || exp[pos] == '-')
    {
        char op = exp[pos++];
        struct Node *newNode = createNode(op);

        newNode->left = root;
        newNode->right = term();

        root = newNode;
    }

    return root;
}

struct Node* term()
{
    struct Node *root = factor();

    while (exp[pos] == '*' || exp[pos] == '/')
    {
        char op = exp[pos++];
        struct Node *newNode = createNode(op);

        newNode->left = root;
        newNode->right = factor();

        root = newNode;
    }

    return root;
}

struct Node* factor()
{
    struct Node *root;

    if (exp[pos] == '(')
    {
        pos++;
        root = expression();
        pos++; // Skip ')'
    }
    else
    {
        root = createNode(exp[pos++]);
    }

    return root;
}

// Generate machine code
int generateCode(struct Node *root)
{
    int leftReg, rightReg, currentReg;

    if (root == NULL)
        return -1;

    // Leaf node
    if (root->left == NULL && root->right == NULL)
    {
        currentReg = regCount++;
        printf("MOV R%d, %c\n", currentReg, root->value);
        return currentReg;
    }

    leftReg = generateCode(root->left);
    rightReg = generateCode(root->right);

    currentReg = regCount++;

    switch (root->value)
    {
        case '+':
            printf("ADD R%d, R%d, R%d\n",
                   currentReg, leftReg, rightReg);
            break;

        case '-':
            printf("SUB R%d, R%d, R%d\n",
                   currentReg, leftReg, rightReg);
            break;

        case '*':
            printf("MUL R%d, R%d, R%d\n",
                   currentReg, leftReg, rightReg);
            break;

        case '/':
            printf("DIV R%d, R%d, R%d\n",
                   currentReg, leftReg, rightReg);
            break;
    }

    return currentReg;
}

int main()
{
    struct Node *root;

    printf("Enter expression: ");
    scanf("%99s", exp);

    root = expression();

    printf("\nGenerated Machine Code:\n");
    generateCode(root);

    return 0;
}
