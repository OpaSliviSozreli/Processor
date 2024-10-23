CXX = g++
SOURCES = asm_main.cpp assembler.cpp stack.cpp array_of_pointers.cpp input_and_output.cpp
EXECUTABLE_file1= assembler
CFLAGS = -b
WARNINGS = -Wshadow -Winit-self -Wredundant-decls -Wcast-align -Wundef -Wfloat-equal \
		   -Winline -Wunreachable-code -Wmissing-declarations -Wmissing-include-dirs \
		   -Wswitch-enum -Wswitch-default -Weffc++ -Wmain -Wextra -Wall -g -pipe \
		   -fexceptions -Wcast-qual -Wconversion -Wctor-dtor-privacy -Wempty-body \
		   -Wformat-security -Wformat=2 -Wignored-qualifiers -Wlogical-op \
		   -Wno-missing-field-initializers -Wnon-virtual-dtor -Woverloaded-virtual \
		   -Wpointer-arith -Wsign-promo -Wstack-usage=8192 -Wstrict-aliasing \
		   -Wstrict-null-sentinel -Wtype-limits -Wwrite-strings -Werror=vla \
		   -D_DEBUG -D_EJUDGE_CLIENT_SIDE

all: assembler

assembler: asm_main.o processor.o stack.o array_of_pointers.o input_and_output.o
	$( CXX ) $( SOURCES ) -o $( EXECUTABLE_file1) $( WARNINGS )

main.o: asm_main.cpp
	$( CXX ) asm_main.cpp -c

assembler.o: assembler.cpp
	$( CXX ) assembler.cpp -c

stack.o: stack.cpp
	$( CXX ) stack.cpp -c

array_of_pointers.o: array_of_pointers.cpp
	$( CXX ) array_of_pointers.cpp -c

input_and_output.o: input_and_output.cpp
	$( CXX ) input_and_output.cpp -c