#include <stdint.h>
#define STACK_DEPTH 254

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
};

struct pmachine* create_machine(char* input_stream);
void destroy_machine(struct pmachine* pico);
void execute_instruction(struct pmachine* pico);

uint8_t read_mem(struct pmachine* pico, uint8_t addr);
void write_mem(struct pmachine* pico, uint8_t addr, uint8_t val);

uint8_t read_stack(struct pmachine* pico, uint8_t addr);
void write_stack(struct pmachine* pico, uint8_t addr, uint8_t val);

void push(struct pmachine* pico, uint8_t val);
uint8_t pop(struct pmachine* pico);


