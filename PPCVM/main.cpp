#include <iostream>

#include "vm.h"

void print_regs(core *vm) {
	for(int i = 0; i<32; i++) {
		printf("r%02i = 0x%08X	", i, vm->cpu.regs.r[i]);
		if((i + 1) % 4 == 0) {
			printf("\n");
		}
	}
	printf("\npc = 0x%08X\n", vm->cpu.regs.pc * 0x04);
	printf("\n");
}
void print_ram(core *vm) {
	for(int addr = 0; addr < RAM_SIZE; addr += 16) {
		printf("0x%08X ", addr);
		for(int i = 0; i<16; i++) {
			printf("%02X ", vm->ram[addr + i]);
		}
		for(int i = 0; i<16; i++) {
			char c = vm->ram[addr + i];
			printf("%c", !c ? '.' : c);
		}
		printf("\n");
	}
}

int main() {
	/*
	__asm(
	"start:"
		"li %r3, 0x100;"
		"li %r4, 0;"
		"li %r5, 0;"
	"loop:"
		"addic %r4, %r4, 0x100;"
		"addic %r5, %r5, 1;"
		"cmpwi %r5, 100;"
		"blt loop;"
		"std %r4, 0(%r3);"
	);
	*/

	int program[] = {
		0x38600100, 0x38800000, 0x38A00000, 0x30840100,
		0x30A50001, 0x2C050064, 0x4180FFF4, 0xF8830000,
	};

	VM vm;
	core *c = vm.get_core();
	vm.execute(program, sizeof(program)/sizeof(int));

	print_regs(c);
	print_ram(c);

	printf("\n");
	system("pause");
	return 0;
}