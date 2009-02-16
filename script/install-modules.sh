cd ../


ROOT_DIR=`pwd`
MODULES_BUILD_DIR="${ROOT_DIR}/build/include/modules"
MODULES_LIST_FILE="${ROOT_DIR}/modules/modules"
MODULES_DIR="${ROOT_DIR}/modules"
F_M_INCLUDES="${MODULES_BUILD_DIR}/include.modules"
F_M_INITIALIZE="${MODULES_BUILD_DIR}/initialize.modules"
F_M_DECLARE_METHODS="${MODULES_BUILD_DIR}/declare_methods.modules"
F_M_TEAR_DOWN="${MODULES_BUILD_DIR}/tear_down.modules"
F_MODULES_PREPARED="${ROOT_DIR}/build/modules-prepared"
MODULES_INITIALIZE=""
MODULES_DECLARE_METHODS=""
SRC_C_MAIN="${ROOT_DIR}/src/svm/EngineStarter.cpp"
DEST_SRC="${ROOT_DIR}/build/src"
DEST_INCLUDE="${ROOT_DIR}/build/include"
DEST_C_MAIN="${DEST_SRC}/svm/EngineStarter.cpp"

: > $F_M_INCLUDES
: > $F_M_INITIALIZE
: > $F_M_DECLARE_METHODS
: > $F_M_TEAR_DOWN



mkdir -p "$MODULES_BUILD_DIR"
mkdir -p "${DEST_SRC}"
cat "$SRC_C_MAIN" > "$DEST_C_MAIN"

modules_list=`cat $MODULES_LIST_FILE`


cat $MODULES_LIST_FILE | while read module ; do
   if [ "${module:0:1}" != "#" ] ; then
      module_rel_id=${module//.//}
      module_def_file="${module_rel_id}/module.h"
      module_abs_file="${MODULES_DIR}/${module_def_file}"
      module_rel_dir="${module_rel_id}"
      module_abs_dir="${MODULES_DIR}/${module_rel_dir}"

      echo "# Module [${module}] found in [${module_abs_file}]."
      if [ ! -f "$module_abs_file" ] ; then
         echo "${module_abs_file} is not a module file."
      else
         cd $module_abs_dir
         pwd
         mkdir -p "${MODULES_BUILD_DIR}/${module_rel_dir}"
         m4 $module_abs_file > "${MODULES_BUILD_DIR}/${module_rel_id}.h"
         cd $ROOT_DIR

         echo "#include \"modules/${module_rel_id}.h\"" >> $F_M_INCLUDES

         echo "INTERNAL(\"<module:${module}> : setup... \\n\");" >> $F_M_INITIALIZE
         echo "modules::${module//./::}::initialize(this->engine);" >> $F_M_INITIALIZE
         echo "INTERNAL(\"OK\\n\");" >> $F_M_INITIALIZE

         echo "INTERNAL(\"<module:${module}> : declaring methods... \\n\");" >> $F_M_DECLARE_METHODS
         echo "modules::${module//./::}::declare_methods(this->engine);" >> $F_M_DECLARE_METHODS
         echo "INTERNAL(\"OK\\n\");" >> $F_M_DECLARE_METHODS

         tear_down_before=`cat $F_M_TEAR_DOWN`
         echo "INTERNAL(\"<module:${module}> : tearing down... \\n\");" > $F_M_TEAR_DOWN
         echo "modules::${module//./::}::tear_down(this->engine);" >> $F_M_TEAR_DOWN
         echo "INTERNAL(\"OK\\n\");" >> $F_M_TEAR_DOWN
         echo $tear_down_before >> $F_M_TEAR_DOWN

         echo "" >> $F_MODULES_PREPARED

      fi
   fi
done

M_INCLUDES=`cat "$F_M_INCLUDES"`
rpl "// @MODULES[INCLUDE]" "$M_INCLUDES" "$DEST_INCLUDE/svm/EngineStarter.h"

M_INITIALIZE=`cat "$F_M_INITIALIZE"`
rpl "// @MODULES[INITIALIZE]" "$M_INITIALIZE" "$DEST_C_MAIN"

M_DECLARE_METHODS=`cat "$F_M_DECLARE_METHODS"`
rpl "// @MODULES[DECLARE_METHODS]" "$M_DECLARE_METHODS" "$DEST_C_MAIN"

M_TEAR_DOWN=`cat "$F_M_TEAR_DOWN"`
rpl "// @MODULES[TEAR_DOWN]" "$M_TEAR_DOWN" "$DEST_C_MAIN"

