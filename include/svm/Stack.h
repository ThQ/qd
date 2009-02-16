#ifndef SVM_STACK_H
#define SVM_STACK_H

#include "svm/Block.h"
#include "svm/Object.h"
#include "svm/String.h"

namespace svm
{
   class Stack
   {
      public: Block** blocks;
      public: unsigned long block_count;

      public: Stack();
      public: ~Stack();

      public: void append(Block* block);
      public: unsigned long count();
      public: Block* get(unsigned long at);
      public: Block* pop();
      public: void print();
   };
}

#endif
