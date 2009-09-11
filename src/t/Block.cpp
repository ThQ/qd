#include "t/Block.h"

namespace t
{
   VM_CLASS__NEW(cBLOCK, t::Block, t::BLOCK_TYPE, &cOBJECT);

   Block::Block ()
   {
      Memory_ALLOC(this->arguments, t::Value, 16);
      this->argument_count = 0;
      this->argument_types = 0;
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
   }

   void
   Block::print_arguments ()
   {
      for (uint i = 0 ; i < this->count_arguments(); ++i)
      {
         INTERNAL(
               "<Block:0x%x> ARGUMENT (.at 0x%x, .equals=%d)\n",
               (uint)this,
               i,
               (int)this->get_argument(i)
         );
      }
   }

}
