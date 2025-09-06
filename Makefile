.PHONY: all clean library

CXXFLAGS := -g -std=c++17 -Werror -Wall
CXX := g++

executable := vm
lib_name := libvm.so

work_dir := $(shell pwd)
build_dir := build
src_dir := src
lib_dir := library
include_dir := include

srcs := $(shell find ${src_dir} -type f -name "*.cpp" )
srcs_objs := $(patsubst %,${build_dir}/%.o,${srcs})
lib_objs := $(patsubst ${src_dir}/%,${build_dir}/${lib_dir}/%.o,${srcs})
deps := $(patsubst %,${build_dir}/%.d,${srcs})

CXXFLAGS += $(addprefix -I,${include_dir})
CXXFLAGS += -MMD -MP

all: target

target: ${build_dir}/${executable}	##		For generating executable that will run the vm translator

${build_dir}/${executable}: ${srcs_objs}
	$(CXX)   $^ -o  $@

${build_dir}/${src_dir}/%.cpp.o: ${src_dir}/%.cpp
	mkdir -p ${@D}
	$(CXX) $(CXXFLAGS) -c $< -o $@

#################################################
################### Library ####################
################################################

CLIBFLAGS := $(filter-out -MMD -MP ,${CXXFLAGS})
CLIBFLAGS += -fPIC -shared

$(info ${CLIBFLAGS})

LDFLAGS := -L ${build_dir}/${lib_dir}
LDLIBS := -Wl,--rpath=${build_dir}/${lib_dir}

lib_objs := $(filter-out %Main.cpp.o,${lib_objs})

library: ${build_dir}/${lib_dir}/${lib_name} ${srcs_objs}	##		Making vm library for testing

${build_dir}/${lib_dir}/${lib_name}: ${lib_objs}
	$(CXX) $(CLIBFLAGS) $^ -o $@ $(LDFLAGS) $(LDLIBS)

${build_dir}/${lib_dir}/%.cpp.o: ${src_dir}/%.cpp
	mkdir -p ${@D}
	$(CXX) $(CLIBFLAGS) -c $< -o $@

include ./test.mk

clean: ##		Removing generated objects, dependencies and binaries
	rm -rf ${build_dir}

-include ${deps}

help: ##		Help, showing all the possible targets and its functionalities
	@grep -Pi "^.*\:.*\#\#" ${MAKEFILE_LIST} \
		| sed 's/\$${.*}//g' \
		| awk 'BEGIN{FS=":";OFS="\t"};{print $$1,$$2}' \
		| sed -E 's/\s.*\#\#\s*/\t\t\t/g'
