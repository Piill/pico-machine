#include "core.h"

void init_machine(struct pmachine* pico, char* input_stream) {
	pico->SP = 0;
	pico->PC = 0;
	memset(pico->mem, 0, 0xFF*sizeof(uint8_t));
	pico->handle_error = NULL;
	pico->handle_exit = NULL;
	pico->write_mem = NULL;
	pico->read_mem = NULL;

	for(int i = 0; i < 0xFF && input_stream[i] > 32
			&& input_stream[i] < 127; i++) {
		pico->mem[i] = input_stream[i];
	}
}

void execute_instruction(struct pmachine* pico) {
	uint8_t val, addr;
	pico->PC++;
	switch(read_mem(pico, pico->PC-1)) {
		case '!': //Push
			push(pico, read_mem(pico, pico->PC) - 33);
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
			val = pop(pico);
			addr = pop(pico);
			push(pico, val);
			push(pico, addr);
			break;
		case '%': //Over
			addr = pop(pico);
			val = pop(pico);
			push(pico, val);
			push(pico, addr);
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
			break;
		case '5': //Exit
            if(pico->handle_exit != NULL) {
			    pico->handle_exit(pico);
            }
			break;
		default:
			break;
	}
}

void push(struct pmachine* pico, uint8_t val) {
	write_stack(pico, 0, val);
	pico->SP++;
}

uint8_t pop(struct pmachine* pico) {
	pico->SP--;
	uint8_t val = read_stack(pico, 0);
	return val;
}

uint8_t read_mem(struct pmachine* pico, uint8_t addr) {
	if(addr <= 0xE0) {
		return pico->mem[addr];
	} else if(addr == 0xF0) {
		return pico->PC;
	} else if(addr == 0xF1) {
		return STACK_DEPTH;
	} else if(addr == 0xF2) {
		return pico->SP;
	} else if(addr <= 0xFF && pico->read_mem != NULL) {
		return pico->read_mem(addr);
	} else if(pico->handle_error != NULL) {
        pico->handle_error(pico, PER_UNBOUNDMEM);
	}
    return -1;
}

void write_mem(struct pmachine* pico, uint8_t addr, uint8_t val) {
	if(addr <= 0xE0) {
		pico->mem[addr] = val;
	} else if(addr <= 0xFF && pico->write_mem != NULL) {
		pico->write_mem(addr, val);
	} else {
		pico->handle_error(pico, PER_UNBOUNDMEM);
	}
}

uint8_t read_stack(struct pmachine* pico, uint8_t addr) {
	if(addr+pico->SP <= STACK_DEPTH) {
		return pico->stack[pico->SP+addr];
	}
	pico->handle_error(pico, PER_STACKOVERFLOW);
    return -1;
}

void write_stack(struct pmachine* pico, uint8_t addr, uint8_t val) {
	if(addr+pico->SP < STACK_DEPTH) {
		pico->stack[pico->SP+addr] = val;
	} else {
		pico->handle_error(pico, PER_STACKOVERFLOW);
	}
}


