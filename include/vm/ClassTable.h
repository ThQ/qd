#ifndef SVM_CLASS_TABLE_H
#define SVM_CLASS_TABLE_H

#include "svm/Class.h"
#include "svm/ClassTableEntry.h"
#include "svm/String.h"
#include "svm/Variable.h"

namespace svm
{
   class ClassTable
   {
      public: ClassTableEntry** items;
      public: ULong item_count;

      public: ClassTable();
      public: ~ClassTable();
      public: void append(Class* cls);
      public: void append(ClassTableEntry* entry);
      public: bool append_method_to(Class* cls, Function* func);
      #ifdef _DEBUG_
      public: void assert_validity();
      #endif
      public: unsigned long count();
      //public: bool declare_fields(svm::Class* cls, unsigned long field_count, svm::Variable** fields);
      public: svm::Object* declare_class(const char* class_name);
      public: svm::Object* declare_class(const char* class_name, svm::Object* parent_class);
      public: svm::Object* declare_class(const char* class_name, const char* parent_class_name);
      public: svm::Object* declare_method(svm::Class* cls, svm::CoreFunction* func);
      public: svm::Object* declare_method(svm::Class* cls, svm::UserFunction* func);
      public: svm::Object* declare_method(svm::Class* cls, svm::Object* func);
      public: svm::Object* declare_method(svm::Object* cls, svm::Object* func);
      //public: svm::Object* declare_function(svm::Object* func);
      public: long find(Class* cls);
      public: long find(std::string name);
      public: Class* get(std::string name);
      public: Function* get_method(std::string class_name, std::string func_name);
      public: Function* get_method(Class* cls, std::string func);
      public: bool has(std::string name);
      public: bool has(Class* cls);
      public: bool has_method(Class* cls, std::string name);
      public: bool has_method(Class* cls, Function* func);

      #ifdef _DEBUG_
      public: void list(bool show_functions);
      #endif
   };
}

#endif
