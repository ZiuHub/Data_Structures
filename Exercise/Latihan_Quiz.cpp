#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

struct tnode{
    char address[100];
    char id[100];
    char type[100];
    int priority;
    tnode* next;
}*queue;

tnode* createNode(char* address, char* id, char* type, int priority){
    tnode* newNode = (tnode*)malloc(sizeof(tnode));
    strcpy(newNode->address, address);
    strcpy(newNode->id, id);
    strcpy(newNode->type, type);

    if(strcmp(type, "Instant") == 0) newNode->priority = 2;
    else if(strcmp(type, "Standard") == 0) newNode->priority = 1;
    else newNode->priority = 0;

    newNode->next = NULL;
    return newNode;
}

void priorityQueue(tnode* newNode){
    if(queue == NULL || queue->priority < newNode->priority){
        newNode->next = queue;
        queue = newNode;
        return;
    }

    // push mid
    tnode* temp = queue;
    while(temp->next && temp->next->priority >= newNode->priority) temp = temp->next;
    if(temp->next == NULL){
        temp->next = newNode;
    }
    else{
        newNode->next = temp->next;
        temp->next = newNode;
    }
}

void insert(){
    // address id type

    char address[100], id[100], type[100];

    do{
        printf("Address (must start with \"Jl.\", 5-20 characters [inclusive]): ");
        scanf("%[^\n]", address); getchar();
    }while(strlen(address) < 9 || strlen(address) > 24 || strncmp(address, "Jl. ", 4) != 0);

    sprintf(id, "%c%c%c", 'C', 'P', 'X');
    for(int i = 3; i < 6; i++){
        int alphaOrNumeric = rand() % 2;

        if(alphaOrNumeric == 0){
            int random = rand() % 26;
            id[i] = random + 'A';
        }

        else{
            int random = rand() % 10;
            id[i] = random + '0';
        }
    }
    id[7] = 0;

    do{
        printf("Package Type (Economy/Standard/Instant [case sensitive]): ");
        scanf("%[^\n]", type); getchar();
    }while(strcmp(type, "Economy") && strcmp(type, "Standard")  && strcmp(type, "Instant"));

    tnode* newNode = createNode(address, id, type, -1);

    priorityQueue(newNode);
}

void send(){
    // pop head
    if(queue == NULL){
        puts("No data");
        return;
    }

    tnode* temp = queue;
    printf("%s (%s) successfully sent to %s\n", temp->id, temp->type, temp->address);
    queue = queue->next;
    free(temp);
}

void view(){
    if(queue == NULL){
        puts("No data");
        return;
    }

    tnode* temp = queue;
    while(temp){
        printf("%s - %s - %s\n", temp->id, temp->type, temp->address);
        temp = temp->next;
    }
}

void exit(){
    tnode* temp = queue;
    while(temp){
        printf("%s (%s) successfully sent to %s\n", temp->id, temp->type, temp->address);
        temp = temp->next;
    }
    puts("Exit Program");
}

int main(){
    srand(time(NULL));
    int choice;
    do{
        puts("");
        puts("Copi Express");
        puts("1. Insert new package");
        puts("2. Send a package");
        puts("3. View all package");
        puts("4. Exit");
        do{
            printf(">> ");
            scanf("%d", &choice); getchar();
        }while(choice < 1 || choice > 4);

        switch(choice){
            case(1):
                insert();
                break;
            case(2):
                send();
                break;
            case(3):
                view();
                break;
            case(4):
                exit();
                return 0;
                break;
        }
    }while(1);

    return 0;
}