# Dirty little tests

CMP = bzcmp
CFLAGS = -I.. -Wall
LDFLAGS = -L../.libs -llzw -Wl,-rpath,../.libs

all install:

check: lot_test simple_test simple2_test

simple_test: simple
	./simple > simple.out
	$(CMP) simple.out simple.good.bz2

simple2_test: simple2
	./simple2 > simple2.out
	$(CMP) simple2.out simple2.good.bz2

lot_test: lot
	./lot > lot.out
	$(CMP) lot.out lot.good.bz2

distdir:
	@cp Makefile *.c *.Z *.bz2 $(distdir)

clean:
	rm -f *.out lot simple simple2

.PHONY: all install check lot_test simple_test simple2_test distdir clean
