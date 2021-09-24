FOLDER_SRCS			= srcs

FOLDER_UTILS		= srcs/utils

FOLDER_EXEC			= srcs/exec

FOLDER_BUILT_IN		= srcs/built_in

SRCS				= ${addprefix ${FOLDER_SRCS}/, minishell.c}

SRCS_UTILS			= ${addprefix ${FOLDER_UTILS}/, global_utils.c ft_atoi.c ft_itoa.c \
						ft_calloc.c ft_strdup.c ft_strjoin.c ft_strlen.c ft_strncmp.c \
						ft_lstadd_back.c ft_lstadd_front.c first_memory_utils.c ft_strlcat.c}

SRCS_EXEC			= ${addprefix ${FOLDER_EXEC}/, exec.c}

SRCS_BUILT_IN		= ${addprefix ${FOLDER_BUILT_IN}/, cd.c echo.c env.c exit.c export.c pwd.c unset.c}

OBJS				= ${SRCS:.c=.o} ${SRCS_UTILS:.c=.o} ${SRCS_BUILT_IN:.c=.o} ${SRCS_EXEC:.c=.o} 

INCLUDES			=	${FOLDER_SRCS}/minishell.h \
						${FOLDER_UTILS}/utils.h \
						${FOLDER_EXEC}/exec.h \
						${FOLDER_BUILT_IN}/built_in.h

NAME				= minishell

CC					= gcc

CFLAGS				= -g3 -fsanitize=address # -Wall -Wextra -Werror

all:		${NAME}

%.o:		%.c
			${CC} ${CFLAGS} -o $@ -c $<

${NAME}:	${OBJS}
				gcc ${CFLAGS} -o ${NAME} ${OBJS} -lreadline
				@echo compilation complete !
			

${OBJS}:	${INCLUDES}

clean:
			@rm -f *.o ${FOLDER_SRCS}/*.o ${FOLDER_UTILS}/*.o ${FOLDER_EXEC}/*.o ${FOLDER_BUILT_IN}/*.o
			@echo files cleaned !

fclean:		clean
			@rm -f ${NAME}

re:			fclean all

.PHONY: all clean fclean re