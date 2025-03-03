#include<stdio.h> 
#include<string.h> 
#include<stdlib.h>

#define SIZE 50 
 
struct Data{ 
    char coin[5]; 
    double price; 
    Data *next; 
} *arr[SIZE]; 
 
int midSquare(const char coin[]){ 
    //Mid square function
    int totalCoin;
    int lenCoin = strlen(coin);
    for(int i = 0; i < lenCoin; i++){
        totalCoin += coin[i];
    }

    int square = totalCoin * totalCoin;
    char str[20];
    sprintf(str, "%d", square);

    int len = strlen(str);
    int pos = len / 2;
    int mid = 0;

    if(len % 2 == 0){
        mid = (str[pos - 1] - '0') * 10 + (str[pos] - '0');
    }
    else{
        mid = (str[pos - 1] - '0') * 100 + (str[pos] - '0') * 10 + (str[pos + 1] - '0');
    }

    return mid % SIZE;
} 
 
void insert(const char coin[], double price){ 
    Data *data = (Data*)malloc(sizeof(Data)); 
    data->price = price; 
    strcpy(data->coin, coin); 
    data->next = NULL; 
    
    int index = midSquare(coin); 
    //Insert with chaining collision handling 
    if(arr[index] == NULL){
        arr[index] = data;
    }
    else{
        Data *temp = arr[index];
        while(temp->next) temp = temp->next;
        temp->next = data;
    }
    printf("Successfully inserted %s at index %d\n", coin, index);
} 
 
int main(){ 
    insert("BTC", 97000.00); 
    insert("ETH", 2700.00); 
    insert("SOL", 172.59); 
    insert("XRP", 2.57); 
    
    return 0; 
}