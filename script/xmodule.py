#!/usr/bin/python

from django.template.loader import render_to_string
import logging
import sys
import xml.dom.minidom

class XModule:
   def __init__(self):
      self.id = ""
      self.name = ""
      self.types = []
      self.includes = []

   def load(self, file_path):
      doc = xml.dom.minidom.parse(file_path)
      n_ns = doc.firstChild

      if n_ns.attributes.has_key("name"):
         self.name = n_ns.attributes["name"].childNodes[0].nodeValue
         self.id = self.name.upper()

      for n_node in n_ns.childNodes:
         if n_node.localName == "include":
            self.parse_include_node(n_node)
         elif n_node.localName == "type":
            self.parse_type_node(n_node)

   def parse_include_node(self, n_node):
      if n_node.attributes.has_key("path"):
         self.includes.append(n_node.attributes["path"].childNodes[0].nodeValue)

   def parse_type_node(self, n_node):
      type = XModuleType()
      if n_node.attributes.has_key("name"):
         type.vm_name = n_node.attributes["name"].childNodes[0].nodeValue
         type.name = type.vm_name

      if n_node.attributes.has_key("object"):
         type.object = n_node.attributes["object"].childNodes[0].nodeValue

      if n_node.attributes.has_key("parent"):
         type.parent_object = n_node.attributes["parent"].childNodes[0].nodeValue

      for n_child in n_node.childNodes:
         if n_child.localName == "method":
            self.parse_type_method_node(type, n_child)
      self.types.append(type)

   def parse_type_method_node(self, type, n_node):
      method = XModuleTypeMethod()
      if n_node.attributes.has_key("name"):
         method.vm_name = n_node.attributes["name"].childNodes[0].nodeValue
         method.name = method.vm_name

      if n_node.attributes.has_key("returns"):
         method.return_type = n_node.attributes["returns"].childNodes[0].nodeValue
      else:
         logging.warning("No return type defined for <" + type.name + "." + method.name + ">")
         method.return_type = "t::tOBJECT"

      for n_child in n_node.childNodes:
         if n_child.localName == "body":
            method.body = n_child.childNodes[0].nodeValue
         elif n_child.localName == "parameter":
            if n_child.attributes.has_key("name") and n_child.attributes.has_key("type"):
               method.parameters.append((n_child.attributes["name"].childNodes[0].nodeValue, n_child.attributes["type"].childNodes[0].nodeValue))

      for param in method.parameters:
         if method.signature != "":
            method.signature += ", "
         method.signature += param[1] + " " + param[0]
      type.methods.append(method)

   def export_to_cpp(self):
      return render_to_string("xmodule/module.th", {"module":self})

class XModuleType:
   def __init__(self):
      self.name = ""
      self.vm_name = ""
      self.methods = []
      self.object = ""
      self.parent_object = ""

class XModuleTypeMethod:
   def __init__(self):
      self.vm_name = ""
      self.name = ""
      self.parameters = []
      self.body = ""
      self.signature = ""
      self.return_type = ""

if __name__ == "__main__":
   module = XModule()
   module.load(sys.argv[1])
   print module.export_to_cpp()
