#include <stdio.h>
#include <stdlib.h>

// Node structure for a linked list
typedef struct Node {
    int data;
    struct Node *next;
} Node;

// Function prototypes
Node* insertAtEnd(Node *head, int value);
Node* deleteValue(Node *head, int value);
Node* invertList(Node *head);
void displayList(Node *head);

int main() {
    Node *head = NULL; // Initialize an empty linked list
    int choice, value;

    while (1) {
        printf("\nMenu:\n");
        printf("1. Insert Element\n");
        printf("2. Delete Element\n");
        printf("3. Invert List\n");
        printf("4. Display List\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter value to insert: ");
                scanf("%d", &value);
                head = insertAtEnd(head, value);
                break;
            case 2:
                printf("Enter value to delete: ");
                scanf("%d", &value);
                head = deleteValue(head, value);
                break;
            case 3:
                head = invertList(head);
                printf("List inverted successfully.\n");
                break;
            case 4:
                displayList(head);
                break;
            case 5:
                exit(0);
            default:
                printf("Invalid choice. Try again.\n");
        }
    }

    return 0;
}

// Function to insert a value at the end of the linked list
Node* insertAtEnd(Node *head, int value) {
    Node *newNode = (Node *)malloc(sizeof(Node));
    newNode->data = value;
    newNode->next = NULL;

    if (head == NULL) {
        return newNode;
    }

    Node *temp = head;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = newNode;

    printf("Inserted %d into the list.\n", value);
    return head;
}

// Function to delete a node with a given value from the linked list
Node* deleteValue(Node *head, int value) {
    if (head == NULL) {
        printf("List is empty.\n");
        return head;
    }

    Node *temp = head;
    Node *prev = NULL;

    // If the value to delete is the head node
    if (head->data == value) {
        head = head->next;
        free(temp);
        printf("Deleted %d from the list.\n", value);
        return head;
    }

    // Traverse the list to find the value
    while (temp != NULL && temp->data != value) {
        prev = temp;
        temp = temp->next;
    }

    // If the value is not found
    if (temp == NULL) {
        printf("Value %d not found in the list.\n", value);
        return head;
    }

    // Delete the node
    prev->next = temp->next;
    free(temp);
    printf("Deleted %d from the list.\n", value);

    return head;
}

// Function to invert (reverse) the linked list
Node* invertList(Node *head) {
    Node *prev = NULL, *current = head, *next = NULL;

    while (current != NULL) {
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }

    return prev; // New head of the inverted list
}

// Function to display the linked list
void displayList(Node *head) {
    if (head == NULL) {
        printf("List is empty.\n");
        return;
    }

    printf("Linked List: ");
    Node *temp = head;
    while (temp != NULL) {
        printf("%d -> ", temp->data);
        temp = temp->next;
    }
    printf("NULL\n");
}
