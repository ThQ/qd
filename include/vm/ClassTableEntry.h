#ifndef SVM_CLASS_TABLE_ENTRY_H
#define SVM_CLASS_TABLE_ENTRY_H

#include "svm/Class.h"
#include "svm/CoreFunction.h"
#include "svm/FieldTable.h"
#include "svm/FunctionTable.h"
#include "svm/UserFunction.h"

namespace svm
{
   class ClassTableEntry
   {
      public: Class* cls;
      public: FieldTable fields;
      public: FunctionTable functions;

      public: ClassTableEntry();
      public: ~ClassTableEntry();
      public: void set_class(Class* cls);
   };
}

#endif
