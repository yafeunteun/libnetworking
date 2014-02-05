CC := gcc
RM := rm -f
CFLAGS := -fPIC -O3 -g -Wall -Werror 
NAME := networking

lib: lib$(NAME).so

lib$(NAME).so: $(NAME).o
	$(CC) -shared -Wl,-soname,lib$(NAME).so $^ -o $@


clean:
	$(RM)  *.o *.so



