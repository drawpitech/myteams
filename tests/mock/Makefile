##
## EPITECH PROJECT, 2024
## my_teams
## File description:
## Makefile
##

SRC := $(shell find . -name '*.c')
OBJ := $(SRC:.c=.o)
NAME := libmyteams.so

CFLAGS := -isystem ../../libs
LDFLAGS := -L ../../libs/myteams
LDLIBS := -lmyteams

.PHONY: all
all: $(NAME)

$(NAME): $(OBJ)
	$(CC) -shared -o $@ $^

.PHONY: clean
clean:
	$(RM) $(OBJ)

.PHONY: fclean
fclean: clean
	$(RM) $(NAME)

.PHONY: re
.NOTPARALLEL: re
re: fclean all
