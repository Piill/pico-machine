#ifndef PMACHINE
#define PMACHINE

#include <stdint.h>
#include <string.h>

#define STACK_DEPTH 254

// Error codes
#define PER_STACKOVERFLOW 1
#define PER_UNBOUNDMEM 2

struct pmachine {
	uint8_t mem[0xFF];
	uint8_t stack[STACK_DEPTH];
	uint8_t SP;
	uint8_t PC;

	//Memory mapped IO
	uint8_t (*read_mem)(uint8_t addr);
	void (*write_mem)(uint8_t addr, uint8_t val);

	//Exception handeling
	void (*handle_error)(struct pmachine* pico ,int error_code);
	void (*handle_exit)(struct pmachine* pico);
	void (*handle_syscall)(struct pmachine* pico, int call_code);
};

void init_machine(struct pmachine*, char* input_stream);
void execute_instruction(struct pmachine* pico);

uint8_t read_mem(struct pmachine* pico, uint8_t addr);
void write_mem(struct pmachine* pico, uint8_t addr, uint8_t val);

uint8_t read_stack(struct pmachine* pico, uint8_t addr);
void write_stack(struct pmachine* pico, uint8_t addr, uint8_t val);

void push(struct pmachine* pico, uint8_t val);
uint8_t pop(struct pmachine* pico);

#endif
