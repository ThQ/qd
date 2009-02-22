#include "svm/String.h"

namespace svm
{
   Object* string_type = NULL;

   String::String()
   {
      this->references = 0;
      //this->value = "";
      this->set_class(string_type);
   }

   #ifdef ALLOW_UNICODE
   Object*
   String::append(Object* base, UnicodeString s)
   {
      // String* base

      Object* app = String::build(s);
      SVM_PICK(app);
      Object* result = String::append(base, app);
      return result;
   }
   #endif

   Object*
   String::append(Object* base, Object* s)
   {
      DEPRECATED();
      // String* base
      // String* s

      return String::join(base, s);
   }

   Object*
   String::append(Object* base, ULong i)
   {
      // String* base

      char buff[33];
      sprintf(buff, "%lu", i);
      Object* app = String::build(buff);
      Object* result = String::append(base, app);
      return result;
   }

   Object*
   String::append(Object* base, char c)
   {
      String* result = (String*)String::build(base);
      result->value.append(1, c);
      return (Object*)result;
   }

   Object*
   String::build()
   {
      return (Object*)new String();
   }

   Object*
   String::build(Object* s)
   {
      String* result = new String();
      result->value = ((String*)s)->value;
      return (Object*)result;
   }

   Object*
   String::build(char c)
   {
      String* result = new String();
      result->value.append(1, c);
      return (Object*)result;
   }

   Object*
   String::build(const char* s)
   {
      ULong len = (ULong)strlen(s);
      String* result = new String();
      result->value.assign((char*)s,len);

      return (Object*)result;
   }

   Object*
   String::build(std::string s)
   {
      String* result = new String();
      result->value = s;
      return (Object*)result;
   }

   #ifdef ALLOW_UNICODE
   Object*
   String::build(UnicodeString s)
   {
      ULong new_size = s.length();
      char* tmp = new char [new_size + 1];

      // TODO : Find a better way to pass from UChar to char
      for (ULong i = 0 ; i < new_size ; ++i)
      {
         tmp[i] = (char)s.charAt(i);
      }
      tmp[new_size] = 0;

      Object* result = String::build(tmp);
      delete tmp;

      return result;
   }
   #endif

   Object*
   String::cast_to_string(Object* s)
   {
      return s;
   }

   Object*
   String::center(Object* s_base, Object* i_length, Object* s_padding)
   {
      String* result;
      String* base = (String*)s_base;
      String* padding = (String*)s_padding;
      ULong base_len = base->value.length();
      ULong padding_str_len = padding->value.length();
      ULong final_len = ((Int*)i_length)->value;

      if (base_len < final_len)
      {
         result = new String();
         ULong padding_len = final_len - base_len;
         ULong pad1_len, pad2_len;

         if (padding_len % 2 == 0)
         {
            pad1_len = padding_len / 2;
            pad2_len = pad1_len;
         }
         else
         {
            pad1_len = (padding_len - 1) / 2;
            pad2_len = pad1_len + 1;
         }

         char* tmp = new char[final_len];

         // Left padding
         for (ULong i = 0 ; i < pad1_len ; ++i)
         {
            for (ULong j = 0 ; j < padding_str_len && i < pad1_len ; ++j, ++i)
            {
               tmp[i] = padding->value[j];
            }
            --i;
         }

         for (ULong i = 0 ; i < base_len ; ++i)
         {
            tmp[pad1_len + i] = base->value[i];
            //result->value.append(s1->value[i], 1);
         }

         // Right padding
         for (ULong i = 0 ; i < pad2_len ; ++i)
         {
            for (ULong j = 0 ; j < padding_str_len && i < pad2_len ; ++i, ++j)
            {
               tmp[pad1_len + base_len + i] = padding->value[j];
               //result->value.append(s2->value[j], 1);
            }
            --i;
         }

         result->value.assign(tmp, final_len);
         delete tmp;
      }
      else
      {
         result = base;
      }

      return (Object*)result;
   }

   bool
   String::check(Object* obj)
   {
      return obj->cls == svm::string_type;
   }

   Short
   String::compare_to(Object* s1, Object* s2)
   {
      Short result;
      if (s1 == s2)
      {
         result = 0;
      }
      else
      {
         result = (Short)((String*)s1)->value.compare(((String*)s2)->value);
      }
      return result;
   }

