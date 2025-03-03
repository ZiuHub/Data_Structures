#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct Node {
    int nomor;
    char judul[255];
    char artis[255];
    struct Node *next, *prev;
} *head = NULL, *tail = NULL, *curr = NULL;

int count = 0;
int isLoop = 0; // Status mode

struct Node *createNode(const char *judul, const char *artis) {
    struct Node *temp = (struct Node*)malloc(sizeof(struct Node));
    strcpy(temp->judul, judul);
    strcpy(temp->artis, artis);
    temp->next = temp->prev = NULL;
    return temp;
}

void enter() {
    printf("Press Enter to continue...");
    getchar();
}

void pushTail(const char *judul, const char *artis) {
    struct Node *temp = createNode(judul, artis);
    if (!head) {
        head = tail = curr = temp;
    } else {
        tail->next = temp;
        temp->prev = tail;
        tail = temp;
    }
}

void printList() {
    struct Node *temp = head;
    count = 0;
    while (temp) {
        temp->nomor = ++count;
        printf("NO. %d\n", temp->nomor);
        printf("TITLE : %s\n", temp->judul);
        printf("ARTIST: %s\n\n", temp->artis);
        temp = temp->next;
        if (isLoop && temp == head) break; // Prevent infinite loop
    }
    if (count == 0) printf("No music in the list\n\n");
}

void prevSong() {
    if (!curr) return;
    curr = curr->prev ? curr->prev : (isLoop ? tail : curr);
}

void nextSong() {
    if (!curr) return;
    curr = curr->next ? curr->next : (isLoop ? head : curr);
}

void addList() {
    char judul[255];
    char artis[255];
    printf("Input music title: ");
    scanf("%[^\n]", judul); getchar();
    printf("Input artist name: ");
    scanf("%[^\n]", artis); getchar();

    pushTail(judul, artis);

    printf("Music added to queue\n\n");
    enter();
}

void removeList() {
    if (!head) return;
    if (head == tail) {
        free(head);
        head = tail = curr = NULL;
    } else {
        printf("Enter the music number to remove: ");
        int choice;
        scanf("%d", &choice); getchar();
        struct Node *temp = head;
        while (temp && temp->nomor != choice) {
            temp = temp->next;
        }
        if (!temp) return;
        if (temp == head) {
            head = head->next;
            head->prev = NULL;
        } else if (temp == tail) {
            tail = tail->prev;
            tail->next = NULL;
        } else {
            temp->prev->next = temp->next;
            temp->next->prev = temp->prev;
        }
        free(temp);
    }
    count--;
    printf("Music removed from queue\n\n");
    enter();
}

void loopMode() {
    if (!head) return;
    tail->next = head;
    head->prev = tail;
    isLoop = 1;

    printf("Loop Mode activated\n\n");
    enter();
}

void playOnce() {
    if (!head) return;
    tail->next = NULL;
    head->prev = NULL;
    isLoop = 0;

    printf("Play Once Mode activated\n\n");
    enter();
}

int main() {
    while (1) {
        system("cls"); // Clear screen
        printf("ZIU Music\n\n");
        printf("NOW PLAYING:\n");
        if (curr) {
            printf("%s - %s\n\n", curr->judul, curr->artis);
        } else {
            printf("No music is playing\n\n");
        }

        printf("QUEUE:\n");
        printList();
        printf("[1] PREVIOUS  [2] NEXT  [3] EDIT LIST (Add/Remove)\n");
        printf("[4] CHANGE MODE (%s Activated)\n", isLoop ? "Loop" : "Play Once");
        printf("[5] CLOSE\n");
        printf(">> ");

        int input;
        if (scanf("%d", &input) != 1) break;
        getchar();

        switch (input) {
            case 1:
                prevSong();
                break;
            case 2:
                nextSong();
                break;
            case 3:
                printf("[1] ADD  [2] REMOVE\n>> ");
                int choiceList;
                if (scanf("%d", &choiceList) == 1) {
                    getchar();
                    if (choiceList == 1) {
                        addList();
                    } else if (choiceList == 2) {
                        removeList();
                        prevSong();
                        nextSong();
                    }
                }
                break;
            case 4:
                printf("[1] LOOP    [2] PLAY ONCE\n>> ");
                int choiceMode;
                if (scanf("%d", &choiceMode) == 1) {
                    getchar();
                    if (choiceMode == 1) {
                        loopMode();
                    } else if (choiceMode == 2) {
                        playOnce();
                    }
                }
                break;
            case 5:
                printf("Closing ZIU Music...\n");
                return 0;
            default:
                printf("Invalid input. Try again.\n");
                break;
        }
    }
    return 0;
}