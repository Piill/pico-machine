#include <stdint.h>
#define STACK_DEPTH 254

struct machine {
	uint8_t mem[0xFF];
	uint8_t stack[STACK_DEPTH];
	uint8_t SP;
	uint8_t PC;
	// TODO
	// Implement function pointers for:
	// memory mapped IO (i.e. read and write functions)
	// system calls
};

struct machine* create_machine(char* input_stream);
void destroy_machine(struct machine* pico);
void execute_instruction(struct machine* pico);

uint8_t read_mem(struct machine* pico, uint8_t addr);
void write_mem(struct machine* pico, uint8_t addr, uint8_t val);

uint8_t read_stack(struct machine* pico, uint8_t addr);
void write_stack(struct machine* pico, uint8_t addr, uint8_t val);

void push(struct machine* pico, uint8_t val);
uint8_t pop(struct machine* pico);


