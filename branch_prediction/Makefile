CC = clang
CFLAGS = -O0

all:
	make btb_associativity
	make btb_capacity
	make ret_addr_stack

btb_associativity: btb_associativity.o

btb_capacity: btb_capacity.o

ret_addr_stack: ret_addr_stack.o

clean:
	rm *.o
	rm btb_associativity
	rm btb_capacity
	rm ret_addr_stack
