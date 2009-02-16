#ifndef SVM_PARSER_H
#define SVM_PARSER_H

#include <math.h>
#include <string>

#include "memory.h"
#include "svm/Block.h"
#include "svm/Bool.h"
#include "svm/HeapObject.h"
#include "svm/Int.h"
#include "svm/Object.h"
#include "svm/OpCode.h"
#include "svm/String.h"
#include "types.h"

namespace svm
{
   class Parser
   {
      public: static UInt parse_arguments(std::string content, ULong start, ULong end, svm::Object**& arguments);
      public: static ULong parse_line(svm::OpCode* opc, std::string content, ULong start, ULong end);
      public: static ULong parse_lines(std::string content, svm::Block**& blocks);
   };
}

#endif
