#ifndef OPCODES__ARRAY__H
#define OPCODES__ARRAY__H __FILE__

#include "t/Array.h"
#include "t/Block.h"
#include "vm/Frame.h"
#include "vm/OpCode.h"

#define OPC_NS_ARRAY              65 /*  A  */

#define OPC_ARRAY_COPY            99 /*  c  */
// nArrayDestReg :uint
// pSrcArray :t::Array*

#define OPC_ARRAY_GET_INT         73 /*  I  */
// nArraySrcReg :uint
// nIndex :uint
// nDestReg :uint

#define OPC_ARRAY_GET_LENGTH     108 /*  l  */
// nDestReg :uint
// nArraySrcReg :uint

#define OPC_ARRAY_GET_OBJECT      79 /*  O  */
// nArraySrcReg :uint
// nIndex :uint
// nDestReg :uint

#define OPC_ARRAY_NEW             33 /*  !  */
// nDestReg :uint
// nType :uint
// nSize :uint

#define OPC_ARRAY_PRINT          112 /*  p  */
// pArray :t::Array*

#define OPC_ARRAY_PRINTL          80 /*  P  */
// pArray :t::Array*

#define OPC_ARRAY_REVERSE        114 /*  r  */
// nArraySrcReg :uint
// nStartIndex :uint
// nLength :uint

#define OPC_ARRAY_REVERSE_ALL     82 /*  R  */
// nArraySrcReg :uint

#define OPC_ARRAY_SET_INT        105 /*  i  */
// nArraySrcReg :t::Array*
// nIndex :uint
// nValue :int

#define OPC_ARRAY_SLICE           35 /*  #  */
// nDestReg :uint
// pArray :t::Array*
// nStartIndex :uint
// nLength :uint
// nStep :uint

namespace opcodes
{
   /**
    * @brief A class that runs array opcodes.
    */
   class Array
   {
      /**
       * @brief Runs opcodes belonging to OPC_NS_ARRAY.
       *
       * @param pFrame The current frame.
       * @param pOpCode The opcode to run.
       * @param pArguments An array of values as arguments.
       */
      public: static bool run (vm::Frame* pFrame, vm::OpCode* pOpCode, t::Value* pArguments);
   };
}

#endif
