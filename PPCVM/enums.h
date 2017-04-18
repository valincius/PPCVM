#pragma once

enum opcodes {
	op_cmpi = 11,
	op_addic = 12,
	op_addi = 14,
	op_addis = 15,
	op_bc = 16,
	op_b = 18,
	op_std = 30,
};
enum bc_condition {
	bc_lt = 12,
};
enum cr_conditions {
	cr_lt = 0,
	cr_gt = 1,
	cr_eq = 2,
	cr_error = 3,
};
