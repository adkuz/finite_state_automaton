Compiler := g++-7
CVersion := -std=c++17
Flags    := $(CVersion) -Wall


SrcDir := src
AxLibDir := $(SrcDir)/ax_libs
MachinesDir := $(SrcDir)/machines
AlgsDir := $(SrcDir)/algorithms

BuildTestsDir := tests/build_tests
AxLibsTestDir := $(BuildTestsDir)/ax_libs
MachinesTestDir := $(BuildTestsDir)/machines
AlgsTestDir := $(BuildTestsDir)/algorithms


test_all: ax_libs_test


ax_libs_test: _bitvector_test _matrix_test


machines_test: base_fsm_test finite_state_machine_test deterministic


#-------------------machines----------------------------------------------------
base_fsm_test:
	$(Compiler) $(Flags) $(MachinesTestDir)/base_fsm.cpp -o base_fsm.test.bin
	./base_fsm.test.bin

finite_state_machine_test:
	$(Compiler) $(Flags) $(MachinesTestDir)/finite_state_machine.cpp -o \
	 	finite_state_machine.test.bin
	./finite_state_machine.test.bin

deterministic:
	$(Compiler) $(Flags) $(MachinesTestDir)/deterministic.cpp -o \
		deterministic.test.bin
	./deterministic.test.bin
#------------------[machines]---------------------------------------------------


#------------------algorithms---------------------------------------------------
lambda_transition_deletion:
	$(Compiler) $(Flags) $(AlgsTestDir)/lambda_transition_deletion.cpp -o \
		lambda_transition_deletion.test.bin
	./lambda_transition_deletion.test.bin

determinization:
	$(Compiler) $(Flags) $(AlgsTestDir)/determinization.cpp -o \
		determinization.test.bin
	./determinization.test.bin
#-----------------[algorithms]--------------------------------------------------


#---------------ax_libs_test----------------------------------------------------
_bitvector_test:
	$(Compiler) $(Flags) $(AxLibsTestDir)/bitvector.cpp -o bitvector.test.bin
	./bitvector.test.bin

_matrix_test:
	$(Compiler) $(Flags) $(AxLibsTestDir)/matrix.cpp -o matrix.test.bin
	./matrix.test.bin
#--------------[ax_libs_test]---------------------------------------------------

clear:
	rm -rf *.o *.bin *.out
