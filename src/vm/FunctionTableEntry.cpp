#include "vm/FunctionTableEntry.h"

namespace NS_VM
{
   FunctionTableEntry::FunctionTableEntry()
   {
      this->function = NULL;
      this->signature = "";
   }

   FunctionTableEntry::FunctionTableEntry(t::Function* func)
   {
      this->function = NULL;
      this->signature = "";
      this->set_function(func);
   }

   FunctionTableEntry::~FunctionTableEntry()
   {
      // @TODO: Better do a final clean-up in opcode.h maybe ??
      t::Object::drop_safe(this->function);
   }

   void
   FunctionTableEntry::set_function(t::Function* func)
   {
      //INTERNAL("FunctionTableEntry::set_function(Function*)\n");
      t::Function::assert(func);
      t::Object::drop_safe(this->function);
      this->function = func;
      t::Object::pick(func);

      this->signature.assign(func->name);
      for(UInt i = 0 ; i < func->arguments_count ; ++i)
      {
         t::Variable::assert(func->arguments[i]);
         t::Class::assert(((t::Variable*)func->arguments[i])->object_type);

         t::Variable* func_var_arg = (t::Variable*)func->arguments[i];
         this->signature += ",";
         this->signature += ((t::Class*)(func_var_arg->object_type))->name;
      }

      //printf("+ method (%s) > %s \n", func->name.c_str(), this->signature.c_str());

      //INTERNAL("/ FunctionTableEntry::set_function(Function*)\n");
   }
}
