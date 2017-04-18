#pragma once

#include <stdint.h>
#include <stdlib.h>  

#define RAM_SIZE 4096
#define swap _byteswap_ulong

class registers {
public:
	uint64_t pc;

	uint64_t xer;
	uint64_t ctr;
	uint64_t lr;
	union {
		int32_t value;
		struct {
			unsigned int cr7 : 4;
			unsigned int cr6 : 4;
			unsigned int cr5 : 4;
			unsigned int cr4 : 4;
			unsigned int cr3 : 4;
			unsigned int cr2 : 4;
			unsigned int cr1 : 4;
			unsigned int cr0 : 4;
		};
	} cr;
	int32_t fpscr;

	uint64_t r[32];

	double f[32];

	registers();
};

class processor {
public:
	registers regs;
};

class core {
public:
	char ram[RAM_SIZE];
	processor cpu;

	core();
};

class VM {
private:
	core vm;

public:
	core *get_core();
	void execute(int *instructions, int count);
};