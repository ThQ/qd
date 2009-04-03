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
   class ClassTable
   {
      public: ClassTableEntry** items;
      public: ULong item_count;

      public: ClassTable();
      public: ~ClassTable();
      public: void append(t::Class* cls);
      public: void append(ClassTableEntry* entry);
      public: bool append_method_to(t::Class* cls, t::Function* func);
      #ifdef _DEBUG_
      public: void assert_validity();
      #endif
      public: unsigned long count();
      //public: bool declare_fields(t::Class* cls, unsigned long field_count, svm::Variable** fields);
      public: t::Object* declare_class(const char* class_name);
      public: t::Object* declare_class(const char* class_name, t::Object* parent_class);
      public: t::Object* declare_class(const char* class_name, const char* parent_class_name);
      public: t::Object* declare_method(t::Class* cls, t::CoreFunction* func);
      public: t::Object* declare_method(t::Class* cls, t::UserFunction* func);
      public: t::Object* declare_method(t::Class* cls, t::Object* func);
      public: t::Object* declare_method(t::Object* cls, t::Object* func);
      //public: t::Object* declare_function(t::Object* func);
      public: long find(t::Class* cls);
      public: long find(std::string name);
      public: Class* get(std::string name);
      public: Function* get_method(std::string class_name, std::string func_name);
      public: Function* get_method(t::Class* cls, std::string func);
      public: bool has(std::string name);
      public: bool has(t::Class* cls);
      public: bool has_method(t::Class* cls, std::string name);
      public: bool has_method(t::Class* cls, Function* func);

      #ifdef _DEBUG_
      public: void list(bool show_functions);
      #endif
   };
}

#endif
