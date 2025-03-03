#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct character{
	char name[50];
	char rank[10];
	int hp;
	int magic;
	int gold;
}character[100];

void menu();
void insert();
void view();
void delet();
void upgrade();
void enter();

int count = 0;

int main(){
	do{
		system("cls");
		menu();
		int choice;
		do{
			scanf("%d", &choice); getchar();
			
			if(choice < 1 || choice > 5){
				puts("Input Must Be Between 1 - 5");
			}
		}while(choice < 1 || choice > 5);
		
		switch(choice){
			case 1:
				insert();
				break;
			case 2:
				view();
				break;
			case 3:
				delet();
				break;
			case 4:
				upgrade();
				break;
			case 5:
				return 0;
		}
	}while(1);
	
	return 0;
}

void menu(){
	puts("1. Insert");
	puts("2. View");
	puts("3. Delete");
	puts("4. Upgrade");
	puts("5. Exit");
	printf(">> ");
}

void insert(){
	printf("Enter Character Name: ");
	scanf("%s", character[count].name); getchar();
	
	do{
		printf("Enter %s Rank (Bronze, Silver, Gold): ", character[count].name);
		scanf("%s", character[count].rank); getchar();
		
		if(strcmp(character[count].rank, "Bronze") != 0 &&
			strcmp(character[count].rank, "Silver") != 0 &&
			strcmp(character[count].rank, "Gold") != 0){
				puts("The Character Rank Must Between Bronze, Silver, Gold!");
			}
	}while(strcmp(character[count].rank, "Bronze") != 0 &&
			strcmp(character[count].rank, "Silver") != 0 &&
			strcmp(character[count].rank, "Gold") != 0);
	
	printf("Enter %s HP: ", character[count].name);
	scanf("%d", &character[count].hp); getchar();
	
	printf("Enter %s Magic: ", character[count].name);
	scanf("%d", &character[count].magic); getchar();
	
	printf("Enter %s Gold: ", character[count].name);
	scanf("%d", &character[count].gold); getchar();
	
	printf("Character %s Successfully Saved!\n", character[count].name);
	count++;
	enter();
	
	return;
}

void view(){
	if(count == 0){
		puts("There is No Data, Insert A New One!");
		enter();
		return;
	}
	
	for(int i = 0; i < count; i++){
		puts("");
		printf("NO. %d\n", i + 1);
		printf("Name: %s\n", character[i].name);
		printf("Rank: %s\n", character[i].rank);
		printf("HP: %d\n", character[i].hp);
		printf("Magic: %d\n", character[i].magic);
		printf("Gold: %d\n", character[i].gold);
	}
	
	enter();
	
	return;
}

void delet(){
	view();
	
	int choice;
	do{
		puts("Enter Character Number You Want to Delete!");
		printf(">> ");
		scanf("%d", &choice); getchar();
	
		if(choice-1 < 0 || choice-1 > count){
			printf("Input Must Be Between 0 - %d!\n", count+1);
		}
	}while(choice-1 < 0 || choice-1 > count);
	
	char temp[50];
	strcpy(temp, character[choice-1].name);
	
	for(int i = choice-1; i < count-1; i++){
		character[i] = character[i+1];
	}
	
	printf("Character %s Successfully Deleted!\n", temp);
	count--;
	enter();
	return;
}

void upgrade(){
	view();
	
	int choice;
	do{
		puts("Enter Character Number You Want to Upgrade!");
		printf(">> ");
		scanf("%d", &choice); getchar();
	
		if(choice-1 < 0 || choice-1 > count){
			printf("Input Must Be Between 0 - %d!\n", count+1);
		}
	}while(choice-1 < 0 || choice-1 > count);
	
	character[choice-1].hp += 150;
	character[choice-1].magic += 150;
	character[choice-1].gold -= 50;
	
	printf("Character %s Successfully Upgraded!\n", character[choice-1].name);
	enter();
	return;
}

void enter(){
	puts("Press ENTER to Continue...");
	getchar();
	return;
}
