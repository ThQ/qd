#ifndef VM__FRAME__H
#define VM__FRAME__H __FILE__


#include "t/Block.h"
#include "t/Exception.h"
#include "vm/RegisterPool.h"
#include "Memory.h"


namespace vm
{
   class Frame
   {
      public: t::Value*       arguments;
      public: uchar           argument_count;
      public: t::Block*       block;
      public: t::Exception*   exception;           ///< A pointer to a @cls{t::Exception} thrown, NULL otherwise.
      public: t::Block*       exception_handler;   ///< A pointer to @cls{t::Block} used as exception handler, NULL if none.
      public: vm::Frame*      parent_frame;
      public: RegisterPool    registers;

      public: Frame ();

      public: Frame (t::Block* pBlock);

      /**
       * @brief Destructor.
       */
      public: ~Frame ();

      /**
       * @brief Sets the exception handler for the block.
       *
       * @param block A pointer to a @cls{t::Block} to use as an exception handler.
       */
      public: void set_exception_handler (t::Block* block);

      /**
       * @brief Throws an exception inside the block.
       *
       * @param exception A pointer to a @cls{t::Object} that is a @cls{t::Exception} to throw.
       */
      public: inline void throw_exception (t::Object* exception)
      {
         t::Exception::assert(exception);
         this->throw_exception((t::Exception*)exception);
      }

      /**
       * @brief Throws an exception inside the block.
       *
       * @param exception A pointer to a @cls{t::Exception} to throw.
       */
      public: void throw_exception (t::Exception* exception);
   };
}

#endif
