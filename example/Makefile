all:
	gcc ./main.c ../core/core.c -o main

count: all
	../assembler/assembler.py ./count.pm > count
	./main ./count

fib: all
	../assembler/assembler.py ./fib.pm > fib
	./main ./fib

overflow: all
	../assembler/assembler.py ./stack_overflow.pm > so
	./main ./so

clean:
	rm -f main count fib so
