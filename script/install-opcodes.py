import getopt
import os
import os.path
import shutil
import sys
import xop

def replace_in(file_path, pattern, rep):
   f = open(file_path, "r+")
   if f != None:
      content = f.read()
      content = content.replace(pattern, rep)
      f.truncate(0)
      f.seek(0)
      f.write(content)
      f.close()


long_options = [
"constants=",
"built-modules=",
"list=",
"modules=",
"modules-setup=",
"prototypes=",
"definitions=",
"opcodes-ini=",
"switch="
]
args = getopt.getopt(sys.argv[1:], "", long_options)

built_modules_dir = ""
modules_dir = ""
modules_list_file = ""
modules_setup_file = ""
constants_file = ""
prototypes_file = ""
definitions_file = ""
namespace_switch_file = ""
list_file = ""
opcodes_ini_file = ""

for opt,value in args[0]:
   if opt == "--built-modules":
      built_modules_dir = value
   elif opt == "--constants":
      constants_file = value;
   elif opt == "--modules":
      modules_dir = value
   elif opt =="--prototypes":
      prototypes_file = value
   elif opt =="--definitions":
      definitions_file = value
   elif opt == "--list":
      list_file = value
   elif opt == "--modules-setup":
      modules_setup_file = value
   elif opt == "--opcodes-ini":
      opcodes_ini_file = value
   elif opt== "--switch":
      namespace_switch_file = value

xop = xop.Files()
hModules = open(list_file, "r")
raw_modules = hModules.read().splitlines()

modules_c_includes = ""
modules_c_init = ""
modules_c_methods = ""
modules_c_tear_down = ""
for raw_module in raw_modules:
   module = modules_dir + "/" + raw_module 
   module_name = module[module.rfind("/") + 1:]

   xop_file = module + "/" + module_name + ".ops"
   h_file = module + "/module.h"
   if os.path.exists(xop_file):
      xop.load_file(xop_file)

   if os.path.exists(h_file):
      modules_c_includes += "#include \"modules/" + raw_module + ".h\"\n"

      #modules_c_init += "INTERNAL(\"<> : initializing...\");\n"
      modules_c_init += "modules::" + raw_module.replace(".", "::") + "::initialize(engine);\n"
      #modules_c_init += "INTERNAL(\"OK\");\n"

      modules_c_methods += "modules::" + raw_module.replace(".", "::") + "::declare_methods(engine);\n"

      modules_c_tear_down += "modules::" + raw_module.replace(".", "::") + "::tear_down(engine);\n"
      module_dir = os.path.dirname(built_modules_dir + "/" + raw_module.replace(".", "/"))
      if not os.path.exists(module_dir):
         os.makedirs(module_dir)

      shutil.copyfile(modules_dir + "/" + raw_module + "/module.h", built_modules_dir + "/" + raw_module + ".h")

#print modules_c_includes
#print modules_c_init
#print modules_c_methods
#print modules_c_tear_down

constants = xop.export_constants()
prototypes = xop.export_function_prototypes()
definitions = xop.export_function_definitions()
ns_switch = xop.export_namespace_switch()

xop.export_to_ini(opcodes_ini_file)

replace_in(constants_file, "// [!opcodes:constants]", constants)
replace_in(prototypes_file, "// [!opcodes:prototypes]\n", prototypes)
replace_in(definitions_file, "// [!opcodes:definitions]\n", definitions)
replace_in(namespace_switch_file, "// [!opcodes:ns_switch]\n", ns_switch)


