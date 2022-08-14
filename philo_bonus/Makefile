CC = gcc

SOURCES = main_bonus.c util_bonus.c init_bonus.c life_cycle_bonus.c

OBJECTS = $(SOURCES:%.c=%.o)

HEADER = header

NAME = philo_bonus

CFLAGS = -I $(HEADER) -Wall -Werror -Wextra -O1

.PHONY: all clean fclean re bonus

all	: $(NAME)

$(NAME)	: $(OBJECTS) $(HEADER)/*.h 
	$(CC) $(CFLAGS) $(OBJECTS) -o $(NAME)

%.o	: %.c $(HEADER_B)/*.h 
	$(CC) $(CFLAGS) -c $< -o $@

bonus	: all

clean	:
	rm -f $(OBJECTS)

fclean	: clean
	rm -f $(NAME)

re	:  fclean all