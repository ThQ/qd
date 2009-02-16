#ifndef SVM_BLOCK_H
#define SVM_BLOCK_H

#include "debug.h"
#include "svm/Exception.h"
#include "svm/Heap.h"
#include "svm/Object.h"
#include "svm/OpCode.h"
#include "types.h"


namespace svm
{
   class Block : public Object
   {
      public: ULong argc;
      public: Object** argv;
      public: Object* exception;
      public: Block* exception_handler;
      //public: OpCode* first_opcode;
      public: Heap heap;
      //public: OpCode* last_opcode;
      public: OpCode** opcodes;
      public: ULong opcode_count;
      public: std::string name;

      public: Block();
      public: ~Block();
      public: void append(OpCode* opc);
      public: void append_line(UnicodeString* line);
      public: void clear();
      public: ULong count();
      public: OpCode* get(ULong at);
      public: void set_exception_handler(Block* block);
      public: void throw_exception(Object* exception);

   };
}

#endif
