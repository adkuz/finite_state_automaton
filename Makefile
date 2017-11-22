Compiler := g++-7
CVersion := -std=c++17
Flags    := $(CVersion) -Wall


SrcDir := fs_machine
AxLibDir := fs_machine/ax_libs

TestsDir := tests


test_all: test_bitvector
	

test_bitvector: 
	$(Compiler) $(Flags) $(TestsDir)/bitvector.cpp -o bitvector_test.tst
	./bitvector_test.tst

low_iq_test:
	$(Compiler) $(Flags) $(TestsDir)/low_iq_bitvector.cpp -o bitvector_test.tst
	./bitvector_test.tst


clear: 
	rm -rf *.o *.tst *.out