   Object*
   String::copy(Object* self)
   {
      SVM_ASSERT_STRING(self);

      String* result = new String();
      result->value = ((String*)self)->value;

      return (Object*)result;
   }


   Object*
   String::cut_after(Object* base, Object* search)
   {
      // String* base
      // String* search
      Object* result;

      long pos = ((Int*)String::find(base, search, Int::build((float)0)))->value;
      if (pos != -1)
      {
         result = String::cut_at(base, Int::build((long)pos));
      }
      else
      {
         result = base;
      }
      return result;
   }

   Object*
   String::cut_at(Object* base, Object* at)
   {
      // String* base
      // Int* at

      Object* result = NULL;
      ULong l_at = ((Int*)at)->value;
      char* tmp = new char[l_at + 1];

      if (((String*)base)->value.length() < l_at)
      {
         for (ULong i = 0 ; i < l_at ; ++i)
         {
            tmp[i] = ((String*)base)->value[i];
         }
         tmp[l_at] = 0;
         result = (Object*)String::build(tmp);
         delete tmp;
      }
      else
      {
         result = base;
      }

      return result;
   }

   Object*
   String::equals(Object* s1, Object* s2)
   {
      Object* result = NULL;

      if (((svm::String*)s1)->value.compare(((svm::String*)s2)->value) == 0)
      {
         result = svm::True;
      }
      else
      {
         result = svm::False;
      }
      ASSERT_NOT_NULL(result);
      return result;
   }

   Object*
   String::find(Object* base, Object* substring, Object* start_at)
   {
      // String* base
      // String* substring
      // Int* start_at

      bool found;
      String* s1 = (String*)base;
      String* s2 = (String*)substring;
      ULong l1 = s1->value.length();
      ULong l2 = s2->value.length();
      long at = -1;
      for (ULong i = 0 ; i < l1 && i + l2 <= l1 ; ++i)
      {
         found = true;
         for (ULong j = 0 ; j < l2 ; ++j)
         {
            if (s1->value[i + j] != s2->value[j])
            {
               found = false;
               break;
            }
         }

         if (found == true)
         {
            at = i;
            break;
         }
      }

      return Int::build(at);
   }

   Object*
   String::insert(Object* s, Object* sub, ULong at)
   {
      SVM_CHECK_STRING(s);
      SVM_CHECK_STRING(sub);

      ULong l1 = ((String*)s)->value.length();
      ULong l2 = ((String*)sub)->value.length();
      ULong new_length = l1 + l2;

      char* tmp = new char[new_length + 1];

      for (ULong i = 0 ; i < at ; ++i)
      {
         tmp[i] = ((String*)s)->value[i];
      }

      for (ULong i = 0 ; i < l2 ; ++ i)
      {
         tmp[at + i] = ((String*)sub)->value[i];
      }

      for (ULong i = at ; i < l1 ; ++i)
      {
         tmp[i + l2] = ((String*)s)->value[i];
      }
      tmp[new_length] = 0;

      Object* result = String::build(tmp);
      delete tmp;

      return result;
   }

   Object*
   String::is_alphabetic(Object* str)
   {
      String* s = (String*)str;
      ULong l = s->value.length();
      Object* result;

      if (l > 0)
      {
         result = svm::True;

         for(ULong i = 0 ; i < l ; ++i)
         {
            if (s->value[i] < 'A' || (s->value[i] > 'Z' && s->value[i] < 'a') || s->value[i] > 'z')
            {
               result = svm::False;
               break;
            }
         }
      }
      else
      {
         result = svm::False;
      }

      SVM_ASSERT_NOT_NULL(result);

      return result;
   }

   Object*
   String::is_digit(Object* str)
   {
      String* s = (String*)str;
      ULong l = s->value.length();
      Object* result;

      if (l > 0)
      {
         result = svm::True;

         for(ULong i = 0 ; i < l ; ++i)
         {
            if (s->value[i] < '0' || s->value[i] > '9')
            {
               result = svm::False;
               break;
            }
         }
      }
      else
      {
         result = svm::False;
      }

      SVM_ASSERT_NOT_NULL(result);

      return result;
   }

