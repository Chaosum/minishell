FOLDER_UTILS		= srcs/utils

FOLDER_EXEC			= srcs/exec

FOLDER_SRCS			= srcs

SRCS				= ${addprefix ${FOLDER_SRCS}/, minishell.c}

SRCS_UTILS			= ${addprefix ${FOLDER_UTILS}/, global_utils.c ft_atoi.c ft_itoa.c ft_calloc.c ft_strdup.c ft_strjoin.c ft_strlen.c ft_strncmp.c}

SRCS_EXEC			= ${addprefix ${FOLDER_EXEC}/, exec.c}

OBJS				= ${SRCS:.c=.o} ${SRCS_UTILS:.c=.o}

INCLUDES			=	${FOLDER_SRCS}/minishell.h \
						${FOLDER_UTILS}/utils.h \
						${FOLDER_EXEC}/exec.h

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
			@rm -f *.o ${FOLDER_SRCS}/*.o ${FOLDER_UTILS}/*.o ${FOLDER_EXEC}/*.o
			@echo files cleaned !

fclean:		clean
			@rm -f ${NAME}

re:			fclean all

.PHONY: all clean fclean re