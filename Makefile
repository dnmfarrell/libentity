test: minunit.h
	gcc -O0 -Wall -Werror -std=c99 -o runtests test.c entity.c
	./runtests
	rm runtests

mem: entity.h
	gcc -O0 -Wall -Werror -std=c99 -o runtests test.c entity.c && valgrind --leak-check=full ./runtests
	rm runtests
