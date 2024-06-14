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
	struct StackNode* top;
}Stack;

//PROTOTYPES
void push(Stack* stack, char* newUrl); //add url to stack
char* pop(Stack* stack); //removes and returns top stack url
char* peek(Stack* stack); // return url from top of stack
bool isEmpty(Stack* stack); //check if stack is empty

//MAIN
int main(void)
{
	


	return	SUCCESS;
}//MAIN END


//
// FUNCTION :  push
// DESCRIPTION :
//	Adds a new url to the stack.
// PARAMETERS :
//	struct FlightInfo* head : the head of the FlightInfo double linked list.
// RETURNS :
//	void: This function returns nothing.
//
void push(Stack* stack, char* newUrl)
{

}