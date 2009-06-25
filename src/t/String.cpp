#include "t/String.h"

namespace t
{
   // T_OBJECT* tSTRING = NULL;

   String::String ()
   {
      this->_init();
   }

   String::String(char chr)
   {
      this->_init();
      this->value.append(1, chr);
   }

   String::String (const char* string_arr)
   {
      this->_init();
      this->value.assign(string_arr);
   }

   String::String (char* string_arr)
   {
      this->_init();
      this->value.assign(string_arr);
   }

   String::String (char* string_arr, UInt64 string_arr_len)
   {
      this->_init();
      this->value.assign(string_arr, string_arr_len);
   }

   String::String (String* str)
   {
      this->_init();
      this->value = str->value;
   }

   String::String (std::string str)
   {
      this->_init();
      this->value = str;
   }

   String*
   String::center(UInt64 centered_str_len, String* pad_str)
   {
      String* pCenteredStr; // Result
      UInt64 this_len = this->value.length();
      UInt64 pad_str_len = pad_str->value.length();

      if (this_len < centered_str_len)
      {
         UInt64 padding_len = centered_str_len - this_len;
         UInt64 left_padding_len;
         UInt64 right_padding_len;

         if (padding_len % 2 == 0)
         {
            left_padding_len = padding_len / 2;
            right_padding_len = left_padding_len;
         }
         else
         {
            left_padding_len = (padding_len - 1) / 2;
            right_padding_len = left_padding_len + 1;
         }

         char* centered_str_arr = new char[centered_str_len];

         // +---+---+---+      +---+---+---+---+---+---+---+---+---+---+---+
         // |  STRING   |  ->  | LEFT_PADDING  |  STRING   | RIGHT PADDING |
         // +---+---+---+      +---+---+---+---+---+---+---+---+---+---+---+

         // Pads left
         LOOP_FROM_TO(UInt64, char_index, 0, left_padding_len)
         {
            UInt64 pad_char_index = 0;
            while (pad_char_index < pad_str_len && pad_char_index < left_padding_len)
            {
               centered_str_arr[char_index] = pad_str->value[pad_char_index];
               ++ char_index;
               ++ pad_char_index;
            }
            -- char_index;
         }

         // Copies string after left padding.
         LOOP_FROM_TO(UInt64, char_index, 0, this_len)
         {
            centered_str_arr[left_padding_len + char_index ] = this->value[char_index];
         }

         // Pads right
         LOOP_FROM_TO(UInt64, char_index, 0, right_padding_len)
         {
            UInt64 pad_char_index = 0;
            while (pad_char_index < pad_str_len && pad_char_index < right_padding_len)
            {
               centered_str_arr[right_padding_len + this_len + pad_char_index] = pad_str->value[pad_char_index];
               ++ char_index;
               ++ pad_char_index;

            }
            -- char_index;
         }

         pCenteredStr = new String(centered_str_arr, centered_str_len);
         delete centered_str_arr;
      }
      else
      {
         pCenteredStr = this->copy();
      }

      return pCenteredStr;
   }

   Short
   String::compare_to(String* pCompareStr)
   {
      return (this == pCompareStr) ? 0 : (Short)this->value.compare(pCompareStr->value);
   }

   String*
   String::copy()
   {
      return new String(this);
   }

   String*
   String::cut_after(String* pSubstr)
   {
      UInt64 pSubstrFoundAt;
      String* pCutStr = NULL;
      if (this->find(pSubstr, (UInt64)0, pSubstrFoundAt))
      {
         pCutStr = this->cut_at(pSubstrFoundAt + pSubstr->value.length());
      }
      else
      {
         pCutStr = this->copy();
      }

      ASSERT_NOT_NULL(pCutStr);

      return pCutStr;
   }

