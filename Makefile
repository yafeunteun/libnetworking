CC := gcc
RM := rm -f
CFLAGS := -fPIC -O3 -g -Wall -Werror 
MAJOR := 0
MINOR := 1
NAME := networking
VERSION := $(MAJOR).$(MINOR)

lib: lib$(NAME).so.$(VERSION)

lib$(NAME).so.$(VERSION): $(NAME).o
	$(CC) -shared -Wl,-soname,lib$(NAME).so.$(MAJOR) $^ -o $@

clean:
	$(RM)  *.o *.so.*


