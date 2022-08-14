CC = gcc

SOURCES = main.c init.c utils.c life_cycle.c dead.c

OBJECTS = $(SOURCES:%.c=%.o)

HEADER = header

NAME = philo

CFLAGS = -I $(HEADER) -Wall -Werror -Wextra -O1

.PHONY: all clean fclean re bonus

all	: $(NAME)

$(NAME)	: $(OBJECTS) $(HEADER)/*.h
	$(CC) $(CFLAGS) $(OBJECTS) -lpthread -o $(NAME)

%.o	: %.c $(HEADER)/*.h
	$(CC) $(CFLAGS) -c $< -o $@

bonus	: all

clean	:
	rm -f $(OBJECTS)

fclean	: clean
	rm -f $(NAME)

re	:  fclean all