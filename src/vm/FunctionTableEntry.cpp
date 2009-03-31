#include "svm/FunctionTableEntry.h"

namespace svm
{
   FunctionTableEntry::FunctionTableEntry()
   {
      this->function = NULL;
      this->signature = "";
   }

   FunctionTableEntry::FunctionTableEntry(Function* func)
   {
      this->function = NULL;
      this->signature = "";
      this->set_function(func);
   }

   FunctionTableEntry::~FunctionTableEntry()
   {
      // Better do a final clean-up in opcode.h maybe
      // SVM_DROP_SAFE(this->function);
   }

   void
   FunctionTableEntry::set_function(Function* func)
   {
      //INTERNAL("FunctionTableEntry::set_function(Function*)\n");
      SVM_ASSERT_FUNCTION(func);
      SVM_DROP_SAFE(this->function);
      this->function = func;
      SVM_PICK(func);

      //ULong signature_len = strlen(func->name.length());
      /*for (UInt i = 0 ; i < func->arguments_count ; ++i)
      {
         signature_len += ((Class*)((Variable*)func->arguments[i])->object_type)->name.length() + 1; // plus ","
      }
      */

      this->signature.assign(func->name);
      for(UInt i = 0 ; i < func->arguments_count ; ++i)
      {
         SVM_CHECK_VARIABLE(func->arguments[i]);
         SVM_CHECK_CLASS(((Variable*)func->arguments[i])->object_type);

         this->signature += ",";
         this->signature += ((Class*)((Variable*)func->arguments[i])->object_type)->name;
      }

      //printf("+ method (%s) > %s \n", func->name.c_str(), this->signature.c_str());

      //INTERNAL("/ FunctionTableEntry::set_function(Function*)\n");
   }
}
