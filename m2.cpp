/*
* FILE : m2.cpp
* PROJECT : SENG1050 - Assignment #2
* PROGRAMMER : Behzad Afrasiabi
* FIRST VERSION : 2024-06-14
* DESCRIPTION :
*	This program uses stacks as url. 
* 	  FILL LATER
* 	  FILL LATER
* 	  FILL LATER
* 	  FILL LATER
* 	  FILL LATER
*/	 


#include<stdio.h>
#include<malloc.h>
#include<stdbool.h>
#include<stdlib.h>
#include<string.h>
#pragma warning (disable: 4996) 

//RETURN CODES
#define SUCCESS 0
#define FAILURE -1
#define MEMORY_ALLOCATION_ERROR -2

//STRUCTS
//Stack Structs:
typedef struct StackNode
{
	char* url;
	struct StackNode* next;
}StackNode;

typedef struct
{
	StackNode* top;
}Stack;

//Queue Structs:
typedef struct QueueNode
{
	char* url;
	struct QueueNode* next;
} QueueNode;

typedef struct
{
	struct QueueNode* front;
	struct QueueNode* rear;
}Queue;


//PROTOTYPES
//Stack functions:
void push(Stack* stack, char* newUrl); //add url to stack
char* pop(Stack* stack); //removes and returns top stack url
char* peek(Stack* stack); // return url from top of stack
bool isEmpty(Stack* stack); //check if stack is empty
StackNode* createStackNode(void); //creates new StackNode object
//Queue functions:
void enqueue(Queue* queue, char* newUrl); //adds url to rear of the queue
char* dequeue(Queue* queue); //removes and returns url from front of the queu
char* peek(Queue* queue); //Returns the URL from the front of the queu without removing it.
bool isEmpty(Queue* queue); //Checks if the queue is empty


//MAIN
int main(void)
{
	Stack* stack = (Stack*)malloc(sizeof(Stack));
	if (stack == NULL)
	{
		printf("Memory allocation failure for Stack* stack");
		return  MEMORY_ALLOCATION_ERROR;
	}
	stack->top = NULL;

	pop(stack);
	push(stack, (char*)"your mom");
	push(stack, (char*)"your dad");
	push(stack, (char*)"your sister");
	printf("%s\n", peek(stack));
	printf("%s\n", pop(stack));
	printf("%s\n", pop(stack));
	printf("%s\n", peek(stack));
	pop(stack);

	return SUCCESS;
}//MAIN END


//
// FUNCTION : createStackNode
// DESCRIPTION :
//	Creates a new StackNode object.
// PARAMETERS :
//	void: no params.
// RETURNS :
//	StackNode*: Pointer to the new StackNode object
//
StackNode* createStackNode(void)
{
	StackNode* node = (StackNode*)malloc(sizeof(StackNode));
	if (node == NULL)
	{//exception
		printf("Memory allocation failure for StackNode* node");
		return NULL;
	}

	node->next = NULL;
	node->url = NULL;

	return node;
}


//
// FUNCTION : push
// DESCRIPTION :
//	Adds a new url to the Stack, and updates the top field of
//	the Stack accordingly.
// PARAMETERS :
//	Stack* stack : stack object the url is to be added to.
//  char* newUrl: new url to be added to the stack.
// RETURNS :
//	void: This function returns nothing.
//
void push(Stack* stack, char* newUrl)
{
	StackNode* newNode = createStackNode();
	if (newNode == NULL)
	{//exception
		printf("error creating new node\n");
	}
	else
	{
		//Memory allocation for node url
		newNode->url = (char*)malloc(strlen(newUrl) + 1);
		if (newNode->url == NULL)
		{//exception
			printf("Memory allocation failure for newNode->url\n");
			free(newNode);
		}
		strcpy(newNode->url, newUrl);

		if (isEmpty(stack))
		{
			stack->top = newNode;
		}
		else
		{
			StackNode* top = stack->top;
			newNode->next = top;
			stack->top = newNode;
		}	
	}
}


//
// FUNCTION : pop
// DESCRIPTION :
//	Removes the top url from the stack and returns the new top stack url.
// PARAMETERS :
//	Stack* stack : stack object the the url is being removed from.
// RETURNS :
//	char*: Memory address to the new top stack url.
//
char* pop(Stack* stack)//removes and returns top stack url
{
	if (isEmpty(stack))
	{//exception
		printf("error: the stack is empty\n");
		return NULL;
	}

	StackNode* top = stack->top;
	char* url = (char*)malloc(strlen(top->url) + 1);
	if (url == NULL)
	{//exception
		printf("Memory allocation failure for url\n");
		return NULL;
	}
	strcpy(url, top->url);

	if (top->next == NULL)
	{
		stack->top = NULL;
	}
	else
	{
		StackNode* newTop = top->next;
		stack->top = newTop;
	}

	free(top->url);
	free(top);

	return url;
}


//
// FUNCTION : peek
// DESCRIPTION :
//	Returns the url from the top of the stack.
// PARAMETERS :
//	Stack* stack : stack object that the url is 
//	being peeked from.
// RETURNS :
//	char*: Memory address to the top stack url.
//
char* peek(Stack* stack)
{
	if (isEmpty(stack))
	{
		printf("error: stack is empty.\n");
		return NULL;
	}
	else
	{
		StackNode* top = stack->top;
		return top->url;
	}	
}


//
// FUNCTION : isEmpty
// DESCRIPTION :
//	Checks if stack is empty and returns an appropriate.
//	boolean value.
// PARAMETERS :
//	Stack* stack : stack object being analyzed.
// RETURNS :
//	bool: Memory address to the top stack url.
//
bool isEmpty(Stack* stack)
{
	if (stack->top == NULL)
	{
		return true;
	}
	else
	{
		return false;
	}
}