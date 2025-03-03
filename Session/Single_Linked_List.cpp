#include <stdio.h>
#include <stdlib.h>

struct tnode{
	int valueNode;
	struct tnode *next;
}*h, *t, *c;

void pushHead(int value){
	c = (struct tnode*) malloc(sizeof(struct tnode));
	c->valueNode = value;
	c->next = NULL;
	if(!h){
		h=t=c;
	}else{
		c->next = h;
		h = c;
	}
}

void pushTail(int value){
	c = (struct tnode*) malloc(sizeof(struct tnode));
	c->valueNode = value;
	c->next = NULL;
	if(!h){
		h=t=c;
	}else{
		t->next = c;
		t = c;
	}
}

void pushMiddle(int value){
	c = (struct tnode*) malloc(sizeof(struct tnode));
	c->valueNode = value;
	c->next = NULL;
	if(!h){
		h=t=c;
	}else if(t->valueNode > value){
		c->next = h;
		h = c;
	}else if(t->valueNode < value){
		t->next = c;
		t = c;
	}else{
		struct tnode *temp;
		temp = h;
		while(value > temp->next->valueNode){
			temp = temp->next;
		}
		c->next = temp->next;
		temp->next = c;
	}
}

void popHead(){
	if(h == NULL) return;
	struct tnode *temp = h;
	h = h->next;
	free(temp);
}

void popTail(){
	if(t == NULL) return;
	struct tnode *temp = h;
	
	while(temp->next->valueNode != t->valueNode){
		temp = temp->next;
	}
	t = temp;
	struct tnode *curr;
	curr = temp->next;
	temp->next = NULL;
	free(curr);
}

void popMiddle(int value){
	if(h == NULL) return;
	struct tnode *temp = h;
	
	while(temp->valueNode != value){
		temp = temp->next;
		if(temp == NULL){
			break;
		}
	}
	
	if(temp == NULL) return;
	
	if(temp->valueNode == h->valueNode){
		h = h->next;
		free(temp);
	}else if(temp->valueNode == t->valueNode){
		struct tnode *temp = h;
		while(temp->next->valueNode != t->valueNode){
			temp = temp->next;
		}
		free(t);
		t = temp;
		t->next = NULL;
	}else{
		struct tnode *temp = h;
		while(temp->next->valueNode != value){
			temp = temp->next;
		}
		struct tnode *curr;
		curr = temp->next;
		temp->next = curr->next;
		free(curr);
	}
}

void printAll(){
	struct tnode *temp = h;
	while(temp != NULL){
		printf("%d ", temp->valueNode);
		temp = temp->next;
	}
	printf("\n");
}
