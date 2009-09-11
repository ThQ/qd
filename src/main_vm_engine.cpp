#include "vm/Engine.h"
#include "Stats.h"

int main(int argc, char** argv){


// registers:size 2 1 0
vm::OpCode* pOpc__1 = new vm::OpCode(OPC_NS_REGISTERS, OPC_REGISTERS_SIZE);
pOpc__1->size_arguments(3);
pOpc__1->set_argument(0, t::INT_TYPE, (t::Value)2);
pOpc__1->set_argument(1, t::INT_TYPE, (t::Value)1);
pOpc__1->set_argument(2, t::INT_TYPE, (t::Value)0);


// registers:set_int 0 99
vm::OpCode* pOpc__2 = new vm::OpCode(OPC_NS_REGISTERS, OPC_REGISTERS_SET_INT);
pOpc__2->size_arguments(2);
pOpc__2->set_argument(0, t::INT_TYPE, (t::Value)0);
pOpc__2->set_argument(1, t::INT_TYPE, (t::Value)99);


// registers:copy_int 1 0
vm::OpCode* pOpc__3 = new vm::OpCode(OPC_NS_REGISTERS, OPC_REGISTERS_COPY_INT);
pOpc__3->size_arguments(2);
pOpc__3->set_argument(0, t::INT_TYPE, (t::Value)1);
pOpc__3->set_argument(1, t::INT_TYPE, (t::Value)0);


// registers:copy_int_to_long 0 0
vm::OpCode* pOpc__4 = new vm::OpCode(OPC_NS_REGISTERS, OPC_REGISTERS_COPY_INT_TO_LONG);
pOpc__4->size_arguments(2);
pOpc__4->set_argument(0, t::INT_TYPE, (t::Value)0);
pOpc__4->set_argument(1, t::INT_TYPE, (t::Value)0);


// registers:print
vm::OpCode* pOpc__5 = new vm::OpCode(OPC_NS_REGISTERS, OPC_REGISTERS_PRINT);
t::Block* pBlock__0 = new t::Block();

vm::Engine* pEng = new vm::Engine();
pEng->size_opcodes(5);
pEng->set_opcode(0, pOpc__1);
pEng->set_opcode(1, pOpc__2);
pEng->set_opcode(2, pOpc__3);
pEng->set_opcode(3, pOpc__4);
pEng->set_opcode(4, pOpc__5);

pEng->size_blocks(1);
pEng->set_block(0, pBlock__0, 0, 5);

pEng->run();

delete pEng;

}

