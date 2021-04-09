#
# 'make'        build executable file 'main'
# 'make clean'  removes all .o and executable files
#

# define the C compiler to use
CC = gcc

# define any compile-time flags
CFLAGS	:= -Wall -Wextra -g -std=c99

# define library paths in addition to /usr/lib
#   if I wanted to include libraries not in /usr/lib I'd specify
#   their path using -Lpath, something like:
LFLAGS =

# define output directory
OUTPUT	:= output

# define source directory
SRC		:= src

# define include directory
INCLUDE	:= include

# define lib directory
LIB		:= lib

TEST := test

ifeq ($(OS),Windows_NT)
MAIN	:= main.exe
TESTRUNNER := run_tests.exe
SOURCEDIRS	:= $(SRC)
SOURCEDIRS  := $(SOURCEDIRS) $(SRC)/handlers
TESTDIRS	:= $(TEST)
TESTDIRS	:= $(TESTDIRS) $(TEST)/munit $(TEST)/support
INCLUDEDIRS	:= $(INCLUDE)
INCLUDEDIRS	:= $(INCLUDEDIRS) $(INCLUDE)/handlers
LIBDIRS		:= $(LIB)
FIXPATH = $(subst /,\,$1)
RM			:= del /q /f
MD	:= mkdir
else
MAIN	:= main
TESTRUNNER := run_tests
SOURCEDIRS	:= $(shell find $(SRC) -type d)
TESTDIRS	:= $(shell find $(TEST) -type d)
INCLUDEDIRS	:= $(shell find $(INCLUDE) -type d)
LIBDIRS		:= $(shell find $(LIB) -type d)
FIXPATH = $1
RM = rm -f
MD	:= mkdir -p
endif

# define any directories containing header files other than /usr/include
INCLUDES	:= $(patsubst %,-I%, $(INCLUDEDIRS:%/=%))

# define the C libs
LIBS		:= $(patsubst %,-L%, $(LIBDIRS:%/=%))

# define the C source files
SOURCES		:= $(wildcard $(patsubst %,%/*.c, $(SOURCEDIRS)))
WITHOUTMAIN		:= $(filter-out  %/main.c, $(SOURCES))

TESTSOURCES := test/munit/munit.c \
	test/test_$(suite).c

# define the C object files 
OBJECTS		:= $(SOURCES:.c=.o)
TESTOBJECTS		:= $(TESTSOURCES:.c=.o)

#
# The following part of the makefile is generic; it can be used to 
# build any executable just by changing the definitions above and by
# deleting dependencies appended to the file from 'make depend'
#

OUTPUTMAIN	:= $(call FIXPATH,$(OUTPUT)/$(MAIN))
OUTPUTTEST	:= $(call FIXPATH,$(OUTPUT)/$(TESTRUNNER))

all: $(OUTPUT) $(MAIN)
	@echo Executing 'all' complete!

build_tests: $(OUTPUT) $(TESTRUNNER)

$(OUTPUT):
	$(MD) $(OUTPUT)

$(MAIN): $(OBJECTS) 
	$(CC) $(CFLAGS) $(INCLUDES) -o $(OUTPUTMAIN) $(OBJECTS) $(LFLAGS) $(LIBS)

$(TESTRUNNER): $(TESTOBJECTS) 
	$(CC) $(CFLAGS) $(INCLUDES) -o $(OUTPUTTEST) $(WITHOUTMAIN) $(TESTSOURCES) $(LFLAGS) $(LIBS)

# this is a suffix replacement rule for building .o's from .c's
# it uses automatic variables $<: the name of the prerequisite of
# the rule(a .c file) and $@: the name of the target of the rule (a .o file) 
# (see the gnu make manual section about automatic variables)
.c.o:
	$(CC) $(CFLAGS) $(INCLUDES) -c $<  -o $@

.PHONY: clean
clean:
	$(RM) $(OUTPUTMAIN)
	$(RM) $(OUTPUTTEST)
	$(RM) $(call FIXPATH,$(OBJECTS))
	$(RM) $(call FIXPATH,$(TESTOBJECTS))
	@echo Cleanup complete!

run: all
	./$(OUTPUTMAIN)
	@echo Executing 'run: all' complete!

test: build_tests
	./$(OUTPUTTEST)
