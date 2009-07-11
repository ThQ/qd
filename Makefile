# SOFTWARES
srcdir=.
DATA_DIR=${srcdir}/data
BUILD_DIR=${srcdir}/build
DOC_DIR=${BUILD_DIR}/doc
OPCODES_DOC_DIR=${DOC_DIR}/opcodes
MODULES_DIR=${srcdir}/modules
DEST_DIR=${BUILD_DIR}/svm
BIN_DIR=${srcdir}/bin
TEST_CXX_DIR=${srcdir}/test/c++
script_dir=$(srcdir)/script

xPYTHON=python
xSH=/bin/bash
xCOMPILE=cd $(BIN_DIR) && $(xSH) compile

bin_PROGRAMS=svm

help:
	@echo ""
	@echo " Qd make "
	@echo "    by Thomas Quémard"
	@echo ""
	@echo ""
	@echo " * Build"
	@echo "   make vm :                  Builds Qd."
	@echo "   make vm-debug :            Builds Qd with debug outputs (errors)."
	@echo "   make vm-introspection :    Builds Qd with partial logging (errors + some internal informations)."
	@echo "   make vm-internal :         Builds Qd with complete logging (errors + all internal intformations)."
	@echo ""
	@echo " * Documentation"
	@echo "   make doc-source :          Generate C API documentation in $(OPCODES_DOC_DIR)/api/."
	@echo "   make doc-opcodes :         Generate opcode documentation in $(OPCODES_DOC_DIR)/."
	@echo ""

clean-build:
	rm -rf $(BUILD_DIR)/*

clear-doc-source:
	rm -r ${DOC_DIR}/*

doc: doc-source doc-opcodes

doc-api: doc-source

doc-source: clear-doc-source
	doxygen Doxyfile

doc-opcodes:
	rm $(OPCODES_DOC_DIR)/*
	cd $(script_dir) ; export DJANGO_SETTINGS_MODULE=doc-settings ; $(PYTHON) opcodes-doc-make.py

vm: vm-release

vm-debug: prepare-modules update-version-number
	$(xCOMPILE) debug

vm-internal: prepare-modules update-version-number
	$(xCOMPILE) internal

vm-introspection: prepare-modules update-version-number
	$(xCOMPILE) introspection

vm-release: prepare-modules update-version-number
	$(xCOMPILE) release

vm-heap: update-version-number
	$(xCOMPILE) vm_heap

t: update-version-number
	$(xCOMPILE) t

t-array: update-version-number
	$(xCOMPILE) t_array

t-exception: update-version-number
	$(xCOMPILE) t_exception

t-list: update-version-number
	$(xCOMPILE) t_list

t-map: update-version-number
	$(xCOMPILE) t_map

t-object: update-version-number
	$(xCOMPILE) t_object

t-string: update-version-number
	$(xCOMPILE) t_string

prepare-modules:
	mkdir -p $(BUILD_DIR)/include/vm
	mkdir -p $(BUILD_DIR)/src/vm
	cp $(srcdir)/include/vm/EngineStarter.h $(BUILD_DIR)/include/vm/EngineStarter.h
	cp $(srcdir)/src/vm/EngineStarter.cpp $(BUILD_DIR)/src/vm/EngineStarter.cpp
	cp $(srcdir)/include/vm/Engine.h $(BUILD_DIR)/include/vm/Engine.h
	cp $(srcdir)/src/vm/Engine.cpp $(BUILD_DIR)/src/vm/Engine.cpp
	cp $(srcdir)/include/vm/OpCode.h $(BUILD_DIR)/include/vm/OpCode.h
	$(xPYTHON) $(script_dir)/install-opcodes.py \
		--constants=$(BUILD_DIR)/include/vm/OpCode.h \
		--built-modules=$(BUILD_DIR)/include/modules \
		--prototypes=$(BUILD_DIR)/include/vm/Engine.h \
		--definitions=$(BUILD_DIR)/src/vm/Engine.cpp \
		--switch=$(BUILD_DIR)/src/vm/Engine.cpp \
		--modules=$(MODULES_DIR) \
		--list=$(MODULES_DIR)/modules \
		--opcodes-ini=$(BUILD_DIR)/opcodes.ini \
		--modules-setup=$(BUILD_DIR)/src/Engine.cpp
	cd $(BIN_DIR) && $(xSH) install-modules

search-todo:
	grep --directories=recurse --exclude=*.svn-base  "//\s*@?TODO" *

search-todos: search-todo

sizeof:
	[ -f `which parrot` ] && du -skD `which parrot`
	[ -f `which python` ] && du -skD `which python`
	[ -f `which ruby` ] && du -skD `which ruby`
	[ -f `which perl` ] && du -skD `which perl`
	[ -f `which svm` ] && du -skD `which svm`

tar-source:
	tar --gzip -cf '${BUILD_DIR}/qd-'`cat VERSION`'.tar.gz' bin/* include/* modules/* src/* script/* tools/* translaters/*

update-version-number:
	$(xSH) $(script_dir)/update-version $(srcdir)/VERSION
