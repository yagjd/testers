
# Compiling
CC = cc
CFLAGS += -Wall -Wextra -Werror -g
# Constants
D = -D BUFFER_SIZE=1024
# Code
SOURCES = get_next_line.c get_next_line_utils.c main.c main_utils.c
SOURCES_BONUS = get_next_line_bonus.c get_next_line_utils_bonus.c main.c main_utils.c

# Name of the executable
NAME = test.a
# Library
LIBFLAG = -lft -L.

## Rules to compile

$(NAME):
	$(CC) $(CFLAGS) $(D) $(SOURCES) -o $(NAME) $(LIBFLAG)

all: $(NAME)

bonus:
	$(CC) $(CFLAGS) $(D) $(SOURCES_BONUS) -o $(NAME) $(LIBFLAG)

no_d:
	$(CC) $(CFLAGS) $(SOURCES) -o $(NAME) $(LIBFLAG)

no_d_bonus:
	$(CC) $(CFLAGS) $(SOURCES_BONUS) -o $(NAME) $(LIBFLAG)

## Rules to run tests

INFILE = testtxt.txt
LINES = 112

FILENAMES_IN =  out_file_read0.txt  out_file_read1.txt  out_file_read2.txt  out_file_read3.txt  out_file_read4.txt  out_file_read5.txt  out_file_read6.txt  out_file_read7.txt  out_file_read8.txt  out_file_read9.txt
FILENAMES_OUT = out_file_written0.txt out_file_written1.txt out_file_written2.txt out_file_written3.txt out_file_written4.txt out_file_written5.txt out_file_written6.txt out_file_written7.txt out_file_written8.txt out_file_written9.txt

run:
	./$(NAME) $(INFILE) $(LINES) 

vrun:
	valgrind ./$(NAME) $(INFILE) $(LINES)

stdin:
	./$(NAME)

vstdin:
	valgrind ./$(NAME)

setbatterytest:
	./$(NAME) $(FILENAMES_IN)

execbatterytest:
	./$(NAME) $(FILENAMES_IN) $(FILENAMES_OUT)

vexecbatterytest:
	valgrind ./$(NAME) $(FILENAMES_IN) $(FILENAMES_OUT)

## Rules to loop over compiling and running tests

SIZES = 1 2 3 4 5 10 42 100 1000 1024 4096 9999 10000 100000

bstest:
	$(foreach N, $(SIZES), \
		$(CC) $(CFLAGS) -D BUFFER_SIZE=$(N) $(SOURCES) -o $(NAME) $(LIBFLAG) ; \
		./$(NAME) $(INFILE) ; \
		rm $(NAME) ; )

vbstest:
	$(foreach N, $(SIZES), \
		$(CC) $(CFLAGS) -D BUFFER_SIZE=$(N) $(SOURCES) -o $(NAME) $(LIBFLAG) ; \
		valgrind ./$(NAME) $(INFILE) ; \
		rm $(NAME) ; )

bstest_bonus:
	$(foreach N, $(SIZES), \
		$(CC) $(CFLAGS) -D BUFFER_SIZE=$(N) $(SOURCES_BONUS) -o $(NAME) $(LIBFLAG) ; \
		./$(NAME) $(INFILE) ; \
		rm $(NAME) ; )

vbstest_bonus:
	$(foreach N, $(SIZES), \
		$(CC) $(CFLAGS) -D BUFFER_SIZE=$(N) $(SOURCES_BONUS) -o $(NAME) $(LIBFLAG) ; \
		valgrind ./$(NAME) $(INFILE) ; \
		rm $(NAME) ; )

execbtbs:
	$(foreach N, $(SIZES), \
		$(CC) $(CFLAGS) -D BUFFER_SIZE=$(N) $(SOURCES_BONUS) -o $(NAME) $(LIBFLAG) ; \
		./$(NAME) $(FILENAMES_IN) $(FILENAMES_OUT) ; \
		rm $(NAME) ; )

vexecbtbs:
	$(foreach N, $(SIZES), \
		$(CC) $(CFLAGS) -D BUFFER_SIZE=$(N) $(SOURCES_BONUS) -o $(NAME) $(LIBFLAG) ; \
		valgrind ./$(NAME) $(FILENAMES_IN) $(FILENAMES_OUT) ; \
		rm $(NAME) ; )

## Rules to clean up

clean:
	rm -f $(FILENAMES_IN) $(FILENAMES_OUT) out.txt

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: $(NAME)
