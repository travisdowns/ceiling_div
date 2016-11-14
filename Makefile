CFLAGS = -Wall -Wextra -O3 -march=haswell
BINARIES = validate list bench_latency bench_throughput
BINFILES = $(addprefix bin/, $(BINARIES))
# objects are things that aren't compiled directly into executables
OBJECTS = funcs.o bench.o
HEADERS = $(wildcard *.h)

all: $(BINFILES) bin/bench throughput.lst latency.lst

clean:
	cd bin && rm -f $(BINARIES) bench

bin/bench: bench.o funcs.o
	$(CC) $(CFLAGS) bench.o funcs.o -o bin/bench

$(BINFILES) : bin/% : %.c $(HEADERS)
	$(CC) $(CFLAGS) $*.c -o $@

$(OBJECTS) : %.o : %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

%.lst : bin/bench_%
	objdump -Mintel -d $< | awk -v RS='' '/[0-9a-f]+ <.*(_32|_64)>:/{print; print ""}' > $@
