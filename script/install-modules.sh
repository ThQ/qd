#!/bin/bash

cd ${0%/*}/..

dRoot=`pwd`
dScript="${dRoot}/script"
dBuild="${dRoot}/build"
dBuildInclude="${dBuild}/include"
dBuildModuleInclude="$dBuildInclude/modules"
dBuildSrc="$dBuild/src"
dModules="$dRoot/modules"
create_directories="$dBuild $dBuildInclude $dBuildModuleInclude $dBuildSrc"

fModulesInclude="$dBuildModuleInclude/include.modules"
fModulesInitialize="$dBuildModuleInclude/initialize.modules"
fModulesDeclareMethods="$dBuildModuleInclude/declare_methods.modules"
fModulesTearDown="$dBuildModuleInclude/tear_down.modules"
fModulesPrepared="$dBuild/modules_prepared"
fModules="$dRoot/modules/modules"
fEngineStarter="${dBuild}/src/svm/EngineStarter.cpp"

create_file="$fModulesInclude $fModulesInitialize $fModulesDeclareMethods $fModulesTearDown"

xPython="python"
xReplace="${xPython} ${dScript}/replace.py"

cd "$dRoot"

for dir in $create_directories ; do
   mkdir -p "$dir"
done

for file in $create_file ; do
   : > $file
done


modules_list=`cat $fModules`
for module in ${modules_list[*]} ; do
   if [ "${module:0:1}" != "#" ] ; then
      module_rel_id="${module//.//}"
      module_def_file="${module_rel_id}/module.h"
      module_abs_file="${dModules}/${module_def_file}"
      module_rel_dir="${module_rel_id}"
      module_abs_dir="${dModules}/${module_rel_dir}"

      #echo "# Module [${module}] found in [${module_abs_file}]."
      if [ -f "$module_abs_file" ] ; then
         cd $module_abs_dir
         mkdir -p "${dBuildModuleInclude}/${module_rel_dir}"
         m4 "module.h" > ${dBuildModuleInclude}/${module_rel_id}.h

         echo "#include \"modules/${module_rel_id}.h\"" >> $fModulesInclude

         echo "INTERNAL(\"<module:${module}> : setup... \\n\");" \
            "modules::${module//./::}::initialize(this->engine);" \
            "INTERNAL(\"OK\\n\");" \
            >> $fModulesInitialize

         echo "INTERNAL(\"<module:${module}> : declaring methods... \\n\");" \
            "modules::${module//./::}::declare_methods(this->engine);" \
            "INTERNAL(\"OK\\n\");" \
            >> $fModulesDeclareMethods

         echo "INTERNAL(\"<module:${module}> : tearing down... \\n\");" \
            "modules::${module//./::}::tear_down(this->engine);" \
            "INTERNAL(\"OK\\n\");" \
            >> $fModulesTearDown

         : > $fModulesPrepared
      fi
   fi
done

c=`cat $fModulesInclude | $xReplace "// @MODULES[INCLUDE]" "$dBuild/include/svm/EngineStarter.h"`
echo "$c" > "$dBuild/include/svm/EngineStarter.h"

c=`cat $fModulesInitialize | $xReplace "// @MODULES[INITIALIZE]" "$fEngineStarter"`
echo "$c" > $fEngineStarter

c=`cat $fModulesDeclareMethods | $xReplace "// @MODULES[DECLARE_METHODS]" "$fEngineStarter"`
echo "$c" > $fEngineStarter

c=`cat $fModulesTearDown | $xReplace "// @MODULES[TEAR_DOWN]" "$fEngineStarter"`
echo "$c" > $fEngineStarter

