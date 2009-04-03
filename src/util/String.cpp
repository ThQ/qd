#include "util/String.h"

namespace NS_UTIL
{
   t::Object*
   String::format(t::Object* format_str, ULong argc, t::Object** argv)
   {
      t::String* s = (t::String*)format_str;
      ULong len = s->value.length();
      ULong arg = 0;
      t::String* result = t::String::build();

      for (ULong i = 0 ; i < len ; ++i)
      {
         if (s->value[i] == '%' && i + 1 <= len)
         {
            switch (s->value[i + 1])
            {
               case 'b': // Boolean (svm::Bool)
               {
                  if (argv[arg]->cls == t::tBOOL)
                  {
                     t::Object* strobj = t::Bool::cast_to_string(argv[arg]);
                     t::Object::pick(strobj);
                     result->value.append(((t::String*)strobj)->value);
                     t::Object::drop(strobj);
                  }
                  else
                  {
                     WARNING("Expected system.Bool type.\n");
                  }
                  break;
               }
               case 'i': // Integer (svm::Integer)
               {
                  if (argv[arg]->cls == t::tINT)
                  {
                     t::Object* strobj = t::Int::cast_to_string(argv[arg]);
                     t::Object::pick(strobj);
                     result->value.append(((t::String*)strobj)->value);
                  }
                  else
                  {
                     WARNING("Expected system.Int type.\n");
                  }
                  break;
               }
               case 's': // String (svm::String)
               {
                  if (argv[arg]->cls == t::tSTRING)
                  {
                     result->value.append(((t::String*)argv[arg])->value);
                  }
                  break;
               }
               case '%':
               {
                  result->value.append('%', 1);
                  break;
               }
            }
         }
      }

      return result;
   }
}