   String*
   String::cut_at (UInt64 dwCutStrLen)
   {
      String* pCutStr = NULL;
      char* psCutStr= new char[dwCutStrLen];

      if (dwCutStrLen < this->value.length())
      {
         LOOP_FROM_TO(UInt64, char_index, 0, dwCutStrLen)
         {
            psCutStr[char_index] = this->value[char_index];
         }
         pCutStr = new String(psCutStr, dwCutStrLen);
         delete psCutStr;
      }
      else
      {
         pCutStr = this->copy();
      }

      return pCutStr;
   }

   String*
   String::cut_before (String* pSubstr)
   {
      UInt64 pSubstrFoundAt;
      String* pCutStr = NULL;
      if (this->find(pSubstr, (UInt64)0, pSubstrFoundAt))
      {
         pCutStr = this->cut_at(pSubstrFoundAt);
      }
      else
      {
         pCutStr = this->copy();
      }

      ASSERT_NOT_NULL(pCutStr);

      return pCutStr;
   }

   bool
   String::equals (String* compare_str)
   {
      return this->value.compare(compare_str->value) == 0;
   }

   bool
   String::find (String* sub_str, UInt64 start_at_pos, UInt64 end_at_pos, UInt64& found_at)
   {
      ASSERT(
            start_at_pos < (UInt64)this->value.length(),
            "start_at_pos(%lu) is outside [0:%lu], the range of the string.",
            start_at_pos,
            (UInt64)this->value.length()
      );

      ASSERT(
            end_at_pos < (UInt64)this->value.length(),
            "end_at_pos(%lu) is outside [0:%lu], the range of the string.",
            end_at_pos,
            (UInt64)this->value.length()
      );

      bool sub_str_found = false;
      UInt64 sub_str_len = sub_str->value.length();
      UInt64 this_char_index = start_at_pos;

      while ((this_char_index < end_at_pos) && (this_char_index + sub_str_len <= end_at_pos))
      {
         sub_str_found = true;
         LOOP_FROM_TO(UInt64, sub_str_char_index, 0, sub_str_len)
         {
            if (this->value[this_char_index + sub_str_char_index] != sub_str->value[sub_str_char_index])
            {
               sub_str_found = false;
               break;
            }
         }

         if (sub_str_found == true)
         {
            found_at = this_char_index;
            break;
         }
         ++ this_char_index;
      }
      return sub_str_found;
   }

   String*
   String::get_character (UInt64 char_index)
   {
      ASSERT(
            char_index < this->value.length(),
            "%s(...) : %lu is outside [0:%lu], the range of the string",
            __FUNCTION__,
            char_index,
            (UInt64)this->value.length()
      );

      return new String(this->value[char_index]);
   }

   UInt64
   String::get_length ()
   {
      return (UInt64)this->value.length();
   }

   String*
   String::insert (UInt64 at_index, String* splice_str)
   {
      UInt64 this_len = this->value.length();
      UInt64 splice_str_len = splice_str->value.length();
      UInt64 joined_len = this_len + splice_str_len;

      char* psJoinedStr = new char[joined_len + 1];

      // Copies the first portion (before @prm{at_index})
      LOOP_FROM_TO(UInt64, char_index, 0, at_index)
      {
         psJoinedStr[char_index] = this->value[char_index];
      }

      // Copies the splice string
      LOOP_FROM_TO(UInt64, char_index, 0, splice_str_len)
      {
         psJoinedStr[at_index + char_index] = splice_str->value[char_index];
      }

      // Copies the second portion (after @prm{at_index})
      ULong second_portion_at = at_index + splice_str_len;
      LOOP_FROM_TO(UInt64, char_index, at_index, this_len)
      {
         psJoinedStr[second_portion_at + char_index] = this->value[char_index];
      }

      String* result = new String(psJoinedStr, joined_len);
      delete psJoinedStr;

      return result;
   }

