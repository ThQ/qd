#include "t/Int.h"

namespace NS_TYPE
{
   T_OBJECT* int_type = NULL;

   Int::Int()
   {
      this->references = 0;
      this->set_class(NS_TYPE::int_type);
      this->value = 0;
   }


   T_OBJECT*
   Int::add(T_OBJECT* base, T_OBJECT* to_add)
   {
      T_INT::assert(base);
      T_INT::assert(to_add);

      long int f = (long int)(((T_INT*)base)->value + ((T_INT*)to_add)->value);
      return Int::build(f);
   }

   T_OBJECT*
   Int::add_to(T_OBJECT* &base, T_OBJECT* to_add)
   {
      T_INT::assert(base);
      T_INT::assert(to_add);

      ((T_INT*)base)->value += ((T_INT*)to_add)->value;
      return base;
   }

   T_OBJECT*
   Int::build()
   {
      T_INT* i = new T_INT();
      i->value = 0;
      return (T_OBJECT*)i;
   }

   T_OBJECT*
   Int::build(float value)
   {
      T_INT* result = new T_INT();
      result->value = (long)value;
      return (T_OBJECT*)result;
   }

   T_OBJECT*
   Int::build(long value)
   {
      T_INT* result = new T_INT();
      result->value = value;
      return (T_OBJECT*)result;
   }

   T_OBJECT*
   Int::build(T_OBJECT* obj)
   {
      T_INT::assert(obj);

      T_INT* result = new T_INT();
      result->value = ((T_INT*)obj)->value;

      return (T_OBJECT*)result;
   }

   T_OBJECT*
   Int::cast_to_string(T_OBJECT* i)
   {
      T_INT::assert(i);

      char* c = new char[30];
      sprintf(c, "%ld", ((T_INT*)i)->value);
      delete c;
      return (T_OBJECT*)T_STRING::build();
   }

   T_OBJECT*
   Int::cast_to_string(T_OBJECT* i, T_OBJECT* b)
   {
      T_INT::assert(i);
      T_INT::assert(b);

      long number = ((T_INT*)i)->value;
      long base = ((T_INT*)b)->value;

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
      return T_STRING::build((const char*)ptr);
   }

   Short
   Int::compare_to(T_OBJECT* i1, T_OBJECT* i2)
   {
      T_INT::assert(i1);
      T_INT::assert(i2);

      Short result;
      if (i1 == i2)
      {
         result = 0;
      }
      else
      {
         Long l1= ((T_INT*)i1)->value;
         Long l2 = ((T_INT*)i2)->value;
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
   Int::debug_id(T_OBJECT* base)
   {
      T_INT::assert(base);
      printf("<int:%ld>\n", ((T_INT*)base)->value);
   }

   T_OBJECT*
   Int::divide(T_OBJECT* base, T_OBJECT* divider)
   {
      T_INT::assert(base);
      T_INT::assert(divider);

      long int i = (long int)(((T_INT*)base)->value / ((T_INT*)divider)->value);

      return Int::build(i);
   }

   T_OBJECT*
   Int::modulus(T_OBJECT* i1, T_OBJECT* i2)
   {
      T_INT::assert(i1);
      T_INT::assert(i2);

      long l1 = ((T_INT*)i1)->value;
      long l2 = ((T_INT*)i2)->value;
      return T_INT::build((long)(l1 % l2));
   }

   T_OBJECT*
   Int::multiply(T_INT* base, T_INT* item)
   {
      T_INT::assert(base);
      T_INT::assert(item);

      long int i = (long int)(((T_INT*)base)->value * ((T_INT*)item)->value);

      return T_INT::build(i);
   }

   T_OBJECT*
   Int::multiply_to(T_OBJECT* &base, T_OBJECT* i)
   {
      T_INT::assert(base);
      T_INT::assert(i);

      ((T_INT*)base)->value = (((T_INT*)base)->value * ((T_INT*)i)->value);

      return base;
   }

   void
   Int::print(T_OBJECT* i)
   {
      T_INT::assert(i);

      printf("%ld", ((T_INT*)i)->value);
   }

   void
   Int::print_line(T_OBJECT* i)
   {
      T_INT::assert(i);

      printf("%ld\n", ((T_INT*)i)->value);
   }

   T_OBJECT*
   Int::range_to(T_OBJECT* self, T_OBJECT* a_to, T_OBJECT* a_step)
   {
      // @todo : Complete
      T_INT::assert(self);
      T_INT::assert(a_to);
      T_INT::assert(a_step);

      T_OBJECT* result = T_LIST::build();
      //long int from = ((T_INT*)self)->value;
      //long int to = ((T_INT*)a_to)->value;
      //long int step = ((T_INT*)a_step)->value;

      return result;
   }

   T_OBJECT*
   Int::substract(T_OBJECT* i1, T_OBJECT* i2)
   {
      T_INT::assert(i1);
      T_INT::assert(i2);

      return T_INT::build((long)(((T_INT*)i1)->value - ((T_INT*)i2)->value));
   }

   T_OBJECT*
   Int::subtract_to(T_OBJECT* base, T_OBJECT* n)
   {
      T_INT::assert(base);
      T_INT::assert(n);

      ((T_INT*)base)->value = (((T_INT*)base)->value - ((T_INT*)n)->value);
      return base;
   }
}

