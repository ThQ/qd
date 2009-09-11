#ifndef T__ARRAY__H
#define T__ARRAY__H __FILE__

#include "t/BaseArray.h"
#include "vm/Class.h"

#define T__ARRAY__ASSERT_ITEM_TYPE(given, expected) \
   ASSERT(given == expected, "BAD_ITEM_TYPE (.given %u, .expected %u)", (uint)(given), (uint)(expected))
#define T__ARRAY__ASSERT_IN_RANGE(pArray, nIndex, nLength) \
   ASSERT( \
         nIndex < nLength, \
         "<Array:0x%x> INDEX_OUT_OF_RANGE (.index %u, .length %u)\n", \
         (uint)pArray, \
         (nIndex), \
         (nLength) \
   );

namespace t
{
   extern vm::Class cARRAY;

   /**
    * A @cls{t::Array} is a list of @cls{t::Object}'s who can only contain elements of a
    * predetermined type and who can never exceed a predetermined (and fixed) number of
    * elements.
    */
   class Array : public BaseArray
   {
      /**
       * @brief Default constructor.
       */
      public: Array ();

      /**
       * @brief Constructs an array whose type and length are known.
       *
       * @param nItemType A ushort describing the type of the items stored in the aray.
       * @param dwArrayLength The length of the array to create.
       */
      public: Array (ushort nItemType, uint dwArrayLength);

      /**
       * @brief Constructs an array whose type and length are known.
       *
       * @param nItemType A ushort describing the type of the items stored in the aray.
       * @param pItemClass A pointer to a @cls{t::Class} to use as item type.
       * @param dwArrayLength The length of the array to create.
       */
      public: Array (ushort nItemType, vm::Class* pItemClass, uint dwArrayLength);

      /**
       * @brief Constructs an array whose type and length are known.
       *
       * @param nItemType A ushort describing the type of the items stored in the aray.
       * @param pItemClass A pointer to a @cls{t::Class} to use as item type.
       * @param dwArrayLength The length of the array to create.
       * @param pItems An array of @cls{t::Value}'s to fill the array. It must
       * contain at least @prm{dwArrayLength} objects.
       */
      public: Array (ushort nItemType, vm::Class* pItemClass, uint dwArrayLength, Value* pItems);

      /**
       * Destructor.
       */
      public: ~Array ();

      /**
       * @brief Deletes a t::Array.
       *
       * @param pObject The t::Array to delete.
       */
      public: static void __delete__ (Value pObject);

      /**
       * @brief Creates a new t::Array.
       *
       * @return A pointer to the t::Array created.
       */
      public: static Value __new__ ();

      /**
       * @brief Prints the string representation of an array.
       *
       * @param o An array to print.
       * @todo Make it print objects too.
       */
      public: static void __print__ (Value o);

      /**
       * @brief Prints on a new line the string representation of an array.
       *
       * @param pObject An array to print.
       */
      public: static void __print_line__ (Value pObject);

      /**
       * Initializes an Array object.
       */
      protected: inline void _init ()
      {
         this->klass = &cARRAY;
         this->type = t::ARRAY_TYPE;
         this->item_type = t::UNDEFINED_TYPE;
         this->item_class = NULL;
         this->items = NULL;
         this->length = 0;

         ASSERT_NOT_NULL(this->klass);
         ASSERT(this->type != t::UNDEFINED_TYPE, "Array object must have a type");
      }

      /**
       * @brief Copies an array to a new one.
       */
      public: Array* copy ();

      /**
       * @brief Asserts that an object is of type t::ARRAY_TYPE.
       *
       * @param obj The object to check.
       */
      public: inline static void assert (Object* obj)
      {
         obj->assert_type(t::ARRAY_TYPE);
      }

      /**
       * @brief Checks if an object is of type @cls{t::Array}.
       *
       * @param obj A pointer to a @cls{t::Object} to check.
       * @return true if @prm{obj} is a pointer to a @cls{t::Object}.
       */
      public: inline static bool check (t::Object* obj)
      {
         return obj->check_type(t::ARRAY_TYPE);
      }

      public: inline int get_int (uint nIndex)
      {
         T__ARRAY__ASSERT_IN_RANGE(this, nIndex, this->length);
         return (int)this->items[nIndex];
      }

      public: inline Object* get_object (uint nIndex)
      {
         T__ARRAY__ASSERT_IN_RANGE(this, nIndex, this->length);
         return (Object*)this->items[nIndex];
      }

      public: inline uint get_uint (uint nIndex)
      {
         T__ARRAY__ASSERT_IN_RANGE(this, nIndex, this->length);
         return (uint)this->items[nIndex];
      }

      public: inline void set_int (uint nIndex, int nValue)
      {
         T__ARRAY__ASSERT_IN_RANGE(this, nIndex, this->length);
         this->set_value(nIndex, (Value)nValue);
      }

      public: inline void set_object (uint nIndex, Object* pObj)
      {
         T__ARRAY__ASSERT_IN_RANGE(this, nIndex, this->length);
         this->set_value(nIndex, (Value)pObj);
      }

      public: inline void set_uint (uint nIndex, uint nValue)
      {
         T__ARRAY__ASSERT_IN_RANGE(this, nIndex, this->length);
         this->set_value(nIndex, (Value)nValue);
      }

      public: void set_value (uint nIndex, Value pValue)
      {
         T__ARRAY__ASSERT_IN_RANGE(this, nIndex, this->length);
         this->items[nIndex] = pValue;
      }

      /**
       * @brief Allocates memory for @prm{array_size} items in array [this->items] and
       * fills each dimension with NULL.
       *
       * @param array_size The size of the array.
       */
      public: void size (uint array_size);

      /**
       * @brief Slices an array and returns the slice array.
       *
       * @param nStartIndex Start index of the slice.
       * @param nLength Length of the slice.
       * @param nStep Step used to make the slice.
       * @return An array containing the slice.
       */
      public: t::Array* slice (uint nStartIndex, uint nLength, uint nStep);
   };
}

#endif
