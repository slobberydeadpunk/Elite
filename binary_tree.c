#include <stdio.h>
#include <stdlib.h>

typedef struct binary_tree_node
{
    int elem;
    struct binary_tree_node *left;
    struct binary_tree_node *right;
}binary_tree_node, *binary_tree;

void init_binary_tree(binary_tree *root);
void create_binary_tree(binary_tree * root);

void preorder_traverse_recursive(binary_tree root);
void inorder_traverse_recursive(binary_tree root);
void postorder_traverse_recursive(binary_tree root);

int main()
{
    binary_tree root;
    init_binary_tree(&root);
    create_binary_tree(&root);

    printf("preorder: \t");
    preorder_traverse_recursive(root);
    printf("\n");

    printf("inorder: \t");
    inorder_traverse_recursive(root);
    printf("\n");

    printf("postorder: \t");
    postorder_traverse_recursive(root);
    printf("\n");

    exit(0);
}

void init_binary_tree(binary_tree *root)
{
    *root = NULL;
}

void create_binary_tree(binary_tree *root)
{
    int elem;
    printf("Enter node value(0 is end): ");
    scanf("%d", &elem);

    if (elem == 0)
        *root = NULL;
    else
    {
        *root = (binary_tree)malloc(sizeof(binary_tree_node));
        if (root == NULL)
        {
            printf("malloc error.\n");
            exit(-1);
        }
        (*root)->elem = elem;
        printf("Creating the left child.\n");
        create_binary_tree(&((*root)->left));
        printf("Creating the right child.\n");
        create_binary_tree(&((*root)->right));
    }
}

void preorder_traverse_recursive(binary_tree root)
{
    if (root != NULL)
    {
        printf("%d\t", root->elem);
        preorder_traverse_recursive(root->left);
        preorder_traverse_recursive(root->right);
    }
}

void inorder_traverse_recursive(binary_tree root)
{
    if (root != NULL)
    {
        inorder_traverse_recursive(root->left);
        printf("%d\t", root->elem);
        inorder_traverse_recursive(root->right);
    }
}

void postorder_traverse_recursive(binary_tree root)
{
    if (root != NULL)
    {
        postorder_traverse_recursive(root->left);
        postorder_traverse_recursive(root->right);
        printf("%d\t", root->elem);
    }
}
