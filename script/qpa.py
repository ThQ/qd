import re

class GlobalAlias:
    def __init__ (self):
        self.name = ""
        self.value = ""


class Block:
    def __init__ (self):
        self.name = ""
        self.opcodes_start_at = 0
        self.opcode_count = 0
        self.aliases = []
        self.parsed_file = None

    def to_string (self):
        s = ""
        s += "." + self.name + "\n"

        if len(self.aliases) > 0:
            s += "\t// " + str(len(self.aliases)) + " aliases\n"
            for alias in self.aliases:
                s += "\t%% " + alias.name + " " + alias.value + "\n"

        if self.opcode_count > 0:
            opcodes_end_at = self.opcodes_start_at + self.opcode_count
            s += "\t// " + str(self.opcode_count) + " opcodes "
            s += "[" + str(self.opcodes_start_at) + ":" + str(opcodes_end_at) + "[\n"
            for i in range(self.opcodes_start_at, opcodes_end_at):
                s += self.parsed_file.opcodes[i].to_string()

        return s


class BlockAlias:
    def __init__ (self):
        self.name = ""
        self.value = ""


class Opcode:
    def __init__ (self):
        self.namespace = ""
        self.function = ""
        self.arguments = []


    def to_string (self):
        s = "\t" + self.namespace + ":" + self.function
        if len(self.arguments) > 0:
            s += " ("
            i = 0
            for arg in self.arguments:
                if i != 0:
                    s += ", "
                s += arg.to_string()
                i += 1
            s += ")"
        s += "\n"
        return s


class OpcodeArgument:
   def to_string (self):
      return ""


class OpcodeAliasArgument (OpcodeArgument):
    def __init__ (self):
        self.name = ""

    def to_string (self):
        return self.name


class OpcodeRegisterArgument (OpcodeArgument):
    def __init__ (self):
        self.type = ""
        self.index = 0

    def to_string (self):
        return "$" + self.type + str(self.index)


class OpcodeIntArgument (OpcodeArgument):
    def __init__ (self):
        self.value = ""

    def to_string (self):
       return self.value

class UnknownOpcodeArgumentTypeError (Exception):
    pass

class ParsedFile:
    def __init__ (self):
        self.opcodes = []
        self.opcode_count = 0
        self.blocks = []
        self.block_count = 0
        self.aliases = []

    def to_string (self):
        s = ""
        if len(self.aliases) > 0:
            for alias in self.aliases:
                s += "%% " + alias.name + " " + alias.value + "\n"

        for block in self.blocks:
            s += block.to_string() + "\n"

        return s

class Parser:
    def __init__ (self):
        self.current_block = None
        self.current_opcode = None
        self.parsed_file = None
        self.path = [".", "..", "../build"]
        self.res_namespace = "[a-zA-Z_0-9]+"
        self.res_function = "[a-zA-Z_0-9]+"
        self.res_int = "(?:[0-9]+)"
        self.res_reg = "(?:\$[iIlLo][0-9]+)"
        self.res_alias = "(?:[a-zA-Z_][a-zA-Z0-9_]+)"
        self.re_alias = re.compile("(" + self.res_alias + ")")
        self.res_arg = "(?:" + self.res_int + "|" + self.res_reg + "|" + self.res_alias + ")"
        self.re_arg = re.compile("(" + self.res_arg + ")")
        self.re_args = re.compile("(" + self.res_arg + ")*")
        self.res_call = "(?:(" + self.res_reg + "|" + self.res_alias + ")\s+=\s+)?"
        self.res_call += "(" + self.res_namespace + "):(" + self.res_function + ")"
        self.res_call += "\s*(?:\(("
        self.res_call += self.res_arg + "(?:\s*,\s*" + self.res_arg + ")*?"
        self.res_call += ")\))?"
        self.res_call + "\s*$"
        self.re_call = re.compile(self.res_call)

    def parse_lines (self, lines):
        lines = self.remove_white_lines(lines)
        for line in lines:
            first_char = line[0:1]

            if line[0:1] == ".":
                self.parse_block_line (line[1:])

            elif line[0:2] == "%%":
                if self.current_block :
                    self.parse_alias_line (line[2:])
                else:
                    self.parse_global_alias_line (line[2:])
                    pass

            elif line[0:2] == "@@":
                self.parse_label_line (line[2:])

            else:
                self.parse_opcode_line (line)
                self.parsed_file.opcode_count += 1

    def parse_global_alias_line (self, line):
        line = line.strip()
        space_pos = line.find(" ")
        if space_pos != -1:
            alias = GlobalAlias()
            alias.name = line[0:space_pos].strip()
            alias.value = line[space_pos:].strip()
            self.parsed_file.aliases.append(alias)
        else:
            pass
            # @todo Throw error

    def parse_alias_line (self, line):
        line = line.strip()
        space_pos = line.find(" ")
        if space_pos != -1:
            alias = BlockAlias()
            alias.name = line[0:space_pos].strip()
            alias.value = line[space_pos:].strip()
            self.current_block.aliases.append(alias)
        else:
            pass
            # @todo Throw error

    def parse_arguments (self, str_args):
        args = str_args.split(",")
        result_args = []
        for arg in args:
            arg = arg.strip()
            arg_match = self.re_alias.match(arg)

            if self.re_alias.match(arg):
                alias_arg = OpcodeAliasArgument()
                alias_arg.name = arg
                result_args.append(alias_arg)

            elif arg.isdigit():
                int_arg = OpcodeIntArgument()
                int_arg.value = arg
                result_args.append(int_arg)

            elif arg[0:1] == "$":
                reg_arg = OpcodeRegisterArgument()
                reg_arg.type = arg[1:2]
                reg_arg.index = int(arg[2:])
                result_args.append(reg_arg)

            else:
                e = UnknownOpcodeArgumentTypeError()
                e.args = ["Unable to determine argument type of litteral argument: " + arg]
                raise e
        return result_args

    def parse_block_line (self, line):
        block = Block()
        block.parsed_file = self.parsed_file
        block.name = line
        block.opcodes_start_at = self.parsed_file.opcode_count
        self.parsed_file.blocks.append(block)
        self.current_block = block

    def parse_file (self, file_path):
        self.parsed_file = ParsedFile()
        file = open(file_path, "r")
        if file:
            self.parse_lines(file.read().splitlines())

        return self.parsed_file

    def parse_label_line (self, line):
        alias = BlockAlias()
        alias.name = line.strip()
        alias.value = str(self.parsed_file.opcode_count)
        self.current_block.aliases.append(alias)

    def parse_opcode_line (self, line):
        _match = self.re_call.match(line)
        if _match != None:
            match = _match.groups()
            opcode = Opcode()
            opcode.namespace = match[1]
            opcode.function = match[2]
            self.parsed_file.opcodes.append(opcode)
            self.current_block.opcode_count += 1
            if match[3]:
                opcode.arguments = self.parse_arguments(match[3])

    def remove_white_lines (self, lines):
        new_lines = []
        if lines != None and len(lines) > 0:
            for line in lines:
                line = line.strip()
                if line != "":
                    new_lines.append(line)
        return new_lines
