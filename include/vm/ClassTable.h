#ifndef VM_CLASS_TABLE

#define VM_CLASS_TABLE NS_VM::ClassTable

#include "t/Class.h"
#include "t/CoreFunction.h"
#include "t/Function.h"
#include "t/String.h"
#include "t/UserFunction.h"
#include "t/Variable.h"
#include "vm/ClassTableEntry.h"

namespace NS_VM
{
   /**
    * A list of all classes declared internally.
    *
    * @todo Make that a Bn-Tree
    */
   class ClassTable
   {
      /**
       * An pointer to an array of pointers to ClassTableEntry's.
       */
      public: ClassTableEntry** items;

      /**
       * How many ClassTableEntry in this ClassTable.
       */
      public: ULong item_count;

      /**
       * Constructor.
       */
      public: ClassTable();

      /**
       * Destructor.
       */
      public: ~ClassTable();

      /**
       * Append a t::Class to the list.
       */
      public: void append(t::Class* cls);

      /**
       * Appends a ClassTableEntry to the list.
       */
      public: void append(ClassTableEntry* entry);

      /**
       * Appends a t::Function to a t::Class contained in the list.
       */
      public: bool append_method_to(t::Class* cls, t::Function* func);

      #ifdef _DEBUG_
      /**
       * Tries to assert the validity of a ClassTable.
       */
      public: void assert_validity();
      #endif


      /**
       * Return how many classes are stored in this list.
       */
      public: ULong count();

      //public: bool declare_fields(t::Class* cls, unsigned long field_count, svm::Variable** fields);

      /**
       * Create a new class named [class_name] and store it in this list.
       */
      public: t::Object* declare_class(const char* class_name);

      /**
       * Create a new class named [class_name], whose parent is [parent_class],
       * and store it in this list.
       */
      public: t::Object* declare_class(const char* class_name, t::Object* parent_class);

      /**
       * Create a new class named [class_name], whose parent name is
       * [parent_class_name], and store it in this list.
       */
      public: t::Object* declare_class(const char* class_name, const char* parent_class_name);
      public: t::Object* declare_method(t::Class* cls, t::CoreFunction* func);
      public: t::Object* declare_method(t::Class* cls, t::UserFunction* func);
      public: t::Object* declare_method(t::Class* cls, t::Object* func);
      public: t::Object* declare_method(t::Object* cls, t::Object* func);
      //public: t::Object* declare_function(t::Object* func);

      /**
       * Finds the entry which contains [cls].
       *
       * @return The index of the entry, -1 otherwise.
       */
      public: long find(t::Class* cls);

      /**
       * Finds a class named [name].
       *
       * @return The index of the class, -1 otherwise.
       */
      public: long find(std::string name);

      /**
       * Gets the t::Class object whose name is [name].
       *
       * @param name The name of the class to search.
       * @return A pointer to a t::Class object.
       */
      public: t::Class* get(std::string name);

      /**
       * Gets a t::Function object whose name is [func_name] and which belongs
       * to a class named [class_name].
       *
       * @param class_name The name of the class to search.
       * @param func_name The name of the function to search.
       * @return A pointer to a t::Function object.
       */
      public: t::Function* get_method(std::string class_name, std::string func_name);

      /**
       * Gets a t::Function object whose name is [func_name] and which belongs
       * to the class [cls].
       *
       * @param class A pointer to the t::Class object to search.
       * @param func_name The name of the function to search.
       * @return A pointer to a t::Function object.
       */
      public: t::Function* get_method(t::Class* cls, std::string func_name);

      /**
       * Checks if the ClassTable contains a class named [name].
       *
       * @param name The name of the class to search.
       * @return true if a class named [name] is contained in this ClassTable.
       */
      public: bool has(std::string name);

      /**
       * Checks if the ClassTable contains a class [cls].
       *
       * @param name The name of the class to search.
       * @return true if a class named [name] is contained in this ClassTable.
       */
      public: bool has(t::Class* cls);
      public: bool has_method(t::Class* cls, std::string name);
      public: bool has_method(t::Class* cls, t::Function* func);

      #ifdef _DEBUG_
      public: void list(bool show_functions);
      #endif
   };
}

#endif
