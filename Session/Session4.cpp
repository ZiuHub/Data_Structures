/*
Anda merupakan seorang programer pada sebuah perusahaan dan diminta untuk membuat sistem yang dapat menyimpan data contact person secara terstruktur dengan Hash Table dengan data yang memiliki objek Nama (tidak bisa duplikat), Nomor Telepon, dan Email. Terdapat beberapa kriteria yang diminta untuk merancang sistem ini. Berikut kriterianya:
• Hash Table harus bisa mengatasi Collision dengan teknik Chaining pada data
• Program memiliki pilihan untuk menggunakan metode hash function yang diinginkan (Mid Square yang hasilnya dilakukan Division)
• Hash function memiliki ketentuan Mid Square, sebagai berikut: Semua karakter dijumlahkan ASCII valuenya ke dalam bentuk integer, hasil penjumlahan diambil nilai tengahnya dengan ketentuan nilai genap diambil 2 angka ditengah dan ganjil diambil 1 angka ditengah, kemudian dilakukan division dengan besarnya hash table yang dimiliki
• Key untuk menentukan index pada hash table menggunakan value dari nama
• Secara umum program ini dapat melakukan Search (print list nama, masukkan input, print detail sesuai input nama), Insert (push), dan Delete (pop) data
Buat tampilan menu (switch case) untuk masing-masing fungsi
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100

int count;

struct Node{
    char name[30];
    char phone[30];
    char email[30];
    Node *next;
}*head[MAX];

Node *createNewNode(const char *name, const char *phone, const char *email){
    Node *newNode = (Node*)malloc(sizeof(Node));
    strcpy(newNode->name, name);
    strcpy(newNode->phone, phone);
    strcpy(newNode->email, email);
    newNode->next = NULL;
    return newNode;
}

int hash(const char *name){ // Mid Square & Division (kuadrat dan ambil nilai tengahnya, contoh: 123*123=15129, nilai tengahnya 1 / 12*12=144, nilai tengahnya 4) lalu modulus dengan MAX
    int key = 0;
    for(int i = 0; i < strlen(name); i++){
        key += name[i];
    }
    key *= key;

    char strKey[20];
    sprintf(strKey, "%d", key);
    int len = strlen(strKey);

    int midVal;
    if(len % 2 == 0){
        midVal = (strKey[len/2 - 1] - '0') * 10 + (strKey[len/2] - '0');
    }
    else{
        midVal = strKey[len/2] - '0';
    }

    return midVal % MAX;
}

void enter(){
    printf("Press ENTER to continue...");
    getchar();
    system("cls");
}

int check(const char *name){
    int pos = hash(name);
    if(head[pos] == NULL){
        return 0;
    }
    else{
        Node *temp = head[pos];
        while(temp != NULL){
            if(strcmp(temp->name, name) == 0){
                return 1;
            }
            temp = temp->next;
        }
        return 0;
    }
}

void insert(){
    char name[30], phone[30], email[30];
    do{
        do{
            printf("Enter name: ");
            scanf("%[^\n]", name); getchar();
            if(check(name) != 0){
                puts("Name already exist!");
            }
        }while(check(name) != 0);
        if(strcmp(name, "") == 0){
            puts("Invalid, can't be empty!");
        }
    }while(strcmp(name, "") == 0);
    
    do{
        printf("Enter phone: ");
        scanf("%[^\n]", phone); getchar();
        if(strcmp(phone, "") == 0){
            puts("Invalid, can't be empty!");
        }
    }while(strcmp(phone, "") == 0);

    do{
        printf("Enter email: ");
        scanf("%[^\n]", email); getchar();
        if(strcmp(email, "") == 0){
            puts("Invalid, can't be empty!");
        }
    }while(strcmp(email, "") == 0);

    Node *newNode = createNewNode(name, phone, email);
    int pos = hash(name);
    if(head[pos] == NULL){
        head[pos] = newNode;
        count++;
        printf("%s has been added to the contact list\n", name);
        return;
    }
    Node *temp = head[pos];
    while(temp->next != NULL){
        temp = temp->next;
    }
    temp->next = newNode;
    count++;
    printf("%s has been added to the contact list\n", name);
}

void view(){
    if(count == 0){
        puts("Contact list is empty!");
        return;
    }

    for(int i = 0; i < MAX; i++){
        if(head[i] != NULL){
            printf("INDEX %d\n", i);
            Node *temp = head[i];
            while(temp != NULL){
                printf("Name: %s\n", temp->name);
                temp = temp->next;
            }
            puts("");
        }
        
    }
}

void search(){
    view();
    if(count == 0){
        return;
    }

    char name[30];
    printf("Enter name to search: ");
    scanf("%[^\n]", name); getchar();

    int pos = hash(name);
    if(head[pos] == NULL){
        puts("Contact not found!");
        return;
    }
    else{
        Node *temp = head[pos];
        while(temp != NULL){
            if(strcmp(temp->name, name) == 0){
                printf("Name: %s\n", temp->name);
                printf("Phone: %s\n", temp->phone);
                printf("Email: %s\n", temp->email);
                return;
            }
            temp = temp->next;
        }
    }
}

void delet(){
    view();
    if(count == 0){
        return;
    }

    char name[30];
    printf("Enter name to delete: ");
    scanf("%[^\n]", name); getchar();

    int pos = hash(name);
    if(head[pos] == NULL){
        puts("Contact not found!");
        return;
    }
    else{
        if(strcmp(head[pos]->name, name) == 0){
            Node *temp = head[pos];
            head[pos] = temp->next;
            free(temp);
            count--;
            printf("%s has been deleted from the contact list\n", name);
            return;
        }
        else{
            Node *temp = head[pos];
            while(temp->next != NULL && strcmp(temp->next->name, name) != 0){
                temp = temp->next;
            }
            if(temp->next == NULL){
                puts("Data not found!");
                return;
            }
            Node *del = temp->next;
            temp->next = del->next;
            free(del);
            count--;
            printf("%s has been deleted from the contact list\n", name);
        }
    }
}

int main(){
    count = 0;
    do{
        puts("Contact List");
        puts("1. Insert");
        puts("2. View");
        puts("3. Search");
        puts("4. Delete");
        puts("5. Exit");
        printf(">> ");

        int choice;
        scanf("%d", &choice); getchar();

        switch(choice){
            case 1:
                insert();
                enter();
                break;
            case 2:
                view();
                enter();
                break;
            case 3:
                search();
                enter();
                break;
            case 4:
                delet();
                enter();
                break;
            case 5:
                puts("Exiting Contact List...");
                return 0;
        }
    }while(1);

    return 0;
}