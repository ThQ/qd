#!/usr/bin/python

from django.template.loader import render_to_string
import os
import os.path

import xop

# @TODO: Should be relative !
D_ROOT="/home/thomas/dev/c++/sws"
D_MODULES=os.path.join(D_ROOT, "modules")
D_OUTPUT=os.path.join(D_ROOT, "build/doc/opcodes")

def u(rel_u):
   return D_OUTPUT + "/" + rel_u + ".html"

class OpcodeFiles:
   def __init__(self):
      self.folders=[]
      self.files=[]

   def list(self, path):
      self.list_dir(path)
      while len(self.folders) > 0:
         self.list_dir(self.folders.pop())

   def list_dir(self, path):
      items = os.listdir(path)
      for item in items:
         item_path = os.path.join(path, item)
         if os.path.isdir(item_path):
            self.folders.append(item_path)
         elif item_path.endswith(".ops"):
            self.files.append(item_path)

files = OpcodeFiles()
files.list(D_MODULES)

def gen_opcode_doc_to(namespace, opcode, output_file):
   o_opcode = open(os.path.join(D_OUTPUT, opfile.namespace.full_name + "." + opc.name + ".html"), "w")
   if o_opcode:
      vars = {}
      vars["u_namespace"] = u(namespace.full_name)
      vars["namespace_name"] = namespace.name
      vars["namespace_full_name"] = namespace.full_name
      vars["opcode"] = opcode
      vars["opcode_parameters_count"] = len(opcode.parameters)
      o_opcode.write(render_to_string("Opcode.thtml", vars))
      o_opcode.close()

for file in files.files:
   opfile = xop.File()
   opfile.load_file(file)
   if opfile.namespace.full_name != "":
      out = open(os.path.join(D_OUTPUT, opfile.namespace.full_name + ".html"), "w")
      if out != None:
         vars = {}
         vars["namespace_name"] = opfile.namespace.name
         vars["namespace_full_name"] = opfile.namespace.full_name
         vars["opcode_count"] = len(opfile.opcodes)
         vars["opcodes"] = []
         for opc in opfile.opcodes:
            opcode = {}
            opcode["name"] = opc.name
            opcode["u"] = u(opfile.namespace.full_name + "." + opc.name)
            opcode["description"] = opc.description
            opcode["parameters"] = opc.parameters
            vars["opcodes"].append(opcode)

            gen_opcode_doc_to(opfile.namespace, opc, os.path.join(D_OUTPUT, opfile.namespace.full_name + "." + opc.name + ".html"))

         out.write(render_to_string("OpcodeNamespace.thtml", vars))
         out.close()

