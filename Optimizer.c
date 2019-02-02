#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "InstrUtils.h"
#include "Utils.h"

int main()
{
	Instruction *head;

	head = ReadInstructionList(stdin);
	if (!head) {
		WARNING("No instructions\n");
		exit(EXIT_FAILURE);
	}
	/* YOUR CODE GOES HERE */
	
	Instruction *previous = head;
	Instruction *current = previous -> next;
	Instruction *next = current -> next;
	
	int check;
	while(next != null){
		if(prev -> opcode == LOADI && curr -> opcode ==LOADI){
			
			if (next -> opcode == ADD){
				check = 1;
				current -> field1 = next -> field1;
				current -> field2 = previous -> field2 + current -> field2;
			}
			
			else if ( next -> opcode == SUB){
				check = 1;
				current -> field1 = next -> field1;
				if (next -> field2 == previous -> field2){
					current -> field2 = previous -> field2 - current -> field2;
					
				}
				else{
				
					current -> field2 = current -> field2 - previous -> field2;
					
				}
			}
			else if (next -> opcode == MUL){
				check = 1;

				current -> field1 = next -> field1;
				current -> field2 = previous -> field2 * current -> field2;
			}
			else {
				printf("ERRor");
				exit(EXIT_FAILURE)
			}
			}
		}
		
	if(check == 0){
		previous = current;
		current = next;
		next = next -> next;
	}
	else{
		Instruction * a = previous;
		Instruction * b = next;
		free(a);
		free(b);
		
		previous -> next = next -> next;
		previous = previous -> next;
		current = previous -> next;
		next = current -> next;
	}
		

	
	if (head) {
		PrintInstructionList(stdout, head);
		DestroyInstructionList(head);
	}
	return EXIT_SUCCESS;
}

