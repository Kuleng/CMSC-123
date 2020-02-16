#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "stack.h"
#include "list.h"

int underFlow(STACK *stack){
	if (stack->length - 2 < 0){ //If the stack length less than 2 is zero
		return 1;				// It will have a stack underflow error after performing an operation
	}
	return 0;
}

int overFlow(STACK *stack){
	if (stack->length + 1 > stack->maxLength){ //If the stack length + 1 will exceed max length
		return 1; // It will have a stack overflow error after pushing operation
	}
	return 0;
}

int checkStack(STACK *stack){ //mainChecker of the stack
	if (underFlow(stack) == 1){
		printf("Stack underflow.\n");
		return 0;
	}
	else if (overFlow(stack) == 1){
		printf("Stack overflow. \n");
		return 0;
	}

	return 1;
}

int elementCounter(char userInput[]){ //counts the element of the character array input as the user
	int element = 0;
	for (int i = 0; i < 100; i++){
		if (userInput[i] == '\0') break;
		element++;
	}

	return element;
}

void performOp(STACK *stack, int *value1, int *value2){
	*value1 = pop(stack); //This function pops the 2 values then
	*value2 = pop(stack); //stores it value to 2 integer variables in main function.
}


int main(){
	STACK *mainStack;

	char userInput[100];
	int num1, num2, stackStatus, result, count, terminate = 0;
	char tempChar, ch;
	
	while(terminate == 0){
		mainStack = createStack(100);
		printf("Input: ");
		scanf("%[^\n]s", userInput);
		ch = getchar(); //gets the new line
		count = strlen(userInput); //gets the length of the user input

		if (ch == '\n' && count == 0){
			terminate =1;	 //if the scanf didnt catch any input aside from the \n
			printf("Exiting program..\n");
			break;
		}

		for (int a = 0; a < count; a++){ //Main loop for comparison of the userinput
			if (isdigit(userInput[a]) != 0){
				if (count == 1) { //if the input is only a single digit, display.
					printf("Result: %s\n", userInput);
					break;
				}
				tempChar = userInput[a]; //Gets the specific character element to avoid catching the whole array
				push(mainStack, createNode(atoi(&tempChar)));
			}
			else{
				char operators[5] = {'+', '-', '*', '/'}; //Operator declaration

				for (int o = 0; o < strlen(operators); o++){
					if (userInput[a] == operators[o]){
						//Operator found, terminate if underflow or overflow.
						stackStatus = checkStack(mainStack);
						if (stackStatus == 0){
							terminate = 1;
							break;
						}
					}
				}

				if (terminate == 1) break; //terminator

				//Perform operation based on catched character.
				if (userInput[a] == '/'){
					performOp(mainStack, &num1,&num2);
					result = num2/num1;
					push(mainStack,createNode(result));
				}else if (userInput[a] == '+'){
					performOp(mainStack, &num1,&num2);
					result = num2 + num1;
					push(mainStack,createNode(result));
				}else if (userInput[a] == '-'){	
					performOp(mainStack, &num1,&num2);
					result = num2-num1;
					push(mainStack,createNode(result));
				}else if (userInput[a] == '*'){	
					performOp(mainStack, &num1,&num2);
					result = num2*num1;
					push(mainStack,createNode(result));
				}else{
					//If non integer and non operator character is found.
					printf("Error in parsing command. Invalid character found(%c). Exiting.. \n", userInput[a]);
					terminate = 1;
					break;
				}
			}
		}

			if (mainStack->length <= 1){ //Checks the stack if the expression was executed successfully
				printf("Result:  %d\n", result);
			} else{
				printf("Length:  %d\n", mainStack->length);
				printf("Incomplete expression. Exiting program... \n");//the stack has ran out of operator but there is still an integer/expression
				terminate = 1;
				break;
			}
	}
}