   bool
   String::is_alphabetic ()
   {
      UInt64 str_len = this->value.length();
      bool is_alphabetic = false;

      if (str_len > 0)
      {
         is_alphabetic = true;

         LOOP_FROM_TO(UInt64, char_index, 0, str_len)
         {
            if (this->value[char_index] < 'A' || (this->value[char_index] > 'Z' && this->value[char_index] < 'a') || this->value[char_index] > 'z')
            {
               is_alphabetic = false;
               break;
            }
         }
      }
      else
      {
         is_alphabetic = false;
      }

      return is_alphabetic;
   }

   bool
   String::is_digit ()
   {
      UInt64 str_len = this->value.length();
      bool is_digit = false;

      if (str_len > 0)
      {
         is_digit = true;

         LOOP_FROM_TO(UInt64, char_index, 0, str_len)
         {
            if (this->value[char_index] < '0' || this->value[char_index] > '9')
            {
               is_digit = false;
               break;
            }
         }
      }
      else
      {
         is_digit = false;
      }

      return is_digit;
   }

   bool
   String::is_lowercase ()
   {
      UInt64 str_len = this->value.length();
      bool is_lowercase = true;

      LOOP_FROM_TO(UInt64, char_index, 0, str_len)
      {
         if (this->value[char_index] >= 'A' && this->value[char_index] <= 'Z')
         {
            is_lowercase = false;
            break;
         }
      }

      return is_lowercase;
   }

   bool
   String::is_space ()
   {
      ULong this_len = this->value.length();
      bool is_space = false;

      if (this_len > 0)
      {
         is_space = true;

         LOOP_FROM_TO(UInt64, char_index, 0, this_len)
         {
            if (this->value[char_index] > ' ')
            {
               is_space = false;
               break;
            }
         }
      }
      else
      {
         is_space = false;
      }

      return is_space;
   }

   bool
   String::is_uppercase ()
   {
      UInt64 this_len = this->value.length();
      bool is_uppercase = true;

      LOOP_FROM_TO(UInt64, char_index, 0, this_len)
      {
         if (this->value[char_index] >= 'a' && this->value[char_index] <= 'z')
         {
            is_uppercase = false;
            break;
         }
      }

       return is_uppercase;
   }

   String*
   String::lower_case ()
   {
      UInt64 lower_case_str_len = this->value.length();
      char* lower_case_str_arr = new char[lower_case_str_len];

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

      String* result = new String(lower_case_str_arr, lower_case_str_len);
      delete lower_case_str_arr;
      return result;
   }

   String*
   String::lpad (UInt64 dest_str_final_len, String* pad_str)
   {
      char* dest_str = new char[dest_str_final_len];
      UInt64 this_len = this->value.length();
      UInt64 pad_str_len = pad_str->value.length();
      UInt64 dest_str_current_len = 0;

      // Copies [this] at the end of the array.
      for (UInt64 char_index = 0 ; char_index < this_len ; ++ char_index)
      {
         dest_str[dest_str_final_len - this_len + char_index] = this->value[char_index];
      }

      // As long as we did not feel the array...
      while (dest_str_current_len < dest_str_final_len)
      {
         // ... copies another time pad_str, backwardly.
         for (UInt64 char_index = pad_str_len - 1 ; char_index >= 0  && dest_str_current_len < dest_str_final_len ; --char_index)
         {
            dest_str[dest_str_final_len - dest_str_current_len] = pad_str->value[char_index];
            ++ dest_str_current_len;
         }
      }
      ASSERT(dest_str_current_len == dest_str_final_len, "We did not feel the array completely, what's wrong ?");

      String* result = new String(dest_str, dest_str_final_len);
      delete dest_str;
      return result;
   }

   String*
   String::multiply (UInt8 nTimes)
   {
      UInt64 dwFinalStrLen = this->value.length() * nTimes;
      char* psFinalStr = new char[dwFinalStrLen];

      // For each from 0 to pTimes, append itself.

      // For pTimes->value == n, result string should look like
      // +---1---+---2---+--...--+---n---+
      // | this  | this  |       | this  |
      // +-------+-------+--...--|-------+
      //
      LOOP_FROM_TO(uint8_t, i, 0, nTimes)
      {
         LOOP_FROM_TO(UInt64, dwCharIndex, 0, this->value.length())
         {
            psFinalStr[i * this->value.length() + dwCharIndex] = this->value[dwCharIndex];
         }
      }

      String* pResult = new String(psFinalStr, dwFinalStrLen);
      delete psFinalStr;
      return pResult;
   }

