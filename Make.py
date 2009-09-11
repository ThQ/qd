#!/usr/bin/python

import getopt
import os
import re
import sys

D_BUILD = "./build"
D_TEMP = D_BUILD + "/tmp"
D_SRC = "./src"
D_INCLUDE = "./include"

xGCC = "colorgcc -x c++ -c "

CXX_INCLUDES=" -I" + D_INCLUDE
CXX_DEBUG_FLAGS=CXX_INCLUDES + " -Wall -pg -O0 -D__DEBUG__=1 -DUSE_COLORS=1"
CXX_INTERNAL_FLAGS=CXX_INCLUDES + " -Wall -pg -O0 -D__INTERNAL__=1 -DUSE_COLORS=1"
CXX_INTROSPECTION_FLAGS=CXX_INCLUDES + " -Wall -pg -O0 -D__INTROSPECTION__=1 -DUSE_COLORS=1"
CXX_RELEASE_FLAGS=CXX_INCLUDES + " -Wall -O2 -D__RELEASE__=1"

class File:
   def __init__(self, rel_path, tags):
      self.rel_path = rel_path
      self.tags = tags

class Files:
   def __init__(self):
      self.files = []

   def filter_by_tag(self, tag):
      result = []
      for f in self.files:
         if tag in f.tags:
            result.append(f)
      return result

FILES = Files()
FILES.files = [
   File("t/Array", ["ns:t", "cu:vm-engine"]),
   File("t/BaseArray", ["ns:t", "cu:vm-engine"]),
   File("t/Block", ["ns:t", "cu:vm-engine", "cu:vm-call-stack"]),
   File("t/CoreFunction", ["ns:t"]),
   File("t/Exception", ["ns:t", "cu:vm-engine"]),
   File("t/Function", ["ns:t"]),
   File("t/List", ["ns:t", "cu:vm-engine"]),
   File("t/Object", ["ns:t", "cu:vm-call-stack", "cu:vm-engine"]),
   File("t/RegisterObject", ["ns:t", "cu:vm-engine"]),
   File("t/String", ["ns:t", "cu:vm-engine"]),
   File("t/UserFunction", ["ns:t"]),
   File("opcodes/Arguments", ["ns:opcodes", "cu:vm-engine"]),
   File("opcodes/Array", ["ns:opcodes", "cu:vm-engine"]),
   File("opcodes/Block", ["ns:opcodes", "cu:vm-engine"]),
   File("opcodes/Debug", ["ns:opcodes", "cu:vm-engine"]),
   File("opcodes/Dummy", ["ns:opcodes", "cu:vm-engine"]),
   File("opcodes/Exception", ["ns:opcodes", "cu:vm-engine"]),
   File("opcodes/Int", ["ns:opcodes", "cu:vm-engine"]),
   File("opcodes/Jump", ["ns:opcodes", "cu:vm-engine"]),
   File("opcodes/List", ["ns:opcodes", "cu:vm-engine"]),
   File("opcodes/Registers", ["ns:opcodes", "cu:vm-engine"]),
   File("vm/CallStack", ["ns:vm", "cu:vm-engine", "cu:vm-call-stack"]),
   File("vm/Class", ["ns:vm", "cu:vm-call-stack", "cu:vm-engine"]),
   File("vm/EngineStarter", ["ns:vm"]),
   File("vm/Engine", ["ns:vm", "cu:vm-engine"]),
   File("vm/Frame", ["ns:vm", "cu:vm-engine"]),
   File("vm/OpCode", ["ns:vm", "cu:vm-call-stack", "cu:vm-engine"]),
   File("vm/Parser", ["ns:vm"]),
   File("vm/RegisterPool", ["ns:vm", "cu:vm-engine", "cu:vm-call-stack"]),
   File("Stats", ["cu:vm-engine", "cu:vm-call-stack"]),
   File("main_vm_call_stack", ["cu:vm-call-stack"]),
   File("main_vm_engine", ["cu:vm-engine"]),
   File("types", ["cu:vm-call-stack", "cu:vm-engine"])
]

class Task:
   def __init__(self):
      self.name = ""

   def run(self):
      pass

class CompilingTask (Task):
   def __init__(self):
      self.cxx_flags = CXX_INTERNAL_FLAGS
      self.name = ""
      self.mode = "internal"
      self.options = []
      self.re_c_include = re.compile("^#include\s+\"([^\"]+).h\"$")

   def parse_options(self):
      short_options = "m:"
      long_options = ["mode="]
      self.options = getopt.getopt(sys.argv[2:], short_options, long_options)
      named_options = self.options[0]

      for opt in named_options:
         if opt[0] == "--mode" or opt[0] == "-m":
            self.mode = opt[1]
            if self.mode == "release":
               self.cxx_flags = CXX_RELEASE_FLAGS
            elif self.mode == "debug":
               self.cxx_flags = CXX_DEBUG_FLAGS
            elif self.mode == "internal" :
               self.cxx_flags = CXX_INTERNAL_FLAGS
            elif self.mode == "introspection" :
               self.cxx_flags = CXX_INTROSPECTION_FLAGS

   def run(self):
      self.parse_options()

      files = FILES.filter_by_tag("cu:" + self.name)
      o_rel_files = []
      o_abs_files = []

      has_errors = False
      max_filename_len = 0

      for f in files:
         if len(f.rel_path) > max_filename_len:
            max_filename_len = len(f.rel_path)
      max_filename_len += 4
      file_count = len(files)
      file_count_str_len = len(str(file_count))

      i = 1
      for f in files:
         progress = (i * 100 / file_count)
         cpp_rel_path = f.rel_path + ".cpp"
         cpp_abs_path = D_SRC + "/" + cpp_rel_path
         o_rel_path = f.rel_path + ".o"
         o_abs_path = D_TEMP + "/" + o_rel_path

         o_rel_files.append(o_rel_path)
         o_abs_files.append(o_abs_path)

         l = ""
         l += " CC "
         l += "| "
         l += str(i).rjust(file_count_str_len)
         l += "/"
         l += str(file_count).ljust(file_count_str_len)
         l += " | "
         l += str(progress).rjust(3) + "%"
         l += " | "
         l += cpp_rel_path.ljust(max_filename_len, " ")
         l += " | "
         l += o_abs_path
         print l

         cmd = xGCC + D_SRC + "/" + cpp_rel_path + " -o " + o_abs_path + self.cxx_flags

         gxx_results = os.popen(cmd, "r")
         i += 1


      if not has_errors:
         cmd = "g++ -o " + D_BUILD + "/" + task_name + " " + " ".join(o_abs_files) + self.cxx_flags
         gxx_results = os.popen(cmd, "r")
         print " O ->", D_BUILD + "/" + task_name

Vm_Engine = CompilingTask()
Vm_Call_Stack = CompilingTask()

def format_task_name (raw_task_name):
   return raw_task_name.lower().replace("_", "-")

if len(sys.argv) >= 2:
   task_name = sys.argv[1]
   task = None

   for c in dir():
      if task_name == format_task_name(c):
         task_type = compile(c, "__", "eval")
         task = eval(task_type)
         task.name = task_name

   if task != None:
      task.run()
