CFLAGS = -Wall -Wextra -O3 -march=haswell
BINARIES = validate list bench_latency
# objects are things that aren't compiled directly into executables
OBJECTS = funcs.o bench.o
HEADERS = $(wildcard *.h)

all: $(BINARIES) bench

clean:
	cd bin && rm -f $(BINARIES) bench

bench: bench.o funcs.o
	$(CC) $(CFLAGS) bench.o funcs.o -o bin/bench

$(BINARIES) : % : %.c $(HEADERS)
	$(CC) $(CFLAGS) $*.c -o bin/$@

$(OBJECTS) : %.o : %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@ 



