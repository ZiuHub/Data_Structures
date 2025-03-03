#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 10

// Struct untuk format data hash
typedef struct Node {
    const char *key;
    const char *value;
    struct Node *next;
} Node;

// Hash function
int hash(const char *key) {
    long long int squared_key = atoll(key) * atoll(key); //atoll : ASCII to long long, atoi : ASCII to integer

    char str_key[20]; //kita asumsi max digit setelah key nya di kuadratkan sebanyak 20 digit 
    
	snprintf(str_key, sizeof(str_key), "%lld", squared_key); 
	//setelah code diatas jalan, skrg isi dari str_key merupakan angka (tapi tipe datanya character (char), bukan int)

    int len = strlen(str_key); //hitung panjang si str_key, untuk tau dia berapa digit 
    int start_pos = len / 2; // sebagai inisialisasi posisi awal di tengah 
    int middle_value = 0; //untuk nampung digit tengah yg kita extract
    
    
    //disini dibuat menjadi 2 kondisi biar tidak pada bingung
    //ada kondisi dimana digitnya genap dan ganjil, di cek pake modulo. Kalo hasilnya ga '0' berati ganjil
    if (len % 2 == 0) {
    	// coba kita simulasikan dengan key value 36 untuk mendapatkan mid valuenya
    	// 36 kuadrat = 1296
    	// di dalam if ini kita start posisition dari tengah nilai len dari 1296 = 4
    	// start pos = len/2 artinya kita ada di posisi 2 (digit ke 3) 
    	// kita ingin biar pas ekstrak ada 2 digit karena ini len nya genap
    	// jadi kita mulai dari str_key[start_pos - 1] dan ditambah nanti sama str_key[start pos]
    	// kenapa dikurangi sama '0', karena yang kita olah disini pengurangan dengan tipe data 'char'
    	// str_key[start_pos - 1] = 2  ; nilai 2 disini character ASCII belum jadi integer 
    	// character 2 di ASCII table punya decimal value 50, nah 50 ini yang nanti dianggap sebagai integer
    	// nilai decimal character '0' = 48 
    	// jadi '2' - '0' sama aja dengan 50 - 48 (secara integer;decimal) maka hasilnya = 2 (sudah dalam bentuk int)
    	// terus setelah itu kenapa dikali 10? karena kita main angka decimal disini jadi untuk membuat nilainya ga salah kita harus kali 10 
    	// next, ada str_key[start_pos] = '9' ; sama seperti sebelumnya ini adalah char, bukan int 
    	// '9' - '0' (character ASCII) = 57 - 48 (Nilai decimal dari char ASCII) ; hasilnya 9 (int)
        middle_value = (str_key[start_pos - 1] - '0') * 10 + (str_key[start_pos] - '0');
        //maka 2 * 10 = 20 + 9 = 29 (nilai tengahnya)
    } else {
        //kalo ganjil simply kita ambil bener2 nilai tengah nya kemudian di convert ke int dengan pengurangan '0'
        middle_value = str_key[start_pos] - '0';
    }
		//terakhit kita modulo dengan max size dari hash table
    int hash_value = middle_value % MAX;

    return hash_value;
}

// Buat node baru
Node* CreateNode(const char *key, const char *value) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) {
        printf("Memory allocation failed");
        exit(1);
    }
    newNode->key = strdup(key);
    newNode->value = strdup(value);
    newNode->next = NULL;
    return newNode;
}

// Insert value berdasarkan key 
void insert(Node* ht[], const char *key, const char *value) {
    int index = hash(key);
    Node* newNode = CreateNode(key, value);
    if (ht[index] == NULL) {
        ht[index] = newNode;
    } else {
        Node* temp = ht[index];
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newNode;
    }
    printf("Allocation success at index : %d\n", index);
}

// Delete value berdasarkan key
void deleteKey(Node* ht[], const char *key) {
    int index = hash(key);
    Node *temp = ht[index];
    Node *prev = NULL;
	
    while (temp != NULL) {
        if (strcmp(temp->key, key) == 0) {
            if (prev == NULL) {
            	//In case kalo yg di delete adalah head masuk ke kondisi if ini
            	//prev == NULL digunakan untuk indikasi kalo kita delete data di posisi awal
            	// contoh : ht[1] -> {data1} -> {data2} 
            	// maka hash table index ke 1 nanti akan nge point langsung ke data 2 (alias temp->next)
                ht[index] = temp->next;
            } else {
            	//In case kalo yg di delete adalah mid ; contoh : ht[1] -> {data1} -> {data2}
            	//Kalo mau delete data2 nanti masuk ke else ini
                prev->next = temp->next;
            }
            free((char*)temp->key); 
            free((char*)temp->value); 
            free(temp); 
            printf("Deletion success for key : %s\n", key);
            return;
        }
        //Konidisi ini masuk kalo misalkan pas awal comparison ga match key value nya
        //jadi sekarang pointer prev ada di temp (yang dulu) dan temp skrg maju ke temp->next
        //prev tidak NULL lagi sehingga bisa dijadikan indikasi kalo data yg di delete ada di tengah 
        prev = temp;
        temp = temp->next;
    }

    printf("Key not found for deletion\n");
}

// Search function
void search(Node* ht[], const char *key) {
    int index = hash(key);
    Node* temp = ht[index];
    while (temp != NULL) {
        if (strcmp(temp->key, key) == 0) {
            printf("Value of key %s is %s \n", key, temp->value);
            return;
        }
        temp = temp->next;
    }
    printf("Key not found\n");
}

void displayHashTable(Node* ht[]) {
	printf("----------------------------------------------- \n");
    printf("Hash Table Contents:\n");
    int i;
    for (i = 0; i < MAX; i++) {
        Node* temp = ht[i];
        printf("Index %d: ", i);
        while (temp != NULL) {
            printf("(%s: %s) ", temp->key, temp->value);
            temp = temp->next;
        }
        printf("\n");
    }
    printf("----------------------------------------------- \n");
}

int main() {
    Node* ht[MAX] = {0};
    
    insert(ht, "36", "orange");
    insert(ht, "12", "apple");
    insert(ht, "21", "kiwi");
    insert(ht, "8", "mango");
    
//    search(ht, "12");
//    deleteKey(ht, "12");
//    search(ht, "12");

//    insert(ht, "orange", "36");
//    insert(ht, "apple", "45");
//    insert(ht, "kiwi", "14");
//    insert(ht, "mango", "10");
    
    displayHashTable(ht);
    return 0;
}

