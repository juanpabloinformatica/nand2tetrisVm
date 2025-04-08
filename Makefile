# Thanks to Job Vranish (https://spin.atomicobject.com/2016/08/26/makefile-c-projects/) // inspired from
# https://makefiletutorial.com
CXXFLAGS := -g -Wall -Werror -std=c++20
CXX  := g++
TARGET_EXEC  := vm

BUILD_DIR:= ./build
SRC_DIR := ./src
INC_DIR := ./include
TEST_DIR := ./test

# this can be done better
# SRCS := $(wildcard $(SRC_DIR)/*.cpp)
# SRCS += $(wildcard $(TEST_DIR)/*.cpp)
SRCS := $(shell find . -type f -name "*.cpp")
OBJS:= $(SRCS:%=$(BUILD_DIR)/%.o)

# --------- I want to understand this part -------------
# # String substitution (suffix version without %).
# # As an example, ./build/hello.cpp.o turns into ./build/hello.cpp.d
DEPS := $(OBJS:.o=.d)

# INC_DIRS := $(shell find $(SRC_DIR) -type d)
INC_FLAGS := $(addprefix -I,$(INC_DIR))

# --------- I want to understand this part -------------
# The -MMD and -MP flags together generate Makefiles for us!
# These files will have .d instead of .o as the output.
CPPFLAGS := $(INC_FLAGS) -MMD -MP

# the only thing here not clear is that LDFLAGS
# the final and default build step
$(BUILD_DIR)/$(TARGET_EXEC):$(OBJS)
	$(CXX) $(OBJS) -o $@ $(LDFLAGS)

#build the compiledb

# Build step for C source
# $(BUILD_DIR)/%.c.o: %.c
# 	mkdir -p $(dir $@)
# 	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@
#
# Build step for C++ source -- here what is not clear for
# me is %.cpp.o
$(BUILD_DIR)/%.cpp.o: %.cpp
	mkdir -p $(dir $@)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@

# compile_commands.json: $(SRCS)
# 	compiledb

.PHONY: clean
clean:
	rm -r $(BUILD_DIR)

# --------- I want to understand this part -------------
# Include the .d makefiles. The - at the front suppresses the errors of missing
# Makefiles. Initially, all the .d files will be missing, and we don't want those
# errors to show up.
-include $(DEPS)
