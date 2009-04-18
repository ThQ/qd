#include "t/Block.h"

namespace NS_TYPE
{
   Block::Block()
   {
      this->argc = 0;
      this->argv = 0;
      this->exception = NULL;
      this->exception_handler = NULL;
      //this->first_opcode = NULL;
      //this->last_opcode = NULL;
      this->opcodes = 0;
      this->opcode_count = 0;
      //this->name = "";
      this->references = 0;
   }

   Block::~Block()
   {
      /*for (unsigned long i = 0 ; i < this->line_count ; ++ i)
      {
         //delete this->lines[i];
      }
      */
      free(this->opcodes);
      if (this->exception != NULL) T_OBJECT::drop(this->exception);
   }

   void
   Block::append(vm::OpCode* opc)
   {
      // @TODO : Too much REALLOC
      ++ this->opcode_count;
      this->opcodes = (vm::OpCode**)REALLOC(this->opcodes, sizeof(vm::OpCode*) * this->opcode_count);
      this->opcodes[this->opcode_count - 1] = opc;
   }

   void
   Block::clear()
   {
      this->opcode_count = 0;
      this->opcodes = (vm::OpCode**)REALLOC(this->opcodes, 0);
   }

   ULong
   Block::count()
   {
      return this->opcode_count;
   }

   vm::OpCode*
   Block::get(ULong at)
   {
      ASSERT(at < this->opcode_count, "[svm::Block::get] Index [%lu] out of range [0:%lu].\n", at, this->opcode_count -1);

      return this->opcodes[at];
   }

   void
   Block::set_exception_handler(Block* block)
   {
      T_OBJECT::drop_safe(this->exception_handler);
      T_OBJECT::pick(block);
      this->exception_handler = block;
   }

   void
   Block::throw_exception(T_OBJECT* e)
   {
      T_OBJECT::drop_safe(this->exception);
      T_OBJECT::pick(e);
      this->exception = e;
   }
}
