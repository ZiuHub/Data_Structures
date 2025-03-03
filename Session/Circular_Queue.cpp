#include <stdio.h>

#define MAX_SIZE 5

int front = -1;
int rear = -1;
int circularQueue[MAX_SIZE];

// Function to check if the circular queue is empty
int isEmpty() {
    return (front == -1 && rear == -1);
}

// Function to check if the circular queue is full
int isFull() {
    return ((rear + 1) % MAX_SIZE == front);
}

// Function to add an element to the circular queue (enqueue)
void enqueue(int value) {
    if (isFull()) {
//    	printf("%d\n", isFull());
        printf("Queue is full. Cannot enqueue %d\n", value);
        return;
    }

    if (isEmpty()) {
        front = 0; // Initialize front if the queue is empty
    }

    rear = (rear + 1) % MAX_SIZE;
    circularQueue[rear] = value;

    printf("Enqueued %d\n", value);
}

// Function to remove an element from the circular queue (dequeue)
void dequeue() {
    if (isEmpty()) {
        printf("Queue is empty. Cannot dequeue.\n");
        return;
    }

    printf("Dequeued %d\n", circularQueue[front]);

    if (front == rear) {
        // Last element is being dequeued, reset front and rear
        front = -1;
        rear = -1;
    } else {
        front = (front + 1) % MAX_SIZE;
    }
}

// Function to display the elements of the circular queue
void display() {
    if (isEmpty()) {
        printf("Queue is empty.\n");
        return;
    }

    printf("Elements in the circular queue: ");
    int i = front;
    do {
        printf("%d ", circularQueue[i]);
        i = (i + 1) % MAX_SIZE;
    } while (i != (rear + 1) % MAX_SIZE);
    printf("\n");
}

int main() {
    enqueue(10);
    enqueue(20);
    enqueue(30);
    enqueue(40);
    enqueue(50);

    display();

    dequeue();
    dequeue();

    display();

    enqueue(60);
    enqueue(70);
    enqueue(80);

    display();

    return 0;
}

