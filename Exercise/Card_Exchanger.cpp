#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct Card {
    int id, price;
    char name[100];
};

struct Node {
    struct Card card;
    struct Node *next;
};

// ENTER to Continue
void enter() {
    printf("Press ENTER to Continue...");
    getchar();
}

// Add Cards (sorted by name)
void addCard(struct Node **head, struct Node **tail, const char *name) {
    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
    newNode->card.id = rand() % 1000;
    strcpy(newNode->card.name, name);
    newNode->card.price = 100;
    newNode->next = NULL;

    if (!*head || strcmp((*head)->card.name, name) > 0) { // Add at the head
        newNode->next = *head;
        *head = newNode;
        if (!*tail) *tail = newNode;
    } else if (strcmp((*tail)->card.name, name) < 0) { // Add at the tail
        (*tail)->next = newNode;
        *tail = newNode;
    } else { // Add in the mid
        struct Node *temp = *head;
        while (temp->next && strcmp(temp->next->card.name, name) < 0)
            temp = temp->next;
        newNode->next = temp->next;
        temp->next = newNode;
    }
}

// Delete Cards
void removeCard(struct Node **head, struct Node **tail, const char *name) {
    struct Node *temp = *head, *prev = NULL;
    while (temp && strcmp(temp->card.name, name)) {
        prev = temp;
        temp = temp->next;
    }
    if (!temp) return; // Tidak ditemukan
    if (temp == *head) *head = temp->next;
    if (temp == *tail) *tail = prev;
    if (prev) prev->next = temp->next;
    free(temp);
}

// Print Cards
void printCards(struct Node *head) {
    if (!head) {
        printf("Kosong.\n");
        return;
    }
    while (head) {
        printf("%s (%d gold) -> ", head->card.name, head->card.price);
        head = head->next;
    }
    printf("NULL\n");
}

// Exchange Cards
void exchangeCard(struct Node **playerHead, struct Node **playerTail,
                  struct Node **exchangerHead, struct Node **exchangerTail,
                  const char *playerCard, const char *exchangerCard) {
    removeCard(playerHead, playerTail, playerCard);
    removeCard(exchangerHead, exchangerTail, exchangerCard);
    addCard(playerHead, playerTail, exchangerCard);
    addCard(exchangerHead, exchangerTail, playerCard);
    printf("\nExchange berhasil!\n");
}

// Buy Cards
void buyCard(struct Node **playerHead, struct Node **playerTail,
             struct Node **exchangerHead, struct Node **exchangerTail,
             const char *cardName, int *gold) {
    if (*gold < 100) {
        printf("\nGold tidak cukup untuk membeli kartu.\n");
        return;
    }
    removeCard(exchangerHead, exchangerTail, cardName);
    addCard(playerHead, playerTail, cardName);
    *gold -= 100;
    printf("\nPembelian berhasil! Sisa gold: %d\n", *gold);
}

// Sell Cards
void sellCard(struct Node **playerHead, struct Node **playerTail,
              struct Node **exchangerHead, struct Node **exchangerTail,
              const char *cardName, int *gold) {
    removeCard(playerHead, playerTail, cardName);
    addCard(exchangerHead, exchangerTail, cardName);
    *gold += 100;
    printf("\nPenjualan berhasil! Gold saat ini: %d\n", *gold);
}

int main() {
    struct Node *playerHead = NULL, *playerTail = NULL;
    struct Node *exchangerHead = NULL, *exchangerTail = NULL;
    int gold = 500; // Player's initial gold
    // Add Cards to Player
    addCard(&playerHead, &playerTail, "Vulpix");
    addCard(&playerHead, &playerTail, "Diglett");
    addCard(&playerHead, &playerTail, "Zubat");
    addCard(&playerHead, &playerTail, "Nidoran");

    // Add Cards to Exchanger
    addCard(&exchangerHead, &exchangerTail, "Rattata");
    addCard(&exchangerHead, &exchangerTail, "Squirtle");
    addCard(&exchangerHead, &exchangerTail, "Charmander");
    addCard(&exchangerHead, &exchangerTail, "Pikachu");

    int choice;
    char playerCard[100], exchangerCard[100];

    do {
        system("cls"); // Clear screen
        printf("\n== CARD EXCHANGER MENU ==\n");
        printf("1. View Cards\n");
        printf("2. Exchange Cards\n");
        printf("3. Buy Cards\n");
        printf("4. Sell Cards\n");
        printf("5. Exit\n");
        printf("Choice: ");
        scanf("%d", &choice);
        getchar(); // Clear newline character

        switch (choice) {
            case 1:
                printf("\nKartu User:\n");
                printCards(playerHead);
                printf("\nKartu Exchanger:\n");
                printCards(exchangerHead);
                printf("\nGold: %d\n", gold);
                enter();
                break;
            case 2:
            	printf("\nKartu User:\n");
                printCards(playerHead);
                printf("\nKartu Exchanger:\n");
                printCards(exchangerHead);
                printf("\nGold: %d\n", gold);
                
                printf("\nMasukkan nama kartu user yang ingin ditukar: ");
                fgets(playerCard, sizeof(playerCard), stdin);
                playerCard[strcspn(playerCard, "\n")] = 0;
                printf("Masukkan nama kartu exchanger yang ingin ditukar: ");
                fgets(exchangerCard, sizeof(exchangerCard), stdin);
                exchangerCard[strcspn(exchangerCard, "\n")] = 0;
                exchangeCard(&playerHead, &playerTail, &exchangerHead, &exchangerTail, playerCard, exchangerCard);
                enter();
                break;
            case 3:
            	printf("\nKartu User:\n");
                printCards(playerHead);
                printf("\nKartu Exchanger:\n");
                printCards(exchangerHead);
                printf("\nGold: %d\n", gold);
                
                printf("\nMasukkan nama kartu yang ingin dibeli: ");
                fgets(exchangerCard, sizeof(exchangerCard), stdin);
                exchangerCard[strcspn(exchangerCard, "\n")] = 0;
                buyCard(&playerHead, &playerTail, &exchangerHead, &exchangerTail, exchangerCard, &gold);
                enter();
                break;
            case 4:
            	printf("\nKartu User:\n");
                printCards(playerHead);
                printf("\nKartu Exchanger:\n");
                printCards(exchangerHead);
                printf("\nGold: %d\n", gold);
                
                printf("\nMasukkan nama kartu yang ingin dijual: ");
                fgets(playerCard, sizeof(playerCard), stdin);
                playerCard[strcspn(playerCard, "\n")] = 0;
                sellCard(&playerHead, &playerTail, &exchangerHead, &exchangerTail, playerCard, &gold);
                enter();
                break;
            case 5:
                printf("\nTerima kasih telah tukar kartu di Card Exchanger. Sampai jumpa!\n");
                break;
            default:
                printf("\nPilihan tidak valid. Coba lagi.\n");
                enter();
        }
    } while (choice != 5);

    return 0;
}
