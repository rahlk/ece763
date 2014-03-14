#SOURCES = $(wildcard *.c)
#OBJECTS = $(SOURCES:.c=.o)

# Main target
: $(OBJECTS)
	cc $(SOURCES) -o OUTPUT -I/home/rahul/Ubuntu64/hdr /home/rahul/Ubuntu64/ifslib/libifs.a -lm
	./OUTPUT
	rm OUTPUT


