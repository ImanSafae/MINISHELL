FILES = 

OBJS = ${FILES:.c=.o}

NAME = minishell-obama

FLAGS = -Wall -Wextra -Werror

%.o:	%.c
	gcc -c ${FLAGS} -o $@ $<

all:	${NAME}

${NAME}:${OBJS}
	${MAKE} -C ./LIBFT bonus
	gcc ${FLAGS} -o ${NAME} ${OBJS} LIBFT/libft.a

clean: 
	rm *f ${OBJS}

fclean:	clean
	rm -f ${NAME}

re:	fclean all

.phony: all clean fclean re