   Object*
   String::is_lowercase(Object* str)
   {
      String* s = (String*)str;
      ULong l1 = s->value.length();

      bool is_lowercase = true;
      for (ULong i = 0 ; i < l1 ; ++i)
      {
         if (s->value[i] >= 'A' && s->value[i] <= 'Z')
         {
            is_lowercase = false;
            break;
         }
      }

      Object* result;
      if (is_lowercase)
      {
         result = svm::True;
      }
      else
      {
         result = svm::False;
      }
      return result;
   }

   Object*
   String::is_space(Object* str)
   {
      String* s = (String*)str;
      ULong l = s->value.length();
      Object* result;

      if (l > 0)
      {
          result = svm::True;

         for (ULong i = 0 ; i < l ; ++i)
         {
            if (s->value[i] > ' ')
            {
               result = svm::False;
               break;
            }
         }
      }
      else
      {
         result = svm::False;
      }

      SVM_ASSERT_NOT_NULL(result);

      return result;
   }

   Object*
   String::is_uppercase(Object* str)
   {
      String* s = (String*)str;
      ULong l1 = s->value.length();

      bool is_uppercase = true;
      for (ULong i = 0 ; i < l1 ; ++i)
      {
         if (s->value[i] >= 'a' && s->value[i] <= 'z')
         {
            is_uppercase = false;
            break;
         }
      }

      Object* result;
      if (is_uppercase)
      {
         result = svm::True;
      }
      else
      {
         result = svm::False;
      }
      return result;
   }

   Object*
   String::join(Object* s1, Object* s2)
   {
      SVM_CHECK_STRING(s1);
      SVM_CHECK_STRING(s2);

      ULong l1 = ((String*)s1)->value.length();
      ULong l2 = ((String*)s2)->value.length();
      ULong new_size = l1 + l2;
      char* tmp = new char[new_size + 1];


      for (ULong i = 0 ; i < l1 ; ++i)
      {
         tmp[i] = ((String*)s1)->value[i];
      }

      for (ULong i = 0 ; i < l2 ; ++i)
      {
         tmp[l1 + i] = ((String*)s2)->value[i];
      }

      tmp[new_size] = 0;

      Object* result = String::build(tmp);
      delete tmp;

      return result;
   }

   Object*
   String::lower(Object* self)
   {
      SVM_CHECK_STRING(self);

      String* s = (String*)self;
      ULong len = s->value.length();
      char* tmp = new char[len + 1];

      for (ULong i = 0 ; i < len ; ++i)
      {
         if (s->value[i] >= 'A' && s->value[i] <= 'Z')
         {
            tmp[i] = s->value[i] + 32;
         }
         else
         {
            tmp[i] = s->value[i];
         }
      }
      tmp[len] = 0;

      Object* result = String::build(tmp);
      delete tmp;
      return result;
   }

   Object*
   String::multiply(Object* self, Object* times)
   {
      SVM_CHECK_STRING(self);
      SVM_CHECK_INT(times);

      int t = ((Int*)times)->value;
      ULong new_length = (((String*)self)->value.length() * (ULong)t);
      char* tmp = new char[new_length + 1];

      for (int i = 1 ; i < t ; ++i)
      {
         for (ULong j = 0 ; j < ((String*)self)->value.length() ; ++j)
         {
            tmp[i + j] = ((String*)self)->value[j];
         }
      }
      tmp[new_length] = 0;

      Object* result = String::build(tmp);
      delete tmp;
      return result;
   }

   Object*
   String::pad(Object* base, ULong len, Object* spad)
   {
      std::string dest = ((String*)base)->value;
      std::string padstr = ((String*)spad)->value;
      ULong i = 0;
      while (dest.length() != len)
      {
         for (i = 0 ; i < padstr.length() && dest.length() != len ; ++i)
         {
            dest.push_back((char)padstr[i]);
         }
      }
      return svm::String::build(dest);
   }

   Object*
   String::lpad(Object* base, ULong len, Object* spad)
   {
      std::string dest = ((String*)base)->value;
      std::string padstr = ((String*)spad)->value;
      ULong i = 0;
      while (dest.length() != len)
      {
         for (i = 0 ; i < padstr.length() && dest.length() != len ; ++i)
         {
            dest.insert(0, 1, padstr[i]);
         }
      }
      return svm::String::build(dest);
   }

