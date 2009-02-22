import xml.dom.minidom


class Files:
   files = []

   def export_constants(self):
      s = ""
      for file in self.files:
         s += file.export_constants()
      return s

   def export_function_definitions(self):
      s = ""
      for file in self.files:
         s += file.export_function_definitions()
      return s

   def export_function_prototypes(self):
      s = ""
      for file in self.files:
         s += file.export_function_prototypes()
      return s

   def export_namespace_switch(self):
      s = ""
      for file in self.files:
         s += file.export_namespace_switch()
      return s

   def export_to_ini(self, file_path):
      s = "[opcodes]\n"
      for file in self.files:
         s += "NS_" + file.namespace.name.upper() + "=" + file.namespace.char + "\n"
         for opcode in file.opcodes:
            s += file.namespace.name.upper() + "_" + opcode.name.upper() + "=" + opcode.char + "\n"
         s += "\n"

      hfile = open(file_path, "w+")
      hfile.truncate(0)
      hfile.seek(0)
      hfile.write(s)
      hfile.close()


   def has_namespace(self, namespace):
      result = False
      for file in self.files:
         if file.namespace == namespace:
            result = True
            break

      return result


   def load_file(self, file_path):
      file = File()
      file.load_file(file_path)
      if self.has_namespace(file.namespace):
         print "Warning | Namespace", file.namespace, "has already been defined."
      self.files.append(file)


class File:
   def __init__(self):
      self.includes = []
      self.namespace = None
      self.opcodes = []
      pass

   def export_constants(self):
      s = "#define " + ("OPC_NS_" + self.namespace.name.upper()).ljust(30, " ")
      s += " " + str(ord(self.namespace.char)).ljust(3, " ") + " /*  " + self.namespace.char + "  */\n"
      for opc in self.opcodes:
         #print opc.name
         s += "#define " + ("OPC_" + self.namespace.name.upper() + "_" + opc.name.upper()).ljust(30, " ")
         s += " " + str(ord(opc.char)).ljust(3, " ") + " /* "  + opc.char + "  */\n"
      s += "\n"
      return s

   def export_function_definitions(self):
      s = " bool svm::Engine::run_" + self.namespace.name.lower() + "_opc(ULong &i, Block* block, Heap& heap, OpCode* opc, Object** argv)\n"
      s += "{\n"
      s += "   bool result = false;\n";
      s += "   switch (opc->method)\n";
      s += "   {\n";
      for opc in self.opcodes:
         s += "      case OPC_" + self.namespace.name.upper() + "_" + opc.name.upper() + ":\n"
         s += "      {\n"
         s += opc.body.strip()
         s += "\n         result = true;\n"
         s += "         break;\n"
         s += "      }\n"
      s += "   }\n";
      s += "   return result;\n";
      s += "}\n"

      return s


   def export_function_prototypes(self):
      s = "public: bool run_" + self.namespace.name.lower() + "_opc(ULong &i, Block* block, Heap& heap, OpCode* opc, Object** argv);\n"

      return s

   def export_namespace_switch(self):
      s = "case OPC_NS_" + self.namespace.name.upper() + ": "
      s += "opc_namespace_handled = true; opc_handled = this->run_" + self.namespace.name.lower() + "_opc(i, block, block->heap, opc, args); break;\n"
      return s


   def load_file(self, file_path):
      dom = xml.dom.minidom.parse(file_path)
      n_ns = dom.firstChild
      self.namespace = Namespace()
      if n_ns.attributes.has_key("name"):
         self.namespace.name = n_ns.attributes["name"].nodeValue
      if n_ns.attributes.has_key("full-name"):
         self.namespace.full_name = n_ns.attributes["full-name"].nodeValue
      else:
         self.namespace.full_name = self.namespace.name

      if n_ns.attributes.has_key("char"):
         self.namespace.char = n_ns.attributes["char"].nodeValue

      for n in n_ns.childNodes:
         if n.localName == "include":
            self.parse_include_node(n)
         elif n.localName == "opcode":
            self.parse_opcode_node(n)


   def parse_opcode_node(self, node):
      opcode = OpCode()
      if node.attributes.has_key("name"):
         opcode.name = node.attributes["name"].nodeValue

      if node.attributes.has_key("char"):
         opcode.char = node.attributes["char"].nodeValue
      for n in node.childNodes:
         if n.localName == "body":
            opcode.body = str(n.childNodes[0].nodeValue)
         if n.localName == "description":
            opcode.description = str(n.childNodes[0].nodeValue)
         if n.localName == "parameters":
            opcode.parameters = self.parse_opcode_parameters_node(n)

      self.opcodes.append(opcode)

   def parse_opcode_parameters_node(self, node):
      params = []
      for n in node.childNodes:
         if n.localName == "parameter":
            param = OpCodeParameter()
            if n.attributes.has_key("type"):
               param.type = n.attributes["type"].nodeValue
            if n.attributes.has_key("name"):
               param.name = n.attributes["name"].nodeValue
            if n.attributes.has_key("description"):
               param.description = n.attributes["description"].nodeValue
            params.append(param)
      return params

   def parse_include_node(self, n):
      if n.attributes.has_key("src"):
         self.includes.append(n.attributes["src"].nodeValue)
      else:
         raise Error("pouet")

class Namespace:
   name = ""
   full_name = ""
   char = ""

class OpCode:
   body = ""
   name = ""
   char = ""
   description = ""
   long_description = ""
   parameters = []


class OpCodeParameter:
   index = 0
   type = "svm::object_type"
   name = ""
   description = ""
