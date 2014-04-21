//Nicholas Ortiz

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#define MAX_EQU_LEN 100

typedef struct node_{
	char data;
	struct node_ *next;
}node;

typedef struct stack_{
	unsigned int size;
	node* stack;
}stack;

stack* create_stack();
void push(stack* s, char val);
char top(stack* s);
void pop(stack* s);
int paren_match(char* equation);
int paren_and_brackets_match(char* equation);

int main(int argc, char **argv){
	int result = 0;
//check file arguments
	if (argc != 2){
		printf("Insufficient arguments\n");
		return 0;
	}
//open file
	FILE* file = fopen(argv[1], "r");
	
	if (file == NULL){
		printf("Unable to open the input file\n");
		return 0;
	}
//malloc memory to hold equations
	char* equ = malloc(MAX_EQU_LEN * sizeof(char));
//read in the equations and check for balance
	while(fscanf(file,"%s", equ) != EOF){
		result = paren_match(equ);
		if(result == 1){
			printf("For Equation %s; Parens match",equ);
		}
		else{
			printf("For Equation %s; Parens do not match",equ);
		}
		result = paren_and_brackets_match(equ);
		if(result == 1){
			printf(";brackets match\n");
		}
		else{
			printf(";brackets do not match\n");
		}
	}
//free memory for string and close file
	free(equ);
	fclose(file);
	return 0;
}
//create an empty stack
stack* create_stack(){
	stack* newStack = NULL;

	newStack = (stack*)malloc(sizeof(stack));
	newStack->size = 0;
	newStack->stack = NULL;
	return newStack;

}
//push to the top of the stack.
void push(stack* s, char val){
	node* new_node = NULL;
	node* tmp = NULL;

	new_node = (node*)malloc(sizeof(node));
	new_node->data = val;
	new_node->next = NULL;

	if (s->stack == NULL){
		s->stack = new_node;
		s->size += 1;
	}
	else{
		tmp = s->stack;
		new_node->next = tmp;
		s->stack = new_node;
		s->size += 1;
	}

}
//find the value at the top of stack
char top(stack* s){
	node* tmp = NULL;

	if (s->stack != NULL){
		tmp = s->stack;
		return tmp->data;
	}
	printf("Nothing on the stack\n");
	return '0';
}
//take off the top value and free its memory
void pop(stack* s){
	node* del = NULL;

	if (s->stack == NULL){
		
		return;
	}
	del = s->stack;
	s->stack = del->next;
	free(del);
	s->size -= 1;
}
//check for balanced parens
int paren_match(char* equation){
	char* ptr = NULL;
	stack* start = NULL;
	int count = 0;
	ptr = equation;
	node* tmp = NULL, *del = NULL;
	
	start = create_stack();
	
	while(*ptr != '\0'){
		if(*ptr == '('){
			push(start,'(');
			count++;
		}
		else if(*ptr == ')'){
			pop(start);
			count--;
		}
		if(count < 0 ){
			return 0;
		}
		ptr++;
	}
	
	tmp = start->stack;
	while (tmp != NULL){
		del = tmp;
		tmp = tmp->next;
		free(del);
	}
	free(start);
	if(count == 0){
		return 1;
	}
	else{
		return 0;
	}
}
//check for balanced brackets
int paren_and_brackets_match(char* equation){
	char* ptr = NULL;
	stack* start = NULL;
	int count = 0, count2 = 0;
	ptr = equation;
	node* tmp = NULL, *del = NULL;
	
	start = create_stack();
	
	while(*ptr != '\0'){
		if(*ptr == '('){
			push(start,'(');
			count++;
		}
		else if(*ptr == '['){
			push(start,'[');
			count2++;
		}
		else if(*ptr == ']'){
			tmp = start->stack;
			if(tmp != NULL && tmp->data == '('){
				return 0;
			}
			pop(start);
			count2--;
		}
		else if(*ptr == ')'){
			tmp = start->stack;
			if(tmp != NULL && tmp->data == '['){
				return 0;
			}
			pop(start);
			count--;
		}
		if(count < 0 || count2 < 0){
			return 0;
		}
		ptr++;
	}
	tmp = start->stack;
	while (tmp != NULL){
		del = tmp;
		tmp = tmp->next;
		free(del);
	}
	free(start);
	if(count == 0){
		return 1;
	}
	else{
		return 0;
	}
}