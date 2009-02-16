#include "svm/Int.h"

namespace svm
{
   Object* int_type = NULL;

   Int::Int()
   {
      this->references = 0;
      this->cls = svm::int_type;
      this->value = 0;
   }

   Object*
   Int::add(Object* base, Object* to_add)
   {
      SVM_ASSERT_INT(base);
      SVM_ASSERT_INT(to_add);

      long int f = (long int)(((Int*)base)->value + ((Int*)to_add)->value);
      return Int::build(f);
   }

   Object*
   Int::add_to(Object* &base, Object* to_add)
   {
      SVM_ASSERT_INT(base);
      SVM_ASSERT_INT(to_add);

      ((Int*)base)->value += ((Int*)to_add)->value;
      return base;
   }

   Object*
   Int::build()
   {
      Int* i = new Int();
      i->value = 0;
      return (Object*)i;
   }

   Object*
   Int::build(float value)
   {
      Int* result = new Int();
      result->value = (long int)value;
      return (Object*)result;
   }

   Object*
   Int::build(long value)
   {
      Int* result = new Int();
      result->value = value;
      return (Object*)result;
   }

   Object*
   Int::build(Object* obj)
   {
      SVM_ASSERT_INT(obj);

      Int* result = new Int();
      result->value = ((Int*)obj)->value;

      return (Object*)result;
   }

   Object*
   Int::cast_to_string(Object* i)
   {
      SVM_ASSERT_INT(i);

      char* c = new char[30];
      sprintf(c, "%ld", ((Int*)i)->value);
      delete c;
      return (Object*)String::build();
   }

   Object*
   Int::cast_to_string(Object* i, Object* b)
   {
      SVM_ASSERT_INT(i);
      SVM_ASSERT_INT(b);

      long number = ((svm::Int*)i)->value;
      long base = ((svm::Int*)b)->value;

      // http://www.dreamincode.net/code/snippet729.htm
      static char buffer[50];
      char *ptr=buffer;

      ptr = &buffer[sizeof(buffer)-1];
      *ptr = '\0';

      while(number != 0)
      {
         *--ptr = "0123456789abcdef"[number % base];
         number /= base;
      }
      return svm::String::build((const char*)ptr);
   }

   Short
   Int::compare_to(Object* i1, Object* i2)
   {
      Short result;
      if (i1 == i2)
      {
         result = 0;
      }
      else
      {
         Long l1= ((Int*)i1)->value;
         Long l2 = ((Int*)i2)->value;
         if (l1 == l2)
         {
            result = 0;
         }
         else if (l1 < l2)
         {
            result = -1;
         }
         else
         {
            result = 1;
         }
      }
      return result;
   }

   void
   Int::debug_id(Object* base)
   {
      SVM_ASSERT_INT(base);
      printf("<int:%ld>\n", ((Int*)base)->value);
   }

   bool
   Int::check(Object* obj)
   {
      return obj->cls == svm::int_type;
   }

   Object*
   Int::divide(Object* base, Object* divider)
   {
      SVM_ASSERT_INT(base);
      SVM_ASSERT_INT(divider);

      long int i = (long int)(((Int*)base)->value / ((Int*)divider)->value);

      return Int::build(i);
   }

   Object*
   Int::modulus(Object* i1, Object* i2)
   {
      long l1 = ((svm::Int*)i1)->value;
      long l2 = ((svm::Int*)i2)->value;
      return svm::Int::build((long)(l1 % l2));
   }

   Object*
   Int::multiply(Int* base, Int* item)
   {
      SVM_ASSERT_INT(base);
      SVM_ASSERT_INT(item);

      long int i = (long int)(((Int*)base)->value * ((Int*)item)->value);

      return Int::build(i);
   }

   Object*
   Int::multiply_to(Object* &base, Object* i)
   {
      SVM_ASSERT_INT(base);
      SVM_ASSERT_INT(i);

      ((Int*)base)->value = (((Int*)base)->value * ((Int*)i)->value);

      return base;
   }

   void
   Int::print(Object* i)
   {
      printf("%ld", ((Int*)i)->value);
   }

   void
   Int::print_line(Object* i)
   {
      printf("%ld\n", ((Int*)i)->value);
   }

   Object*
   Int::range_to(Object* self, Object* a_to, Object* a_step)
   {
      // @todo : Complete
      SVM_ASSERT_INT(self);

      Object* result = List::build();
      //long int from = ((Int*)self)->value;
      //long int to = ((Int*)a_to)->value;
      //long int step = ((Int*)a_step)->value;

      return result;
   }

   Object*
   Int::substract(Object* i1, Object* i2)
   {
      return svm::Int::build((long)(((Int*)i1)->value - ((Int*)i2)->value));
   }

   Object*
   Int::subtract_to(Object* base, Object* n)
   {
      SVM_ASSERT_INT(base);
      SVM_ASSERT_INT(n);

      ((Int*)base)->value = (((Int*)base)->value - ((Int*)n)->value);
      return base;
   }
}

