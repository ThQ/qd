#include "t/ClassUtil.h"

namespace NS_UTIL
{
   void
   ClassUtil::declare_field(t::Object* cls, t::Object* type, std::string name)
   {
      t::Object* field = t::Variable::build(type, name);
      t::Object::pick(field);
      t::Class* c = (t::Class*)cls;

      ++ c->field_count;

      if (c->field_count > c->field_rooms)
      {
         c->resize_fields_up();
      }
      c->fields[c->field_count - 1] = field;
   }
}
