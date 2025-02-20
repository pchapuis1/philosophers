SRCS		=	philo.c \
				ft_atoi.c \
				init.c \
				action.c \
				utils.c \
				error.c \
				check_end.c

OBJS		= ${addprefix ./objs/, ${SRCS:.c=.o}}

NAME		= philo

CC			= cc

RM 			= rm -rf

CFLAGS		= -g -pthread -Wall -Wextra -Werror -g3

HEADERS		= includes/philo.h 

all:		${NAME}

./objs/%.o:	./srcs/%.c ${HEADERS}
			@mkdir -p objs
			${CC} ${CFLAGS} -c $< -o $@ -Iincludes

${NAME}: 	${OBJS} Makefile
			${CC} ${CFLAGS} -o ${NAME} ${OBJS}

clean:
			${RM} objs

fclean:		clean
			${RM} ${NAME}

re:			fclean all

.PHONY:		all clean fclean re