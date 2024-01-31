# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ali <ali@student.42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/26 21:03:24 by ali               #+#    #+#              #
#    Updated: 2024/01/31 15:46:49 by ali              ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

P			= 	parsing
X			= 	execution

# SOURCES -----------------------------------------------------------------------------
BUILT_INS 	=	built_ins/built_in.c built_ins/cd.c built_ins/echo.c built_ins/env.c \
				built_ins/export.c built_ins/pwd.c built_ins/unset.c\

PARSING 	=	${P}/evaluate_quotes.c ${P}/expand.c ${P}/get_args.c ${P}/get_redirections.c \
				${P}/get_redirections_helpers.c ${P}/parse_error.c ${P}/parse_free.c ${P}/parse_utils.c \
				${P}/parse_utils2.c ${P}/parse_utils3.c ${P}/parse_utils4.c ${P}/parse_utils5.c ${P}/parse_utils6.c \
				${P}/parse_utils7.c ${P}/parser.c \

EXECUTION 	= 	${X}/error.c ${X}/execution.c ${X}/execution_utils.c ${X}/execution_utils2.c \
				${X}/execution_utils3.c ${X}/exit_shell.c ${X}/exit_status.c ${X}/fds.c ${X}/free_handler.c \
				${X}/herdoc.c ${X}/redirection.c ${X}/run_cmd.c ${X}/signals.c \

SRC 		=	${BUILT_INS} ${PARSING} ${EXECUTION} main/main.c
OBJ 		=	$(SRC:.c=.o)
CC 			=	cc
CFLAGS 		=	-Wall -Wextra -Werror -fsanitize=address -g
NAME 		=	minishell
REMOVE 		=	rm -rf

# TARGETS -----------------------------------------------------------------------------
all: ${NAME}

${NAME}: ${OBJ} minishell.h
	@$(MAKE) -C ./libft
	@${CC} $(CFLAGS) $(OBJ) -o ${NAME} -Llibft -lft -lreadline
	@echo "\033[32;1mCompiling minishell...\033[0m"

clean:
	@$(MAKE) -C ./libft clean
	@${REMOVE} ${OBJ}
	@echo "\033[31;1mRemoving minishell obj files...\033[0m"

fclean:
	@$(MAKE) -C ./libft fclean
	@${REMOVE} ${OBJ}
	@${REMOVE} ${NAME}
	@echo "\033[31;1mRemoving Minishell...\033[0m"

re: fclean all 

.phony: all clean fclean re