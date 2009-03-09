base_SOURCES=\
src/debug.cpp \
src/svm/Array.cpp \
src/svm/Block.cpp \
src/svm/Bool.cpp \
src/svm/Class.cpp \
src/svm/ClassUtil.cpp \
src/svm/ClassTable.cpp \
src/svm/ClassTableEntry.cpp \
src/svm/CoreFunction.cpp \
src/svm/Exception.cpp \
build/src/svm/EngineStarter.cpp \
build/src/svm/Engine.cpp \
src/svm/FieldTable.cpp \
src/svm/File.cpp \
src/svm/Float.cpp \
src/svm/Function.cpp \
src/svm/FunctionTable.cpp \
src/svm/FunctionTableEntry.cpp \
src/svm/Heap.cpp \
src/svm/HeapObject.cpp \
src/svm/Int.cpp \
src/svm/IntUtil.cpp \
src/svm/List.cpp \
src/svm/ListUtil.cpp \
src/svm/Map.cpp \
src/svm/Object.cpp \
src/svm/OpCode.cpp \
src/svm/Parser.cpp \
src/svm/Stack.cpp \
src/svm/String.cpp \
src/svm/StringUtil.cpp \
src/svm/UserFunction.cpp \
src/svm/UserObject.cpp \
src/svm/UString.cpp \
src/svm/Variable.cpp

# SOFTWARES
PYTHON=python
SH=/bin/bash

srcdir=.
DATA_DIR=${srcdir}/data
BUILD_DIR=${srcdir}/build
DOC_DIR=${BUILD_DIR}/doc
OPCODES_DOC_DIR=${DOC_DIR}/opcodes
MODULES_DIR=${srcdir}/modules
DEST_DIR=${BUILD_DIR}/svm
TEST_CXX_DIR=${srcdir}/test/c++
script_dir=$(srcdir)/script

bin_PROGRAMS=svm

svm_SOURCES=src/main.cpp $(base_SOURCES)
svm_CXXFLAGS=-I$(BUILD_DIR)/include -I$(srcdir)/include -Wall
svm_LDADD=-licui18n -licuuc -licudata
svm_CXX=time ccache colorgcc -x c++ ${svm_SOURCES} ${svm_CXXFLAGS} ${svm_LDADD} -o ${BUILD_DIR}/svm


test_CXX=time ccache -s ${CXX} -g -O0 ${base_SOURCES} ${svm_CXXFLAGS} ${svm_LDADD} -L/usr/local/lib -lgtest -Wall

manual-compilation:

check: test

clean-build:
	rm -rf $(BUILD_DIR)/*

debug: update-version-number prepare-modules manual-compilation
	${svm_CXX} -pg -O0 -D__DEBUG__=1 -DUSE_COLORS=1

#install: update-version-number prepare-modules release
#	cp --force $(BUILD_DIR)/svm $(bindir)

doc-opcodes:
	rm $(OPCODES_DOC_DIR)/*
	cd $(script_dir) ; export DJANGO_SETTINGS_MODULE=doc-settings ; $(PYTHON) opcodes-doc-make.py

internal: update-version-number prepare-modules manual-compilation
	${svm_CXX} -pg -O0 -D __INTERNAL__=1 -DUSE_COLORS=1

introspection: update-version-number prepare-modules manual-compilation
	$(SH) rc.compile

introspection-test:
	time ./cci  ${svm_SOURCES} ${svm_CXXFLAGS} ${svm_LDADD} -Wall

prepare-modules:
	mkdir -p $(BUILD_DIR)/include/svm
	mkdir -p $(BUILD_DIR)/src/svm
	cp $(srcdir)/include/svm/EngineStarter.h $(BUILD_DIR)/include/svm/EngineStarter.h
	cp $(srcdir)/src/svm/EngineStarter.cpp $(BUILD_DIR)/src/svm/EngineStarter.cpp
	cp $(srcdir)/include/svm/Engine.h $(BUILD_DIR)/include/svm/Engine.h
	cp $(srcdir)/src/svm/Engine.cpp $(BUILD_DIR)/src/svm/Engine.cpp
	cp $(srcdir)/include/svm/OpCode.h $(BUILD_DIR)/include/svm/OpCode.h
	$(PYTHON) $(script_dir)/install-opcodes.py \
		--constants=$(BUILD_DIR)/include/svm/OpCode.h \
		--built-modules=$(BUILD_DIR)/include/modules \
		--prototypes=$(BUILD_DIR)/include/svm/Engine.h \
		--definitions=$(BUILD_DIR)/src/svm/Engine.cpp \
		--switch=$(BUILD_DIR)/src/svm/Engine.cpp \
		--modules=$(MODULES_DIR) \
		--list=$(MODULES_DIR)/modules \
		--opcodes-ini=$(BUILD_DIR)/opcodes.ini \
		--modules-setup=$(BUILD_DIR)/src/Engine.cpp
	$(SH) $(script_dir)/install-modules.sh

release: update-version-number prepare-modules manual-compilation
	${svm_CXX} -O2 -D __RELEASE__=1

release-O0: update-version-number prepare-modules manual-compilation
	${svm_CXX} -O0 -D __RELEASE__=1

test: test-array

test-array:
	${test_CXX} ${TEST_CXX_DIR}/ArrayTest.cpp -o ${BUILD_DIR}/TestArray

search-todo:
	grep --directories=recurse --exclude=*.svn-base  "//\s*@?TODO" *

search-todos: search-todo

sizeof:
	[ -f `which parrot` ] && du -skD `which parrot`
	[ -f `which python` ] && du -skD `which python`
	[ -f `which ruby` ] && du -skD `which ruby`
	[ -f `which perl` ] && du -skD `which perl`
	[ -f `which svm` ] && du -skD `which svm`

update-version-number:
	$(SH) $(script_dir)/update-version $(srcdir)/VERSION
