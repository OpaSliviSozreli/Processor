CXX = g++
SOURCES = main.cpp processor.cpp ../stack_lib/stack.cpp
EXECUTABLE_file1= processor
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

all: processor

processor: main.o processor.o stack.o
	$( CXX ) $( SOURCES ) -o $( EXECUTABLE_file1) $( WARNINGS )

main.o: main.cpp
	$( CXX ) main.cpp -c

processor.o: processor.cpp
	$( CXX ) processor.cpp -c

stack.o: stack.cpp
	$( CXX ) stack.cpp -c


g++ main.cpp -I /onegin_lib 