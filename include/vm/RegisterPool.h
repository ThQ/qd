#ifndef VM__REGISTER_POOL__H
#define VM__REGISTER_POOL__H __FILE__

#include "t/Object.h"
#include "t/RegisterObject.h"
#include "Memory.h"
#include "types.h"

namespace vm
{
   /**
    * @brief A place to manage all the registers allocations/deallocation/retrieval/etc...
    *
    * How ::values looks likes :
    *
    * /================\ int_register_start_at = 0
    * |     Int 0      |
    * |----------------|
    * |      ...       |
    * |----------------|
    * |     Int x      |
    * |================| long_register_start_at = int_register_start_at + int_register_length
    * |     Long 0     |
    * |----------------|
    * |      ...       |
    * |----------------|
    * |     Long y     |
    * |================| object_register_start_at = long_register_start + long_register_length
    * |    Object 1    |
    * |----------------|
    * |      ...       |
    * |----------------|
    * |    Object z    |
    * \================/ length
    *
    * Depending on the machines, each Long slot may take more than one word.
    */
   class RegisterPool
   {
      public: uint              int_register_start_at;   ///< Where the int register start.
      public: uint              int_register_length;     ///< The length of the int register.
      public: uint              length;                  ///< The length of all registers cumulated.
      public: uint              long_register_start_at;  ///< Where the long register start.
      public: uint              long_register_length;    ///< The length of the long register.
      public: uint              object_register_start_at;///< Where the object register start.
      public: uint              object_register_length;  ///< The length of the object register.
      public: t::Value*         values;                  ///< An array of all the values.

      /**
       * @brief Default contructor.
       */
      public: RegisterPool();

      /**
       * @brief Destructor.
       *
       * @todo Determine why objects don't get dropped.
       */
      public: ~RegisterPool();

      /**
       * @brief Cleans everything up.
       */
      public: void destroy();

      /**
       * @brief Gets a value in the int register.
       *
       * @param nIndex Index of the value to get in the int register.
       * @return The int value wanted.
       */
      public: int get_int (uint nIndex);

      /**
       * @brief Gets a value in the long register.
       *
       * @param nIndex Index of the value to get in the long register.
       * @return The long value wanted.
       */
      public: long get_long (uint nIndex);

      /**
       * @brief Gets a value in the object register.
       *
       * @param nIndex Index of the value to get in the object register.
       * @return The object pointer wanted.
       */
      public: t::Object* get_object (uint nIndex);

      /**
       * @brief Prints a representation of the registers to the console.
       */
      public: void print ();

      /**
       * @brief Sets a value in the int register.
       *
       * @param nIndex Index of the value to set in the int register.
       * @param nValue The int value to use.
       */
      public: void set_int (uint nIndex, int nValue);

      /**
       * @brief Sets a value in the long register.
       *
       * @param nIndex Index of the value to set in the long register.
       * @param nValue The long value to use.
       */
      public: void set_long (uint nIndex, long nValue);

      /**
       * @brief Sets a value in the object register.
       *
       * @param nIndex Index of the value to set in the object register.
       * @param pObject The object pointer to use.
       */
      public: void set_object (uint nIndex, t::Object* pObject);

      /**
       * @brief Sets a value in the int register.
       *
       * @param nIndex Index of the value to set in the int register.
       * @param nValue The unsigned int value to use.
       */
      public: inline void set_uint (uint nIndex, uint nValue)
      {
         this->set_int(nIndex, (int)nValue);
      }

      /**
       * @brief Sets a value in the long register.
       *
       * @param nIndex Index of the value to set in the long register.
       * @param nValue The unsigned long value to use.
       */
      public: inline void set_ulong (uint nIndex, ulong nValue)
      {
         this->set_int(nIndex, (long)nValue);
      }

      /**
       * @brief Sizes this registry pool.
       *
       * @param nInt How many int registers.
       * @param nLong How many long registers.
       * @param nObject How many object registers.
       * @todo Take into account platform variations (is a long really two ints long ?)
       */
      public: void size (uint nInt, uint nLong, uint nObject);
   };
}

#endif
