// Copyright 2018 IBM
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#ifndef ROCC_SOFTWARE_SRC_XCUSTOM_H_
#define ROCC_SOFTWARE_SRC_XCUSTOM_H_

#define STR1(x) #x
#ifndef STR
#define STR(x) STR1(x)
#endif

#define XCUSTOM_OPCODE(x) XCUSTOM_OPCODE_##x
#define XCUSTOM_OPCODE_0 0b0001011
#define XCUSTOM_OPCODE_1 0b0101011
#define XCUSTOM_OPCODE_2 0b1011011
#define XCUSTOM_OPCODE_3 0b1111011

// Standard macro that passes rd, rs1, and rs2 via registers
#define ROCC_INSTRUCTION(x, rd, rs1, rs2, funct7) \
  ROCC_INSTRUCTION_R_R_R(x, rd, rs1, rs2, funct7)

// rd, rs1, and rs2 are data
#define ROCC_INSTRUCTION_R_R_R(x, rd, rs1, rs2, funct7)                                 \
  {                                                                                     \
    asm volatile(                                                                       \
        ".insn r " STR(XCUSTOM_OPCODE(x)) ", " STR(0x3) ", " STR(funct7) ", %0, %1, %2" \
        : "=r"(rd)                                                                      \
        : "r"(rs1), "r"(rs2));                                                          \
  }

#define ROCC_INSTRUCTION_0_R_R(x, rs1, rs2, funct7)                                     \
  {                                                                                     \
    asm volatile(                                                                       \
        ".insn r " STR(XCUSTOM_OPCODE(x)) ", " STR(0x3) ", " STR(funct7) ", x0, %0, %1" \
        :                                                                               \
        : "r"(rs1), "r"(rs2));                                                          \
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

#endif  // ROCC_SOFTWARE_SRC_XCUSTOM_H_
