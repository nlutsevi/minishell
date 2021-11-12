NAME = minishell

INC = includes

CC =  gcc

CFLAGS =  -Wall -Werror -Wextra  -g  -fsanitize=address

RM = rm -f

SRCS = 	gnl/get_next_line.c \
		prompt.c \
		init_env.c \
		cmd_parse.c \
		run_generic_cmds.c \
		init_cmd.c \
		main.c \
		builtins/echo/echo.c \
		builtins/echo/echo2.c \
		builtins/echo/echo3.c \
		builtins/pwd.c \
		builtins/cd/cd.c \
		builtins/cd/cd2.c \
		builtins/exit.c \
		builtins/exit2.c \
		builtins/env.c \
		builtins/unset/unset.c \
		builtins/unset/unset2.c \
		builtins/export/export.c \
		builtins/export/export2.c \
		builtins/export/export3.c \
		free_memory.c \
		free_memory2.c \
		get_redirections.c \
		get_redirections2.c \
		get_pipes.c \
		get_redirection_parser.c \
		nodos_manager.c \
		calculate_pipes.c \
		calculate_pipes2.c \
		calculate_complex_pipes.c \
		nodos_env.c \
		double_files.c \
		pipes.c \
		pipes2.c \
		pipes3.c \
		pipes4.c \
		quotes.c

OBJS = 	$(SRCS:.c=.o)

%.o: %.c
		$(CC) $(CFLAGS) -I $(INC) $< -c -o $@

all: $(NAME)

$(NAME): $(OBJS)
					@echo "Building minishell..."
					@make -sC libft re
					$(CC) $(CFLAGS) $(OBJS) -o $(NAME) -lreadline -L libft/ -lft -L/Users/$USER/.brew/opt/readline/lib -I/Users/$USER/.brew/opt/readline/include
					@chmod 777 $(NAME)
clean:
					@echo "Cleaning up *.o files..."
					@make -sC libft clean
					$(RM) $(OBJS)

fclean: clean
					@echo "Removing *.a files..."
					@make -sC libft fclean
					$(RM) $(NAME)

re:	fclean all

.PHONY: all clean fclean re
