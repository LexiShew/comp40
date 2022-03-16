# -------------------------------- MAKEFILE --------------------------------- #
#
# Assignment: Homework 7 -- profiling
# Authors: Lexi Shewchuk (ashewc01), Aaron Hamburg (ahambu01)
# Date: 7 December 2021
#
# This Makefile was created to execute and test our UM. It creates a single,
#		optimized executable, um, which is a program that expects an input .um
#		binary file and runs the instructions found in that file.
#
# --------------------------------------------------------------------------- #



# -------------------------------- VARIABLES -------------------------------- #

# compiler
CC = gcc

# include flags to get comp40 stuff
IFLAGS = -I. -I/comp/40/build/include -I/usr/sup/cii40/include/cii

# compile flags
CFLAGS = -O3 -g -std=c99 -Wall -Wextra -Werror -Wfatal-errors -pedantic \
																	$(IFLAGS)

# linking flags
LDFLAGS = -g -L/comp/40/build/lib -L/usr/sup/cii40/lib64

# libraries to link
LDLIBS = -lcii40-O2 -lbitpack -lcii40 -lnetpbm -lm -lrt -lpnm -l40locality \
																-larith40


# collect every .h file found in the folder (even ones that aren't used)
INCLUDES = $(shell echo *.h)

# --------------------------------------------------------------------------- #



# ---------------------------------- RULES ---------------------------------- #

# turn .c files into .o files
%.o: %.c $(INCLUDES)
	$(CC) $(CFLAGS) -c $< -o $@

#list out all the executables you want to create
EXECUTABLES = um #mem-test reg-test

all: $(EXECUTABLES)

um: um.o
	$(CC) $(LDFLAGS) $^ -o $@ $(LDLIBS)

clean:
	rm -f $(EXECUTABLES) *.o

# --------------------------------------------------------------------------- #
