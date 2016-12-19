// See LICENSE for license details.

#ifndef SRC_ROCC_H_
#define SRC_ROCC_H_

#define STR1(x) #x
#define STR(x) STR1(x)
#define EXTRACT(a, size, offset) (((~(~0 << size) << offset) & a) >> offset)

#define XCUSTOM_OPCODE(x) XCUSTOM_OPCODE_ ## x
#define XCUSTOM_OPCODE_0 0b0001011
#define XCUSTOM_OPCODE_1 0b0101011
#define XCUSTOM_OPCODE_2 0b1011011
#define XCUSTOM_OPCODE_3 0b1111011

#define XCUSTOM(x, rd, rs1, rs2, funct)         \
  XCUSTOM_OPCODE(x)                   |         \
  (rd                   << (7))       |         \
  (0x7                  << (7+5))     |         \
  (rs1                  << (7+5+3))   |         \
  (rs2                  << (7+5+3+5)) |         \
  (EXTRACT(funct, 7, 0) << (7+5+3+5+5))

#define ROCC_INSTRUCTION_RAW_R_R_R(x, rd, rs1, rs2, funct)      \
  .word XCUSTOM(x, ## rd, ## rs1, ## rs2, funct)

// Standard macro that passes rd, rs1, and rs2 via registers
#define ROCC_INSTRUCTION(x, rd, rs1, rs2, funct)                \
  ROCC_INSTRUCTION_R_R_R(x, rd, rs1, rs2, funct, 10, 11, 12)

// rd, rs1, and rs2 are data
// rd_n, rs_1, and rs2_n are the register numbers to use
#define ROCC_INSTRUCTION_R_R_R(x, rd, rs1, rs2, funct, rd_n, rs1_n, rs2_n) { \
    register uint64_t rd_  asm ("x" # rd_n);                            \
    register uint64_t rs1_ asm ("x" # rs1_n) = (uint64_t) rs1;          \
    register uint64_t rs2_ asm ("x" # rs2_n) = (uint64_t) rs2;          \
    asm volatile (                                                      \
        ".word " STR(CUSTOMX(x, rd_n, rs1_n, rs2_n, funct)) "\n\t"      \
        : "=r" (rd_)                                                    \
        : [_rs1] "r" (rs1_), [_rs2] "r" (rs2_));                        \
    rd = rd_;                                                           \
  }

// [TODO] fix these to align with the above approach
// Macro to pass rs2_ as an immediate
/*
#define ROCC_INSTRUCTION_R_R_I(XCUSTOM_, rd_, rs1_, rs2_, funct_) \
  asm volatile (XCUSTOM_" %[rd], %[rs1], %[rs2], %[funct]"        \
                : [rd] "=r" (rd_)                                 \
                : [rs1] "r" (rs1_), [rs2] "i" (rs2_), [funct] "i" (funct_))

// Macro to pass rs1_ and rs2_ as immediates
#define ROCC_INSTRUCTION_R_I_I(XCUSTOM_, rd_, rs1_, rs2_, funct_) \
  asm volatile (XCUSTOM_" %[rd], %[rs1], %[rs2], %[funct]"        \
                : [rd] "=r" (rd_)                                 \
                : [rs1] "i" (rs1_), [rs2] "i" (rs2_), [funct] "i" (funct_))
*/

#define RVTEST_XS_ENABLE \
  li a0, MSTATUS_XS & (MSTATUS_XS >> 1); \
  csrs mstatus, a0;

#define RVTEST_WITH_ROCC \
  .macro init; \
  RVTEST_XS_ENABLE \
  .endm

#endif  // SRC_XCUSTOM_H_
