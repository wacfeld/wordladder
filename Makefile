all: main.c
	cc main.c -o main
debug:
	cc main.c -o main -g
	gdb main
run:
	make all
	./main
out:
	make all
	./main > out.txt
clean:
	rm -rf main
