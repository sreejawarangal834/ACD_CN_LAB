 
#include <stdio.h>
#include <stdlib.h>

struct Node
{
    char value;
    struct Node *left, *right;
};

int regCount = 0;

// Function to create a node
struct Node* createNode(char value, struct Node *left, struct Node *right)
{
    struct Node *node = (struct Node*)malloc(sizeof(struct Node));

    node->value = value;
    node->left = left;
    node->right = right;

    return node;
}

// Function to generate target code
int generateCode(struct Node *root)
{
    int leftReg, rightReg, currentReg;

    if (root == NULL)
        return -1;
                                                                                                                                                                                                                                                                                                                                                                                                                                     
    // Check leaf node
    if (root->left == NULL && root->right == NULL)
    {
        currentReg = regCount++;
        printf("MOV R%d, %c\n", currentReg, root->value);
        return currentReg;
    }

    // Generate code for left and right children
    leftReg = generateCode(root->left);
    rightReg = generateCode(root->right);

    // Allocate register
    currentReg = regCount++;

    // Generate instruction based on operator
    switch (root->value)
    {
        case '+':
            printf("ADD R%d, R%d, R%d\n", currentReg, leftReg, rightReg);
            break;

        case '-':
            printf("SUB R%d, R%d, R%d\n", currentReg, leftReg, rightReg);
            break;

        case '*':
            printf("MUL R%d, R%d, R%d\n", currentReg, leftReg, rightReg);
            break;

        case '/':
            printf("DIV R%d, R%d, R%d\n", currentReg, leftReg, rightReg);
            break;
    }

    return currentReg;
}

int main()
{
    // Create leaf nodes
    struct Node *a = createNode('a', NULL, NULL);
    struct Node *b = createNode('b', NULL, NULL);
    struct Node *c = createNode('c', NULL, NULL);

    // Construct AST for a + (b * c)
    struct Node *mul = createNode('*', b, c);
    struct Node *root = createNode('+', a, mul);

    printf("Abstract Syntax Tree:\n\n");
    printf("    +\n");
    printf("   / \\\n");
    printf("  a   *\n");
    printf("     / \\\n");
    printf("    b   c\n");
    
    printf("\nGenerated Machine Code:\n");
    generateCode(root);

    return 0;
}
