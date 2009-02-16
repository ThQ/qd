#ifndef SVM_OPCODE_H
#define SVM_OPCODE_H


#define OPC_NS_NIL      59  /*  ;  */

// [!opcodes:constants]

#include <string>
#include <unicode/unistr.h>
#include "debug.h"
#include "svm/Object.h"

namespace svm
{
   class OpCode
   {
      public: UInt argc;
      public: Object** argv;
      public: std::string content;
      public: OpCode* next_opcode;
      public: UShort type;
      public: UShort method;

      public: OpCode();
   };
}

#endif
