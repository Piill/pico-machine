#include "../../core/pmachine.h"
#include <stdio.h>

void print_status(struct pmachine*, int);

void handle_error(struct pmachine* pico ,int error_code);
void handle_exit(struct pmachine* pico);
void handle_syscall(struct pmachine* pico, int sys_code);

int running = 1;
int interactive = 0;

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

	struct pmachine pico;
    init_machine(&pico, pmachine_code);
    pico.handle_error = &handle_error;
    pico.handle_exit = &handle_exit;
    pico.handle_syscall = &handle_syscall;
	while(running) {
        if(interactive) {
            getchar();
            print_status(&pico, 30);
        }
		execute_instruction(&pico);
	}
}

void handle_error(struct pmachine* pico ,int error_code) {
    running = 0;
    printf("PMachine error %d\n", error_code);
}

void handle_exit(struct pmachine* pico) {
    running = 0;
    printf("PMachine stopped\n");
}

void handle_syscall(struct pmachine* pico, int syscode) {
    printf("PMachine syscall\n");
    switch (syscode) {
        case 0:  //Enable stepping
            interactive = 1;
            break;
        case 1: //Disable stepping
            interactive = 0;
            break;
    }
}

void print_status(struct pmachine* pico, int lines) {
	printf("\033[2J\033[1;1H");
	printf("addr\t content\t\t stack\n");
	for(int i = 0; i < lines; i++) {
		if(i < pico->SP) {
			printf("%x:\t %c\t\t %d\n",
             i+pico->PC, read_mem(pico, i+pico->PC), pico->stack[pico->SP-i]);
		} else {
			printf("%x:\t %c\t\n",
             i+pico->PC, read_mem(pico, i+pico->PC));
		}
	}
}
