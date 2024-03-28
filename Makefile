NAME = Philo

HEADERS = Philo.h

CFILES = srcs/main.c \
			srcs/utils.c \
			srcs/init.c \
			srcs/actions.c \
			srcs/threads_function.c \
			srcs/free.c

OFILES = $(CFILES:.c=.o)

CC = gcc
FLAGS = -Wall -Werror -Wextra
GFLAGS =

%.o: %.c $(HEADERS)
	$(CC) $(FLAGS) $(GFLAGS) -c -o $@ $<

all : $(NAME)
	@clear
	@echo "\033[0;32m***********************************************************"
	@echo "*                                                         *"
	@echo "*  Compilation successful!                                *"
	@echo "*                                                         *"
	@echo "*  Run './\033[0;33m$(NAME)\033[0;32m' with arguments: numbers_of_philo         *"
	@echo "*  time_to_die time_to_eat time_to_sleep (numers_of_meal) *"
	@echo "*                                                         *"
	@echo "***********************************************************\033[0m"

$(NAME) : $(OFILES)
	$(CC) $(OFILES) -o $(NAME)

gdb : GFLAGS += -g 
gdb : fclean all

clean :
	rm -rf $(OFILES)
	@clear
	@echo "\033[0;32mclean success"

fclean : clean
	rm -rf $(NAME)
	@clear
	@echo "\033[0;32mfclean success"

re : fclean all

.PHONY :
	all clean fclean re