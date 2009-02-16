#include "svm/Bool.h"

namespace svm
{
   Object* bool_type;
   Object* True = NULL;
   Object* False = NULL;

   Bool::Bool()
   {
      this->value = false;
      this->references = 0;
      this->set_class(svm::bool_type);
   }

   Object*
   Bool::build(bool b)
   {
      Bool* result = new Bool();
      result->value = b == true;
      return (Object*)result;
   }

   Object*
   Bool::build(int i)
   {
      Bool* result = new Bool();
      result->value = i != 0;
      return (Object*)result;
   }

   Object*
   Bool::cast_to_string(Object* b)
   {
      SVM_ASSERT_BOOL(b);

      String* s = new String();
      s->value = ((Bool*)b)->value == true ? (char*)"True" : (char*)"False";
      return (Object*)s;
   }

   Object*
   Bool::copy(Object* b)
   {
      if (!Bool::check(b))
      {
         return NULL;
      }
      Bool* result = new Bool();
      result->value = ((Bool*)b)->value;

      return result;
   }

   bool
   Bool::check(Object* b)
   {
      SVM_ASSERT_BOOL(b);

      return ((svm::Bool*)b)->cls == svm::bool_type;
   }

   bool
   Bool::is_false(Object* b)
   {
      return b == svm::False;
   }

   bool
   Bool::is_true(Object* b)
   {
      return b == svm::True;
   }

   void
   Bool::print(Object* b)
   {
      if (b == svm::True)
      {
         printf("True");
      }
      else
      {
         printf("False");
      }
   }

   void
   Bool::print_line(Object* b)
   {
      if (b == svm::True)
      {
         printf("True\n");
      }
      else
      {
         printf("False\n");
      }
   }

   Object*
   Bool::reverse(Object* b)
   {
      return b == svm::True ? svm::False : svm::True;
   }
}

