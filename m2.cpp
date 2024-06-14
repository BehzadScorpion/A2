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

//RETURN CODES
#define SUCCESS 0
#define FAILURE -1

//STRUCTS
typedef struct 
{
	char* url;
	struct StackNode* next;
}StackNode;

typedef struct
{
	StackNode* top;
}Stack;

//PROTOTYPES
void push(Stack* stack, char* newUrl); //add url to stack
char* pop(Stack* stack); //removes and returns top stack url
char* peek(Stack* stack); // return url from top of stack
bool isEmpty(Stack* stack); //check if stack is empty
StackNode* createStackNode(void); //creates new StackNode object

//MAIN
int main(void)
{
	Stack* newStack = (Stack*)malloc(sizeof(Stack));


	return	SUCCESS;
}//MAIN END


//
// FUNCTION :  createStackNode
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

	char* url = (char*)malloc(sizeof(char*));
	if (url == NULL)
	{//exception
		printf("Memory allocation failure for char* url");
		free(node);
		return NULL;
	}

	node->next = NULL;
	node->url = url;

	return node;
}


//
// FUNCTION :  push
// DESCRIPTION :
//	Adds a new url to the stack.
// PARAMETERS :
//	Stack* stack : stack object representing the stack 
//	the url is to be added to.
//  char* newUrl: new url to be added to the stack.
// RETURNS :
//	void: This function returns nothing.
//
void push(Stack* stack, char* newUrl)
{
	StackNode* newNode = createStackNode();
	if (newNode == NULL)
	{
		printf("error creating new node");
	}
	else
	{
		newNode->url = newUrl;
		stack->top = newNode;
	}

}