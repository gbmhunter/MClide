# Define the compiler to use (e.g. gcc, g++)
CC = g++

# Define any compile-time flags (e.g. -Wall, -g)
CFLAGS = -Wall -g

# Define any directories containing header files other than /usr/include.
# Prefix every directory with "-I" e.g. "-I./src/include"
INCLUDES = -I./src/include

# Define library paths in addition to /usr/lib
# if I wanted to include libraries not in /usr/lib I'd specify
# their path using -Lpath, something like:
LFLAGS = -L./test/UnitTest++

# Define any libraries to link into executable:
#   if I want to link in libraries (libx.so or libx.a) I use the -llibname 
#   option, something like (this will link in libmylib.so and libm.so:
LIBS = -lUnitTest++

SRC_OBJ_FILES := $(patsubst %.cpp,%.o,$(wildcard src/*.cpp))
SRC_LD_FLAGS := 
SRC_CC_FLAGS := -Wall -g

TEST_OBJ_FILES := $(patsubst %.cpp,%.o,$(wildcard test/*.cpp))
TEST_LD_FLAGS := 
TEST_CC_FLAGS := -Wall -g


.PHONY: depend clean

# All
all: ClideLib Test
	
	# Run unit tests:
	@./test/ClideTest.elf
	
ClideLib : $(SRC_OBJ_FILES)
	# Make Clide library
	ar r libClide.a $(SRC_OBJ_FILES)
	
# Generic rule for src object files
src/%.o: src/%.cpp
	# Compiling src2
	g++ $(SRC_CC_FLAGS) -c -o $@ $<
	
# Compiles unit test code
Test : $(TEST_OBJ_FILES) | ClideLib UnitTestLib
	# Compiling unit test code
	g++ $(TEST_LD_FLAGS) -o ./test/ClideTest.elf $(TEST_OBJ_FILES) -L./test/UnitTest++ -lUnitTest++ -L./ -lClide
	
# Generic rule for test object files
test/%.o: test/%.cpp
	g++ $(TEST_CC_FLAGS) -c -o $@ $<
	
UnitTestLib:
	# Compile UnitTest++ library (has it's own Makefile)
	$(MAKE) -C ./test/UnitTest++/ all
	
clean:
	# Clean UnitTest++ library (has it's own Makefile)
	$(MAKE) -C ./test/UnitTest++/ clean
	
	# Clean everything else
	@echo " Cleaning src object files..."; $(RM) ./src/*.o
	@echo " Cleaning Clide static library..."; $(RM) ./*.a
	@echo " Cleaning test object files..."; $(RM) ./test/*.o
	@echo " Cleaning test executable..."; $(RM) ./test/*.elf
	
clean-ut:
	@echo " Cleaning test object files..."; $(RM) ./test/*.o
	@echo " Cleaning test executable..."; $(RM) ./test/*.elf
	
clean-clide:
	@echo " Cleaning src object files..."; $(RM) ./src/*.o
	@echo " Cleaning Clide static library..."; $(RM) ./*.a
	@echo " Cleaning test object files..."; $(RM) ./test/*.o
	@echo " Cleaning test executable..."; $(RM) ./test/*.elf
