#include "svm/StringUtil.h"

namespace svm
{
   Object*
   StringUtil::format(Object* format_str, ULong argc, Object** argv)
   {
      String* s = (String*)format_str;
      ULong len = s->value.length();
      ULong arg = 0;
      String* result = new String();
      result->value.assign("");

      for (ULong i = 0 ; i < len ; ++i)
      {
         if (s->value[i] == '%' && i + 1 <= len)
         {
            switch (s->value[i + 1])
            {
               case 'b': // Boolean (svm::Bool)
               {
                  if (argv[arg]->cls == svm::bool_type)
                  {
                     Object* strobj = Bool::cast_to_string(argv[arg]);
                     SVM_PICK(strobj);
                     result->value.append(((String*)strobj)->value);
                     SVM_DROP(strobj);
                  }
                  else
                  {
                     WARNING("Expected system.Bool type.\n");
                  }
                  break;
               }
               case 'i': // Integer (svm::Integer)
               {
                  if (argv[arg]->cls == svm::int_type)
                  {
                     Object* strobj = Int::cast_to_string(argv[arg]);
                     SVM_PICK(strobj);
                     result->value.append(((String*)strobj)->value);
                  }
                  else
                  {
                     WARNING("Expected system.Int type.\n");
                  }
                  break;
               }
               case 's': // String (svm::String)
               {
                  if (argv[arg]->cls == svm::string_type)
                  {
                     result->value.append(((String*)argv[arg])->value);
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