   Object*
   String::prepend(Object* s1, Object* s2)
   {
      ULong l1 = ((String*)s1)->value.length();
      ULong l2 = ((String*)s2)->value.length();
      ULong new_size = l1 + l2;
      char* tmp = new char[new_size + 1];

      for (ULong i = 0 ; i < l2 ; ++i)
      {
         tmp[i] = ((String*)s2)->value[i];
      }

      for (ULong i = 0 ; i < l1 ; ++i)
      {
         tmp[i + l2] = ((String*)s1)->value[i];
      }

      tmp[new_size] = 0;

      Object* result = String::build(tmp);
      delete tmp;

      return result;
   }

   void
   String::print(Object* s)
   {
      // String* s
      printf("%s", ((String*)s)->value.c_str());
   }

   void
   String::print_line(Object* s)
   {
      printf("%s\n", ((String*)s)->value.c_str());
   }

   Object*
   String::get_character(Object* self, Object* pos)
   {
      SVM_ASSERT_STRING(self);
      SVM_ASSERT_INT(pos);
      ASSERT(
            (ULong)((Int*)pos)->value < ((String*)self)->value.length(),
            "%s(...) : %lu is outside of range [0:%lu]",
            __FUNCTION__, (ULong)((Int*)pos)->value,
            (ULong)((String*)self)->value.length()
      );

      char* tmp = new char[2];
      tmp[0] = ((String*)self)->value[((Int*)pos)->value];
      tmp[1] = 0;

      Object* s = svm::String::build(tmp);
      delete[] tmp;
      return s;
   }

   Object*
   String::get_length(Object* s)
   {
      SVM_ASSERT_STRING(s);
      return svm::Int::build((long)((svm::String*)s)->value.length());
   }

   Object*
   String::reverse(Object* s)
   {
      String* result = new String();
      String* base = (String*)s;
      ULong l = base->value.length();
      char* tmp = new char[l];

      for (ULong i = 0 ; i < l ; ++i)
      {
         tmp[l - i - 1] = base->value[i];
      }

      result->value.assign(tmp, l);
      delete tmp;

      return (Object*)result;
   }

   Object*
   String::strip(Object* self, Object* characters, Object* start_at, Object* end_at)
   {

      /*
      SVM_ASSERT_STRING(self);
      SVM_ASSERT_STRING(characters);
      SVM_ASSERT_INT(start_at);
      SVM_ASSERT_INT(end_at);

      long int self_len = ((String*)self)->value.length();
      UnicodeString base = UNICODE_STRING("", 0);
      UnicodeString chars = ((String*)characters)->value;
      long int start, end;

      if (((Int*)start_at)->value == 0 || ((Int*)start_at)->value < 0) start = 0;
      else if (((Int*)start_at)->value > self_len) start = self_len;
      else start = ((Int*)start_at)->value;

      if (((Int*)end_at)->value == -1) end = self_len;
      else if (((Int*)end_at)->value > self_len) end = self_len;
      else if (((Int*)end_at)->value < 0) end = self_len;
      else end = ((Int*)end_at)->value;

      for (long int i = start ; i < end ; ++i)
      {
         UChar c = ((String*)self)->value.charAt(i);
         if (chars.indexOf(c) == -1)
         {
            base.append(c);
         }
      }
      */

      return String::build();
   }

   Object*
   String::swap_case(Object* self)
   {
      String* s = (String*)self;
      ULong len = (ULong)s->value.length();
      char* tmp = new char[len + 1];

      for (ULong i = 0 ; i < len ; ++i)
      {
         if (s->value[i] >= 'a' && s->value[i] <= 'z')
         {
            tmp[i] = s->value[i] - 32;
         }
         else if (s->value[i] >= 'A' && s->value[i] <= 'Z')
         {
            tmp[i] = s->value[i] + 32;
         }
         else
         {
            tmp[i] = s->value[i];
         }
      }
      tmp[len] = 0;

      Object* result = String::build(tmp);
      delete tmp;
      return result;
   }

   Object*
   String::upper(Object* self)
   {
      String* s = (String*)self;
      ULong len = (ULong)s->value.length();
      char* tmp = new char[len + 1];


      for (ULong i = 0 ; i < len ; ++i)
      {
         if (s->value[i] >= 'a' && s->value[i] <= 'z')
         {
            tmp[i] = s->value[i] - 32;
         }
         else
         {
            tmp[i] = s->value[i];
         }
      }
      tmp[len] = 0;

      Object* result = (Object*)svm::String::build(tmp);

      delete tmp;

      return result;
   }
}

