##
## Makefile for philo in /home/kruszk_t/rendu/PSU_2014_philo
## 
## Made by Tony Kruszkewycz
## Login   <kruszk_t@epitech.net>
## 
## Started on  Mon Jun 22 14:51:03 2015 Tony Kruszkewycz
## Last update Tue Jun 23 10:45:49 2015 Tony Kruszkewycz
##

SRC		= src/main.c	\
		  src/philo.c

NAME		= philo

OBJ		= $(SRC:.c=.o)

CC		= gcc

RM		= rm -f

CFLAGS		+= -Wall -Wextra -ansi -pedantic
CFLAGS		+= -I./inc -D_DEFAULT_SOURCE

LDFLAGS		+= -lpthread

all:		$(NAME)

$(NAME):	$(OBJ)
		$(CC) -o $(NAME) $(OBJ) $(LDFLAGS)

clean:
		$(RM) $(OBJ)

fclean:		clean
		rm -f $(NAME)

re:		fclean all

.PHONY:		all clean fclean re
