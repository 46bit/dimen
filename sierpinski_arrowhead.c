#include <stdio.h>
#include <stdlib.h>
#include "sierpinski_arrowhead.h"

#define DESCRIBE 0
#define LOGO_MOVE 15

int main()
{
	uint64_t length = 2;
	char *axiom = malloc(sizeof(char) * length);
	*(axiom) = 'X';
	*(axiom+1) = 'F';
	char **state = &axiom;

	uint64_t move;
	for (move = 0; move < 16; move++)
	{
		#if DESCRIBE==1
			printf("%d. %.*s\n", (int) move, (int) length, *state);
		#endif
		#ifdef LOGO_MOVE
			uint64_t i;
			for (i = 0; i < length && move == LOGO_MOVE; i++) {
				if ((*state)[i] == 'F') {
					printf("FD 5\n");
				} else if ((*state)[i] == '+') {
					printf("LT 60\n");
				} else if ((*state)[i] == '-') {
					printf("RT 60\n");
				}
			}
		#endif
		printf("\n");
		length = evolve(state, length);
	}

	return 0;
}

uint64_t evolve(char **state, uint64_t length)
{
	uint64_t new_length = length * 7 + 1;
	char *new_state = malloc(sizeof(char) * new_length);
	uint64_t i, j = 0;

	for (i = 0; i < length; i++)
	{
		char symbol = (*state)[i];

		if (symbol == 'X')
		{
			new_state[j++] = 'Y';
			new_state[j++] = 'F';
			new_state[j++] = '+';
			new_state[j++] = 'X';
			new_state[j++] = 'F';
			new_state[j++] = '+';
			new_state[j++] = 'Y';

			continue;
		}
		if (symbol == 'Y')
		{
			new_state[j++] = 'X';
			new_state[j++] = 'F';
			new_state[j++] = '-';
			new_state[j++] = 'Y';
			new_state[j++] = 'F';
			new_state[j++] = '-';
			new_state[j++] = 'X';

			continue;
		}
	}
	free(*state);
	*state = new_state;
	return j;
}
