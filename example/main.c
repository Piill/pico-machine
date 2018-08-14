#include "../core/core.h"
#include <stdio.h>

void print_status(struct machine*, int);

int main(int argc, char* argv[]) {
	if(argc < 2) {
		printf("No argument given.\n");
		return -1;
	}

	FILE* fp = fopen(argv[1], "r");
	int res = 0;
	char machine_code[0xFF];
	for(int i = 0; i < 0xFF && res != EOF; i++) {
		res = fgetc(fp);
		machine_code[i] = res;
		machine_code[i+1] = '\0';
	}

	struct machine* pico = create_machine(machine_code);
	for(;;) {
		print_status(pico, 30);
		execute_instruction(pico);
		getchar();
	}
}


void print_status(struct machine* pico, int lines) {
	printf("\033[2J\033[1;1H");
	printf("addr\t content\t\t stack\n");
	for(int i = 0; i < lines; i++) {
		if(i < pico->SP) {
			printf("%x:\t %c\t\t %d\n",
					pico->PC+i, read_mem(pico, pico->PC+i), pico->stack[i]);
		} else {
			printf("%x:\t %c\t\n",
					pico->PC+i, read_mem(pico, pico->PC+i));
		}
	}
}