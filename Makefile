#
# @file 			Makefile
# @author 			Geoffrey Hunter <gbmhunter@gmail.com> (wwww.mbedded.ninja)
# @edited 			n/a
# @created			2013-08-29
# @last-modified 	2014-09-14
# @brief 			Makefile for Linux-based make, to compile MClide library, example and run unit test code.
# @details
#					See README in repo root dir for more info.

SRC_COMPILER := g++
SRC_CC_FLAGS := -Wall -g -c -std=c++11
SRC_OBJ_FILES := $(patsubst %.cpp,%.o,$(wildcard src/*.cpp))
SRC_LD_FLAGS := 

DEP_LIB_PATHS := -L ../MAssert -L ../MUnitTest -L ../MCallbacks
DEP_LIBS := -l MAssert -l MUnitTest -l MCallbacks
DEP_INCLUDE_PATHS := -I../

TEST_COMPILER := g++
TEST_CC_FLAGS := -Wall -g -c -std=c++11
TEST_OBJ_FILES := $(patsubst %.cpp,%.o,$(wildcard test/*.cpp))
TEST_LD_FLAGS := 

EXAMPLE_COMPILER := g++
EXAMPLE_CC_FLAGS := -Wall -g -c -std=c++11
EXAMPLE_OBJ_FILES := $(patsubst %.cpp,%.o,$(wildcard example/*.cpp))
EXAMPLE_LD_FLAGS := 

.PHONY: depend clean

# All
all: src test example
	
	# Run unit tests:
	@./test/Tests.elf

	
#======== SRC LIB ==========	

src : deps $(SRC_OBJ_FILES)
	# Make Clide library
	ar r libMClide.a $(SRC_OBJ_FILES)
	
# Generic rule for src object files
src/%.o: src/%.cpp
	# Compiling src/ files
	$(SRC_COMPILER) $(SRC_CC_FLAGS) $(DEP_LIB_PATHS) $(DEP_LIBS) $(DEP_INCLUDE_PATHS) -MD -o $@ $<
	-@cp $*.d $*.P >/dev/null 2>&1; \
	sed -e 's/#.*//' -e 's/^[^:]*: *//' -e 's/ *\\$$//' \
		-e '/^$$/ d' -e 's/$$/ :/' < $*.d >> $*.P; \
		rm -f $*.d >/dev/null 2>&1

-include $(SRC_OBJ_FILES:.o=.d)

# ======== DEPENDENCIES ========

deps :
	# Downloading and building dependencies...
	if [ ! -d ../MUnitTest ]; then \
	git clone https://github.com/mbedded-ninja/MUnitTest ../MUnitTest; \
	fi;
	$(MAKE) -C ../MUnitTest/ all
	if [ ! -d ../MAssert ]; then \
	git clone https://github.com/mbedded-ninja/MAssert ../MAssert; \
	fi;
	$(MAKE) -C ../MAssert/ all
	if [ ! -d ../MCallbacks ]; then \
	git clone https://github.com/mbedded-ninja/MCallbacks ../MCallbacks; \
	fi;
	$(MAKE) -C ../MCallbacks/ all
	
	
# ======== TEST ========
	
# Compiles unit test code
test : deps $(TEST_OBJ_FILES) | src
	# Compiling unit test code
	g++ $(TEST_LD_FLAGS) -o ./test/Tests.elf $(TEST_OBJ_FILES)  $(DEP_LIB_PATHS) $(DEP_LIBS) $(DEP_INCLUDE_PATHS) -L./ -lMClide

# Generic rule for test object files
test/%.o: test/%.cpp
	# Compiling test/ files
	$(TEST_COMPILER) $(TEST_CC_FLAGS) $(DEP_LIB_PATHS) $(DEP_LIBS) $(DEP_INCLUDE_PATHS) -MD -o $@ $<
	-@cp $*.d $*.P >/dev/null 2>&1; \
	sed -e 's/#.*//' -e 's/^[^:]*: *//' -e 's/ *\\$$//' \
		-e '/^$$/ d' -e 's/$$/ :/' < $*.d >> $*.P; \
		rm -f $*.d >/dev/null 2>&1

-include $(TEST_OBJ_FILES:.o=.d)
	
	
# ===== EXAMPLE ======

# Compiles example code
example : $(EXAMPLE_OBJ_FILES) src
	# Compiling example code
	g++ $(EXAMPLE_LD_FLAGS) -o ./example/example.elf $(EXAMPLE_OBJ_FILES) -L./ -lMClide
	
# Generic rule for test object files
example/%.o: example/%.cpp
	$(EXAMPLE_COMPILER) $(EXAMPLE_CC_FLAGS) $(DEP_INCLUDE_PATHS) -c -o $@ $<
	
# ====== CLEANING ======
	
clean: clean-src clean-deps clean-ut 

clean-src:
	@echo " Cleaning src object files..."; $(RM) ./src/*.o
	@echo " Cleaning src dependency files..."; $(RM) ./src/*.d
	@echo " Cleaning src static library..."; $(RM) ./*.a
	@echo " Cleaning test object files..."; $(RM) ./test/*.o
	@echo " Cleaning test dependency files..."; $(RM) ./test/*.d
	@echo " Cleaning test executable..."; $(RM) ./test/*.elf
	@echo " Cleaning example object files..."; $(RM) ./example/*.o
	@echo " Cleaning example executable..."; $(RM) ./example/*.elf
	
clean-deps:
	@echo " Cleaning deps...";
	$(MAKE) -C ../MUnitTest/ clean
	$(MAKE) -C ../MAssert/ clean
	$(MAKE) -C ../MCallbacks/ clean
	
clean-ut:
	@echo " Cleaning test object files..."; $(RM) ./test/*.o
	@echo " Cleaning test executable..."; $(RM) ./test/*.elf
	


	