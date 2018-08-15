all:
	gcc ./main.c ../core/core.c -o main

count: all
	../assembler/assembler.py ./count.pm > count
	./main ./count

fib: all
	../assembler/assembler.py ./fib.pm > fib
	./main ./fib

clean:
	rm main count fib
