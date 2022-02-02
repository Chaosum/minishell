FOLDER_SRCS			= srcs

FOLDER_SIGNALS		= srcs/signals

FOLDER_UTILS		= srcs/utils

FOLDER_PARSING		= srcs/parsing

FOLDER_EXEC			= srcs/exec

FOLDER_BUILT_IN		= srcs/built_in

SRCS				= ${addprefix ${FOLDER_SRCS}/, minishell.c env.c}

SRCS_PARSING		= ${addprefix ${FOLDER_PARSING}/, tokenizer.c token_redir_state.c \
						parsing.c parsing_utils.c parsing_utils_bis.c parsing_utils_re_bis.c \
						lexer.c lexer_bis.c lexer_re_bis.c free_parsing.c create_token.c}

SRCS_UTILS			= ${addprefix ${FOLDER_UTILS}/, global_utils.c \
						ft_lstadd_back.c ft_lstadd_front.c first_memory_utils.c}

SRCS_EXEC			= ${addprefix ${FOLDER_EXEC}/, exec.c exec_pipe.c heredoc.c \
						exec_single_command.c redir_infile.c free_exec.c redir.c \
						built_in_exec.c exec_utils.c execution.c}

SRCS_BUILT_IN		= ${addprefix ${FOLDER_BUILT_IN}/, cd.c echo.c env.c exit.c \
						export.c pwd.c unset.c}

SRCS_SIGNALS		= ${addprefix ${FOLDER_SIGNALS}/, signals.c}

OBJS				= ${SRCS:.c=.o} ${SRCS_UTILS:.c=.o} ${SRCS_BUILT_IN:.c=.o} \
						${SRCS_EXEC:.c=.o} ${SRCS_PARSING:.c=.o} ${SRCS_SIGNALS:.c=.o}

INCLUDES			=	${FOLDER_SRCS}/minishell.h \
						${FOLDER_UTILS}/utils.h \
						${FOLDER_EXEC}/exec.h \
						${FOLDER_BUILT_IN}/built_in.h \
						${FOLDER_PARSING}/parsing.h \
						${FOLDER_SIGNALS}/signals.h

NAME				= minishell

CC					= gcc

CFLAGS				= -g3 -fsanitize=address -Wall -Wextra -Werror

all:		MAKELIBFT ${NAME}

%.o:		%.c
			${CC} ${CFLAGS} -o $@ -c $<

${NAME}:	${OBJS}
				gcc ${CFLAGS} -o ${NAME} ${OBJS} ./libft/libft.a -lreadline
				@echo compilation complete !
			

${OBJS}:	${INCLUDES}

MAKELIBFT:
			@make -C ./libft

clean:
			@rm -f *.o ${FOLDER_SRCS}/*.o ${FOLDER_UTILS}/*.o ${FOLDER_EXEC}/*.o \
				${FOLDER_BUILT_IN}/*.o ${FOLDER_PARSING}/*.o ${FOLDER_SIGNALS}/*.o
			@echo files cleaned !
			@make clean -C ./libft

fclean:		clean
			@rm -f ${NAME}
			@make fclean -C ./libft

re:			fclean all

.PHONY: all clean fclean re
