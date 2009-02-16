#include "svm/Block.h"

namespace svm
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
      DEBUG("Are blocks really destroyed here ?");
      /*for (unsigned long i = 0 ; i < this->line_count ; ++ i)
      {
         //delete this->lines[i];
      }
      */
      free(this->opcodes);
      if (this->exception != NULL) SVM_DROP(this->exception);
   }

   void
   Block::append(OpCode* opc)
   {
      ++ this->opcode_count;
      this->opcodes = (OpCode**)REALLOC(this->opcodes, sizeof(OpCode*) * this->opcode_count);
      this->opcodes[this->opcode_count - 1] = opc;
   }

   void
   Block::clear()
   {
      this->opcode_count = 0;
      this->opcodes = (OpCode**)realloc(this->opcodes, 0);
   }

   ULong
   Block::count()
   {
      return this->opcode_count;
   }

   OpCode*
   Block::get(ULong at)
   {
      ASSERT(at < this->opcode_count, "[svm::Block::get] Index [%lu] out of range [0:%lu].\n", at, this->opcode_count -1);

      return this->opcodes[at];
   }

   void
   Block::set_exception_handler(Block* block)
   {
      if (this->exception_handler != NULL)
      {
         SVM_DROP(this->exception_handler);
      }

      SVM_PICK(block);
      this->exception_handler = block;
   }

   void
   Block::throw_exception(Object* e)
   {
      if (this->exception != NULL)
      {
         SVM_DROP(this->exception);
      }
      SVM_PICK(e);
      this->exception = e;
   }
}
