CC = cc
CFLAGS = -Wall -Werror -Wextra
SRC = client.c utils.c
SRC2 = server.c utils.c
OBJ = $(SRC:.c=.o)
OBJ2 = $(SRC2:.c=.o)
NAME = client
NAME2 = server
RM = rm -f
all: $(NAME) $(NAME2)
$(NAME): $(OBJ) minitalk.h
	$(CC) $(CFLAGS) $(SRC) -o $(NAME)
$(NAME2): $(OBJ2) minitalk.h
	$(CC) $(CFLAGS) $(SRC2) -o $(NAME2)
clean:
	$(RM) $(OBJ) $(OBJ2)
fclean: clean
	$(RM) $(NAME) $(NAME2)
re: fclean all