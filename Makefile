#
# @brief       Makefile for building and testing SmartOptions libary.
#
# @copyright   This content is released under Berkeley Software Distribution license (BSD)
#

#... *********************************--->System Configuration Section... *********************************--->

# Project Directories
INC_DIR := inc
TST_DIR := tests
OUT_DIR := bin
DOC_DIR := docs

TEST_RUNNER := $(OUT_DIR)/TestRunner

# SmartOptions Library source files...
PRJ_FILES := $(INC_DIR)/SmartOptions/SmartOptions.hpp

# tests/Test1.cpp, tests/Test2.cpp
TEST_FILES := $(wildcard $(TST_DIR)/*.h)
TEST_RUNNER_CPP := $(TST_DIR)/TestRunner.cpp

CPP      := g++
CXXFLAGS := -g -Wall -Werror -pedantic
LFLAGS   :=
LLIBS    := 

CXXTESTGEN := cxxtestgen

CMD_ECHO := @

#... *********************************--->Rules Section... *********************************--->

all: help

# Phony target to print help message...
help: copyright
	@printf "\n---> make test  (Run Tests )"
	@printf "\n---> make clean (Clean all temporary files )"
	@printf "\n---> make docs  (Create Doxygen HTML Documentation )\n"

test: copyright $(TEST_RUNNER)
	@printf "\n---> Running Tests for SmartOptions library...\n"
	$(CMD_ECHO)$(TEST_RUNNER)

$(TEST_RUNNER): createOutDir createTestRunner buildTestRunner $(PRJ_FILES) $(TEST_FILES)

# Phony target to create TestRunner.cpp
createTestRunner:
	@printf "\n---> Generating Test Runner...\n"
	$(CMD_ECHO)$(CXXTESTGEN) --error-printer -o $(TEST_RUNNER_CPP) $(TEST_FILES)

# Phony target to build TestRunner
buildTestRunner:
	@printf "\n---> Building Test Runner...\n"
	$(CMD_ECHO)$(CPP) -o $(TEST_RUNNER) $(TEST_RUNNER_CPP) -I $(INC_DIR) $(CXXFLAGS)

# Phony target to create output directory...
createOutDir:
	@printf "\n---> Creating Output Directory... n"
	$(shell mkdir -p $(OUT_DIR) >/dev/null)
	printf "done\n\n"

# Phony target to display Project/Copyright information...
copyright:
	@printf "Welcome to SmartOptions library, the next generation of Command Line Parameter processing library.\n"
	@printf "Author: Harsha Yalagach\n"
	@printf "This content is released under Berkelley Software Distribution license (BSD).\n"


# Phony target to create Doxygen Document...
docs: copyright $(PRJ_FILES)
	@printf "\n---> Generating Doxygen HTML Documentation..."
	$(CMD_ECHO)doxygen
	@printf "done.\n\n"

# Target to clean all temporary files...
clean: copyright
	@printf "\n---> Cleaning up files..."
	$(CMD_ECHO)rm -f  $(TEST_RUNNER_CPP)
	$(CMD_ECHO)rm -rf $(OUT_DIR)
	$(CMD_ECHO)rm -rf $(DOC_DIR)
	@printf "done.\n\n"


# These are the pattern matching rules. In addition to the automatic
# variables used here, the variable $* that matches whatever % stands for
# can be useful in special cases.
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $(OUT_DIR)/$@

# The list of phony targets
.PHONY: clean copyright createTestRunner buildTestRunner
