run-tests: tests
	./tests

rnc: src/rnc.c src/rnc.h
	gcc -Wall -c -std=c99 src/rnc.c -o rnc.o
	ar rcs librnc.a rnc.o

test_rnc: test/test_rnc.c src/rnc.h
	gcc -c -std=c99 test/test_rnc.c

tests: test_rnc rnc
	gcc -o tests test_rnc.o -lcheck -pthread -lcheck_pic -lrt -lm -L. -lrnc

clean:
	rm -f *.o
	rm -f *.a
	rm -f tests
