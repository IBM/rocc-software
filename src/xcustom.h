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

#define CAT_(A, B) A ## B
#define CAT(A, B) CAT_(A, B)

#define ROCC_INSTRUCTION_RAW_R_R_R(x, rd, rs1, rs2, func7) \
  .insn r CAT(CUSTOM_, x), 7, func7, rd, rs1, rs2

#define ROCC_INSTRUCTION_RAW_0_R_R(x, rs1, rs2, func7) \
  .insn r CAT(CUSTOM_, x), 3, func7, x0, rs1, rs2


#define ROCC_INSTRUCTION(x, rd, rs1, rs2, func7) \
  ROCC_INSTRUCTION_R_R_R(x, rd, rs1, rs2, func7)

#define ROCC_INSTRUCTION_R_R_R(x, rd, rs1, rs2, func7)                 \
  {                                                                     \
    asm volatile(                                                       \
        ".insn r " STR(CAT(CUSTOM_, x)) ", " STR(0x7) ", " STR(func7) ", %0, %1, %2" \
        : "=r"(rd)                                                      \
        : "r"(rs1), "r"(rs2));                                          \
  }

#define ROCC_INSTRUCTION_0_R_R(x, rs1, rs2, func7)                     \
  {                                                                     \
    asm volatile(                                                       \
        ".insn r " STR(CAT(CUSTOM_, x)) ", " STR(0x3) ", " STR(func7) ", x0, %0, %1" \
        :: "r"(rs1), "r"(rs2));                                         \
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
