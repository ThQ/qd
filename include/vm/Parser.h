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

namespace vm
{
   /**
    * A SOP parser.
    *
    * @todo Rename the methods to be more accurate.
    * @todo Use flex !
    */
   class Parser
   {
      /**
       * Parses the arguments of an opcode.
       *
       * @param content The content in which to find the arguments.
       * @param start Where to start parsing.
       * @param end Where to end.
       * @param arguments An array of @cls{t::Object} that will contain all the arguments.
       * @return The number of arguments found.
       */
      public: static UInt parse_arguments(std::string content, ULong start, ULong end, t::Object**& arguments);

      /**
       * Tries to find an opcode and its namespace in a string content.
       *
       * @param opc A pointer to an empty @cls{vm::OpCode} that will be filled.
       * @param content The text content.
       * @param start At which position to start to parser in the text content.
       * @param end Where to stop.
       * @return At wich position we must try to find the opcode arguments.
       */
      public: static ULong parse_line(vm::OpCode* opc, std::string content, ULong start, ULong end);

      /**
       * Parses a text content so as to find opcode calls.
       *
       * @param content The content to parser.
       * @param blocks A pointer to a @cls{t::Block} array that will contain all the blocks found.
       * @return The number of blocks found.
       */
      public: static ULong parse_lines(std::string content, t::Block**& blocks);
   };
}

#endif
