#ifndef SVM_LIST_H
#define SVM_LIST_H

#include <stdlib.h>
#include <stdio.h>

#include "debug.h"
#include "svm/Object.h"
#include "svm/String.h"
#include "types.h"

#ifdef __ALLOW_SVM_ASSERTIONS__
   #define SVM_ASSERT_LIST(o) SVM_ASSERT_NOT_NULL(o); if (o->cls != svm::list_type) {FATAL("Should be of type <system.List>.\n");abort();}
#else
   #define SVM_ASSERT_LIST(o)
#endif

#ifdef __ALLOW_SVM_CHECKS__
   #define SVM_CHECK_LIST(o) SVM_CHECK_NOT_NULL(o); if (o->cls != svm::list_type){WARNING("Bad type given, expected <system.List>.\n");}
#else
   #define SVM_CHECK_LIST(o)
#endif


svm::Object* svm_cast_to_string(svm::Object* o);
void svm_print(svm::Object* o);

namespace svm
{
   extern Object* list_type;

   class List : Object
   {
      public: UInt length;
      public: Object** items;

      public: List();
      public: static Object* append(Object* list, Object* obj);
      public: static Object* build();
      public: static Object* cast_to_string(Object* list);
      public: static bool check(Object* obj);
      public: static Object* clear(Object*);
      public: static void debug_id(Object* list);
      public: static Object* flatten(Object* list);
      public: static Object* get_item(Object* list, UInt index);
      public: static Object* insert(Object* list, UInt at, Object* obj);
      public: static Object* pop(Object* self);
      public: static Object* pop(Object* self, UInt num);
      public: static Object* push(Object* list, Object* obj);
      public: static void push_list(Object* l1, Object* l2);
      public: static Object* remove_item(Object* list, UInt at);
      public: static Object* reverse(Object*);
      public: static Object* resize(Object* list, UInt size);
      public: static Object* set_item(Object* list, UInt at, Object* obj);
      public: static Object* slice(Object* list, UInt start, UInt end, UInt step);
   };
}

#endif
