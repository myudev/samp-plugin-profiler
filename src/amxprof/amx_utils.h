// Copyright (c) 2013-2015 Zeex
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
//
// 1. Redistributions of source code must retain the above copyright notice,
//    this list of conditions and the following disclaimer.
// 2. Redistributions in binary form must reproduce the above copyright notice,
//    this list of conditions and the following disclaimer in the documentation
//    and/or other materials provided with the distribution.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
// ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
// LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
// CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
// SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
// INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
// CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
// ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
// POSSIBILITY OF SUCH DAMAGE.

#ifndef AMXPROF_AMX_UTILS_H
#define AMXPROF_AMX_UTILS_H

#include "amx_types.h"

namespace amxprof {

enum {
  OP_NONE,         OP_LOAD_PRI,     OP_LOAD_ALT,
  OP_LOAD_S_PRI,   OP_LOAD_S_ALT,   OP_LREF_PRI,
  OP_LREF_ALT,     OP_LREF_S_PRI,   OP_LREF_S_ALT,
  OP_LOAD_I,       OP_LODB_I,       OP_CONST_PRI,
  OP_CONST_ALT,    OP_ADDR_PRI,     OP_ADDR_ALT,
  OP_STOR_PRI,     OP_STOR_ALT,     OP_STOR_S_PRI,
  OP_STOR_S_ALT,   OP_SREF_PRI,     OP_SREF_ALT,
  OP_SREF_S_PRI,   OP_SREF_S_ALT,   OP_STOR_I,
  OP_STRB_I,       OP_LIDX,         OP_LIDX_B,
  OP_IDXADDR,      OP_IDXADDR_B,    OP_ALIGN_PRI,
  OP_ALIGN_ALT,    OP_LCTRL,        OP_SCTRL,
  OP_MOVE_PRI,     OP_MOVE_ALT,     OP_XCHG,
  OP_PUSH_PRI,     OP_PUSH_ALT,     OP_PUSH_R,
  OP_PUSH_C,       OP_PUSH,         OP_PUSH_S,
  OP_POP_PRI,      OP_POP_ALT,      OP_STACK,
  OP_HEAP,         OP_PROC,         OP_RET,
  OP_RETN,         OP_CALL,         OP_CALL_PRI,
  OP_JUMP,         OP_JREL,         OP_JZER,
  OP_JNZ,          OP_JEQ,          OP_JNEQ,
  OP_JLESS,        OP_JLEQ,         OP_JGRTR,
  OP_JGEQ,         OP_JSLESS,       OP_JSLEQ,
  OP_JSGRTR,       OP_JSGEQ,        OP_SHL,
  OP_SHR,          OP_SSHR,         OP_SHL_C_PRI,
  OP_SHL_C_ALT,    OP_SHR_C_PRI,    OP_SHR_C_ALT,
  OP_SMUL,         OP_SDIV,         OP_SDIV_ALT,
  OP_UMUL,         OP_UDIV,         OP_UDIV_ALT,
  OP_ADD,          OP_SUB,          OP_SUB_ALT,
  OP_AND,          OP_OR,           OP_XOR,
  OP_NOT,          OP_NEG,          OP_INVERT,
  OP_ADD_C,        OP_SMUL_C,       OP_ZERO_PRI,
  OP_ZERO_ALT,     OP_ZERO,         OP_ZERO_S,
  OP_SIGN_PRI,     OP_SIGN_ALT,     OP_EQ,
  OP_NEQ,          OP_LESS,         OP_LEQ,
  OP_GRTR,         OP_GEQ,          OP_SLESS,
  OP_SLEQ,         OP_SGRTR,        OP_SGEQ,
  OP_EQ_C_PRI,     OP_EQ_C_ALT,     OP_INC_PRI,
  OP_INC_ALT,      OP_INC,          OP_INC_S,
  OP_INC_I,        OP_DEC_PRI,      OP_DEC_ALT,
  OP_DEC,          OP_DEC_S,        OP_DEC_I,
  OP_MOVS,         OP_CMPS,         OP_FILL,
  OP_HALT,         OP_BOUNDS,       OP_SYSREQ_PRI,
  OP_SYSREQ_C,     OP_FILE,         OP_LINE,
  OP_SYMBOL,       OP_SRANGE,       OP_JUMP_PRI,
  OP_SWITCH,       OP_CASETBL,      OP_SWAP_PRI,
  OP_SWAP_ALT,     OP_PUSH_ADR,     OP_NOP,
  OP_SYSREQ_D,     OP_SYMTAG,       OP_BREAK,
  NUM_OPCODES
};

cell RelocateOpcode(cell opcode);

Address GetNativeAddress(AMX *amx, NativeTableIndex index);
Address GetPublicAddress(AMX *amx, PublicTableIndex index);

const char *GetNativeName(AMX *amx, NativeTableIndex index);
const char *GetPublicName(AMX *amx, PublicTableIndex index);

Address GetReturnAddress(AMX *amx, Address frame);
Address GetCalleeAddress(AMX *amx, Address frame);

} // naemspace amxprof

#endif // !AMXPROF_AMX_UTILS_H
