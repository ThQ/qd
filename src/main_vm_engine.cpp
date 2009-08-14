#include "vm/Engine.h"
#include "Stats.h"

int main(int argc, char** argv){


// registers:size 2 0 1
vm::OpCode* pOpc__1 = new vm::OpCode(OPC_NS_REGISTERS, OPC_REGISTERS_SIZE);
pOpc__1->size_arguments(3);
pOpc__1->set_argument(0, t::INT_TYPE, (t::Value)2);
pOpc__1->set_argument(1, t::INT_TYPE, (t::Value)0);
pOpc__1->set_argument(2, t::INT_TYPE, (t::Value)1);


// registers:set_int 0 0
vm::OpCode* pOpc__2 = new vm::OpCode(OPC_NS_REGISTERS, OPC_REGISTERS_SET_INT);
pOpc__2->size_arguments(2);
pOpc__2->set_argument(0, t::INT_TYPE, (t::Value)0);
pOpc__2->set_argument(1, t::INT_TYPE, (t::Value)0);


// registers:set_int 1 0
vm::OpCode* pOpc__3 = new vm::OpCode(OPC_NS_REGISTERS, OPC_REGISTERS_SET_INT);
pOpc__3->size_arguments(2);
pOpc__3->set_argument(0, t::INT_TYPE, (t::Value)1);
pOpc__3->set_argument(1, t::INT_TYPE, (t::Value)0);


// list:new 0 13
vm::OpCode* pOpc__4 = new vm::OpCode(OPC_NS_LIST, OPC_LIST_NEW);
pOpc__4->size_arguments(2);
pOpc__4->set_argument(0, t::INT_TYPE, (t::Value)0);
pOpc__4->set_argument(1, t::INT_TYPE, (t::Value)13);


// int:lt 1 $i0 10
vm::OpCode* pOpc__5 = new vm::OpCode(OPC_NS_INT, OPC_INT_LT);
pOpc__5->size_arguments(3);
pOpc__5->set_argument(0, t::INT_TYPE, (t::Value)1);
pOpc__5->set_argument(1, t::REGISTER_VALUE_TYPE, new t::RegisterObject(t::INT_TYPE, 0));
pOpc__5->set_argument(2, t::INT_TYPE, (t::Value)10);


// jump:unless $i1 9
vm::OpCode* pOpc__6 = new vm::OpCode(OPC_NS_JUMP, OPC_JUMP_UNLESS);
pOpc__6->size_arguments(2);
pOpc__6->set_argument(0, t::REGISTER_VALUE_TYPE, new t::RegisterObject(t::INT_TYPE, 1));
pOpc__6->set_argument(1, t::INT_TYPE, (t::Value)9);


// list:push_int 0 $i0
vm::OpCode* pOpc__7 = new vm::OpCode(OPC_NS_LIST, OPC_LIST_PUSH_INT);
pOpc__7->size_arguments(2);
pOpc__7->set_argument(0, t::INT_TYPE, (t::Value)0);
pOpc__7->set_argument(1, t::REGISTER_VALUE_TYPE, new t::RegisterObject(t::INT_TYPE, 0));


// int:add 0 $i0 1
vm::OpCode* pOpc__8 = new vm::OpCode(OPC_NS_INT, OPC_INT_ADD);
pOpc__8->size_arguments(3);
pOpc__8->set_argument(0, t::INT_TYPE, (t::Value)0);
pOpc__8->set_argument(1, t::REGISTER_VALUE_TYPE, new t::RegisterObject(t::INT_TYPE, 0));
pOpc__8->set_argument(2, t::INT_TYPE, (t::Value)1);


// jump:to 4
vm::OpCode* pOpc__9 = new vm::OpCode(OPC_NS_JUMP, OPC_JUMP_TO);
pOpc__9->size_arguments(1);
pOpc__9->set_argument(0, t::INT_TYPE, (t::Value)4);


// dummy:hello
vm::OpCode* pOpc__10 = new vm::OpCode(OPC_NS_DUMMY, OPC_DUMMY_HELLO);

// list:printl 0
vm::OpCode* pOpc__11 = new vm::OpCode(OPC_NS_LIST, OPC_LIST_PRINTL);
pOpc__11->size_arguments(1);
pOpc__11->set_argument(0, t::INT_TYPE, (t::Value)0);

t::Block* pBlock__0 = new t::Block();

vm::Engine* pEng = new vm::Engine();
pEng->size_opcodes(11);
pEng->set_opcode(0, pOpc__1);
pEng->set_opcode(1, pOpc__2);
pEng->set_opcode(2, pOpc__3);
pEng->set_opcode(3, pOpc__4);
pEng->set_opcode(4, pOpc__5);
pEng->set_opcode(5, pOpc__6);
pEng->set_opcode(6, pOpc__7);
pEng->set_opcode(7, pOpc__8);
pEng->set_opcode(8, pOpc__9);
pEng->set_opcode(9, pOpc__10);
pEng->set_opcode(10, pOpc__11);

pEng->size_blocks(1);
pEng->set_block(0, pBlock__0, 0, 11);
pEng->run();

delete pEng;

}

