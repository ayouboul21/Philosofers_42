SRC = philo_bonus.c utils_bonus.c simulation_bonus.c ft_atoi_bonus.c
OBJS = ${SRC:.c=.o}
CFLAGS = -Wall -Wextra -Werror
CC = cc
RM = rm -f
NAME = philo_bonus

%.o: %.c philo_bonus.h
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