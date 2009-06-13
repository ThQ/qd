#ifndef T_STRING
#define T_STRING t::String

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "t/Bool.h"
#include "t/Int.h"
#include "t/Object.h"

namespace t
{
   extern T_OBJECT* tSTRING;

   /**
    * A string of characters.
    *
    * @todo Create method [cut_before]
    */
   class String : public Object
   {
      public: std::string value; ///< The content of the string.

      /**
       * Constructor.
       */
      public: String();

      /**
      public: static T_OBJECT* append(T_OBJECT* base, T_OBJECT* s);


      public: static T_OBJECT* append(T_OBJECT* base, ULong i);
      public: static T_OBJECT* append(T_OBJECT* base, char c);
      */

      /**
       * Asserts that an object is of type t::String.
       */
      public: inline static void assert(T_OBJECT* obj)
      {
         ASSERT_NOT_NULL(NS_TYPE::tSTRING);
         T_OBJECT::assert_type(obj, NS_TYPE::tSTRING);
      }

      /**
       * Creates a new empty @cls{t::String}.
       *
       * @return A pointer to a new empty @cls{t::String}.
       */
      public: static T_OBJECT* build();

      /**
       * Creates a @cls{t::String} by copying another one.
       */
      public: static T_OBJECT* build(String* s);

      /**
       * Creates a @cls{t::String} by using a C char.
       */
      public: static T_OBJECT* build(char c);

      /**
       * Creates a @cls{t::String} by using a C string.
       */
      public: static T_OBJECT* build(const char* s);

      /**
       * Creates a @cls{t::String} by using a std::string.
       */
      public: static T_OBJECT* build(std::string s);

      /**
       * Centers a string on a given length with a given string.
       *
       * @param str_base The base string to center.
       * @param centered_length The length of the new string centered.
       * @param pad_str The string to use as padding (left and right).
       * @return A pointer to a new @cls{t::String} which content is the one of @prm{str_base} centered on @prm{centered_length} using @prm{pad_str}.
       */
      public: static T_OBJECT* center(T_OBJECT* str_base, T_OBJECT* centered_length, T_OBJECT* pad_str);

      /**
       * Checks if an object is of type t::String.
       *
       * @param obj The object to check.
       * @return true if @prm{obj} is of type t::tSTRING, false otherwise.
       */
      public: inline static bool check(T_OBJECT* obj)
      {
         return T_OBJECT::check_type(obj, NS_TYPE::tSTRING);
      }

      /**
       * Compares the contents of two @cls{t::String}.
       *
       * @param str1 The first string.
       * @param str2 The second string.
       * @return 0 if str1==str2, what otherwise ?? (see std::string.compare)
       * @todo Document properly.
       */
      public: static Short compare_to(T_OBJECT* str1, T_OBJECT* str2);

      /**
       * Creates a new @cls{t::String} whose content is the same as another one.
       *
       * @param base_str The base string to copy.
       * @return A pointer to a new @cls{t::String} with the same content as @prm{base_str}.
       */
      public: static T_OBJECT* copy(String* base_str);

      /**
       * Cuts a string after a substring is found.
       *
       * @param base_str The string to cut.
       * @param search_str The substring to search
       * @return A pointer to a new @cls{t::String} whose content is @prm{base_str} cut after the first occurence of @prm{search_str}.
       */
      public: static T_OBJECT* cut_after(String* base_str, String* search_str);

      /**
       * Cuts a string after a given index.
       *
       * @param base_str The string to cut.
       * @param cut_at At which index to cut.
       * @return A pointer to a new @cls{t::String}} whose content is @prm{base_str} from index 0 to @prm{cut_at}.
       */
      public: static T_OBJECT* cut_at(T_OBJECT* base_str, T_OBJECT* cut_at);

      /**
       * Checks if two strings have the same content.
       */
      public: static T_OBJECT* equals(T_OBJECT* s1, T_OBJECT* s2);

      /**
       * Finds a t::String substring in another t::String, starting from
       * @prm{start_at}.
       */
      public: static T_OBJECT* find(T_OBJECT* s, T_OBJECT* search, T_OBJECT* start_at);

      /**
       * Returns the character at @prm{char_index} in @prm{base_str} as a @cls{t::String}.
       *
       * @param base_str The string to get a character from.
       * @param char_index The index of the character to get.
       * @return A pointer to a new @cls{t::String} only containing the character to get.
       */
      public: static T_OBJECT* get_character(String* base_str, Int* char_index);

