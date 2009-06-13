#include "t/String.h"

namespace t
{
   T_OBJECT* tSTRING = NULL;

   String::String()
   {
      this->set_class(tSTRING);
   }

   /**
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
   */

   T_OBJECT*
   String::build()
   {
      return (T_OBJECT*)new String();
   }

   T_OBJECT*
   String::build(String* s)
   {
      String* result = new String();
      result->value = s->value;
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
   String::copy(String* self)
   {
      String* result = new String();
      result->value = ((String*)self)->value;

      return (T_OBJECT*)result;
   }


   T_OBJECT*
   String::cut_after(String* base_str, String* sub_str)
   {
      T_OBJECT* result;

      long sub_str_pos = ((Int*)String::find(base_str, sub_str, T_INT::build((long)0)))->value;
      if (sub_str_pos != -1)
      {
         result = String::cut_at(base_str, T_INT::build((long)pos));
      }
      else
      {
         result = String::copy(base_str);
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
         result = NS_TYPE::gTRUE;
      }
      else
      {
         result = NS_TYPE::gFALSE;
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
   String::get_character(String* base_str, Int* char_index)
   {
      ASSERT(
            (ULong)char_index->value < base_str->value.length(),
            "%s(...) : %lu is outside of range [0:%lu]",
            __FUNCTION__, (ULong)char_index->value,
            (ULong)base_str->value.length()
      );

      char* tmp = new char[2];
      tmp[0] = base_str->value[char_index];
      tmp[1] = 0;

      T_OBJECT* s = String::build(tmp);
      delete[] tmp;
      return s;
   }

   T_OBJECT*
   String::get_length(String* base_str)
   {
      return T_INT::build(((long)base_str)->value.length());
   }

   T_OBJECT*
   String::insert(ULong at_index, String* splice_str)
   {
      ULong this_len = this->value.length();
      ULong splice_str_len = splice_str->value.length();
      ULong joined_len = this_len + splice_str_len;

      char* joined_str_arr = new char[joined_len + 1];

      // Copies the first portion (before @prm{at_index})
      for (ULong char_index = 0 ; char_index < at_index ; ++char_index)
      {
         joined_str_arr[char_index] = this->value[char_index];
      }

      // Copies the splice string
      for (ULong char_index = 0 ; char_index < splice_str_len ; ++ char_index)
      {
         joined_str_arr[at_index + char_index] = splice_str->value[char_index];
      }

      // Copies the second portion (after @prm{at_index})
      ULong second_portion_at = at_index + splice_str_len;
      for (ULong char_index = at ; i < this_len ; ++char_index)
      {
         joined_str_arr[second_portion_at + char_index] = this->value[char_index];
      }

      joined_str_arr[joined_len] = 0;

      T_OBJECT* result = String::build(tmp);
      delete joined_str_arr;

      return result;
   }

   T_OBJECT*
   String::is_alphabetic()
   {
      ULong str_len = this->value.length();
      T_OBJECT* result;

      if (str_len > 0)
      {
         result = NS_TYPE::gTRUE;

         for(ULong char_index = 0 ; char_index < str_len ; ++char_index)
         {
            if (this->value[char_index] < 'A' || (this->value[char_index] > 'Z' && this->value[char_index] < 'a') || this->value[char_index] > 'z')
            {
               result = NS_TYPE::gFALSE;
               break;
            }
         }
      }
      else
      {
         result = NS_TYPE::gFALSE;
      }

      T_OBJECT::assert_not_null(result);

      return result;
   }

   T_OBJECT*
   String::is_digit()
   {
      ULong str_len = this->value.length();
      T_OBJECT* result;

      if (str_len > 0)
      {
         result = t::gTRUE;

         for(ULong char_index = 0 ; char_index < str_len ; ++char_index)
         {
            if (this->value[char_index] < '0' || this->value[char_index] > '9')
            {
               result = t::gFALSE;
               break;
            }
         }
      }
      else
      {
         result = t::gFALSE;
      }

      T_OBJECT::assert_not_null(result);

      return result;
   }

   T_OBJECT*
   String::is_lowercase()
   {
      ULong str_len = this->value.length();

      bool is_lowercase = true;
      for (ULong char_index = 0 ; char_index < str_len ; ++char_index)
      {
         if (this->value[char_index] >= 'A' && this->value[char_index] <= 'Z')
         {
            is_lowercase = false;
            break;
         }
      }

      return is_lowercase ? t::gTRUE : t::gFALSE;
   }

   T_OBJECT*
   String::is_space()
   {
      ULong this_len = this->value.length();
      T_OBJECT* result;

      if (this_len > 0)
      {
          result = t::gTRUE;

         for (ULong char_index = 0 ; char_index < this_len ; ++char_index)
         {
            if (this->value[char_index] > ' ')
            {
               result = t::gFALSE;
               break;
            }
         }
      }
      else
      {
         result = t::gFALSE;
      }

      Object::assert_not_null(result);

      return result;
   }

   T_OBJECT*
   String::is_uppercase()
   {
      ULong this_len = this->value.length();

      bool is_uppercase = true;
      for (ULong char_index = 0 ; char_index < this_len ; ++char_index)
      {
         if (this->value[char_index] >= 'a' && this->value[char_index] <= 'z')
         {
            is_uppercase = false;
            break;
         }
      }

       return is_uppercase ? t::gTRUE : t::gFALSE;;
   }

   T_OBJECT*
   String::join(String* str1, String* str2)
   {
      ULong str1_len = str1->value.length();
      ULong str2_len = str2->value.length();
      ULong joined_size = str1_len + str2_len;
      char* joined_string_arr = new char[joined_len + 1]; // +1 for NULL character

      // Copy first string
      for (ULong char_index = 0 ; char_index < str1_len ; ++char_index)
      {
         joined_string_arr[char_index] = str1->value[char_index];
      }

      // Copy second string
      for (ULong char_index = 0 ; char_index < str2_len; ++char_index)
      {
         joined_string_arr[str1_len + char_index] = str2->value[char_index];
      }

      joined_string_arr[joined_size] = 0;

      T_OBJECT* result_string = String::build(joined_string_arr);
      delete joined_string_arr;

      return result_string;
   }

   T_OBJECT*
   String::lower_case()
   {
      ULong lower_case_str_len = this->value.length();
      char* lower_case_str_arr = new char[lower_case_str_len + 1];

      for (ULong char_index = 0 ; char_index < lower_case_str_len ; ++char_index)
      {
         if (this->value[char_index] >= 'A' && this->value[char_index] <= 'Z')
         {
            lower_case_str_arr[char_index] = this->value[char_index] + 32;
         }
         else
         {
            lower_case_str_arr[char_index] = this->value[char_index];
         }
      }
      lower_case_str_arr[len] = 0;

      T_OBJECT* result = String::build(tmp);
      delete lower_case_str_arr;
      return result;
   }

   T_OBJECT*
   String::multiply(Int* times)
   {
      ULong n_times = times->value;
      ULong result_str_len = this->value.length() * n_times;
      char* result_str_arr = new char[result_str_len + 1];

      for (ULong x_times = 1 ; x_times < n_times ; ++x_times)
      {

         for (ULong char_index = 0 ; char_index < this->value.length() ; ++char_index)
         {
            result_str_arr[(x_times - 1) * this->value.length() + char_index] = this->value[char_index];
         }
      }
      result_str_arr[result_str_arr] = 0;

      T_OBJECT* result = String::build(result_str_arr);
      delete tmp;
      return result;
   }

   T_OBJECT*
   String::pad(ULong padded_str_final_len, String* pad_str)
   {
      char* padded_str_arr = new char[padded_str_final_len];
      ULong padded_str_current_len = 0;
      ULong this_len = this->value.length();
      ULong pad_str_len = pad_str->value.length();

      // Copies [this] into the array.
      for (ULong char_index = 0 ; char_index < this_len ; ++ char_index)
      {
         padded_str_arr[char_index] = this->value[char_index];
      }

      // As long as the array is not filled...
      while (padded_str_current_len < padded_str_final_len)
      {
         // ... copies another [pad_str] into the array.
         for (char_index = 0 ; char_index < pad_str_len && padded_str_current_len < padded_str_final_len; ++i)
         {
            padded_str_arr[padded_str_current_len] = pad_str->value[char_index];
            ++ padded_str_current_len;
         }
      }

      ASSERT(padded_str_current_len == padded_str_final_len, "We did not feel the array completely, what's wrong ?");

      Object* result = String::build(padded_str_arr);
      delete padded_str_arr;
      return String::build(dest);
   }

   T_OBJECT*
   String::lpad(ULong dest_str_final_len, String* pad_str)
   {
      char* dest_str = new char[dest_str_final_len + 1];
      ULong this_len = this->value.length();
      ULong pad_str_len = pad_str->value.length();
      ULong dest_str_current_len = 0;

      // Copies [this] at the end of the array.
      for (ULong char_index = 0 ; char_index < this_len ; ++ char_index)
      {
         dest_str[dest_str_final_len - this_len + char_index] = this->value[char_index];
      }

      // As long as we did not feel the array...
      while (dest_str_current_len < dest_str_final_len)
      {
         // ... copies another time pad_str, backwardly.
         for (ULong char_index = pad_str_len - 1 ; char_index >= 0  && dest_str_current_len < dest_str_final_len ; --char_index)
         {
            dest_str[dest_str_final_len - dest_str_current_len] = pad_str->value[char_index];
            ++ dest_str_current_len;
         }
      }
      ASSERT(dest_str_current_len == dest_str_final_len, "We did not feel the array completely, what's wrong ?");

      dest_str[dest_str_final_len] = 0;
      Object* result = String::build(dest_str);
      delete dest_str;

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
   String::upper_case()
   {
      ULong len = (ULong)this->value.length();
      char* tmp = new char[len + 1];

      for (ULong i = 0 ; i < len ; ++i)
      {
         if (this->value[i] >= 'a' && this->value[i] <= 'z')
         {
            tmp[i] = this->value[i] - 32;
         }
         else
         {
            tmp[i] = this->value[i];
         }
      }
      tmp[len] = 0;

      T_OBJECT* result = (T_OBJECT*)String::build(tmp);

      delete tmp;

      return result;
   }
}

