#include <stdio.h>
#include <stdlib.h>

// Node structure for Threaded Binary Tree
typedef struct TBTNode {
    int data;
    struct TBTNode *left, *right;
    int isThreaded;
} TBTNode;

// Node structure for AVL Tree
typedef struct AVLNode {
    int data, height;
    struct AVLNode *left, *right;
} AVLNode;

// Prototypes for Threaded Binary Tree
TBTNode* insertTBT(TBTNode *root, int value);
void inorderTBT(TBTNode *root);

// Prototypes for AVL Tree
AVLNode* insertAVL(AVLNode *node, int value);
AVLNode* rotateRight(AVLNode *y);
AVLNode* rotateLeft(AVLNode *x);
int getHeight(AVLNode *node);
int getBalanceFactor(AVLNode *node);
void inorderAVL(AVLNode *root);

int main() {
    int choice, value;
    TBTNode *tbtRoot = NULL;
    AVLNode *avlRoot = NULL;

    while (1) {
        printf("\nMenu:\n");
        printf("1. Insert into Threaded Binary Tree\n");
        printf("2. Inorder Traversal of Threaded Binary Tree\n");
        printf("3. Insert into AVL Tree\n");
        printf("4. Inorder Traversal of AVL Tree\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter value to insert into Threaded Binary Tree: ");
                scanf("%d", &value);
                tbtRoot = insertTBT(tbtRoot, value);
                break;
            case 2:
                printf("Inorder Traversal of Threaded Binary Tree: ");
                inorderTBT(tbtRoot);
                printf("\n");
                break;
            case 3:
                printf("Enter value to insert into AVL Tree: ");
                scanf("%d", &value);
                avlRoot = insertAVL(avlRoot, value);
                break;
            case 4:
                printf("Inorder Traversal of AVL Tree: ");
                inorderAVL(avlRoot);
                printf("\n");
                break;
            case 5:
                exit(0);
            default:
                printf("Invalid choice. Try again.\n");
        }
    }

    return 0;
}

// ----------------------- Threaded Binary Tree Functions -----------------------

// Create a new node for Threaded Binary Tree
TBTNode* createTBTNode(int value) {
    TBTNode *newNode = (TBTNode *)malloc(sizeof(TBTNode));
    newNode->data = value;
    newNode->left = newNode->right = NULL;
    newNode->isThreaded = 0;
    return newNode;
}

// Insert a node into Threaded Binary Tree
TBTNode* insertTBT(TBTNode *root, int value) {
    TBTNode *newNode = createTBTNode(value);
    if (root == NULL)
        return newNode;

    TBTNode *current = root, *parent = NULL;
    while (current != NULL) {
        parent = current;
        if (value < current->data) {
            if (current->left == NULL)
                break;
            current = current->left;
        } else {
            if (current->isThreaded)
                break;
            current = current->right;
        }
    }

    if (value < parent->data) {
        parent->left = newNode;
    } else {
        newNode->right = parent->right;
        newNode->isThreaded = 1;
        parent->right = newNode;
    }

    return root;
}

// Inorder traversal of Threaded Binary Tree
void inorderTBT(TBTNode *root) {
    TBTNode *current = root;
    while (current != NULL) {
        while (current->left != NULL)
            current = current->left;

        printf("%d ", current->data);

        while (current->isThreaded && current->right != NULL) {
            current = current->right;
            printf("%d ", current->data);
        }
        current = current->right;
    }
}

// ----------------------- AVL Tree Functions -----------------------

// Create a new node for AVL Tree
AVLNode* createAVLNode(int value) {
    AVLNode *newNode = (AVLNode *)malloc(sizeof(AVLNode));
    newNode->data = value;
    newNode->height = 1; // New node is initially at height 1
    newNode->left = newNode->right = NULL;
    return newNode;
}

// Get the height of a node
int getHeight(AVLNode *node) {
    return node == NULL ? 0 : node->height;
}

// Get the balance factor of a node
int getBalanceFactor(AVLNode *node) {
    return node == NULL ? 0 : getHeight(node->left) - getHeight(node->right);
}

// Right rotation
AVLNode* rotateRight(AVLNode *y) {
    AVLNode *x = y->left;
    AVLNode *T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = 1 + (getHeight(y->left) > getHeight(y->right) ? getHeight(y->left) : getHeight(y->right));
    x->height = 1 + (getHeight(x->left) > getHeight(x->right) ? getHeight(x->left) : getHeight(x->right));

    return x;
}

// Left rotation
AVLNode* rotateLeft(AVLNode *x) {
    AVLNode *y = x->right;
    AVLNode *T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = 1 + (getHeight(x->left) > getHeight(x->right) ? getHeight(x->left) : getHeight(x->right));
    y->height = 1 + (getHeight(y->left) > getHeight(y->right) ? getHeight(y->left) : getHeight(y->right));

    return y;
}

// Insert a node into AVL Tree
AVLNode* insertAVL(AVLNode *node, int value) {
    if (node == NULL)
        return createAVLNode(value);

    if (value < node->data)
        node->left = insertAVL(node->left, value);
    else if (value > node->data)
        node->right = insertAVL(node->right, value);
    else
        return node; // Duplicates not allowed

    node->height = 1 + (getHeight(node->left) > getHeight(node->right) ? getHeight(node->left) : getHeight(node->right));

    int balance = getBalanceFactor(node);

    if (balance > 1 && value < node->left->data)
        return rotateRight(node);

    if (balance < -1 && value > node->right->data)
        return rotateLeft(node);

    if (balance > 1 && value > node->left->data) {
        node->left = rotateLeft(node->left);
        return rotateRight(node);
    }

    if (balance < -1 && value < node->right->data) {
        node->right = rotateRight(node->right);
        return rotateLeft(node);
    }

    return node;
}

// Inorder traversal of AVL Tree
void inorderAVL(AVLNode *root) {
    if (root != NULL) {
        inorderAVL(root->left);
        printf("%d ", root->data);
        inorderAVL(root->right);
    }
}
