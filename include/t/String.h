#ifndef T__STRING__H
#define T__STRING__H __FILE__

#include <stdlib.h>
#include <stdio.h>
#include <string>

#include "t/Collection.h"

namespace t
{
   extern vm::Class cSTRING;

   /**
    * @brief A string of characters.
    *
    * @todo Remove dependency to std::string.
    */
   class String : public Collection
   {
      public: std::string value; ///< The content of the string.

      /**
       * @brief Constructor.
       */
      public: String ();

      /**
       * @brief Creates a new string with a char.
       *
       * @param chr The character to base the new string on.
       */
      public: String (char chr);

      /**
       * @brief Creates a new string based on a character array.
       *
       * @param string_arr The character array to be used as value.
       */
      public: String (const char* string_arr);

      /**
       * @brief Creates a new string based on a character array.
       *
       * @param string_arr The character array to be used as value.
       */
      public: String (char* string_arr);

      /**
       * @brief Creates a new string based on a character array.
       *
       * @param string_arr The character array to be used as value.
       * @param string_arr_len The length of the character array.
       */
      public: String (char* string_arr, uint string_arr_len);

      /**
       * @brief Creates a new string based on another one.
       *
       * @param str The string to copy.
       */
      public: String (String* str);

      /**
       * @brief Creates a new string based on another one.
       *
       * @param str The string to copy.
       */
      public: String (std::string str);

      /**
       * @brief Initializes a string object.
       */
      protected: inline void _init ()
      {
         this->klass = &t::cSTRING;
      }

      /**
       * @brief Asserts that an object is of type t::String.
       */
      public: inline static void assert (Object* obj)
      {
         obj->assert_type(t::STRING_TYPE);
      }

      /**
       * @brief Centers a string on a given length with a given string.
       *
       * @param centered_length The length of the new string centered.
       * @param pad_str The string to use as padding (left and right).
       * @return A pointer to a new @cls{t::String} which content is the one of @prm{str_base} centered on @prm{centered_length} using @prm{pad_str}.
       * @todo Break this into functions: left padding and right padding in place.
       */
      public: String* center (uint centered_length, String* pad_str);

      /**
       * @brief Checks if an object is of type t::String.
       *
       * @param obj The object to check.
       * @return true if @prm{obj} is of type t::tSTRING, false otherwise.
       */
      public: inline static bool check (Object* obj)
      {
         return obj->check_type(t::STRING_TYPE);
      }

      /**
       * @brief Compares the contents of two @cls{t::String}.
       *
       * @param pCompareStr The string to compare two.
       * @return 0 if str1==str2, what otherwise ?? (see std::string.compare)
       * @todo Document properly.
       */
      public: Short compare_to (String* pCompareStr);

      /**
       * @brief Copies the content in another newly created @cls{t::String}.
       *
       * @return A pointer to a new @cls{t::String} with the same content as @prm{base_str}.
       */
      public: String* copy ();

      /**
       * @brief Cuts a string after a substring is found.
       *
       * @param pSubstring The substring to search
       * @return A pointer to a new @cls{t::String} whose content is [this] cut after the first occurence of @prm{pSubstring}.
       */
      public: String* cut_after (String* pSubstring);

      /**
       * @brief Cuts a string after a given index.
       *
       * @param cut_at At which index to cut.
       * @return A pointer to a new @cls{t::String} whose content is @prm{base_str} from index 0 to @prm{cut_at}.
       */
      public: String* cut_at (uint cut_at);

      /**
       * @brief Cuts a string before a substring is found.
       *
       * @param pSubstring The substring to search
       * @return A pointer to a new @cls{t::String} whose content is [this] cut before the first occurence of @prm{pSubString}.
       */
      public: String* cut_before (String* pSubstring);

      /**
       * Destroys a @cls{t::String} object.
       *
       * @param pObject A pointer to a @cls{t::String} object to destroy.
       * @return true if everything went well.
       */
      public: inline static bool destroy (Value pObject)
      {
         return t::Object::destroy(pObject);
      }

      /**
       * @brief Checks if two strings have the same content.
       *
       * @param compare_str The string to compare to.
       * @return true if it has the same content.
       */
      public: bool equals (String* compare_str);

