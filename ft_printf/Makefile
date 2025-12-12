# Name of the executable
NAME = test.out

# Compiling
CC = cc
CFLAGS = -Wall -Wextra -Werror -g
LIB = -L./deliver -lftprintf 

# Code
SOURCES = main.c

## Rules to compile
$(NAME): $(SOURCES) deliver/libftprintf.a
	$(CC) $(CFLAGS) $(SOURCES) $(LIB) -o $(NAME)

deliver/libftprintf.a:
	$(MAKE) -C deliver

all: $(NAME)

run: $(NAME)
	./$(NAME) 

vrun:
	valgrind ./$(NAME)

## Tests against printf

tap: deliver/libftprintf.a
	$(CC) $(CFLAGS) -D FT=printf $(SOURCES) -o $(NAME)
	./$(NAME) > outstd.txt
	$(CC) $(CFLAGS) -D FT=ft_printf $(SOURCES) $(LIB) -o $(NAME)
	./$(NAME) > outft.txt


## Rules to clean up

clean:
	$(MAKE) fclean -C deliver

fclean: clean
	rm -f $(NAME) outstd.txt outft.txt

re: fclean all

.PHONY:
