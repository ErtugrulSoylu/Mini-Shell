NAME	=	minishell
SRCS	=	main.c command.c exec.c exec2.c exec3.c env.c utils.c env_utils.c builtin_funcs.c builtin_funcs_2.c handle_quote.c handle_pipe.c
OBJS	=	$(SRCS:.c=.o)
CFLAGS	=	-Wall -Wextra -Werror -I/goinfre/cagirdem/homebrew/opt/readline/include
LIBFT	=	libft/libft.a

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	$(CC) -L/goinfre/cagirdem/homebrew/opt/readline/lib -lreadline $^ $(LIBFT) -o $@ $(CFLAGS) -g 

$(LIBFT):
	make -C libft

clean:
	make -C libft clean
	rm -rf $(NAME)

fclean: clean
	make -C libft fclean
	rm -rf $(NAME) $(OBJS)

re: fclean all

.PHONY: all, clean, fclean, re
