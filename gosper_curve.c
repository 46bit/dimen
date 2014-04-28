#include <stdio.h>
#include <stdlib.h>
#include "gosper_curve.h"

// compile to -g ASM, output to s.s
//   gcc-4.2 -S s.c
// assemble with clang, output to ./a.out
//   rm -f ./a.out && clang s.s
// decompile to s.dump
//   gobjdump -S --disassemble ./a.out > s.dump

#define DESCRIBE 0
#define LOGO_MOVE 4

int main()
{
	uint64_t length = 1;
	char *axiom = malloc(sizeof(char) * length);
	*axiom = 'A';
	char **state = &axiom;

	uint64_t move;
	for (move = 0; move < 7; move++)
	{
		#if DESCRIBE==1
			printf("%d. %.*s\n", (int) move, (int) length, *state);
		#endif
		#ifdef LOGO_MOVE
			uint64_t i;
			for (i = 0; i < length && move == LOGO_MOVE; i++) {
				if ((*state)[i] == '-') {
					printf("LT 60\n");
				}
				if ((*state)[i] == '+') {
					printf("RT 60\n");
				}
				if ((*state)[i] == 'A' || (*state)[i] == 'B') {
					printf("FD 4\n");
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
	uint64_t new_length = length * 15;
	char *new_state = malloc(sizeof(char) * new_length);
	uint64_t i, j = 0, k;
	for (i = 0; i < length; i++)
	{
		char symbol = (*state)[i];

		if (symbol == 'A')
		{
			new_state[j++] = 'A';
			new_state[j++] = '-';
			new_state[j++] = 'B';
			new_state[j++] = '-';
			new_state[j++] = '-';

			new_state[j++] = 'B';
			new_state[j++] = '+';
			new_state[j++] = 'A';
			new_state[j++] = '+';
			new_state[j++] = '+';

			new_state[j++] = 'A';
			new_state[j++] = 'A';
			new_state[j++] = '+';
			new_state[j++] = 'B';
			new_state[j++] = '-';

			continue;
		}
		if (symbol == 'B')
		{
			new_state[j++] = '+';
			new_state[j++] = 'A';
			new_state[j++] = '-';
			new_state[j++] = 'B';
			new_state[j++] = 'B';

			new_state[j++] = '-';
			new_state[j++] = '-';
			new_state[j++] = 'B';
			new_state[j++] = '-';
			new_state[j++] = 'A';

			new_state[j++] = '+';
			new_state[j++] = '+';
			new_state[j++] = 'A';
			new_state[j++] = '+';
			new_state[j++] = 'B';

			continue;
		}
		new_state[j++] = symbol;
	}
	free(*state);
	*state = new_state;
	return j;
}
