#include "t/Bool.h"

namespace t
{
   T_OBJECT* tBOOL;
   T_OBJECT* gTRUE = NULL;
   T_OBJECT* gFALSE = NULL;

   Bool::Bool()
   {
      this->value = false;
      this->references = 0;
      this->set_class(NS_TYPE::tBOOL);
   }

   T_OBJECT*
   Bool::build(bool b)
   {
      Bool* result = new Bool();
      result->value = b == true;
      return (T_OBJECT*)result;
   }

   T_OBJECT*
   Bool::build(int i)
   {
      Bool* result = new Bool();
      result->value = i != 0;
      return (T_OBJECT*)result;
   }

   T_OBJECT*
   Bool::cast_to_string(T_OBJECT* b)
   {
      Bool::assert(b);

      T_STRING* s = new T_STRING();
      s->value = ((Bool*)b)->value == true ? (char*)"True" : (char*)"False";
      return (T_OBJECT*)s;
   }

   T_OBJECT*
   Bool::copy(T_OBJECT* b)
   {
      Bool::assert(b);

      Bool* result = new Bool();
      result->value = ((Bool*)b)->value;

      return result;
   }

   bool
   Bool::is_false(T_OBJECT* b)
   {
      return b == NS_TYPE::gFALSE;
   }

   bool
   Bool::is_true(T_OBJECT* b)
   {
      return b == NS_TYPE::gTRUE;
   }

   void
   Bool::print(T_OBJECT* b)
   {
      printf(b == NS_TYPE::gTRUE ? "True" : "False");
   }

   void
   Bool::print_line(T_OBJECT* b)
   {
      printf(b == NS_TYPE::gTRUE ? "True\n" : "False\n");
   }

   T_OBJECT*
   Bool::reverse(T_OBJECT* b)
   {
      return b == NS_TYPE::gTRUE ? NS_TYPE::gFALSE : NS_TYPE::gTRUE;
   }
}
