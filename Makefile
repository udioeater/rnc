run-tests: rnc-tests elc-tests
	./rnc-tests
	./elc-tests

rnc: src/rnc.c src/rnc.h src/facts.h src/elc.h src/elc.c
	gcc -Wall -c -std=c99 src/elc.c -o elc.o
	gcc -Wall -c -std=c99 src/rnc.c -o rnc.o
	ar rcs librnc.a rnc.o elc.o

rnc-tests: rnc
	gcc -c -std=c99 test/test_rnc.c
	gcc -o rnc-tests test_rnc.o -lcheck -pthread -lcheck_pic -lrt -lm -L. -lrnc

elc-tests: rnc
	gcc -c -std=c99 test/test_elc.c
	gcc -o elc-tests test_elc.o -lcheck -pthread -lcheck_pic -lrt -lm -L. -lrnc

clean:
	rm -f *.o
	rm -f *.a
	rm -f *-tests
