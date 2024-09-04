SRC = philo.c utils.c init_utils.c simulation.c actions.c
OBJS = ${SRC:.c=.o}
CFLAGS = -Wall -Wextra -Werror #-fsanitize=thread -g
CC = cc
RM = rm -f
NAME = philo

%.o: %.c philo.h
	@$(CC) $(CFLAGS) -c -o $@ $<

all: ${NAME}
	
${NAME}: ${OBJS}
		@echo "Compiling..."
		@echo "Linking..."
		@${CC} ${CFLAGS} -o ${NAME} ${OBJS}
		@echo "Finished"

clean:
	@echo "Cleaning..."
	@${RM} $(OBJS)
	@echo "Finished"

fclean: clean
	@${RM} ${NAME}

re: fclean all

.PHONY: clean