#include "util/Object.h"

namespace util
{
   void
   Object::assert_type(t::Object* object, t::Object* type)
   {
      #ifdef __ALLOW_SVM_ASSERTIONS__
      ASSERT(object != NULL, "util::Object::assert_type(@%lu, @%lu) : object <t::Object @%lu> must NOT be NULL.", (ULong)object, (ULong)type, (ULong)object);
      ASSERT(type != NULL, "util::Object::assert_type(@%lu, @%lu) : type <t::Object @%lu> must NOT be NULL.", (ULong)object, (ULong)type, (ULong)type);
      ASSERT(object->cls != NULL, "util::Object::assert_type(@%lu, @%lu) : object's class <t::Object @%lu> must NOT be NULL.", (ULong)object, (ULong)type, (ULong)object->cls);

      if (object->cls != type)
      {
         FATAL(
               "<Object @%lu> is of type <@%lu>, not <@%lu> as expected.",
               (ULong)object,
               //((t::Class*)object->cls)->name.c_str(),
               (ULong)object->cls,
               //((t::Class*)type)->name.c_str(),
               (ULong)type
         );
         abort();
      }
      #endif
   }
}
