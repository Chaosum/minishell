FOLDER_UTILS		= srcs/utils

FOLDER_SRCS			= srcs

SRCS				= ${addprefix ${FOLDER_SRCS}/, minishell.c}

SRCS_UTILS			= ${addprefix ${FOLDER_UTILS}/,}

OBJS				= ${SRCS:.c=.o} ${SRCS_UTILS:.c=.o}

INCLUDES			= ${addprefix ${FOLDER_SRCS}/, minishell.h}

NAME				= minishell

CC					= gcc

CFLAGS				=  -g3 -fsanitize=address # -Wall -Wextra -Werror

all:		${NAME}

%.o:		%.c
			${CC} ${CFLAGS} -o $@ -c $<

${NAME}:	${OBJS}
				gcc ${CFLAGS} -o ${NAME} ${OBJS} -lreadline
				@echo compilation complete !
			

${OBJS}:	${INCLUDES}

clean:
			@rm -f *.o ${FOLDER_SRCS}/*.o
			@echo files cleaned !

fclean:		clean
			@rm -f ${NAME}

re:			fclean all

.PHONY: all clean fclean re