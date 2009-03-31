#include "t/String.h"

namespace NS_TYPE
{
   T_OBJECT* string_type = NULL;

   String::String()
   {
      this->set_class(string_type);
   }

   #ifdef ALLOW_UNICODE
   T_OBJECT*
   String::append(T_OBJECT* base, UnicodeString s)
   {
      String::assert(base);

      T_OBJECT* app = String::build(s);
      T_OBJECT::pick(app);
      T_OBJECT* result = String::append(base, app);
      return result;
   }
   #endif

   T_OBJECT*
   String::append(T_OBJECT* base, T_OBJECT* s)
   {
      DEPRECATED();
      // String* base
      // String* s

      return String::join(base, s);
   }

   T_OBJECT*
   String::append(T_OBJECT* base, ULong i)
   {
      String::assert(base);

      char buff[33];
      sprintf(buff, "%lu", i);
      T_OBJECT* app = String::build(buff);
      T_OBJECT* result = String::append(base, app);
      return result;
   }

   T_OBJECT*
   String::append(T_OBJECT* base, char c)
   {
      String::assert(base);

      String* result = (String*)String::build(base);
      result->value.append(1, c);
      return (T_OBJECT*)result;
   }

   T_OBJECT*
   String::build()
   {
      return (T_OBJECT*)new String();
   }

   T_OBJECT*
   String::build(T_OBJECT* s)
   {
      String::assert(s);

      String* result = new String();
      result->value = ((String*)s)->value;
      return (T_OBJECT*)result;
   }

   T_OBJECT*
   String::build(char c)
   {
      String* result = new String();
      result->value.append(1, c);
      return (T_OBJECT*)result;
   }

   T_OBJECT*
   String::build(const char* s)
   {
      ULong len = (ULong)strlen(s);
      String* result = new String();
      result->value.assign((char*)s,len);

      return (T_OBJECT*)result;
   }

   T_OBJECT*
   String::build(std::string s)
   {
      String* result = new String();
      result->value = s;
      return (T_OBJECT*)result;
   }

   #ifdef ALLOW_UNICODE
   T_OBJECT*
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

      T_OBJECT* result = String::build(tmp);
      delete tmp;

