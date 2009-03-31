#include "t/Variable.h"

namespace NS_TYPE
{
   T_OBJECT* tVARIABLE = NULL;

   Variable::Variable()
   {
      this->object = NULL;
      this->object_type = NULL;
      this->set_class(NS_TYPE::tVARIABLE);
      this->name = "";
   }

   Variable::~Variable()
   {
      T_OBJECT::drop_safe(this->object);
      T_OBJECT::drop_safe(this->object_type);
   }

   T_OBJECT*
   Variable::build(T_OBJECT* type)
   {
      T_CLASS::assert(type);

      Variable* result = new Variable();
      result->set_object_type(type);

      return (T_OBJECT*)result;
   }

   T_OBJECT*
   Variable::build(T_OBJECT* type, std::string name)
   {
      T_CLASS::assert(type);

      Variable* result = new Variable();
      result->set_object_type(type);
      result->name = name;

      return (T_OBJECT*)result;
   }

   T_OBJECT*
   Variable::set(T_OBJECT* var, T_OBJECT* obj)
   {
      T_VARIABLE::assert(var);
      T_OBJECT::assert_not_null(obj);

      Variable* v = (Variable*)var;
      T_OBJECT::assert_not_null(v->object_type);
      T_OBJECT::assert_not_null(v->object);

      // @TODO: Replace that by an inline function, please...
      SVM_ASSERT_SAME_TYPES(obj->cls, v->object_type);

      T_OBJECT::drop_safe(v->object);
      v->object = obj;
      T_OBJECT::pick(v->object);

      return obj;
   }

   void
   Variable::set_object_type(T_OBJECT* type)
   {
      T_CLASS::assert(type);
      T_OBJECT::drop_safe(this->object_type);
      this->object_type = type;
      T_OBJECT::pick(this->object_type);
   }
}

