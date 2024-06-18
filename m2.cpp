/*
* FILE : m2.cpp
* PROJECT : SENG1050 - Assignment #2
* PROGRAMMER : Behzad Afrasiabi
* FIRST VERSION : 2024-06-14
* DESCRIPTION :
*  This program simulates web-based navigation using a stack and a queue.
*  Each new web page visited is added to the stack for backward navigation.
*  Pages popped from the stack are added to the queue for forward navigation.
*  The program allows users to visit new pages, navigate backward and forward,
*  display the current page, and view navigation history. It also provides an 
*  option to exit the navigation simulation gracefully.
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
#define CHOICE_INPUT_LIMIT 5
#define URL_INPUT_LIMIT 30

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
char* dequeue(Queue* queue); //removes and returns url from front of the queue
char* peek(Queue* queue); //Returns the url from the front of the queu without removing it.
bool isEmpty(Queue* queue); //Checks if the queue is empty
QueueNode* createQueueNode(void); //creates new Queue Node object
//Menu functions:
void replaceNewLineCharacter(char text[]);
void visitNewPage(Stack* stack, char* url); // adds a page to the stack and prints info appropriately


//MAIN
int main(void)
{
	//Queue init
	Queue* queue = (Queue*)malloc(sizeof(Queue));
	if (queue == NULL)
	{
		printf("Memory allocation failure for Queue* queue\n");
		return  MEMORY_ALLOCATION_ERROR;
	}
	queue->front = NULL;
	queue->rear = NULL;

	//Stack init
	Stack* stack = (Stack*)malloc(sizeof(Stack));
	if (stack == NULL)
	{
		printf("Memory allocation failure for Stack* stack\n");
		return  MEMORY_ALLOCATION_ERROR;
	}
	stack->top = NULL;

	//Menu code
	char input[CHOICE_INPUT_LIMIT] = { " " };
	int choice = 0;

	while (choice != 5) //Menu loop
	{
		printf("Menu:\n");
		printf("1. Visit New Web Page\n");
		printf("2. Navigate Backward\n");
		printf("3. Navigate Forward\n");
		printf("4. Display Current Page and History\n");
		printf("5. Exit\n\n");
		printf("Enter your choice: ");
		if (fgets(input, CHOICE_INPUT_LIMIT, stdin) != NULL)
		{
			replaceNewLineCharacter(input);
			if (sscanf(input, "%d", &choice) == 1)
			{
				char url[URL_INPUT_LIMIT] = { " " };
				StackNode* currentStackNode = stack->top;
				QueueNode* currentQueueNode = queue->front;
				int i = 0;
				switch (choice)
				{
					case 1: //Visit New Web Page
						printf("Enter the URL of the web page: "); 
						if (fgets(url, URL_INPUT_LIMIT, stdin) != NULL)
						{
							replaceNewLineCharacter(url);
							push(stack, url);
						}
						printf("\n");
						break;

					case 2: //Navigate Backward
						if (isEmpty(stack))
						{
							printf("No pages to display.\n");
						}
						else
						{
							strcpy(url, pop(stack));
							enqueue(queue, url);
							printf("Previous Page: %s\n\n", url);
						}
						break;
						
					case 3: //Navigate Forward
						if (isEmpty(queue))
						{
							printf("No pages to display.\n");
						}
						else
						{
							strcpy(url, dequeue(queue));
							push(stack, url);
							printf("Next Page: %s\n\n", url);
						}
						break;

					case 4: //Display Current Page and History
						printf("Current Page: %s\n", peek(stack));
						if (isEmpty(stack) || currentStackNode->next == NULL)
						{
							printf("Backward History:\n");
							printf("No pages to display.\n");
						}
						else
						{
							//Backward History
							printf("Backward History:\n");
							while (currentStackNode->next != NULL)
							{
								i++;
								printf("%d. %s\n", i, currentStackNode->url);
								currentStackNode = currentStackNode->next;
								if (currentStackNode->next == NULL)
								{
									i++;
									printf("%d. %s\n", i, currentStackNode->url);
								}
							}
						}

						//Forward History
						if (isEmpty(queue))
						{
							printf("Forward History:\n");
							printf("No pages to display.\n");
						}
						else
						{
							printf("Forward History:\n");
							QueueNode* currentQueueNode = queue->front;
							i = 0;
							while (currentQueueNode->next != NULL)
							{
								i++;
								printf("%d. %s\n", i, currentQueueNode->url);
								currentQueueNode = currentQueueNode->next;
								if (currentQueueNode->next == NULL)
								{
									i++;
									printf("%d. %s\n", i, currentQueueNode->url);
								}
							}
						}
						printf("\n");
						break;

					case 5: //Exit
						while (!isEmpty(stack))
						{
							pop(stack);
						}

						while (!isEmpty(queue))
						{
							dequeue(queue);
						}

						return SUCCESS;

					default:
						printf("Invalid choice entry. Please try again.\n");
						break;
				}

			}
			else 
			{
				printf("Invalid choice entry. Please try again.\n");
			}
		}
		else
		{
			printf("NULL input error. Please try again.\n");
		}

	}//Menu loop end


	return SUCCESS;
}//MAIN END


//MENU FUNCTIONS
//
// FUNCTION :  replaceNewLineCharacter
// DESCRIPTION :
//	This function takes in a C-style string and checks whether it ends with
//	a new line character. If the new line character is found, it is replaced
//  with a null terminator throgh derefrencing, so that the C-style strings 
//  becomes usable in the program.
// PARAMETERS :
//	char text[] : The C-style string.
// RETURNS :
//	void: This function returns nothing.
//
void replaceNewLineCharacter(char text[])
{
	//removing new line character and replacing it with a null terminator
	char* newLine = strchr(text, '\n');
	if (newLine != NULL)
	{
		*newLine = '\0';
	}
}


//STACK FUNCTIONS
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
//	void: returns nothing.
//
void push(Stack* stack, char* newUrl)
{
	StackNode* newNode = createStackNode();
	if (newNode == NULL)
	{//exception
		printf("error creating new StackNode\n");
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
		else
		{
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
//	bool: true if stack is empty and false otherwise.
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


//QUEUE FUNCTIONS
//
// FUNCTION : createQueueNode
// DESCRIPTION :
//	Creates a new QueueNode object with fields set to NULL.
// PARAMETERS :
//	void: no params.
// RETURNS :
//	void: returns nothing.
//
QueueNode* createQueueNode(void)
{
	QueueNode* node = (QueueNode*)malloc(sizeof(QueueNode));
	if (node == NULL)
	{//exception
		printf("Memory allocation failure for QueueNode* node");
		return NULL;
	}

	node->url = NULL;
	node->next = NULL;

	return node;
}


//
// FUNCTION : enqueue
// DESCRIPTION :
//	Adds url to rear of the queue.
// PARAMETERS :
//	Queue* queue : Queue object the url is being addded to
//  char* newUrl: new url being added to Queue.
// RETURNS :
//	void: returns nothing.
//
void enqueue(Queue* queue, char* newUrl)
{
	QueueNode* newNode = createQueueNode();
	if (newNode == NULL)
	{//exception
		printf("error creating new QueueNode\n");
	}
	else
	{
		newNode->url = (char*)malloc(strlen(newUrl) + 1);
		if (newNode->url == NULL)
		{
			printf("Memory allocation failure for newNode->url\n");
			free(newNode);
		}
		else
		{
			strcpy(newNode->url, newUrl); //url copied to newNode
			if (isEmpty(queue))
			{
				queue->front = newNode;
				queue->rear = newNode;
			}
			else if (queue->front == queue->rear)
			{
				queue->front->next = newNode;
				queue->rear = newNode;
			}
			else
			{
				queue->rear->next = newNode;
				queue->rear = newNode;
			}
		}
	}
}


//
// FUNCTION : dequeue
// DESCRIPTION :
//	Removes and returns url from front of the queue.
// PARAMETERS :
//	Queue* queue : Queue object the url is being removed from
// RETURNS :
//	char*: the removed url pointer.
//
char* dequeue(Queue* queue)
{
	if (isEmpty(queue))
	{//exception
		printf("error: the queue is empty\n");
		return NULL;
	}
	else
	{
		QueueNode* front = queue->front;
		char* url = (char*)malloc(strlen(front->url) + 1);
		if (url == NULL)
		{//exception
			printf("Memory allocation failure for url\n");
			return NULL;
		}
		strcpy(url, front->url);

		if (queue->front == queue->rear)
		{
			free(front->url);
			free(front);
			queue->front = NULL;
			queue->rear = NULL;
		}
		else
		{
			queue->front = front->next;
			free(front->url);
			free(front);
		}

		return url;
	}
}	


//
// FUNCTION : peek
// DESCRIPTION :
//	Returns the url from the front of the queu without removing it.
// PARAMETERS :
//	Queue* queue : Queue object the url is being peeked from
// RETURNS :
//	char*: the peeked url pointer.
//
char* peek(Queue* queue)
{
	if(isEmpty(queue))
	{//exception
		printf("error: the queue is empty\n");
		return NULL;
	}
	else
	{
		return queue->front->url;
	}
}


//
// FUNCTION : isEmpty
// DESCRIPTION :
//	Checks if queue is empty and returns an appropriate.
//	boolean value.
// PARAMETERS :
//	Queue* queue : queue object being analyzed.
// RETURNS :
//	bool: true if queue is empty and false otherwise.
//
bool isEmpty(Queue* queue)
{
	if (queue->front == NULL && queue->rear == NULL)
	{
		return true;
	}
	else
	{
		return false;
	}
}