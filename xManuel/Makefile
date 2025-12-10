# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: marhuber <falcino@gmail.com>               +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/11/14 13:19:29 by marhuber          #+#    #+#              #
#    Updated: 2025/12/10 11:33:13 by marhuber         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Name of the executable
NAME = fdf

# Compiling
CC = cc
CFLAGS = -Wall -Wextra -Werror -g #-I../minilibx-linux
LIBS = -lmlx -lXext -lX11 -lm -L./minilibx-linux

# Name of all sources files to be passed to the CC command
MY_SOURCES = \
	main.c  \
	get_next_line.c get_next_line_utils.c \
	lists.c \
	read_file.c read_tab.c\
	colors.c linalg.c \
	launch.c \
	display.c segments.c \
	hooks.c updates_linear.c updates_rotational.c 

MY_OBJECTS = $(MY_SOURCES:.c=.o)


## Rules to compile


# Rule that gets called by default 
$(NAME): $(MY_OBJECTS) minilibx-linux/libmlx.a
	$(CC) $^ $(LIBS) -o $(NAME) 
# An implicit rule creates the objects using CFLAGS

minilibx-linux/libmlx.a:
	$(MAKE) -C minilibx-linux

## Rules to clean up
all: $(NAME)
	
clean:
	rm -f $(MY_OBJECTS)
	$(MAKE) clean -C minilibx-linux

fclean: clean
	rm -f $(NAME) minilibx-linux/Makefile.gen minilibx-linux/test/Makefile.gen
	
re: fclean all

.SECONDARY: $(MY_OBJECTS)

## Demo

 FDF = demo/42.fdf

run: $(NAME)
	./$(NAME) $(FDF)

vrun: $(NAME)
	valgrind --track-origins=yes ./$(NAME) $(FDF)

TEST_FILES = $(wildcard demo/*.fdf) #$(wildcard test_maps/*.fdf)

mrun: $(NAME) 
	@$(foreach F, $(TEST_FILES), \
		echo "\n--- $(F) ---" ; \
		./$(NAME) $(F) ; )