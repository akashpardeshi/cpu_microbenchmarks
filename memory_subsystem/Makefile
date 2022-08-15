CC = clang
CFLAGS = -O0

all:
	make cache_line_size
	make tlb_associativity
	make tlb_capacity

cache_line_size: cache_line_size.o

tlb_associativity: tlb_associativity.o

tlb_capacity: tlb_capacity.o

clean:
	rm *.o
	rm cache_line_size
	rm tlb_associativity
	rm tlb_capacity
