#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

// Stack structure
typedef struct Stack {
    int data;
    struct Stack *next;
} Stack;

// Queue structure
typedef struct Queue {
    int data;
    struct Queue *next;
} Queue;

// Stack function prototypes
Stack* push(Stack *top, int value);
Stack* pop(Stack *top, int *poppedValue);
void displayStack(Stack *top);

// Queue function prototypes
Queue* enqueue(Queue *rear, int value);
Queue* dequeue(Queue *front, int *dequeuedValue);
void displayQueue(Queue *front);

// Expression evaluation prototypes
int evaluatePostfix(char *expression);
int performOperation(int operand1, int operand2, char operator);

int main() {
    Stack *stack1 = NULL, *stack2 = NULL; // Two stacks
    Queue *queue1 = NULL, *queue2 = NULL; // Two queues
    int choice, value, poppedValue, dequeuedValue;
    char expression[100];

    while (1) {
        printf("\nMenu:\n");
        printf("1. Push into Stack 1\n");
        printf("2. Push into Stack 2\n");
        printf("3. Merge Stacks\n");
        printf("4. Enqueue into Queue 1\n");
        printf("5. Enqueue into Queue 2\n");
        printf("6. Merge Queues\n");
        printf("7. Evaluate Postfix Expression\n");
        printf("8. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter value to push into Stack 1: ");
                scanf("%d", &value);
                stack1 = push(stack1, value);
                break;
            case 2:
                printf("Enter value to push into Stack 2: ");
                scanf("%d", &value);
                stack2 = push(stack2, value);
                break;
            case 3:
                printf("Merged Stack: ");
                while (stack2 != NULL) {
                    stack1 = push(stack1, stack2->data);
                    stack2 = pop(stack2, &poppedValue);
                }
                displayStack(stack1);
                break;
            case 4:
                printf("Enter value to enqueue into Queue 1: ");
                scanf("%d", &value);
                queue1 = enqueue(queue1, value);
                break;
            case 5:
                printf("Enter value to enqueue into Queue 2: ");
                scanf("%d", &value);
                queue2 = enqueue(queue2, value);
                break;
            case 6:
                printf("Merged Queue: ");
                while (queue2 != NULL) {
                    queue1 = enqueue(queue1, queue2->data);
                    queue2 = dequeue(queue2, &dequeuedValue);
                }
                displayQueue(queue1);
                break;
            case 7:
                printf("Enter a postfix expression: ");
                scanf("%s", expression);
                printf("Result of evaluation: %d\n", evaluatePostfix(expression));
                break;
            case 8:
                exit(0);
            default:
                printf("Invalid choice. Try again.\n");
        }
    }

    return 0;
}

// Push into a stack
Stack* push(Stack *top, int value) {
    Stack *newNode = (Stack *)malloc(sizeof(Stack));
    newNode->data = value;
    newNode->next = top;
    return newNode;
}

// Pop from a stack
Stack* pop(Stack *top, int *poppedValue) {
    if (top == NULL) {
        printf("Stack is empty.\n");
        return NULL;
    }
    *poppedValue = top->data;
    Stack *temp = top;
    top = top->next;
    free(temp);
    return top;
}

// Display stack
void displayStack(Stack *top) {
    if (top == NULL) {
        printf("Stack is empty.\n");
        return;
    }
    Stack *temp = top;
    while (temp != NULL) {
        printf("%d ", temp->data);
        temp = temp->next;
    }
    printf("\n");
}

// Enqueue into a queue
Queue* enqueue(Queue *rear, int value) {
    Queue *newNode = (Queue *)malloc(sizeof(Queue));
    newNode->data = value;
    newNode->next = NULL;
    if (rear == NULL) {
        return newNode;
    }
    Queue *temp = rear;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = newNode;
    return rear;
}

// Dequeue from a queue
Queue* dequeue(Queue *front, int *dequeuedValue) {
    if (front == NULL) {
        printf("Queue is empty.\n");
        return NULL;
    }
    *dequeuedValue = front->data;
    Queue *temp = front;
    front = front->next;
    free(temp);
    return front;
}

// Display queue
void displayQueue(Queue *front) {
    if (front == NULL) {
        printf("Queue is empty.\n");
        return;
    }
    Queue *temp = front;
    while (temp != NULL) {
        printf("%d ", temp->data);
        temp = temp->next;
    }
    printf("\n");
}

// Evaluate postfix expression
int evaluatePostfix(char *expression) {
    Stack *stack = NULL;
    int i, operand1, operand2, result;

    for (i = 0; expression[i] != '\0'; i++) {
        if (isdigit(expression[i])) {
            stack = push(stack, expression[i] - '0');
        } else {
            stack = pop(stack, &operand2);
            stack = pop(stack, &operand1);
            result = performOperation(operand1, operand2, expression[i]);
            stack = push(stack, result);
        }
    }
    stack = pop(stack, &result);
    return result;
}

// Perform a mathematical operation
int performOperation(int operand1, int operand2, char operator) {
    switch (operator) {
        case '+': return operand1 + operand2;
        case '-': return operand1 - operand2;
        case '*': return operand1 * operand2;
        case '/': return operand1 / operand2;
        default: return 0;
    }
}
