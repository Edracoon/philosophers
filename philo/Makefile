NAME =		philo

CFLAGS =	-Wall -Wextra -Werror

SRCS =		srcs/main.c \
			srcs/main_init_threads.c \
			srcs/eat_sleep_think.c \
			srcs/ft_atoi.c \

OBJS =		$(SRCS:.c=.o)

all:		$(NAME)

$(NAME):	$(OBJS)
			gcc $(CFLAGS) $(OBJS) -o $(NAME)

clean:
			rm -f $(OBJS)

fclean:		clean
			rm -f $(NAME)

re: 		fclean all

.PHONY:		re clean fclean all