      /**
       * Returns the length of a @cls{t::String}.
       *
       * @return A pointer to a @cls{t::Int} containing the length of the string.
       */
      public: T_OBJECT* get_length();

      /**
       * Inserts a string into another one.
       *
       * @param at_index At which position to insert.
       * @param splice_str The string to insert.
       * @return A pointer to a new @cls{t::String} which content is the same as [this] with the substring inserted.
       */
      public: static T_OBJECT* insert(ULong at_index, String* splice_str);

      /**
       * Tests if a string only contains letter.
       *
       * @return t::gTRUE if the string only contains letter, t::gFALSE otherwise.
       */
      public: T_OBJECT* is_alphabetic();

      /**
       * Tests if a string only contains digits.
       *
       * @return t::gTRUE if the string only contains digits, t::gFALSE otherwise.
       */
      public: T_OBJECT* is_digit();

      /**
       * Tests if a string is lowercased.
       *
       * @return t::gTRUE if the string is lowercased, t::gFALSE otherwise.
       */
      public: T_OBJECT* is_lowercase();

      /**
       * Tests if it only contains space characters.
       *
       * @return t::gTRUE if it only contains space characters.
       * @todo Make this take into account tabs, EOL, etc.
       */
      public: T_OBJECT* is_space();

      /**
       * Tests if all letters are upper case.
       *
       * @return t::gTRUE if all characters are uppercased, t::gFALSE otherwise.
       */
      public: T_OBJECT* is_uppercase();

      /**
       * Tests if all letters contained in a @cls{t::String} are upper case.
       *
       * @return t::gTRUE if all characters are uppercased, t::gFALSE otherwise.
       */
      public: inline static T_OBJECT* is_uppercase(T_OBJECT* str)
      {
         String::assert(str);
         return ((String*)str)->is_uppercase();
      }

      /**
       * Creates a @cls{t::String} by joining two other strings.
       *
       * @param str1 First string.
       * @param str2 First string.
       * @return A pointer to a @cls{t::String} whose value = str1 + str2.
       */
      public: static T_OBJECT* join(String* str1, String* str2);

      /**
       * Copies this string and converts all characters to lower case.
       * @return A pointer to a new @cls{t::String} which is a copy of @prm{base_string} all lowercased.
       */
      public: T_OBJECT* lower_case();

      /**
       * Creates a @cls{t::String} which is a copy of a base string left padded to a certain length.
       *
       * @param pad_len The length of the padded string.
       * @param pad_str The string to be used as padding.
       * @return A pointer to a new @cls{t::String} whose value is [this] padded to @prm{pad_len} using @prm{pad_str}.
       */
      public: static T_OBJECT* lpad(ULong pad_len, String* pad_str);

      /**
       * Creates a @cls{t::String} whose content is the one of @prm{self} multiplied n times.
       *
       * @param times The number of times to multiply the base string.
       * @return A pointer to a @cls{t::String} whose value is @prm{base_str} concatenated n times.
       */
      public: static T_OBJECT* multiply(Int* times);

      /**
       * Creates a @cls{t::String} which is a copy of a base string right padded to a certain length.
       *
       * @param pad_len The length of the padded string.
       * @param pad_str The string to be used as padding.
       * @return A pointer to a new @cls{t::String} whose value is @prm{base_str} padded to @prm{pad_len} using @prm{pad_str}.
       */
      public: static T_OBJECT* pad(ULong pad_len, String* pad_str);

      /**
       * Prints the content of a t::String.
       */
      public: static void print(T_OBJECT* s);

      /**
       * Prints the content of a t::String on a new line.
       */
      public: static void print_line(T_OBJECT* s);

      /**
       * Reverses the characters of a t::String.
       */
      public: static T_OBJECT* reverse(T_OBJECT* self);

      /**
       * Strips white characters off a t::String <self.>
       */
      public: static T_OBJECT* strip(T_OBJECT* self, T_OBJECT* characters, T_OBJECT* start_at, T_OBJECT* end_at);

      /**
       * Changes all lowercased characters to upper case, and all uppercased
       * characters to lower case.
       */
      public: static T_OBJECT* swap_case(T_OBJECT* self);

      /**
       * Converts all lower case letters to upper case.
       *
       * @return A pointer to a new @cls{t::String} which content is the same as this but with all letters uppercased.
       */
      public: T_OBJECT* upper_case();
   };
}

#endif

