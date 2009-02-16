#ifndef SVM_OBJECT_H
#define SVM_OBJECT_H

#include <stdio.h>
#include <stdlib.h>
#include <cstdarg>

#include "debug.h"
#include "memory.h"
#include "types.h"

#define SVM_PICK(o) \
   ASSERT_NOT_NULL(o); \
   GC("Picking <svm::Object(@%lu)>...", (ULong)(o)); \
   svm::Object::pick(o);\
   GC_APD(" OK"); \
   if(o != NULL){GC_APD(" [references_now=%d]", (o)->references);} \
   GC_APD("\n");

#define SVM_PICK_SAFE(o) if ((o) != NULL) {SVM_PICK((o));}

#define SVM_DROP(o) \
   ASSERT_NOT_NULL(o); \
   GC("Dropping <svm::Object(@%lu)>...", (ULong)(o)); \
   svm::Object::drop(o); \
   GC_APD(" OK"); \
   if(o != NULL){GC_APD(" [references_now=%d]", (o)->references);} \
   GC_APD("\n");

#define SVM_DROP_SAFE(o) if ((o) != NULL) {SVM_DROP(o);}

#define SVM_ASSERT_REF_COUNT(object, ref_count) \
   if (((svm::Object*)object)->references != ref_count) \
   { FATAL("<svm::Object*(@%lu)>.references must be <%d>, not <%d>.", (ULong)object, ref_count, ((svm::Object*)object)->references); abort(); }


#define SVM_OBJECT_FIELDS_STEP 5

namespace svm
{
   class Object
   {
      public: Object* cls;
      public: Object** fields;
      public: ULong field_count;
      public: ULong field_rooms;
      public: int references;
      public: int id;
      public: bool is_abstract;

      public: Object();
      public: static Object** build_array(int argc, ...);
      public: static Short compare_to(Object* obj1, Object* obj);
      public: static bool drop(Object* obj);
      public: Object* get_field(ULong at);
      public: static bool is_null(Object* obj);
      public: static bool pick(Object* obj);
      public: static void print(Object* o);
      public: static void print_line(Object* o);
      public: void resize_field_array(ULong new_size);
      public: void resize_fields_up();
      public: void set_class(Object* type);
      public: void set_field(ULong at, Object* obj);
   };

   extern Object* object_type;
   extern Object* Null;
   extern Object* null_type;
}

#endif
