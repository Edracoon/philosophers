NAME =		philo

CFLAGS =	-Wall -Wextra -Werror -g -fsanitize=address

SRCS =		srcs/main.c \
			srcs/main_init_threads.c \
			srcs/ft_atoi.c \
			srcs/ft_putstr_fd.c \
			srcs/ft_putnbr_fd.c \
			srcs/ft_putchar_fd.c

OBJS =		$(SRCS:.c=.o)

all:		$(NAME)

$(NAME):	$(OBJS)
			gcc $(CFLAGS) $(OBJS) -o $(NAME)

clean:
			rm -f $(OBJS)

fclean:		clean
			rm -f $(NAME)

re: 		fclean all

.PHONY:		re clean fclean all libft