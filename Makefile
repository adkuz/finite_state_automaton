Compiler := g++-7
CVersion := -std=c++17
Flags    := $(CVersion) -Wall


SrcDir := src
AxLibDir := $(SrcDir)/ax_libs
MachinesDir := $(SrcDir)/machines
AlgsDir := $(SrcDir)/algorithms


TestDir := tests
BuildTestsDir := $(TestDir)/build_tests
AxLibsTestDir := $(BuildTestsDir)/ax_libs
MachinesTestDir := $(BuildTestsDir)/machines
AlgsTestDir := $(BuildTestsDir)/algorithms
FullTestsDir := $(TestDir)/full_tests
AnalysisDir  := analysis


all: main

clear:
	rm -rf *.o *.bin *.out


test_all: _ax_libs_test _machines_test _algorithms_test

smart_test: _full_tests

#-------------------------------------------------------------------------------

_ax_libs_test: _bitvector_test _matrix_test

_algorithms_test: _lambda_transition_deletion _determinization

_machines_test: _base_fsm_test _finite_state_machine_test _deterministic



#-------------------main--------------------------------------------------------
main:
	$(Compiler) $(Flags) ./main.cpp -o main.bin
#------------------[main]-------------------------------------------------------


#------------------analysis-----------------------------------------------------
analytics:
	$(Compiler) $(Flags) $(AnalysisDir)/get_CPU_time.cpp \
		$(AnalysisDir)/time_check.cpp -o analysis.bin
	./analysis.bin $(AnalysisDir)/0.fsa

#-----------------[analysis]----------------------------------------------------


#-------------------full_tests--------------------------------------------------
_full_tests:
	$(Compiler) $(Flags) $(FullTestsDir)/full.cpp -o full.test.bin
	./full.test.bin
#------------------[full_tests]-------------------------------------------------



#-------------------machines----------------------------------------------------
_base_fsm_test:
	$(Compiler) $(Flags) $(MachinesTestDir)/base_fsm.cpp -o base_fsm.test.bin
	./base_fsm.test.bin

_finite_state_machine_test:
	$(Compiler) $(Flags) $(MachinesTestDir)/finite_state_machine.cpp -o \
	 	finite_state_machine.test.bin
	./finite_state_machine.test.bin

_deterministic:
	$(Compiler) $(Flags) $(MachinesTestDir)/deterministic.cpp -o \
		deterministic.test.bin
	./deterministic.test.bin
#------------------[machines]---------------------------------------------------



#------------------algorithms---------------------------------------------------
_lambda_transition_deletion:
	$(Compiler) $(Flags) $(AlgsTestDir)/lambda_transition_deletion.cpp -o \
		lambda_transition_deletion.test.bin
	./lambda_transition_deletion.test.bin

_determinization:
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
