test_rnc: test/test_rnc.c
	gcc -c test/test_rnc.c

tests: test_rnc
	gcc -o tests test_rnc.o -lcheck -pthread -lcheck_pic -lrt -lm

clean:
	rm *.o
	rm tests
