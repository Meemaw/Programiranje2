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
	ulimit -t 1 ; ./$(ID) < ./tests/input-1
	if diff -w -B svet.txt ./tests/output-1 ; then echo "1 - correct" ; fi
	ulimit -t 1 ; ./$(ID) < ./tests/input-2
	if diff -w -B ChessBoard.txt ./tests/output-2 ; then echo "2 - correct" ; fi
	ulimit -t 1 ; ./$(ID) < ./tests/input-3
	if diff -w -B Mongoose.txt ./tests/output-3 ; then echo "3 - correct" ; fi

	@echo
	@'rm' -fr $(ID) *~
	@'rm' -fr result-* *~
