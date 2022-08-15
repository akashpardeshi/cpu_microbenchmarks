CC = clang
CFLAGS = -O0

all:
	make btb
	make ret_addr_stack

btb: btb.o

ret_addr_stack: ret_addr_stack.o

clean:
	rm *.o
	rm btb
	rm ret_addr_stack
