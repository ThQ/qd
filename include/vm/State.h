#ifndef VM__STATE__H
#define VM__STATE__H __FILE__

namespace vm
{
   class State
   {
      public: t::Block**      blocks;           ///< An array of @cls{t::Block}.
      public: ulong           block_count;      ///< The number of blocks.
      public: CallStack       call_stack;       ///< Call stack.
      public: vm::Class**     classes;          ///< A class table.
      public: ulong           class_count;      ///< How many classes.
      public: t::Block*       current_block;    ///< The block being currently run.
      public: t::Function**   functions;        ///< A function table.
      public: ulong           function_count;   ///< How many functions.
      public: vm::OpCode**    opcodes;          ///< An array of @cls{vm::OpCode}.
      public: uint            opcode_count;     ///< The number of opcodes.
   };
}

#endif
