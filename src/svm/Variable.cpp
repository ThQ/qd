#include "svm/Variable.h"

namespace svm
{
   Object* variable_type = NULL;

   Variable::Variable()
   {
      SVM_ASSERT_CLASS(svm::variable_type);

      this->object = NULL;
      this->object_type = NULL;
      this->set_class(svm::variable_type);
      this->name = "";
      this->references = 0;
   }

   Variable::~Variable()
   {
      SVM_DROP_SAFE(this->object);
      SVM_DROP_SAFE(this->object_type);
   }

   Object*
   Variable::build(Object* type)
   {
      SVM_ASSERT_CLASS(type);

      Variable* result = new Variable();
      result->set_object_type(type);

      return (Object*)result;
   }

   Object*
   Variable::build(Object* type, std::string name)
   {
      SVM_ASSERT_CLASS(type);

      Variable* result = new Variable();
      result->set_object_type(type);
      result->name = name;

      return (Object*)result;
   }

   bool
   Variable::check(Object* variable)
   {
      return variable->cls == svm::variable_type;
   }

   Object*
   Variable::set(Object* var, Object* obj)
   {
      SVM_ASSERT_VARIABLE(var);
      ASSERT_NOT_NULL(obj);

      Variable* v = (Variable*)var;
      ASSERT_NOT_NULL(v->object_type);
      ASSERT_NOT_NULL(v->object);
      SVM_ASSERT_SAME_TYPES(obj->cls, v->object_type);

      SVM_DROP_SAFE(v->object);
      v->object = obj;
      SVM_PICK(v->object);

      return obj;
   }

   void
   Variable::set_object_type(Object* type)
   {
      SVM_ASSERT_CLASS(type);
      SVM_DROP_SAFE(this->object_type);
      this->object_type = type;
      SVM_PICK(this->object_type);
   }
}

