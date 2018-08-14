#include "core.h"
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

struct machine* create_machine(char* input_stream) {
	struct machine* pico = malloc(sizeof(struct machine));
	pico->SP = 0;
	pico->PC = 0;
	memset(pico->mem, 0, 0xFF*sizeof(uint8_t));

	for(int i = 0; i < 0xFF && input_stream[i] > 32
			&& input_stream[i] < 127; i++) {
		pico->mem[i] = input_stream[i];
	}
	return pico;
}

void destroy_machine(struct machine* pico) {
	free(pico);
}

void execute_instruction(struct machine* pico) {
	uint8_t val, addr;
	switch(read_mem(pico, pico->PC)) {
		case '!': //Push
			push(pico, read_mem(pico, pico->PC+1) - 33);
			pico->PC++;
			break;
		case '"': //Pop
			pop(pico);
			break;
		case '#': //Dup
			val = pop(pico);
			push(pico, val);
			push(pico, val);
			break;
		case '$': //Swap
			val = read_stack(pico, 0);
			write_stack(pico, 0, read_stack(pico, 1));
			write_stack(pico, 1, val);
			break;
		case '%': //Over
			val = read_stack(pico, 1);
			push(pico, val);
			break;
		case '&': //Add
			push(pico, pop(pico) + pop(pico));
			break;
		case 39: //Sub
			push(pico, pop(pico) - pop(pico));
			break;
		case '(': //Or
			push(pico, pop(pico) | pop(pico));
			break;
		case ')': //Xor
			push(pico, pop(pico) ^ pop(pico));
			break;
		case '*': //And
			push(pico, pop(pico) & pop(pico));
			break;
		case '+': //Ones' complement
			push(pico, ~pop(pico));
			break;
		case ',': //Load
			addr = pop(pico);
			push(pico, read_mem(pico, addr));
			break;
		case '-': //Store
			val = pop(pico);
			addr = pop(pico);
			write_mem(pico, addr, val);
			break;
		case '.': // Greater than
			push(pico, pop(pico) > pop(pico));
			break;
		case '/': // Less than
			push(pico, pop(pico) < pop(pico));
			break;
		case '0': // Equals
			push(pico, pop(pico) == pop(pico));
			break;
		case '1': // If
			addr = pop(pico);
			val = pop(pico);
			if(val) {
				pico->PC = addr;
			}
			break;
		case '2': //Not
			val = pop(pico);
			if(val == 0)
				push(pico, 1);
			else
				push(pico, 0);
			break;
		case '3': //Jump
			pico->PC = pop(pico);
			break;
		case '4': //Syscall
		default:
			break;
	}
	pico->PC++;
}

void push(struct machine* pico, uint8_t val) {
	write_stack(pico, 0, val);
	pico->SP++;
}

uint8_t pop(struct machine* pico) {
	pico->SP--;
	uint8_t val = read_stack(pico, 0);
	return val;
}

uint8_t read_mem(struct machine* pico, uint8_t addr) {
	if(addr >= 0 && addr <= 0xff) {
		return pico->mem[addr];
	}
	printf("Unbound mem access\n");
	printf("Terminating program\n");
	exit(-1);
}

void write_mem(struct machine* pico, uint8_t addr, uint8_t val) {
	if(addr <= 0xff) {
		pico->mem[addr] = val;
	} else {
		printf("Unbound mem access\n");
		printf("Terminating program\n");
		exit(-1);
	}
}

uint8_t read_stack(struct machine* pico, uint8_t addr) {
	if(addr+pico->SP <= STACK_DEPTH) {
		return pico->stack[pico->SP+addr];
	}
	printf("Stack overflow\n");
	printf("Terminating program\n");
	exit(-1);
}

void write_stack(struct machine* pico, uint8_t addr, uint8_t val) {
	if(addr+pico->SP <= STACK_DEPTH) {
		pico->stack[pico->SP+addr] = val;
	} else {
		printf("Stack overflow\n");
		printf("Terminating program\n");
		exit(-1);
	}
}

