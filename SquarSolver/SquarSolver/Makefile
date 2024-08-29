# Это комментарий, который говорит, что переменная CC указывает компилятор, используемый для сборки
CC = g++
# Это еще один комментарий. Он поясняет, что в переменной CFLAGS лежат флаги, которые передаются компилятору
CFLAGS  = 	-Wshadow -Winit-self -Wredundant-decls -Wcast-align -Wundef -Wfloat-equal -Winline -Wunreachable-code\
			-Wmissing-declarations -Wmissing-include-dirs -Wswitch-enum -Wswitch-default -Weffc++ -Wmain -Wextra -Wall -g -pipe\
			-fexceptions -Wcast-qual -Wconversion -Wctor-dtor-privacy -Wempty-body -Wformat-security -Wformat=2\
			-Wignored-qualifiers -Wlogical-op -Wno-missing-field-initializers -Wnon-virtual-dtor -Woverloaded-virtual\
			-Wpointer-arith -Wsign-promo -Wstack-usage=8192 -Wstrict-aliasing -Wstrict-null-sentinel -Wtype-limits\
			-Wwrite-strings -Werror=vla -D_DEBUG -D_EJUDGE_CLIENT_SIDE

all: main.o input_output.o solve.o test.o general_functions.o
	g++ main.o input_output.o solve.o test.o general_functions.o -o solve

main.o: cpp/main.cpp
	$(CC) $(CFLAGS) -c cpp/main.cpp

input_output.o: cpp/input_output.cpp
	$(CC) $(CFLAGS) -c cpp/input_output.cpp

solve.o: cpp/solve.cpp
	$(CC) $(CFLAGS) -c cpp/solve.cpp

test.o: cpp/test.cpp
	$(CC) $(CFLAGS) -c cpp/test.cpp

general_functions.o: cpp/general_functions.cpp
	$(CC) $(CFLAGS) -c cpp/general_functions.cpp

.PHONY: clean
clean:
	rm -rf *.o solve
