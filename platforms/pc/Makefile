all:
	gcc ./main.c ../../core/pmachine.c -o main

count: all
	../../assembler/assembler.py ./examples/count.pm > ./examples/count
	./main ./examples/count

fib: all
	../../assembler/assembler.py ./examples/fib.pm > ./examples/fib
	./main ./examples/fib

overflow: all
	../../assembler/assembler.py ./examples/stack_overflow.pm > ./examples/so
	./main ./examples/so

clean:
	rm -f main
	cd examples && rm -f count fib so