      /**
       * @brief Finds a substring starting at @prm{start_at}.
       *
       * @param sub_str The substring to look for.
       * @param start_at The index at which to start looking for.
       * @param found_at A pointer that will receive the index at which
       * the substring was found (points to uint(0) if not found).
       * @return true if the substring was found.
       */
      public: inline bool find (String* sub_str, uint start_at, uint& found_at)
      {
         return this->find(sub_str, start_at, this->value.length(), found_at);
      }

      /**
       * @brief Finds a substring starting at @prm{start_at}.
       *
       * @param sub_str The substring to look for.
       * @param start_at The index at which to start looking for.
       * @param end_at The index at which to end looking for.
       * @param found_at A pointer that will receive the index at which
       * the substring was found (points to uint(0) if not found).
       * @return true if the substring was found.
       */
      public: bool find (String* sub_str, uint start_at, uint end_at, uint& found_at);

      /**
       * @brief Gets a character.
       *
       * @param char_index The index of the character to get.
       * @return A pointer to a new @cls{t::String} only containing the character to get.
       */
      public: String* get_character (uint char_index);

      /**
       * @brief Returns the length of a @cls{t::String}.
       *
       * @return A pointer to a @cls{t::Int} containing the length of the string.
       */
      public: uint get_length ();

      /**
       * @brief Inserts a string into another one.
       *
       * @param at_index At which position to insert.
       * @param splice_str The string to insert.
       * @return A pointer to a new @cls{t::String} which content is the same as [this] with the substring inserted.
       */
      public: String* insert (uint at_index, String* splice_str);

      /**
       * @brief Tests if a string only contains letter.
       *
       * @return true if the string only contains letter.
       */
      public: bool is_alphabetic ();

      /**
       * @brief Tests if a string only contains digits.
       *
       * @return true if the string only contains digits.
       */
      public: bool is_digit ();

      /**
       * @brief Tests if a string is lowercased.
       *
       * @return true if the string is lowercased.
       */
      public: bool is_lowercase ();

      /**
       * @brief Tests if it only contains space characters.
       *
       * @return true if it only contains space characters.
       * @todo Make this take into account tabs, EOL, etc.
       */
      public: bool is_space ();

      /**
       * @brief Tests if all letters are upper case.
       *
       * @return true if all characters are uppercased.
       */
      public: bool is_uppercase ();

      /**
       * @brief Copies this string and converts all characters to lower case.
       *
       * @return A pointer to a new @cls{t::String} which is a copy of @prm{base_string} all lowercased.
       */
      public: String* lower_case ();

      /**
       * @brief Creates a @cls{t::String} which is a copy of a base string left padded to a certain length.
       *
       * @param pad_len The length of the padded string.
       * @param pad_str The string to be used as padding.
       * @return A pointer to a new @cls{t::String} whose value is [this] padded to @prm{pad_len} using @prm{pad_str}.
       */
      public: String* lpad (uint pad_len, String* pad_str);

      /**
       * @brief Creates a @cls{t::String} whose content is the one of @prm{self} multiplied n times.
       *
       * @param times The number of times to multiply the base string.
       * @return A pointer to a @cls{t::String} whose value is @prm{base_str} concatenated n times.
       */
      public: String* multiply (uint times);

      /**
       * @brief Creates a @cls{t::String} which is a copy of a base string right padded to a certain length.
       *
       * @param pad_len The length of the padded string.
       * @param pad_str The string to be used as padding.
       * @return A pointer to a new @cls{t::String} whose value is @prm{base_str} padded to @prm{pad_len} using @prm{pad_str}.
       */
      public: String* pad (uint pad_len, String* pad_str);

      /**
       * @brief Prints the content.
       */
      public: static void print (Value pString);

      /**
       * @brief Prints the content on a new line.
       */
      public: static void print_line (Value pString);

      /**
       * @brief Reverses the characters.
       */
      public: String* reverse ();

      /**
       * @brief Strips white characters off a t::String <self.>
       *
       * @todo Make this work
       */
      public: String* strip (String* characters, uint start_at, uint end_at);

      /**
       * @brief Changes all lowercased characters to upper case, and all uppercased
       * characters to lower case.
       */
      public: String* swap_case ();

      /**
       * @brief Converts all lower case letters to upper case.
       *
       * @return A pointer to a new @cls{t::String} which content is the same as this but with all letters uppercased.
       */
      public: String* upper_case ();
   };
}

#endif

