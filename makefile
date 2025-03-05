CC = cc
CFLAGS = -Wall -Werror -Wextra
SRC = mandatory/client.c mandatory/utils.c
SRC2 = mandatory/server.c
OBJ = $(SRC:.c=.o)
OBJ2 = $(SRC2:.c=.o)
NAME = client
NAME2 = server
RM = rm -f
all: $(NAME) $(NAME2)
$(NAME): $(OBJ) mandatory/minitalk.h
	$(CC) $(CFLAGS) $(SRC) -o $(NAME)
$(NAME2): $(OBJ2) mandatory/minitalk.h
	$(CC) $(CFLAGS) $(SRC2) -o $(NAME2)
clean:
	$(RM) $(OBJ) $(OBJ2)
fclean: clean
	$(RM) $(NAME) $(NAME2)
re: fclean all