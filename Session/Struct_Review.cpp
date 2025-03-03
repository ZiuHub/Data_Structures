#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct mahasiswa{
	char nim[10];
	char nama[50];
}mahasiswa;

int main(){
//	mahasiswa ppti[100];
//	strcpy(ppti[0].nim, "2802538435");
//	
//	printf("%s\n", ppti[0].nim);
	
	struct mahasiswa* ppti = (struct mahasiswa*)malloc(sizeof(struct mahasiswa));
	
	return 0;
}
