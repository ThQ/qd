#include "svm/ListUtil.h"

namespace svm
{
   void
   ListUtil::print(List* list)
   {
      printf("[");
      for (UInt i = 0 ; i < list->length ; ++i)
      {
         if (i > 0)
         {
            printf(", ");
         }

         Object* obj = list->items[i];
         if (obj->cls == svm::bool_type)
         {
               svm::Bool::print(obj);
         }
         else if(obj->cls == svm::int_type)
         {
               svm::Int::print(obj);
         }
         else if(obj->cls == svm::string_type)
         {
               printf("\"");
               svm::String::print(obj);
               printf("\"");
         }
         else if(obj->cls == svm::list_type)
         {
            svm::ListUtil::print((svm::List*)obj);
         }
         else
         {
            svm::Object::print(obj);
         }
      }
      printf("]");
   }
}
