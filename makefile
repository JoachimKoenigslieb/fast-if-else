# Makefile

# Compiler settings
CC=gcc
# Targets
all: simple cpu_parallel

simple: simple.c
	$(CC) simple.c -o simple 

cpu_parallel: cpu-parallel.c
	$(CC) cpu-parallel.c -o cpu_parallel 

clean:
	rm -f simple cpu_parallel
