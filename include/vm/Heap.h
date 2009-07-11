#ifndef VM_HEAP
#define VM_HEAP NS_VM::Heap

#include "t/HeapObject.h"

namespace vm
{
   class Heap
   {
      public: const uint kBASE_ROOM_STEP = 10;

      public: T_OBJECT** items;
      public: uint item_count;
      public: uint last_position;
      public: uint rooms;
      public: uint resizing_count;

      /**
       * Default constructor.
       */
      public: Heap();

      /**
       * Destructor.
       */
      public: ~Heap();

      /**
       * Pushes an object.
       *
       * @param pObject An object to push.
       */
      public: void append(T_OBJECT* pObject);
      public: void append(uint object_count, T_OBJECT** objects);

      /**
       * @brief Clears the heap.
       *
       * Replaces each item with NULL, droping objects when necessary. No
       * resizing is done.
       */
      public: void clear();

      /**
       * @brief Counts how many items there are.
       *
       * @return How many items there are.
       */
      public: uint count();

      /**
       * @brief Gets an item.
       *
       * @param nAt The index of the item to get.
       * @return A pointer to the object to get.
       */
      public: t::Object* get(uint nAt);

      /**
       * @brief Picks the last objects pops it off.
       *
       * @return A pointer to the object poped.
       */
      public: t::Object* pick_last_and_pop();

      /**
       * @brief Pops one item off.
       */
      public: inline void pop()
      {
         this->pop(1);
      }

      /**
       * @brief Pops n items off.
       *
       * @param nCount The number of items to pop.
       */
      public: void pop(uint nCount);

      /**
       * @brief Replaces an item by another.
       *
       * @param nAt The index of the item to replace.
       * @param pReplacement The object to use as replacement.
       */
      public: void replace_at(uint nAt, t::Object* pReplacement);

      /**
       * @brief Resizes to an exact size.
       *
       * @param nRooms The new size.
       */
      public: void resize(uint nRooms);

      /**
       * @brief Grows the heap.
       */
      public: void resize_up();

      /**
       * @brief Reverse n elements at the end.
       *
       * @param nNum The number of elements to reverse.
       */
      public: void reverse(uint nNum);

      /**
       * @brief Swaps the last two items.
       */
      public: void swap()
   };
}

#endif
