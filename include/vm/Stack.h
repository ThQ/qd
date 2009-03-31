#ifndef VM_STACK_H
#define VM_STACK_H

#include "t/Block.h"
#include "t/Object.h"
#include "t/String.h"

namespace NS_VM
{
   class Stack
   {
      public: t::Block** blocks;
      public: ULong block_count;

      public: Stack();
      public: ~Stack();

      public: void append(t::Block* block);
      public: ULong count();
      public: t::Block* get(ULong at);
      public: t::Block* pop();
      public: void print();
   };
}

#endif
