#ifndef OPCODES__H
#define OPCODES__H __FILE__

#include "vm/Frame.h"
#include "vm/OpCode.h"

typdef enum opcodes
{
   NOP=0,

   // INT (8)
   I_ADD,
   I_SUB,
   I_MUL,
   I_DIV,
   I_MOD,
   I_XOR,
   I_LSHIFT,
   I_RSHIFT,

   // LONG (8)
   L_ADD,
   L_SUB,
   L_MUL,
   L_DIV,
   L_MOD,
   L_XOR,
   L_LSHIFT,
   L_RSHIFT,

   // FLOAT (5)
   F_ADD,
   F_SUB,
   F_MUL,
   F_DIV,
   F_MOD,

   // DOUBLE (5)
   D_ADD,
   D_SUB,
   D_MUL,
   D_DIV,
   D_MOD,

   // JUMP (14)
   JUMP_IF,
   JUMP_IF_L,
   JUMP_IF_EQ,
   JUMP_IF_EQ_L
   JUMP_IF_NE,
   JUMP_IF_NE_L,
   JUMP_IF_GT,
   JUMP_IF_GT_L,
   JUMP_IF_GE,
   JUMP_IF_GE_L,
   JUMP_IF_LT,
   JUMP_IF_LT_L,
   JUMP_IF_LE,
   JUMP_IF_LE_L,

   // RETURN (15)
   RETURN,
   RETURN_IF,
   RETURN_IF_L,
   RETURN_IF_EQ,
   RETURN_IF_EQ_L,
   RETURN_IF_NE,
   RETURN_IF_NE_L,
   RETURN_IF_GT,
   RETURN_IF_GT_L,
   RETURN_IF_GE,
   RETURN_IF_GE_L,
   RETURN_IF_LT,
   RETURN_IF_LT_L,
   RETURN_IF_LE,
   RETURN_IF_LE_L,

   // REGISTERS (3)
   COPY,
   COPY_WIDE,
   COPY_OBJECT,
   SIZE,

   // OBJECTS (3)
   NEW,
   CALL,
   CALL_WIDE,

   // ARRAY (8)
   ARR_NEW,
   ARR_SET,
   ARR_SET_WIDE
   ARR_GET,
   ARR_GET_WIDE,
   ARR_LEN,
   ARR_SLICE,
   ARR_COPY,

   // LIST (8)
   LST_NEW,
   LST_SET,
   LST_SET_WIDE,
   LST_GET,
   LST_GET_WIDE,
   LST_LEN,
   LST_SLICE,
   LST_COPY,

   // HASH (5)
   HSH_NEW,
   HSH_SET,
   HSH_SET_WIDE,
   HSH_GET,
   HSH_GET_WIDE,

   // EXCEPTION ()
   THROW,

   DEBUG,

   // TOTAL = 30
}

#define OPCODE_FUNCTION(_name_) _name_ (vm::Frame* FRAME, vm::OpCode* OPCODE, t::Value* ARGUMENTS)

#endif
