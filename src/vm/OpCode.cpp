#include "vm/OpCode.h"

namespace vm
{
   OpCode::OpCode()
   {
      this->argc = 0;
      this->argv = NULL;
      this->content = "";
      this->type = 0;
      this->method = 0;
      this->next_opcode = NULL;
   }
}
