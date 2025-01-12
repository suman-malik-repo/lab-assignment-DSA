#include <stdio.h>
#include <stdlib.h>

#define MAX 100

// Stack structure
typedef struct Stack {
    int arr[MAX];
    int top;
} Stack;

// Queue structure
typedef struct Queue {
    int arr[MAX];
    int front, rear;
} Queue;

// Function prototypes
void push(Stack *s, int val);
int pop(Stack *s);
int isStackEmpty(Stack *s);
void displayStack(Stack *s);

void enqueue(Queue *q, int val);
int dequeue(Queue *q);
int isQueueEmpty(Queue *q);
void displayQueue(Queue *q);

int main() {
    Stack s;
    s.top = -1;

    Queue q;
    q.front = q.rear = -1;

    int choice, value;

    while (1) {
        printf("\nMenu:\n");
        printf("1. Push (Stack)\n");
        printf("2. Pop (Stack)\n");
        printf("3. Display Stack\n");
        printf("4. Enqueue (Queue)\n");
        printf("5. Dequeue (Queue)\n");
        printf("6. Display Queue\n");
        printf("7. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter value to push into stack: ");
                scanf("%d", &value);
                push(&s, value);
                break;
            case 2:
                if (isStackEmpty(&s)) {
                    printf("Stack is empty.\n");
                } else {
                    printf("Popped: %d\n", pop(&s));
                }
                break;
            case 3:
                displayStack(&s);
                break;
            case 4:
                printf("Enter value to enqueue into queue: ");
                scanf("%d", &value);
                enqueue(&q, value);
                break;
            case 5:
                if (isQueueEmpty(&q)) {
                    printf("Queue is empty.\n");
                } else {
                    printf("Dequeued: %d\n", dequeue(&q));
                }
                break;
            case 6:
                displayQueue(&q);
                break;
            case 7:
                exit(0);
            default:
                printf("Invalid choice. Try again.\n");
        }
    }
    return 0;
}

// Stack functions
void push(Stack *s, int val) {
    if (s->top >= MAX - 1) {
        printf("Stack Overflow.\n");
        return;
    }
    s->arr[++s->top] = val;
    printf("Pushed %d into stack.\n", val);
}

int pop(Stack *s) {
    return s->arr[s->top--];
}

int isStackEmpty(Stack *s) {
    return s->top == -1;
}

void displayStack(Stack *s) {
    if (isStackEmpty(s)) {
        printf("Stack is empty.\n");
        return;
    }
    printf("Stack elements: ");
    for (int i = s->top; i >= 0; i--) {
        printf("%d ", s->arr[i]);
    }
    printf("\n");
}

// Queue functions
void enqueue(Queue *q, int val) {
    if (q->rear >= MAX - 1) {
        printf("Queue Overflow.\n");
        return;
    }
    if (q->front == -1) {
        q->front = 0;
    }
    q->arr[++q->rear] = val;
    printf("Enqueued %d into queue.\n", val);
}

int dequeue(Queue *q) {
    int val = q->arr[q->front];
    if (q->front == q->rear) {
        q->front = q->rear = -1;  // Reset queue if empty
    } else {
        q->front++;
    }
    return val;
}

int isQueueEmpty(Queue *q) {
    return q->front == -1;
}

void displayQueue(Queue *q) {
    if (isQueueEmpty(q)) {
        printf("Queue is empty.\n");
        return;
    }
    printf("Queue elements: ");
    for (int i = q->front; i <= q->rear; i++) {
        printf("%d ", q->arr[i]);
    }
    printf("\n");
}
