#ifndef VM_PARSER_H
#define VM_PARSER_H

#include <math.h>
#include <string>

#include "t/Block.h"
#include "t/Bool.h"
#include "t/HeapObject.h"
#include "t/Int.h"
#include "t/Object.h"
#include "t/String.h"
#include "vm/OpCode.h"

namespace NS_VM
{
   class Parser
   {
      public: static UInt parse_arguments(std::string content, ULong start, ULong end, t::Object**& arguments);
      public: static ULong parse_line(vm::OpCode* opc, std::string content, ULong start, ULong end);
      public: static ULong parse_lines(std::string content, t::Block**& blocks);
   };
}

#endif
