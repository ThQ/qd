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
      public: ClassTableEntry** items;
      public: ULong item_count;

      public: ClassTable();
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
      public: void assert_validity();
      #endif


      /**
       * Return how many classes are stored in this list.
       */
      public: ULong count();

      //public: bool declare_fields(t::Class* cls, unsigned long field_count, svm::Variable** fields);

      /**
       * Create a new class named <class_name> and store it in this list.
       */
      public: t::Object* declare_class(const char* class_name);

      /**
       * Create a new class named <class_name>, whose parent is <parent_class>,
       * and store it in this list.
       */
      public: t::Object* declare_class(const char* class_name, t::Object* parent_class);

      /**
       * Create a new class named <class_name>, whose parent name is
       * <parent_class_name>, and store it in this list.
       */
      public: t::Object* declare_class(const char* class_name, const char* parent_class_name);
      public: t::Object* declare_method(t::Class* cls, t::CoreFunction* func);
      public: t::Object* declare_method(t::Class* cls, t::UserFunction* func);
      public: t::Object* declare_method(t::Class* cls, t::Object* func);
      public: t::Object* declare_method(t::Object* cls, t::Object* func);
      //public: t::Object* declare_function(t::Object* func);
      public: long find(t::Class* cls);
      public: long find(std::string name);
      public: t::Class* get(std::string name);
      public: t::Function* get_method(std::string class_name, std::string func_name);
      public: t::Function* get_method(t::Class* cls, std::string func);
      public: bool has(std::string name);
      public: bool has(t::Class* cls);
      public: bool has_method(t::Class* cls, std::string name);
      public: bool has_method(t::Class* cls, t::Function* func);

      #ifdef _DEBUG_
      public: void list(bool show_functions);
      #endif
   };
}

#endif
