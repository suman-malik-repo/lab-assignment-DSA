#include <stdio.h>

#define MAX 100

void insert(int arr[], int *n, int pos, int val);
void delete(int arr[], int *n, int pos);
int search(int arr[], int n, int val);
void display(int arr[], int n);

int main() {
    int arr[MAX], n = 0, choice, pos, val;

    while (1) {
        printf("\nMenu:\n");
        printf("1. Insert Element\n");
        printf("2. Delete Element\n");
        printf("3. Search Element\n");
        printf("4. Display Array\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter position to insert (1 to %d): ", n + 1);
                scanf("%d", &pos);
                printf("Enter value to insert: ");
                scanf("%d", &val);
                insert(arr, &n, pos, val);
                break;
            case 2:
                printf("Enter position to delete (1 to %d): ", n);
                scanf("%d", &pos);
                delete(arr, &n, pos);
                break;
            case 3:
                printf("Enter value to search: ");
                scanf("%d", &val);
                pos = search(arr, n, val);
                if (pos != -1)
                    printf("Element found at position %d.\n", pos + 1);
                else
                    printf("Element not found.\n");
                break;
            case 4:
                display(arr, n);
                break;
            case 5:
                return 0;
            default:
                printf("Invalid choice. Try again.\n");
        }
    }
    return 0;
}

void insert(int arr[], int *n, int pos, int val) {
    if (*n >= MAX) {
        printf("Array Overflow.\n");
        return;
    }
    if (pos < 1 || pos > *n + 1) {
        printf("Invalid position.\n");
        return;
    }

    for (int i = *n; i >= pos - 1; i--)
        arr[i + 1] = arr[i];

    arr[pos - 1] = val;
    (*n)++;
    printf("Inserted %d at position %d.\n", val, pos);
}

void delete(int arr[], int *n, int pos) {
    if (*n <= 0) {
        printf("Array Underflow.\n");
        return;
    }
    if (pos < 1 || pos > *n) {
        printf("Invalid position.\n");
        return;
    }

    for (int i = pos - 1; i < *n - 1; i++)
        arr[i] = arr[i + 1];

    (*n)--;
    printf("Deleted element at position %d.\n", pos);
}

int search(int arr[], int n, int val) {
    for (int i = 0; i < n; i++) {
        if (arr[i] == val)
            return i;
    }
    return -1;
}

void display(int arr[], int n) {
    if (n == 0) {
        printf("Array is empty.\n");
        return;
    }
    printf("Array elements: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}
