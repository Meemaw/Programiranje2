CC	= gcc
CFLAGS	= -std=c99 -pedantic -Wall
LIBS	= -lm
ID = code

$(ID)	: code.c
	@echo "=== COMPILING: ==="
	$(CC) $(CFLAGS) -o $@ $< $(LIBS)
	@echo

test	: $(ID)
	../scripts/runTests.sh $(ID)

	@echo
	@'rm' -fr $(ID) *~
	@'rm' -fr result-* *~