all: main.c eval.c
	cc main.c eval.c -o main -g -lm
debug:
	make all
	gdb main
run:
	make all
	./main
out:
	make all
	./main > out.txt
clean:
	rm -rf main
