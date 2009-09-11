#ifndef OPCODES__INT__H
#define OPCODES__INT__H __FILE__

#define OPC_NS_INT           105 /*  i  */
#define OPC_INT_ADD           43 /*  +  */
#define OPC_INT_DECR          68 /*  D  */ ///< @todo IMPLEMENT
#define OPC_INT_DIV           47 /*  /  */
#define OPC_INT_INCR          73 /*  I  */
#define OPC_INT_LE           108 /*  l  */
#define OPC_INT_LT            60 /*  <  */
#define OPC_INT_MOD           37 /*  %  */
#define OPC_INT_MUL           42 /*  *  */
#define OPC_INT_PRINT        112 /*  p  */
#define OPC_INT_PRINTL        80 /*  P */
#define OPC_INT_SUB           45 /*  -  */

#include "t/Block.h"
#include "t/RegisterObject.h"
#include "vm/Frame.h"
#include "vm/OpCode.h"

namespace opcodes
{
   enum int_opcodes { ADD = 43 };

   /**
    * @brief Runs the opcodes whose namespace is OPC_NS_INT.
    *
    * - OPC_INT_ADD__iii : Adds two integers and puts the result in an int register.
    * - OPC_INT_DIV__iii : Divides two integers and puts the result in an int register.
    * - OPC_INT_LE__iii : 1 is put in an int register if an int is lower or equal to another.
    * - OPC_INT_LT__ii : 1 is put in an int register if an int is lower than another int.
    * - OPC_INT_MUL__iii : Multiplies two integers and puts the result in an int register.
    * - OPC_INT_PRINT__i : Prints an integer to the console.
    * - OPC_INT_PRINTN__i : Prints an integer and a new line to the console.
    * - OPC_INT_SUB__iii : Subtracts two integers and puts the result in an int register.
    */
   class Int
   {
      /**
       * @brief Runs an opcode belonging to OPC_NS_INT.
       *
       * @param pBlock The current block.
       * @param pOpc The opcode being currently run.
       * @param pArguments An array of values to be used as arguments.
       */
      public: static bool run (vm::Frame* pFrame, vm::OpCode* pOpc, t::Value* pArguments);
   };
}

#endif
