# -------------------------------- MAKEFILE -------------------------------- #
#
#	Assignment: Homework 8 -- asmcoding
#
#	This hopefully makes our lives easier?
#
# -------------------------------------------------------------------------- #



# --------------------------------- RULES ---------------------------------- #

EXECUTABLES = hello-world rpn-calc

all: $(EXECUTABLES)

hello-world: urt0.ums hello-world.ums printd.ums callmain.ums
	umasm -o hello-world.um urt0.ums hello-world.ums printd.ums callmain.ums
	# um hello-world.um

rpn-calc: urt0.ums calc40.ums printd.ums callmain.ums
	umasm -o rpn-calc.um urt0.ums calc40.ums printd.ums callmain.ums
	um rpn-calc.um

clean:
	rm *.um
	rm core*

run-tests:
	sh test-calc.sh

clean-tests:
	rm test/*.ref
	rm test/*.out


# --------------------------------------------------------------------------- #
