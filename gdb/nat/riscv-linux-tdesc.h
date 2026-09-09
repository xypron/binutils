/* GNU/Linux/RISC-V native target description support for GDB.
   Copyright (C) 2020-2026 Free Software Foundation, Inc.

   This file is part of GDB.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

#ifndef GDB_NAT_RISCV_LINUX_TDESC_H
#define GDB_NAT_RISCV_LINUX_TDESC_H

#include "arch/riscv.h"
#include "asm/ptrace.h"

/* Determine XLEN and FLEN for the LWP identified by TID, and return a
   corresponding features object.  */
struct riscv_gdbarch_features riscv_linux_read_features (int tid);

#define RISCV_MAX_VLENB (8192)

/* This must be the struct describing the fixed-size header that precedes
   the vector register data (v0..v31) in the ptrace wire format used for
   PTRACE_GETREGSET/PTRACE_SETREGSET with NT_RISCV_VECTOR, i.e.
   "struct __riscv_v_regset_state" ({ vstart, vl, vtype, vcsr, vlenb,
   vreg[] }), and NOT the similarly named, but different,
   "struct __riscv_v_ext_state" ({ vstart, vl, vtype, vcsr, vlenb,
   datap }), which some branches/commits of the Linux kernel called
   "struct __riscv_v_state".  Using a macro to stand-in for that struct
   type to make it easier to modify in a single place, if compiling
   against older Linux kernel headers that lack the definition of
   struct __riscv_v_regset_state.  */
#ifndef RISCV_VECTOR_STATE_T
#define RISCV_VECTOR_STATE_T struct __riscv_v_regset_state
#endif

/* Struct for use in ptrace() calls for vector CSRs/registers */
struct __riscv_vregs
{
  RISCV_VECTOR_STATE_T vstate;
  gdb_byte data[RISCV_MAX_VLENB * 32]; /* data will arrive packed, VLENB bytes per element, not necessarily RISCV_MAX_VLENB bytes per element */
};

#define VCSR_MASK_VXSAT 0x1
#define VCSR_POS_VXSAT 0
#define VCSR_MASK_VXRM 0x3
#define VCSR_POS_VXRM 1


#endif /* GDB_NAT_RISCV_LINUX_TDESC_H */
