#include "util/List.h"

namespace NS_UTIL
{
   void
   List::print(t::List* list)
   {
      printf("[");
      for (UInt i = 0 ; i < list->length ; ++i)
      {
         if (i > 0)
         {
            printf(", ");
         }

         t::Object* obj = list->items[i];
         if (obj->cls == t::tBOOL)
         {
               t::Bool::print(obj);
         }
         else if(obj->cls == t::tINT)
         {
               t::Int::print(obj);
         }
         else if(obj->cls == t::tSTRING)
         {
               printf("\"");
               t::String::print(obj);
               printf("\"");
         }
         else if(obj->cls == t::tLIST)
         {
            util::List::print((t::List*)obj);
         }
         else
         {
            t::Object::print(obj);
         }
      }
      printf("]");
   }
}
