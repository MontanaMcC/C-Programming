SOURCES=vm.c vm_menu.c vm_options.c vm_stock.c vm_coin.c utility.c
HEADERS=vm.h vm_menu.h vm_options.h vm_stock.h vm_coin.h utility.h vm_system.h
PROGRAM=vm
DEBUG=-g
FLAGS=-ansi -pedantic -Wall $(DEBUG)
OBJS = vm.o vm_menu.o vm_options.o vm_stock.o vm_coin.o utility.o

all: $(OBJS)
	gcc $(FLAGS) -o $(PROGRAM) $(OBJS)

%.o: %.c
		$(CC) $(CFLAGS) -c -o $@ $^

clean:
	rm -f *.o *.out core $(PROGRAM)

archive:
	zip $(USER)-a2 $(SOURCES) $(HEADERS) Requirement13Part1.txt Requirement13Part2.txt Makefile
