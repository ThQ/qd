#include "t/Block.h"

namespace t
{
   VM_CLASS__NEW(cBLOCK, t::Block, t::BLOCK_TYPE, &cOBJECT);

   Block::Block ()
   {
      this->argument_count = 0;
      this->argument_types = 0;
      this->exception = NULL;
      this->exception_handler = NULL;
      this->type = t::BLOCK_TYPE;
      this->klass = &cBLOCK;
      this->opcodes = 0;
      this->opcode_count = 0;
   }

   Block::~Block ()
   {
      this->destroy();
   }

   void
   Block::__delete__ (Value pObject)
   {
      ((t::Block*)pObject)->destroy();
   }

   Value
   Block::__new__ ()
   {
      return new Block();
   }

   void
   Block::__print__ (Value pObject)
   {

   }

   void
   Block::__print_line__ (Value pObject)
   {

   }

   void
   Block::append (vm::OpCode* opc)
   {
      ++ this->opcode_count;
      Memory_REALLOC(this->opcodes, vm::OpCode*, this->opcode_count);
      this->opcodes[this->opcode_count - 1] = opc;
   }

   ulong
   Block::count ()
   {
      return this->opcode_count;
   }

   void
   Block::define_arguments (uchar nCount, uchar* pArgs)
   {
      ASSERT(this->argument_types == NULL, "Arguments have already been set.");

      this->argument_types = pArgs;
      this->argument_count = nCount;
   }

   void
   Block::destroy ()
   {
      // Opcodes are actually freed in vm::Engine

      if (this->exception != NULL)
      {
         this->exception->drop();
      }
   }

   vm::OpCode*
   Block::get (ulong at)
   {
      ASSERT(
            at < this->opcode_count,
            "[svm::Block::get] Index [%lu] out of range [0:%lu].\n",
            at,
            this->opcode_count -1
      );

      return this->opcodes[at];
   }

   void
   Block::set_exception_handler (Block* block)
   {
      ASSERT_NOT_NULL(block);

      if (this->exception_handler != NULL)
      {
         this->exception_handler->drop();
      }
      block->pick();
      this->exception_handler = block;
   }

   void
   Block::throw_exception (Exception* pException)
   {
      if (this->exception != NULL)
      {
         this->exception->drop();
      }
      pException->pick();
      this->exception = pException;
   }
}
