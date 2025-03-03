#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Node {
    char name[11];
    char ticket[11]; 
    struct Node* prev;
    struct Node* next;
};

Node* createNode(const char* name, const char* ticket) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    strcpy(newNode->name, name);
    strcpy(newNode->ticket, ticket);
    newNode->prev = newNode->next = NULL;
    return newNode;
}

void regist(Node** head, Node** tail) {
    int n;
    scanf("%d", &n); getchar();

    for(int i = 0; i < n; i++) {
        char name[11], ticket[11];
        scanf("%s %s", name, ticket); getchar();

        Node* newNode = createNode(name, ticket);

        // Jika queue kosong
        if (*head == NULL) {
            *head = *tail = newNode;
            continue;
        }

        // Jika FAST_TRACK, masukkan sebelum REGULER pertama
        if (strcmp(ticket, "FAST_TRACK") == 0) {
            Node* temp = *head;
            while (temp != NULL && strcmp(temp->ticket, "FAST_TRACK") == 0) {
                temp = temp->next;
            }
            // Insert di awal jika semua REGULER
            if (temp == *head) {
                newNode->next = *head;
                (*head)->prev = newNode;
                *head = newNode;
            }
            // Insert sebelum REGULER pertama
            else {
                newNode->next = temp;
                newNode->prev = temp->prev;
                if (temp->prev) temp->prev->next = newNode;
                temp->prev = newNode;
            }
        }
        // Jika REGULER, masukkan di akhir queue
        else if (strcmp(ticket, "REGULER") == 0){
            (*tail)->next = newNode;
            newNode->prev = *tail;
            *tail = newNode;
        }
    }
}

void printQueue(Node* head) {
    Node* temp = head;
    int i = 1;
    
    if (temp == NULL) {
        puts("Queue is empty");
        return;
    }

    puts("No Name       Ticket");
    while (temp != NULL) {
        printf("%2d %-10s %s\n", i++, temp->name, temp->ticket);
        temp = temp->next;
    }
}

void remov(Node** head, Node** tail) {
    int n;
    scanf("%d", &n); getchar();

    for (int i = 0; i < n; i++) {
        char name[11];
        scanf("%s", name); getchar();

        Node* temp = *head;

        while (temp != NULL && strcmp(temp->name, name) != 0) {
            temp = temp->next;
        }

        if (temp == NULL) {
            puts("Name not found");
            continue;
        }

        // Hapus node
        if (temp == *head) {
            *head = temp->next;
            if (*head) (*head)->prev = NULL;
        } else if (temp == *tail) {
            *tail = temp->prev;
            (*tail)->next = NULL;
        } else {
            temp->prev->next = temp->next;
            temp->next->prev = temp->prev;
        }
        free(temp);
    }
}

void call(Node** head, Node** tail) {
    int count = 0;
    Node* temp = *head;
    
    // Cetak nama yang naik perahu
    while (temp != NULL && count < 4) {
        printf("%s ", temp->name);
        temp = temp->next;
        count++;
    }
    puts("got into the boat.");

    // Hapus 4 pertama dari queue
    for (int i = 0; i < count; i++) {
        Node* toDelete = *head;
        *head = (*head)->next;
        if (*head) (*head)->prev = NULL;
        free(toDelete);
    }

    // Hitung sisa antrean
    int remaining = 0;
    temp = *head;
    while (temp != NULL) {
        remaining++;
        temp = temp->next;
    }
    printf("%d queues remaining.\n", remaining);
}

int main() {
    Node* head = NULL;
    Node* tail = NULL;
    char input[10];

    while (1) {
        system("cls");
        printQueue(head);
        puts("");

        printf("Input (REGISTER, REMOVE, CALL, EXIT): ");
        scanf("%s", input); getchar();

        if (strcmp(input, "REGISTER") == 0) {
            regist(&head, &tail);
        } else if (strcmp(input, "REMOVE") == 0) {
            remov(&head, &tail);
        } else if (strcmp(input, "CALL") == 0) {
            call(&head, &tail);
        } else if (strcmp(input, "EXIT") == 0) {
            break;
        }
    }

    return 0;
}