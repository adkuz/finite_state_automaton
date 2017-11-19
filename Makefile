Compiler := g++
CVersion := -std=c++14
Flags    := $(CVersion) -Wall


SrcDir := fs_machine
AxLibDir := fs_machine/ax_libs

TestsDir := tests

test_all: test_bitvector


test_bitvector: 
	$(Compiler) $(Flags) $(TestsDir)/bitvector.cpp -o bitvector_test.tst
	./bitvector_test.tst

clear: 
	rm -rf *.o *.tst *.out