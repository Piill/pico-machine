#include "../core/core.h"
#include <stdio.h>

void print_status(struct pmachine*, int);

int main(int argc, char* argv[]) {
	if(argc < 2) {
		printf("No argument given.\n");
		return -1;
	}

	FILE* fp = fopen(argv[1], "r");
	int res = 0;
	char pmachine_code[0xFF];
	for(int i = 0; i < 0xFF && res != EOF; i++) {
		res = fgetc(fp);
		pmachine_code[i] = res;
		pmachine_code[i+1] = '\0';
	}

	struct pmachine* pico = create_machine(pmachine_code);
	for(;;) {
		print_status(pico, 30);
		execute_instruction(pico);
		getchar();
	}
}


void print_status(struct pmachine* pico, int lines) {
	printf("\033[2J\033[1;1H");
	printf("addr\t content\t\t stack\n");
	for(int i = 0; i < lines; i++) {
		if(i < pico->SP) {
			printf("%x:\t %c\t\t %d\n",
					i+pico->PC, read_mem(pico, i+pico->PC), pico->stack[i]);
		} else {
			printf("%x:\t %c\t\n",
					i+pico->PC, read_mem(pico, i+pico->PC));
		}
	}
}
