define(`forloop', `pushdef(`$1', `$2')_forloop(`$1', `$2', `$3', `$4')popdef(`$1')')dnl
define(`_forloop', `$4`'ifelse($1, `$3', , `define(`$1', incr($1))_forloop(`$1', `$2', `$3', `$4')')')dnl
define(`concat', `$1$2$3$4$5$6$7$8$9')dnl
define(`_method_count_', -1)dnl
dnl
define(`FUNCTION', `dnl
   METHOD_START($1, $2) dnl
   define(`_m_class_method', 0)dnl
   define(`_m_object_type_', `')dnl
')dnl
define(`METHOD', `dnl
   METHOD_START($2, $3) dnl
   define(`_m_class_method', 1)dnl
   define(`_m_object_type_', $1)dnl
')dnl
define(`STATIC_FUNCTION', `dnl
   METHOD_START($2, $3)dnl
   define(`_m_class_method', 1)dnl
   define(`_m_object_type', $1)dnl
')dnl
define(`METHOD_START', `dnl
   define(`_m_object_type_', `')dnl
   define(`_m_parameter_count_', 0)dnl
   define(`_m_return_type_', `')dnl
   define(`_m_function_', $2)dnl
   define(`_method_count_', incr(_method_count_))dnl
   define(`_m_alias_', translit(_method_count_, `0123456789', `abcdefghjk'))dnl
   define(`_m_name_', $1)dnl
   // _m_name_ ,  _method_count_ , _m_alias_ , || translit(`8', `0123456789', `abcdefghjk'))
   INTERNAL("<t::CoreFunction[name=\"_m_name_\"]> : declaring... ");
')dnl
define(`PARAM', `dnl
   define(`_m_parameter_count_', incr(_m_parameter_count_))dnl
   METHOD_WRITE_PARAM(_m_parameter_count_, $1, $2, _m_alias_) dnl
')dnl
define(`RETURNS', `dnl
   t::Function* _m_alias_ = t::CoreFunction::build("_m_name_", (long int)_m_function_, $1);
   t::Function::assert( _m_alias_ );
   t::Object::pick( _m_alias_ );
   ifdef(`_m_parameter_count_', `dnl
      ifelse(_m_parameter_count_, `0', `', `dnl
         concat(_m_alias_,->set_arguments)(_m_parameter_count_ dnl
         define(`i', `1')dnl
         forloop(`i', `1', _m_parameter_count_, `, concat(_m_alias_,`_a', i)')dnl
         );dnl
      ')dnl
   ')dnl
   ifelse(_m_class_method, 1, `
      engine.classes.declare_method(_m_object_type_, (t::Object*)_m_alias_);
   ', `
      engine.functions.append(_m_alias_);
   ')dnl
   t::Object::drop((t::Object*)_m_alias_);
   ifdef(`_m_parameter_count_', `dnl
      ifelse(_m_parameter_count_, `0', `', `dnl
         define(`i', `1')dnl
         forloop(`i', `1', _m_parameter_count_, `dnl
           t::Object::drop(concat(_m_alias_,`_a', i));
           SVM_ASSERT_REF_COUNT(concat(_m_alias_,`_a', i), 1);
         ')dnl
      ')dnl
   ')dnl
   t::Function::assert(_m_alias_);
   SVM_ASSERT_REF_COUNT(_m_alias_ , 1);
   INTERNAL_APD("OK\n");
')dnl
dnl
define(`METHOD_DECLARE_PARAMS',  `dnl
   concat(_m_alias_,->set_arguments)(_m_parameter_count_ dnl
   define(`i', `0')dnl
   forloop(`i', `1', _m_parameter_count_, `, concat(_m_alias_,`_a', i)')dnl
   );
')dnl
dnl
define(`METHOD_WRITE_PARAM', `dnl
   t::Object* $4_a$1 = t::Variable::build($3, "$2");
   SVM_ASSERT_NOT_NULL($4_a$1);
   t::Object::pick($4_a$1);
')dnl
