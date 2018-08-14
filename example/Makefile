all:
	gcc ./main.c ../core/core.c -o main

count: all
	../assembler/assembler.py ./count.pm > count
	./main ./count

clean:
	rm main count
