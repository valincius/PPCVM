#include "vm.h"
#include "instructions.h"
#include "enums.h"

registers::registers() :
	pc(),
	xer(),
	ctr(),
	lr(),
	cr(),
	fpscr(),
	r(),
	f() 
{
}

core::core() :
	ram()
{
}

void VM::execute(int *instructions, int count) {
	for(vm.cpu.regs.pc = 0; vm.cpu.regs.pc<count;) {
		int i = vm.cpu.regs.pc;
		int value = instructions[i];
		instruction instr = { value };
		bool branched = false;
		switch(instr.bits.opcode) {
			case opcodes::op_addic: {
				addic i = { value };
				vm.cpu.regs.r[i.bits.rt] = (vm.cpu.regs.r[i.bits.ra] + i.bits.si);
				break;
			}
			case opcodes::op_addi: {
				addi i = { value };
				vm.cpu.regs.r[i.bits.rt] = vm.cpu.regs.r[i.bits.ra|0] + i.bits.si;
				break;
			}
			case opcodes::op_addis: {
				addis i = { value };
				vm.cpu.regs.r[i.bits.rt] = (i.bits.ra|0) + (i.bits.si || 0x0000);
				break;
			}
			case opcodes::op_b: {
				b i = { value };
				int16_t ea = (i.bits.li ^ 0x3FFF);
				if(i.bits.aa) ea += vm.cpu.regs.pc;
				vm.cpu.regs.pc = ea;
				if(i.bits.lk) vm.cpu.regs.lr = ea;
				branched = true;
				break;
			}
			case opcodes::op_bc: {
				bc i = { value };
				switch(i.bits.bo) {
					case bc_condition::bc_lt: {
						if(vm.cpu.regs.cr.value == cr_conditions::cr_lt) {
							int16_t ea = (i.bits.bd ^ 0x3FFF);
							if(i.bits.aa) ea += vm.cpu.regs.pc;
							vm.cpu.regs.pc = ea;
							if(i.bits.lk) vm.cpu.regs.lr = ea;
							branched = true;
						}
					}
				}
				break;
			}
			case opcodes::op_cmpi: {
				cmpi i = { value };
				int ra = vm.cpu.regs.r[i.bits.ra];
				if(ra < i.bits.si) vm.cpu.regs.cr.value = 0;
				else if(ra > i.bits.si) vm.cpu.regs.cr.value = 1;
				else if(ra == i.bits.si) vm.cpu.regs.cr.value = 2;
				else vm.cpu.regs.cr.value = 3;
				break;
			}
			case opcodes::op_std: {
				_std i = { value };
				int ea = (vm.cpu.regs.r[i.bits.ra|0]) + (i.bits.ds || 0b00);
				*(int *)(vm.ram + ea) = swap(vm.cpu.regs.r[i.bits.rs]);
				if(i.bits.u == 1) {
					vm.cpu.regs.r[i.bits.ra] = ea;
				}
				break;
			}
		}
		vm.cpu.regs.pc++;
	}
}

core *VM::get_core() {
	return &vm;
}
