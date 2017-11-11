Compiler    := g++
LangVersion := -std=c++17
Flags       := -O3 -Wall

Command     := $(Compiler) $(LangVersion) $(Flags)

TestDir     := tests
BuildDir    := build

test-fs-machine:
	$(Command) $(TestDir)/finite_state_machine.cpp -o $(BuildDir)/fs_machine

clear:
	rm $(BuildDir)/fs_machine