      return result;
   }
   #endif

   T_OBJECT*
   String::cast_to_string(T_OBJECT* s)
   {
      return s;
   }

   T_OBJECT*
   String::center(T_OBJECT* s_base, T_OBJECT* i_length, T_OBJECT* s_padding)
   {
      String::assert(s_base);
      T_INT::assert(i_length);
      String::assert(s_padding);

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

      return (T_OBJECT*)result;
   }

   Short
   String::compare_to(T_OBJECT* s1, T_OBJECT* s2)
   {
      String::assert(s1);
      String::assert(s2);

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

   T_OBJECT*
   String::copy(T_OBJECT* self)
   {
      String::assert(self);

      String* result = new String();
      result->value = ((String*)self)->value;

      return (T_OBJECT*)result;
   }


   T_OBJECT*
   String::cut_after(T_OBJECT* base, T_OBJECT* search)
   {
      String::assert(base);
      String::assert(search);
      T_OBJECT* result;

      long pos = ((Int*)String::find(base, search, T_INT::build((float)0)))->value;
      if (pos != -1)
      {
         result = String::cut_at(base, T_INT::build((long)pos));
      }
      else
      {
         result = base;
      }
      return result;
   }

   T_OBJECT*
   String::cut_at(T_OBJECT* base, T_OBJECT* at)
   {
      String::assert(base);
      T_INT::assert(at);

      T_OBJECT* result = NULL;
      ULong l_at = ((Int*)at)->value;
      char* tmp = new char[l_at + 1];

      if (((String*)base)->value.length() < l_at)
      {
         for (ULong i = 0 ; i < l_at ; ++i)
         {
            tmp[i] = ((String*)base)->value[i];
         }
         tmp[l_at] = 0;
         result = (T_OBJECT*)String::build(tmp);
         delete tmp;
      }
      else
      {
         result = base;
      }

      return result;
   }

   T_OBJECT*
   String::equals(T_OBJECT* s1, T_OBJECT* s2)
   {
      String::assert(s1);
      String::assert(s2);

      T_OBJECT* result = NULL;

      if (((String*)s1)->value.compare(((String*)s2)->value) == 0)
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

   T_OBJECT*
   String::find(T_OBJECT* base, T_OBJECT* substring, T_OBJECT* start_at)
   {
      String::assert(base);
      String::assert(substring);
      T_INT::assert(start_at);

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

      return T_INT::build(at);
   }

   T_OBJECT*
   String::insert(T_OBJECT* s, T_OBJECT* sub, ULong at)
   {
      String::assert(s);
      String::assert(sub);

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

      T_OBJECT* result = String::build(tmp);
      delete tmp;

      return result;
   }

   T_OBJECT*
   String::is_alphabetic(T_OBJECT* str)
   {
      String::assert(str);

      String* s = (String*)str;
      ULong l = s->value.length();
      T_OBJECT* result;

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

   T_OBJECT*
   String::is_digit(T_OBJECT* str)
   {
      String::assert(str);

      String* s = (String*)str;
      ULong l = s->value.length();
      T_OBJECT* result;

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

   T_OBJECT*
   String::is_lowercase(T_OBJECT* str)
   {
      String::assert(str);

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

      T_OBJECT* result;
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

   T_OBJECT*
   String::is_space(T_OBJECT* str)
   {
      String::assert(str);

      String* s = (String*)str;
      ULong l = s->value.length();
      T_OBJECT* result;

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

   T_OBJECT*
   String::is_uppercase(T_OBJECT* str)
   {
      String::assert(str);

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

      T_OBJECT* result;
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

   T_OBJECT*
   String::join(T_OBJECT* s1, T_OBJECT* s2)
   {
      String::assert(s1);
      String::assert(s2);

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

      T_OBJECT* result = String::build(tmp);
      delete tmp;

      return result;
   }

   T_OBJECT*
   String::lower(T_OBJECT* self)
   {
      String::assert(self);

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

      T_OBJECT* result = String::build(tmp);
      delete tmp;
      return result;
   }

   T_OBJECT*
   String::multiply(T_OBJECT* self, T_OBJECT* times)
   {
      String::assert(self);
      T_INT::assert(times);

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

      T_OBJECT* result = String::build(tmp);
      delete tmp;
      return result;
   }

   T_OBJECT*
   String::pad(T_OBJECT* base, ULong len, T_OBJECT* spad)
   {
      String::assert(base);
      String::assert(spad);

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
      return String::build(dest);
   }

   T_OBJECT*
   String::lpad(T_OBJECT* base, ULong len, T_OBJECT* spad)
   {
      String::assert(base);
      String::assert(spad);

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
      return String::build(dest);
   }

   T_OBJECT*
   String::prepend(T_OBJECT* s1, T_OBJECT* s2)
   {
      String::assert(s1);
      String::assert(s2);

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

      T_OBJECT* result = String::build(tmp);
      delete tmp;

      return result;
   }

   void
   String::print(T_OBJECT* s)
   {
      String::assert(s);
      printf("%s", ((String*)s)->value.c_str());
   }

   void
   String::print_line(T_OBJECT* s)
   {
      String::assert(s);
      printf("%s\n", ((String*)s)->value.c_str());
   }

   T_OBJECT*
   String::get_character(T_OBJECT* self, T_OBJECT* pos)
   {
      String::assert(self);
      T_INT::assert(pos);

      ASSERT(
            (ULong)((T_INT*)pos)->value < ((String*)self)->value.length(),
            "%s(...) : %lu is outside of range [0:%lu]",
            __FUNCTION__, (ULong)((T_INT*)pos)->value,
            (ULong)((String*)self)->value.length()
      );

      char* tmp = new char[2];
      tmp[0] = ((String*)self)->value[((T_INT*)pos)->value];
      tmp[1] = 0;

      T_OBJECT* s = String::build(tmp);
      delete[] tmp;
      return s;
   }

   T_OBJECT*
   String::get_length(T_OBJECT* s)
   {
      String::assert(s);

      return T_INT::build((long)((String*)s)->value.length());
   }

   T_OBJECT*
   String::reverse(T_OBJECT* s)
   {
      String::assert(s);

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

      return (T_OBJECT*)result;
   }

   T_OBJECT*
   String::strip(T_OBJECT* self, T_OBJECT* characters, T_OBJECT* start_at, T_OBJECT* end_at)
   {
      String::assert(self);
      String::assert(characters);
      T_INT::assert(start_at);
      T_INT::assert(end_at);

      /*
      String::assert(self);
      String::assert(characters);
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

   T_OBJECT*
   String::swap_case(T_OBJECT* self)
   {
      String::assert(self);

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

      T_OBJECT* result = String::build(tmp);
      delete tmp;
      return result;
   }

   T_OBJECT*
   String::upper(T_OBJECT* self)
   {
      String::assert(self);

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

      T_OBJECT* result = (T_OBJECT*)String::build(tmp);

      delete tmp;

      return result;
   }
}

