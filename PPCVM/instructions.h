#pragma once

union instruction {
	int value;
	struct {
		unsigned int operands : 26;
		unsigned int opcode : 5;
	} bits;
};
union addi {
	int value;
	struct {
		unsigned int si : 16;
		unsigned int ra : 5;
		unsigned int rt : 5;
		unsigned int opcode : 5;
	} bits;
};
union b {
	int value;
	struct {
		unsigned int lk : 1;
		unsigned int aa : 1;
		unsigned int li : 24;
		unsigned int opcode : 5;
	} bits;
};
union bc {
	int value;
	struct {
		unsigned int lk : 1;
		unsigned int aa : 1;
		unsigned int bd : 14;
		unsigned int bi : 5;
		unsigned int bo : 5;
		unsigned int opcode : 5;
	} bits;
};
union cmpi {
	int value;
	struct {
		unsigned int si : 16;
		unsigned int ra : 5;
		unsigned int l : 1;
		unsigned int _ : 1;
		unsigned int bf : 3;
		unsigned int opcode : 5;
	} bits;
};
union _std {
	int value;
	struct {
		unsigned int u : 1;
		unsigned int ds : 15;
		unsigned int ra : 5;
		unsigned int rs : 5;
		unsigned int opcode : 5;
	} bits;
};

typedef addi addis;
typedef addi addic;