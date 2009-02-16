#include "svm/ClassUtil.h"

namespace svm
{
   void
   ClassUtil::declare_field(Object* cls, Object* type, std::string name)
   {
      svm::Object* field = svm::Variable::build(type, name);
      SVM_PICK(field);
      svm::Class* c = (svm::Class*)cls;

      ++ c->field_count;

      if (c->field_count > c->field_rooms)
      {
         c->resize_fields_up();
      }
      c->fields[c->field_count - 1] = field;
   }
}
