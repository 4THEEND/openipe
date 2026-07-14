include ../Makefile.include

NAME            = ipe-main
SOURCES         = main.c bigint.c ipe-step.c
OBJECTS         = $(SOURCES:.c=.o)

CFLAGS			+= -Os
LDFLAGS 		+= --dumb-memory-stub

all: $(NAME).elf

$(NAME).elf: $(OBJECTS)
	$(LD) $(LDFLAGS) $(OBJECTS) -o $@ 

%.o : %.c
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

clean:
	rm -f *.o *.elf *.ihex pmem.* output/*.o
