#ifndef OPCODES__ARRAY__H
#define OPCODES__ARRAY__H __FILE__

#include "t/Array.h"
#include "t/Block.h"
#include "vm/OpCode.h"

#define OPC_NS_ARRAY          65 /*  A  */
#define OPC_ARRAY_GET_INT     73 /*  I  */
#define OPC_ARRAY_GET_OBJECT  79 /*  O  */
#define OPC_ARRAY_NEW         33 /*  !  */
#define OPC_ARRAY_PRINT      112 /*  p  */
#define OPC_ARRAY_PRINTL      80 /*  P  */
#define OPC_ARRAY_SET_INT    105 /*  i  */
#define OPC_ARRAY_SLICE       35 /*  #  */

namespace opcodes
{
   /**
    * @brief A class that runs array opcodes.
    *
    * * OPC_ARRAY_GET_INT[3]     (nArrayRegisterIndex :uint, nIndex :uint,nDestRegisterIndex :uint)
    * * OPC_ARRAY_GET_OBJECT[3]  (nArrayRegisterIndex :uint, nIndex :uint,nDestRegisterIndex :uint)
    * * OPC_ARRAY_NEW[3]         (dest_register :uint, type :uint, size :uint)
    * * OPC_ARRAY_PRINT[1]       (nArrayRegisterIndex :uint)
    * * OPC_ARRAY_PRINTL[1]      (nArrayRegisterIndex :uint)
    * * OPC_ARRAY_SET_INT[3]     (array_register_index :uint, index :uint, value :int)
    * * OPC_ARRAY_SLICE[4]       (nArrayRegister :uint, nStartIndex :uint, nLength :uint, nStep :uint)
    */
   class Array
   {
      /**
       * @brief Runs opcodes belonging to OPC_NS_ARRAY.
       *
       * @param pBlock The block being currently run.
       * @param pOpCode The opcode to run.
       * @param pArguments An array of values as arguments.
       */
      public: static bool run (t::Block* pBlock, vm::OpCode* pOpCode, t::Value* pArguments);
   };
}

#endif