   String*
   String::pad (UInt64 padded_str_final_len, String* pad_str)
   {
      char* padded_str_arr = new char[padded_str_final_len];
      UInt64 padded_str_current_len = 0;
      UInt64 this_len = this->value.length();
      UInt64 pad_str_len = pad_str->value.length();

      // Copies [this] into the array.
      for (ULong char_index = 0 ; char_index < this_len ; ++ char_index)
      {
         padded_str_arr[char_index] = this->value[char_index];
      }

      // As long as the array is not filled...
      while (padded_str_current_len < padded_str_final_len)
      {
         // ... copies another [pad_str] into the array.
         for (ULong char_index = 0 ; char_index < pad_str_len && padded_str_current_len < padded_str_final_len; ++char_index)
         {
            padded_str_arr[padded_str_current_len] = pad_str->value[char_index];
            ++ padded_str_current_len;
         }
      }

      ASSERT(padded_str_current_len == padded_str_final_len, "We did not feel the array completely, what's wrong ?");

      String* result = new String(padded_str_arr, padded_str_final_len);
      delete padded_str_arr;
      return result;
   }

   void
   String::print (Object* pString)
   {
      String::assert(pString);

      printf("%s", ((String*)pString)->value.c_str());
   }

   void
   String::print_line (Object* pString)
   {
      String::assert(pString);

      printf("%s\n", ((String*)pString)->value.c_str());
   }

   String*
   String::reverse ()
   {
      UInt64 this_len = this->value.length();
      char* reversed_str_arr = new char[this_len];

      LOOP_FROM_TO(ULong, char_index, 0,this_len)
      {
         reversed_str_arr[this_len - char_index - 1] = this->value[char_index];
      }

      String* result = new String(reversed_str_arr, this_len);
      delete reversed_str_arr;

      return result;
   }

   String*
   String::strip (String* characters, UInt64 start_at, UInt64 end_at)
   {
      return new String();
   }

   String*
   String::swap_case ()
   {
      UInt64 dwThisLen= this->value.length();
      char* psSwapedCaseStr = new char[dwThisLen];

      LOOP_FROM_TO (UInt64, dwCharIndex, 0, dwThisLen)
      {
         if (this->value[dwCharIndex] >= 'a' && this->value[dwCharIndex] <= 'z')
         {
            psSwapedCaseStr[dwCharIndex] = this->value[dwCharIndex] - 32;
         }
         else if (this->value[dwCharIndex] >= 'A' && this->value[dwCharIndex] <= 'Z')
         {
            psSwapedCaseStr[dwCharIndex] = this->value[dwCharIndex] + 32;
         }
         else
         {
            psSwapedCaseStr[dwCharIndex] = this->value[dwCharIndex];
         }
      }

      String* pSwapedCaseStr = new String(psSwapedCaseStr, dwThisLen);
      delete psSwapedCaseStr;
      return pSwapedCaseStr;
   }

   String*
   String::upper_case ()
   {
      UInt64 this_len = this->value.length();
      char* upper_cased_str_arr = new char[this_len];

      LOOP_FROM_TO(UInt64, char_index, 0, this_len)
      {
         if (this->value[char_index] >= 'a' && this->value[char_index] <= 'z')
         {
            upper_cased_str_arr[char_index] = this->value[char_index] - 32;
         }
         else
         {
            upper_cased_str_arr[char_index] = this->value[char_index];
         }
      }

      String* result = new String(upper_cased_str_arr, this_len);
      delete upper_cased_str_arr;
      return result;
   }
}

