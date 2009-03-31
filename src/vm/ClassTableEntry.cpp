#include "svm/ClassTableEntry.h"

namespace svm
{
   ClassTableEntry::ClassTableEntry()
   {
      this->cls = NULL;
   }

   ClassTableEntry::~ClassTableEntry()
   {
      //printf("Class name: %s @%lu / Ref count: %d\n", ((svm::Class*)this->cls)->name.c_str(), (ULong)this->cls, this->cls->references);
      SVM_DROP_SAFE(((svm::Class*)this->cls)->parent_class);
      SVM_DROP_SAFE(this->cls);
      this->cls = NULL;
   }

   void
   ClassTableEntry::set_class(Class* cls)
   {
      if (cls != NULL)
      {
         SVM_DROP_SAFE(this->cls);
         this->cls = cls;
         SVM_PICK(cls);
      }
      #ifdef _SHOW_WARNING_
      else
      {
         WARNING("svm::ClassTableEntry::set_Class(Class*) : Null class object.\n");
      }
      #endif
   }
}
