CC	= gcc
CFLAGS	= -std=c99 -pedantic -Wall
LIBS	= -lm
ID = code

$(ID)	: code.c
	@echo "=== COMPILING: ==="
	$(CC) $(CFLAGS) -o $@ $< $(LIBS)
	@echo

test	: $(ID)
	@echo "=== TESTING: ==="
	./$(ID) < ./tests/input-1 > result-1
	if diff -w -B result-1 ./tests/output-1 ; then echo "1 - correct" ; fi
	./$(ID) < ./tests/input-2 > result-2
	if diff -w -B result-2 ./tests/output-2 ; then echo "2 - correct" ; fi
	./$(ID) < ./tests/input-3 > result-3
	if diff -w -B result-3 ./tests/output-3 ; then echo "3 - correct" ; fi
	./$(ID) < ./tests/input-4 > result-4
	if diff -w -B result-4 ./tests/output-4 ; then echo "4 - correct" ; fi
	./$(ID) < ./tests/input-5 > result-5
	if diff -w -B result-5 ./tests/output-5 ; then echo "5 - correct" ; fi
	./$(ID) < ./tests/input-6 > result-6
	if diff -w -B result-6 ./tests/output-6 ; then echo "6 - correct" ; fi
	./$(ID) < ./tests/input-7 > result-7
	if diff -w -B result-7 ./tests/output-7 ; then echo "7 - correct" ; fi
	./$(ID) < ./tests/input-8 > result-8
	if diff -w -B result-8 ./tests/output-8 ; then echo "8 - correct" ; fi
	./$(ID) < ./tests/input-9 > result-9
	if diff -w -B result-9 ./tests/output-9 ; then echo "9 - correct" ; fi
	./$(ID) < ./tests/input-10 > result-10
	if diff -w -B result-10 ./tests/output-10 ; then echo "10 - correct" ; fi

	@echo
	@'rm' -fr $(ID) *~
	@'rm' -fr result-* *~