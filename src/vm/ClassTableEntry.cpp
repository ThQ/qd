#include "t/ClassTableEntry.h"

namespace NS_VM
{
   ClassTableEntry::ClassTableEntry()
   {
      this->cls = NULL;
   }

   ClassTableEntry::~ClassTableEntry()
   {
      //printf("Class name: %s @%lu / Ref count: %d\n", ((svm::Class*)this->cls)->name.c_str(), (ULong)this->cls, this->cls->references);
      // SVM_DROP_SAFE(((svm::Class*)this->cls)->parent_class); Why would we drop the parent class ?
      t::Object::drop_safe(this->cls);
      this->cls = NULL;
   }

   void
   ClassTableEntry::set_class(t::Class* cls)
   {
      ASSERT(cls != NULL, "Null class object.");
      if (cls != NULL)
      {
         t::Object::drop_safe(this->cls);
         this->cls = cls;
         t::Object::pick(cls);
      }
   }
}
